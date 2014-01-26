/*CSuffixTree类有CreatTree,Show,Search,PrintNode四个方法，
主要讨论CreatTree及Search方法.

CreatTree：通过两层循环查找目标字符串的每一个前缀的所有后缀，
通过调用Search方法将结果分为四种。通过switch分别处理四种情况。

Search：搜索函数，通过遍历搜索参数传入的字符串。
将搜索结果通过point指针及其指向的节点的breakpoint变量，left字符串，
以及函数返回值影响CreatTree的处理方法。

************************************/

#include <vector>
#include <iostream>
#include <string>
#include <stack>
#include <deque>

using namespace std;

typedef struct node//声明节点的结构

{
       string strdata;//存储节点上的字符串
       vector<node*> Child;//存储该节点的字节点的地址
       int flag;//辅助标志位,用0和1表示该节点是否有子节点
       int breakpoint;//副主变量,当该节点需要分裂时,用于记录分裂点的位置
}*mynode;

class CSuffixTree

{
       private:
       string data,left;//data源字符串变量，在构造函数中初始化
                        //left用于记录每次搜索结束后，目标字符串中的剩余字符串
       public:
       mynode ST,point;//ST生成的后缀树的根节点
                        //point节点指针，搜索时指向搜索节点的父节点，搜索结束时根据搜索//结果指向要操作的节点

       CSuffixTree(string str);
       int Search(string str);
       void CreatTree();
       void Show(mynode ST);
       void PrintNode(mynode p, int c, vector<bool>& isend);
       ~CSuffixTree(void);
};


CSuffixTree::CSuffixTree(string str)
//构造函数，初始化data变量和ST,point指针并产个根节
//点的第一个子节点，ST的flag置1
{

              data=str;
              ST=(mynode) new node;
              point=(mynode) new node;
              point->strdata = data[0];
              point->flag = 0;
              ST->Child.push_back(point);
              ST->flag=1;
}

CSuffixTree::~CSuffixTree(void)//析构函数
{

}


int CSuffixTree::Search(string str)
//返回1则在指针point所指向的节点的strdata后追加
//left字符串
//返回2则生成point所指向的节点的子节点，子节点
//的strdata值为left字符串
//返回0则donothing
//返回－1则分裂节点将分裂点写入point指针所指向的
//节点的breakpoint，并将目标字符串的剩余字符串写
//入left
{
       stack<char> s;
       int i,n=0;
       mynode child;
       char target;
       point=ST;//初始搜索位置为根
       child=NULL;
       for (i=(str.length()-1);i>=0;i--)//将目标字符串str压栈
              s.push(str[i]);
       while(!s.empty())//直到搜索完str串
       {
              for (i=0;i<=(point->Child.size()-1);i++)//寻找point所指向的节点下与str首字母相同的子节点
                    if (point->Child[i]->strdata[0]==s.top())
                     {
                            child=point->Child[i];//child指针指向与str具有相同首字母的节点
                            break;
                     }
        if (child==NULL)//父节点point下没有首字母相同的子节点

              {                          //将str中剩余的字符串保存在left中

                     left.erase(left.begin(),left.end());
                     while(!s.empty())
                     {
                            left.insert(left.end(),s.top());
                            s.pop();
                     }
                     return (2);
              }
              target=s.top();//
              s.pop();
              if (1)
              {
                     for (i=0;i<=(child->strdata.length()-1);i++)// child节点下的每个字符与str中的字符顺序比较
                     {
                            if (child->strdata[i]==target)
                            {
                                   if (!s.empty())
                                   {
                                          target=s.top();
                                          s.pop();
                                          continue;
                                   }
                                   else return(0);//若str中的字符串先于strdata中的字符串完成比较，则

//说明该字符串已经包含在树中
                            }
                            else //比较中出现不同，需要分裂节点
                            {
                                   point=child;//point指向要分裂的节点
                                   left.erase(left.begin(),left.end());//将str中剩余的字符串写入left
                                   s.push(target);
                                   while(!s.empty())
                                   {
                                          left.insert(left.end(),s.top());
                                          s.pop();
                                   }
                                   point->breakpoint=i;//写入父节点point的分裂点
                                   return (-1);//分裂节点
                            }
                     }
                     point=child;//走出循环则进行下一个节点的搜索
                     if (!point->flag)//判断刚刚搜索的是否为叶节点，若是则停止搜索
                     {
                            left.erase(left.begin(),left.end());
                            s.push(target);
                            while(!s.empty())
                            {
                                   left.insert(left.end(),s.top());
                                   s.pop();
                            }
                            return (1);
                     }
                     s.push(target);
                     child=NULL;
              }
       }
       //字符串str搜索完成，仍没有到达叶节点，返回0
       return(0);
}

