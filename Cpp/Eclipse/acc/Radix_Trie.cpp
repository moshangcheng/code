//采用深度确定的基数树能够在 O(d) 时间内找到 K-th 数
//插入时，先插入最高位
//若采用深度不确定的基数树，无法再 O(d) 时间内找到 K-th数
//插入时，先插入最低位 
#include <iostream>
using namespace std;

int Power(int n, int p)
{
    int k = 1;
    if(p == 0) return 1;
    while( p > 0) {
        if(p & 1 == 1) k *= n;
        n *= n;
        p /= 2;
    }
    return n * k;
}

class RTrie_node {
    RTrie_node(int base);
    ~RTrie_node() { delete [] branch; }
    int data, count;
    RTrie_node** branch;
};

RTrie_node::RTrie_node(int base)
{
    data = count = 0;
    branch = new RTrie_node*[base];
    memset(branch, 0, sizeof(*RTrie_node)*base);
}

class RTrie {
    private:
        int d, base;
        RTrie_node *root;
    public:
        RTrie(int d, int base): base(base), d(d), (*root)(base){}
        int Height() { return d; }
        int Base() { return base; }
        RTrie_node* Root() { return root; }
        int insert(int vlu); //返回插入vlu后与vlu相同的数量 
        int remove(int vlu); //返回删除vlu后与vlu相同的数量 
        int search(int vlu); //返回找到的vlu的数量 
        void InOrder  (void(*Visit)(RTrie_node*), RTrie_node*);
        void PreOrder (void(*Visit)(RTrie_node*), RTrie_node*);
        void PostOrder(void(*Visit)(RTrie_node*), RTrie_node*);
};

int RTrie::insert(int vlu)
{
    if(root == NULL) root = new RTrie_node;
    RTrie_node* cnt = root;
    int m = Power(base, d), p;
    for(int i = 0; i < d; m /= d, i++) {
        p = vlu % m / (m/d);
        if(cnt.branch[p] == NULL) cnt.branch[p] = new RTrie_node;
        cnt = cnt.branch[p];
    }        
    cnt->data = vlu;
    cnt->count++;
    return cnt->count;
}

int RTrie::remove(int vlu)
{
    RTrie_node* cnt = root;
    int m = Power(base, d), p;
    for(int i = 0; i < d; m /= d, i++) {
        p = vlu % m / (m/d);
        if(cnt.branch[p] == NULL) return -1;
        cnt = cnt.branch[p];
    } 
    if(cnt->count < 1) return -1;       
    cnt->count--;
    return cnt->count;
}

int RTrie::search(int vlu)
{
    RTrie_node* cnt = root;
    int m = Power(base, d), p;
    for(int i = 0; i < d; m /= d, i++) {
        p = vlu % m / (m/d);
        if(cnt.branch[p] == NULL) return 0;
        cnt = cnt.branch[p];
    } 
    if(cnt->count < 1) return 0;       
    return cnt->count;
}

void RTrie::InOrder(void(*Visit)(RTrie_node* u), RTrie_node* v)
{
}

void RTrie::PreOrder(void(*Visit)(RTrie_node* u), RTrie_node* v)
{
    if(v != NULL) {
        Visit(v);
        for(int i = 0; i < d; i++) PreOrder(Visit, v->branch[i]);
    }
}

void RTrie::PostOrder(void(*Visit)(RTrie_node* u), RTrie_node* v)
{
}
    
