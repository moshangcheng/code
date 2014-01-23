#include <algorithm> //如果要使用算法函数，你必须要包含这个头文件。 
#include <numeric> // 包含accumulate（求和）函数的头文件 
#include <vector> 
#include <iostream> 
using namespace std; 

int testscore[] = {67, 56, 24, 78, 99, 87, 56}; 

//判断一个成绩是否通过了考试 
bool passed_test(int n) 
{ 
return (n >= 60); 
} 

// 判断一个成绩是否不及格 
bool failed_test(int n) 
{ 
return (n < 60); 
} 

int main(int argc, char* argv[]) 
{ 
int total; 
// 初始化向量，使之能够装入testscore数组中的元素 
vector <int> vecTestScore(testscore, 
testscore + sizeof(testscore) / sizeof(int)); 
vector <int>::iterator vi; 

// 排序并显示向量中的数据 
sort(vecTestScore.begin(), vecTestScore.end()); 
cout << "Sorted Test Scores:" << endl; 
for (vi=vecTestScore.begin(); vi != vecTestScore.end(); vi++) 
{ cout << *vi << ", "; } 
cout << endl; 

// 显示统计信息 

// min_element 返回一个 _iterator_ 类型的对象，该对象指向值最小的那个元素。 
//"*"运算符提取元素中的值。 
vi = min_element(vecTestScore.begin(), vecTestScore.end()); 
cout << "The lowest score was " << *vi << "." << endl; 

//与min_element类似，max_element是选出最大值。 
vi = max_element(vecTestScore.begin(), vecTestScore.end()); 
cout << "The highest score was " << *vi << "." << endl; 

// 使用声明函数（predicate function，指vecTestScore.begin()和vecTestScore.end()）来确定通过考试的人数。 
cout << count_if(vecTestScore.begin(), vecTestScore.end(), passed_test) << 
" out of " << vecTestScore.size() << 
" students passed the test" << endl; 

// 确定有多少人考试挂了 
cout << count_if(vecTestScore.begin(), 
vecTestScore.end(), failed_test) << 
" out of " << vecTestScore.size() << 
" students failed the test" << endl; 

//计算成绩总和 
total = accumulate(vecTestScore.begin(), 
vecTestScore.end(), 0); 
// 计算显示平均成绩 
cout << "Average score was " << 
(total / (int)(vecTestScore.size())) << endl; 
system("pause");
return 0; 
}