void CSuffixTree::CreatTree()
{
              int i,j,n,h,ic,jc;
              string temp;
              string tempuse;
              mynode cnode;
              for (i=1;i <= (data.length()-1);i++)//调用两层循环，产生目标字符串每一个前缀的所有后缀
                     for (j=0;j <= i;j++)
                     {
                            temp.erase(temp.begin(),temp.end());
                            ic=i;
                            jc=j;
                            for (;jc<=ic;jc++)
                                   temp.insert(temp.end(),data[jc]);
                            n=Search(temp);//调用Search函数搜索生成的字符串
                            switch (n)
                            {
                            case (-1)://分裂节点，父分裂点为point->breakpoint
                                   tempuse=point->strdata;
                                   cnode=(mynode) new node;
                                   if (point->Child.size() != 0)
                                          cnode->Child=point->Child;
                                   cnode->flag=point->flag;
                                   point->Child.erase(point->Child.begin(),point->Child.end());
                                   point->strdata.erase(point->strdata.begin(),point->strdata.end());
                                   for (h=0;h<(point->breakpoint);h++)

                                          point->strdata.insert(point->strdata.end(),tempuse[h]);
                                   for (h=(point->breakpoint);h<tempuse.length();h++)
                                          cnode->strdata.insert(cnode->strdata.end(),tempuse[h]);
                                   point->Child.push_back(cnode);
                                   cnode=(mynode) new node;
                                   cnode->strdata=left;
                                   cnode->flag=0;
                                   point->Child.push_back(cnode);
                                   point->flag=1;
                                   break;

                            case (0)://do nothing
                                   break;

                            case (1)://在叶节点point处追加left字符串
                                   point->strdata=point->strdata+left;
                                   break;

                            case (2)://在父节点point下添加子节点cnode
                                   cnode=(mynode) new node;
                                   cnode->strdata=left;
                                   cnode->flag=0;
                                   point->Child.push_back(cnode);
                                   point->flag=1;
                                   break;
                            }
                     }
       }

void CSuffixTree::Show(mynode m_pSTreeRoot)
{
       vector<bool> bIsEnd;
       bIsEnd.push_back(0);
       cout<<"Root"<<endl;
       for(int i=0;i<(int)m_pSTreeRoot->Child.size();i++)
       {
              if(i==(int)m_pSTreeRoot->Child.size()-1)
                     bIsEnd[0]=1;
              PrintNode(m_pSTreeRoot->Child[i],1,bIsEnd);
       }
       cout<<endl;
}

void CSuffixTree::PrintNode(mynode p, int c, vector<bool>& isend)
{

       for(int j=0;j<c;j++)
       {
              if(isend[j]==0)
                     if(j!=c-1)cout<<"│";
                            else cout<<"├";
              else
                     if(j!=c-1)cout<<"  ";
                            else cout<<"└";
              if(j!=c-1)cout<<"  ";
                     else cout<<"─";
       }

       cout<<" "<<p->strdata;
       //if(p->Child.size()==0)cout<<" ("<<p->nIndex<<")";
       cout<<endl;
       for(int i=0;i<(int)p->Child.size();i++)
       {
              if(isend.size()==c)isend.push_back(0);
              else isend[c]=0;
              if(i==(int)p->Child.size()-1)
                     if(isend.size()==c)isend.push_back(1);
                     else isend[c]=1;
              PrintNode(p->Child[i],c+1,isend);
       }
}


int main()
{
       string a;
       while(1) {
            cout<<"Please input a string:";
            cin>>a;//通过输入获得目标字符串a
            CSuffixTree mytree(a);//产生CsuffixTree类的实例mytree
            mytree.CreatTree();//调用CreatTree方法创建一棵后缀树
            mytree.Show(mytree.ST);//调用Show方法输出生成的后缀树
        }
       return 0;
}

