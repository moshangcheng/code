#include <iostream>
using namespace std;
const int PointNum = 16;
const int SideNum  = 18;

struct Point{
  int x;
  int y;
  int F;
  int H;
  int D;
  int index;
  int pre;
};
struct Index{
  int from;
  int to;
};
struct Gather{
  struct Point  pnode;
  struct Gather *next;
};
struct Point P[PointNum] = {
  {1,1,0,0,0,0, -1}, {1,2,0,0,0,1 ,-2}, {1,3,0,0,0,2 ,-2}, {1,4,0,0,0,3 ,-2},
  {2,1,0,0,0,4 ,-2}, {2,2,0,0,0,5 ,-2}, {2,3,0,0,0,6 ,-2}, {2,4,0,0,0,7 ,-2},
  {3,1,0,0,0,8 ,-2}, {3,2,0,0,0,9 ,-2}, {3,3,0,0,0,10,-2}, {3,4,0,0,0,11,-2},
  {4,1,0,0,0,12,-2}, {4,2,0,0,0,13,-2}, {4,3,0,0,0,14,-2}, {4,4,0,0,0,15,-2}
};
struct Index In[SideNum] = {
  {0, 1 }, {1, 2 }, {2, 6 }, {3, 7 }, {4 , 5 }, {4 , 8}, {5 , 6}, {5 ,9 },
  {6, 7 }, {7, 11}, {8, 9 }, {8, 12}, {9 , 10}, {10,11}, {10,14}, {12,13},
  {13,14}, {14,15}
};
struct Gather *const OPEN   = new struct Gather;
struct Gather *const CLOSED = new struct Gather;
void AddClosed(struct Gather *des){
  des->next = CLOSED->next;
  CLOSED->next = des;
}
void PartInit_Point(void){
  for (int i=0; i<PointNum; i++){
    P[i].H = (4 - P[i].x) + (4 - P[i].y);
  }
  P[0].D = 0;
  P[0].F = P[0].H + P[0].D;
  OPEN->next = NULL;
  CLOSED->next = NULL;
}
void AddOpen(struct Point des){
  struct Gather *q = OPEN, *r = NULL, *temp = new struct Gather;
  temp->pnode = des;

  while ((q->next != NULL) && (q->next->pnode.F < des.F)){
    q = q->next;
  }
  r = q->next;
  temp->next = r;
  q->next = temp;
}
bool Goal(struct Gather *n){
  return (n->pnode.index == 15);
}
bool IsOpenEmpty(void){
  return (OPEN->next == NULL);
}
void Remove(struct Gather *des){
  struct  Gather *p = OPEN, *q = NULL;
  while ((p->next!=NULL) && (p->next->pnode.index!=des->pnode.index)){
    p = p->next;
  }
  if (p->next == NULL)
    cout<<"Error occurs when delete node from Open!"<<endl;
  else{
    q = p->next;
    p->next = q->next;
  }
}
struct Gather *First(void){
  return OPEN->next;
}
int InOPENorCLOSED(struct Point R){
  struct Gather *p = NULL;
  for (p = OPEN; p->next!=NULL; p = p->next){
    if (p->next->pnode.index == R.index) return 0;
  }
  for (p = CLOSED; p->next!=NULL ;p = p->next){
    if (p->next->pnode.index == R.index) return 1;
  }
  return 2;
}
void  Process(struct Point *A, struct Gather *curr){
  (*A).D++;
  (*A).F = (*A).D + (*A).H;
  if (InOPENorCLOSED(*A) == 2){
    AddOpen(*A);
    (*A).pre = curr->pnode.index;
  }
  if (InOPENorCLOSED(*A) == 0){
    struct    Gather *r = OPEN;
    while ((r->next != NULL) && (r->next->pnode.index != (*A).index)) {
      r = r->next;
    }
    if ((*A).F < r->next->pnode.F){
      r->next->pnode.F = (*A).F;
      (*A).pre = curr->pnode.index;
    }
  }
  if (InOPENorCLOSED(*A) == 1){
    struct    Gather *r = CLOSED;
    while ((r->next != NULL) && (r->next->pnode.index != (*A).index)){
        r = r->next;
    }
    if ((*A).F < r->next->pnode.F){
        (*A).pre = curr->pnode.index;
        AddOpen(*A);
    }
  }
}
void Expand(struct Gather *curr) {
  for (int i=0; i<SideNum; i++) {
    if (In[i].from == curr->pnode.index) {
      int    t = In[i].to;
      Process(&P[t], curr);
    }
    if (In[i].to == curr->pnode.index) {
      int t = In[i].from;
      Process(&P[t], curr);
    }
  }
}
void DrawMap(void){
cout<<"The labyrinth is : "<<endl<<endl;
cout<<"     _______________@"<<endl
  <<"          |    |    |"<<endl
  <<"     _____|    |____|"<<endl
  <<"     |    |    |    |"<<endl
  <<"     |    |____|    |"<<endl
  <<"     |    |    |    |"<<endl
  <<"    .|    |____|____|"<<endl
  <<endl;
}
int main(){
  DrawMap();
  PartInit_Point();
  struct Gather  *n = new struct Gather;
  AddOpen(P[0]);
LOOP:
  if (IsOpenEmpty()){
    cout<<"Fail for Open is Null!"<<endl;
    exit(0);
  }
  n = First();
  if (Goal(n)){
    cout<<"Succeed! The shortest route is: " <<endl<<endl;
    int  i = n->pnode.index;
    do  {
      cout<<"("<<P[i].x<<","<<P[i].y<<")"<<"   ";
      i = P[i].pre;
    }while (P[i].pre != -1);
    cout<<"("<<P[i].x<<", "<<P[i].y<<")"<<endl;
    goto FINISH;
  }
  Remove(n);
  AddClosed(n);
  Expand(n);
  goto    LOOP;
FINISH:
  system("pause");
  return 0;
}
