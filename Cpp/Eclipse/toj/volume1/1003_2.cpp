#include <iostream>
using namespace std;

struct Order{
    int start;
    int dest;
    int num;
};

Order a[22];
int capcity[7];
int Cpt,NmCityB,NmOdrs,profit,prft;

bool bound(int n)
{
    int sum=0;
    for(int i=n;i<NmOdrs;i++) sum+=a[i].num*(a[i].dest-a[i].start);
    if(sum+prft<profit) return false;
    return true;
}

void compute(int m)
{
    if(m<NmOdrs){
        int i,j;      
        for(i=a[m].start;i<a[m].dest;i++) if(capcity[i]<a[m].num) break;
        if(i==a[m].dest){
            for(j=a[m].start;j<i;j++) 
            capcity[j]-=a[m].num;
            prft+=a[m].num*(a[m].dest-a[m].start);
            compute(m+1);
            for(j=a[m].start;j<i;j++)
            capcity[j]+=a[m].num;
            prft-=a[m].num*(a[m].dest-a[m].start);
        }
        if(bound(m+1)) compute(m+1);
    }
    else if(prft>profit) profit=prft;
}    
    
int main()
{
    cin>>Cpt>>NmCityB>>NmOdrs;
    while(Cpt!=0||NmCityB!=0||NmOdrs!=0){
        prft=profit=0;
        if(NmOdrs==0) cout<<profit<<endl;
        else{
            for(int i=0;i<NmCityB;i++) capcity[i]=Cpt;
            for(int i=0;i<NmOdrs;i++) 
            cin>>a[i].start>>a[i].dest>>a[i].num;
            compute(0);
            cout<<profit<<endl;
        }
        cin>>Cpt>>NmCityB>>NmOdrs;
    }
    return 0;
}

