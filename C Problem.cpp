#include <bits/stdc++.h>
using namespace std;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t,n,m,x,y;
    cin>>t;
    while(t--){
        cin>>n>>m;
        vector<int> g(n+1),s(n+1),p(n+1),d(n+1),f(n+1),o;
        for(int i=1;i<n;i++)cin>>x>>y,g[x]++,g[y]++,s[x]^=y,s[y]^=x;
        for(int i=1;i<n;i++)
            for(x=i;g[x]==1&&x!=n;x=y)y=s[x],p[x]=y,o.push_back(x),g[x]=0,g[y]--,s[y]^=x;
        for(int k=o.size();k--;){
            int u=o[k];
            d[u]=d[p[u]]+1;
            f[u]=f[p[u]]|(u==1);
        }
        int r=d[1];
        while(m--)cin>>x,r=max(r,f[x]?0:d[x]+1);
        cout<<r<<'\n';
    }
}