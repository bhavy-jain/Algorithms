#include<bits/stdc++.h>
using namespace std;
#define X real()
#define Y imag()
complex<int>g={0,0};
bool cmp(complex<int>a,complex<int>b)
{
    int cross=(conj(a-g)*(b-g)).Y;
    if(cross==0)
        return a.Y<b.Y;
    return cross>0;
}
void convex_hull(vector<pair<int,int>>&p,vector<pair<int,int>>&hull)
{
    int n=(int)p.size(),idx=0;
    vector<complex<int>>v;
    for(auto i:p)
    {
        v.push_back({0,0});
        v.back().real(i.first);
        v.back().imag(i.second);
    }
    int ans=0;
    for(int i=1;i<n-1;i++)
    {
        int cross=(conj(v[i]-v[0])*(v[i+1]-v[0])).Y;
        if(cross)
        {
            ans=1;
            break;
        }   
    }
    if(ans==0)
    {
        hull.push_back({-1,-1});
        return;
    }
    for(int i=1;i<n;i++)
    {
        if(v[i].Y<v[idx].Y)
            idx=i;
        else if(v[i].Y==v[idx].Y&&v[i].X<v[idx].X)
            idx=i;
    }
    swap(v[0],v[idx]);
    g=v[0];
    sort(v.begin()+1,v.end(),cmp);
    vector<complex<int>>s;
    s.push_back(v[0]);
    s.push_back(v[1]);
    s.push_back(v[2]);
    for(int i=3;i<n;i++)
    {
        while((conj(s[(int)s.size()-1]-s[(int)s.size()-2])*(v[i]-s[(int)s.size()-1])).Y<=0)
            s.pop_back();
        s.push_back(v[i]);
    }
    for(auto i:s)
        hull.push_back({i.X,i.Y});
}
int main()
{
    vector<pair<int,int>>a={{1,0},{2,0},{2,2},{0,4},{5,5}},b;
    convex_hull(a,b);
    for(auto i:b)
        cout<<i.first<<" "<<i.second<<"\n";
}