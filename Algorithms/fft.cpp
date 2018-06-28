#include<bits/stdc++.h>
using namespace std;
void fft(vector<complex<long double>> &a,bool invert)
{
    int n=(int)a.size();
    for(int i=0;i<n;i++)
    {
        int reverse=0;
        for(int j=1;j<n;j<<=1)
        {
            if(i&j)
            reverse+=((n>>1)/j);
        }
        if(i<reverse)
            swap(a[i],a[reverse]);
    }
    for(int l=2;l<=n;l<<=1)
    {
        long double angle=(2*acos(-1)*(invert?-1:1))/l;
        complex<long double>w(cos(angle),sin(angle));
        for(int i=0;i<n;i+=l)
        {
            complex<long double>wi(1);
            for(int j=0;j<l/2;j++)
            {
                complex<long double>p=a[i+j],q=a[i+j+l/2]*wi;
                a[i+j]=p+q;
                a[i+j+l/2]=p-q;
                wi*=w;
            }
        }
    }
    if(invert)
    {
        for(int i=0;i<n;i++)
            a[i]/=n;
    }
}
void multiply(vector<int> &a,vector<int> &b,vector<int> &c)
{
    int n=1;
    while(n<max((int)a.size(),(int)b.size()))
        n<<=1;
    n<<=1;
    vector<complex<long double>>aa(a.begin(),a.end()),bb(b.begin(),b.end());
    aa.resize(n);
    bb.resize(n);
    fft(aa,0);
    fft(bb,0);
    for(int i=0;i<n;i++)
        aa[i]*=bb[i];
    fft(aa,1);
    c.resize(n);
    for(int i=0;i<n;i++)
        c[i]=(int)(aa[i].real()+0.5);
}
int main()
{
    vector<int>a={1,2,1},b={1,1,0},c;
    multiply(a,b,c);
    for(auto i:c)
        cout<<i<<" ";
}

