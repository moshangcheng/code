#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

bool WD;

int Power(int n, int p)
{
    int k = 1;
    if(p == 0) return 1;
    while( p > 0) {
        if(p & 1 == 1) k *= n;
        n *= n;
        p /= 2;
    }
    return k;
}

struct RTrie_node {
    int data, count;
    RTrie_node** branch;
    RTrie_node(int base);
    ~RTrie_node() { delete [] branch; }
};

class RTrie {
    private:
        int d, base;
        RTrie_node *root;
    public:
        RTrie(int base, int d): base(base), d(d) 
        { root = new RTrie_node(base); }
        RTrie_node* Root() { return root; }
        int insert(int vlu);
        void PreOrder (void(*Visit)(RTrie_node*), RTrie_node*);
};

void out(RTrie_node* u)
{   
    if(u->count > 1) {
        WD = 1;
        cout.fill('0');
        cout << setw(3) << u->data / 10000 << "-";
        cout << setw(4) << u->data % 10000 << " " << u->count << endl;   
    }
}

int main()
{
    string s;
    int i, j, vlu, nphone;
    int c[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6,
                 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0};
    while(cin >> nphone)  {
        WD = 0;
        RTrie Tree(10, 7);
        for(i = 0; i < nphone; i++) {
            cin >> s;
            for(vlu = j = 0; j < s.size(); j++)
            if(s[j] != '-') {
                if(s[j] <= 'Z' && s[j] >= 'A')
                vlu = vlu*10 + c[s[j] - 'A'];
                else vlu = vlu*10 + s[j] - '0';
            }
            Tree.insert(vlu);
        }
        Tree.PreOrder(out, Tree.Root());
        if(WD == 0) cout << "No duplicates.\n";
    }
    return 0;
}

RTrie_node::RTrie_node(int base)
{
    data = count = 0;
    branch = new RTrie_node*[base];
    for(int i = 0; i < base; i++) branch[i] = NULL;
}

int RTrie::insert(int vlu)
{
    if(root == NULL) root = new RTrie_node(base);
    RTrie_node* cnt = root;
    int m = Power(base, d), p;
    for(int i = 0; i < d; m /= base, i++) {
        p = vlu % m / (m/base);
        if(cnt->branch[p] == NULL) 
        cnt->branch[p] = new RTrie_node(base);
        cnt = cnt->branch[p];
    }        
    cnt->data = vlu;
    cnt->count++;
    return cnt->count;
}

void RTrie::PreOrder(void(*Visit)(RTrie_node* u), RTrie_node* v)
{
    if(v != NULL) {
        Visit(v);
        for(int i = 0; i < base; i++) PreOrder(Visit, v->branch[i]);
    }
}
