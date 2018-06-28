#include<bits/stdc++.h>
using namespace std;
void f(vector<int> &a,vector<int> &b,vector<int> &c)
{
    int n=(int)a.size();
    if(n==1)
    {
        c.push_back(a[0]*b[0]);
        c.push_back(0);
        return;
    }
    vector<int>al,ar,bl,br;
    for(int i=0;i<n/2;i++)
    {
        al.push_back(a[i]);
        bl.push_back(b[i]);
        ar.push_back(a[i+n/2]);
        br.push_back(b[i+n/2]);
    }
    vector<int> ans1,ans2;
    f(al,bl,ans1);
    f(ar,br,ans2);
    for(int i=0;i<n/2;i++)
    {
        al[i]+=ar[i];
        bl[i]+=br[i];
    }
    ar.clear();
    f(al,bl,ar);
    for(int i=0;i<n;i++)
        ar[i]-=(ans1[i]+ans2[i]);
    c.resize(n<<1);
    for(int i=0;i<n;i++)
    {
        c[i]+=ans1[i];
        c[i+n/2]+=ar[i];
        c[i+n]+=ans2[i];
    }
}
void multiply(vector<int> &a,vector<int> &b,vector<int> &c)
{
    int n=1;
    while(n<max((int)a.size(),(int)b.size()))
        n<<=1;
    vector<int>aa=a,bb=b;
    aa.resize(n);
    bb.resize(n);
    f(aa,bb,c);
}
int main()
{
    vector<int>a={1,2,1},b={1,1,0},c;
    multiply(a,b,c);
    for(auto i:c)
        cout<<i<<" ";
}