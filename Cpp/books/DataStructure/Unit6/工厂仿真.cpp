//工厂仿真问题   一间工厂有m台机器，工厂所执行的每项任务
//都有若干道工序组成，一台机器完成一道工序，不同的机器完成不同的工序，
//一旦一台机器开始处理一道工序，它就会连续处理到该工序完成为止。

//机器的转换时间在程序开始时和结束时均不必计算 。

//TotalWait是指所有任务在等待机器 p 的时间，而不是机器 p等任务的时间
//（即机器 p 的空闲时间） ，每个任务花费的等待时间之和
//与花费在所有机器上的等待时间之和相等 。

//TotalWait反映了 p 的忙碌程度

#include <iostream>
#include <fstream>
using namespace std;
#include "LinkedQueue.h"

class Task {
private:
	friend class Job;
	friend bool MoveToNextMachine(Job*);
	long time;
	int machine;
};

class Job {
public:
	friend bool MoveToNextMachine(Job*);
	friend Job* ChangeState(int);
	friend void Simulate();
	friend class Machine;
	Job(long id) {
		ID = id;
		Length = ArriveTime = 0;
	}
	void AddTask(int p, long t) {
		Task x;
		x.machine = p;
		x.time = t;
		TaskQ.Add(x);
	}
	long DeleteTask() {
		Task x;
		TaskQ.Delete(x);
		Length += x.time;
		return x.time;
	}
private:
	LinkedQueue<Task> TaskQ;
	long Length;
	long ArriveTime;//到达当当前队列的时间
	long ID;
};

class Machine {
public:
	friend Job* ChangeState(int);
	Machine() {
		Active = 0;
		TotalWait = NumTasks = 0;
	}
	bool IsEmpty() {
		return JobQ.IsEmpty();
	}
	void AddJob(Job* x) {
		JobQ.Add(x);
	}
	void SetChange(long w) {
		ChangeTime = w;
	}
	void Stats(long& tw, long& nt, long& ft) {
		tw = TotalWait;
		nt = NumTasks;
		ft = finishtime;
	}
private:
	LinkedQueue<Job*> JobQ;//等待队列
	long ChangeTime;//机器转换时间
	long TotalWait;//机器总的等待时间
	long finishtime;//机器的完成时间
	long NumTasks;//所处理的工序数
	Job* Active;//指向当前任务的指针
};

class EventList {
public:
	EventList(int, long);
	~EventList() {
		delete[] FinishTime;
	}
	void NextEvent(int& p, long& t);
	long NextEvent(int p) {
		return FinishTime[p];
	}
	void SetFinishTime(int p, long t) {
		FinishTime[p] = t;
	}
private:
	long* FinishTime;//完成时间数组
	int NumMachines;//机器总数
};

EventList::EventList(int m, long BigT) {
	FinishTime = new long[m + 1];
	NumMachines = m;
	for (int i = 1; i <= m; i++)
		FinishTime[i] = BigT;
}

void EventList::NextEvent(int& p, long& t) {
	p = 1;
	t = FinishTime[1];
	for (int i = 2; i <= NumMachines; i++)
		if (FinishTime[i] < t) {
			p = i;
			t = FinishTime[i];
		}
}

long Now = 0; //当前时间
int m; //机器数
long n; //任务数
long LargeTime = 10000; //空闲时间机器的完成时间
EventList* EL; //指向事件表的指针
Machine* M; // 机器数组

void InputData() {
	ifstream in("in.txt");
	cout << "Enter the number of machines and jobs\n";
	in >> m >> n;
	EL = new EventList(m, LargeTime);
	M = new Machine[m + 1];

	cout << "Enter change-over times for machines\n";
	for (int j = 1; j <= m; j++) {
		long ct;
		in >> ct;
		M[j].SetChange(ct);
	}
	Job* J;
	for (int i = 1; i <= n; i++) {
		cout << "Enter number of tasks for job " << i << endl;
		int tasks, first;
		in >> tasks;
		J = new Job(i);
		cout << "Enter the tasks(machine,time)" << " in process order\n";
		for (int j = 1; j <= tasks; j++) {
			int p;
			long tt;
			in >> p >> tt;
			if (j == 1)
				first = p;
			J->AddTask(p, tt);
		}
		M[first].AddJob(J);
	}
}

void StartShop() {
	for (int p = 1; p <= m; p++)
		ChangeState(p);//可惜是串行的，不能模拟 m 台
	//机器同时运行
}

Job* ChangeState(int p) {
	Job* LastJob;
	if (!M[p].Active) {//空闲或转换状态
		LastJob = 0;
		if (M[p].JobQ.IsEmpty()) //没有处于等待状态的任务 ，机器进入
			//等待状态 ，M[p].Active=0，
			// FinishTime[p]=LargeTime
			EL->SetFinishTime(p, LargeTime);
		else {
			M[p].JobQ.Delete(M[p].Active);//机器 p 上运行的下一个任务
			M[p].TotalWait += Now - M[p].Active->ArriveTime;
			M[p].NumTasks++;
			long t = M[p].Active->DeleteTask();//运行在机器 p 上的任务
			//的当前工序结束
			EL->SetFinishTime(p, Now + t);//重设机器 p 的结束时间
		}
	} else {//M[p]上的工序刚刚完成，处于转换状态中 ，M[p].Acitive=0,
		//FinishTime[p]=M[p].ChangeTime,不是LargeTime
		LastJob = M[p].Active;
		M[p].Active = 0;
		EL->SetFinishTime(p, Now + M[p].ChangeTime);//重设 p 的结束时间
		M[p].finishtime = Now;
	}
	return LastJob;
}

void Simulate() {
	int p;
	long t;
	while (n) {
		EL->NextEvent(p, t);//下一个事件发生的机器 p 和时间 t
		Now = t;
		Job* J = ChangeState(p);//J 为机器 p 上运行的任务
		if (J && !MoveToNextMachine(J))
			n--;
	}
}

bool MoveToNextMachine(Job* J) {
	if (J->TaskQ.IsEmpty()) {
		cout << "Job " << J->ID << " has completed at " << Now
				<< " Total wait was " << (Now - J->Length) << endl;
		return false;
	} else {
		int p = J->TaskQ.First().machine;//任务 J 的当前工序
		M[p].AddJob(J);
		J->ArriveTime = Now;//任务 J 当前任务的到达时间
		if (EL->NextEvent(p) == LargeTime)//机器为空闲
			ChangeState(p);
		return true;
	}
}

void OutputState() {
	cout << "Finish time= " << Now << endl;
	long TotalWait, NumTasks, finishtime;
	for (int p = 1; p <= m; p++) {
		M[p].Stats(TotalWait, NumTasks, finishtime);
		cout << "Machine " << p << " completed " << NumTasks
				<< " tasks at time " << finishtime << endl;
		cout << "The Total wait time was " << TotalWait;
		cout << endl << endl;
	}
}

int main() {
	InputData(); //获取机器数据和任务数据
	StartShop(); //启动
	Simulate(); //仿真
	OutputState(); //输出机器等待时间
	system("pause");
	return 0;
}
