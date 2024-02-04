
#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<math.h>
#include<stack>
#include<queue>
#include<deque>
#define int long long int
#define ff first
#define ss second
#define md 998244353
#include<bitset>
const int MD=1e9+7;
const int MX =1e18;
const int MN=-1e18;
using namespace std;
//#include <ext/pb_ds/assoc_container.hpp> 
//#include <ext/pb_ds/tree_policy.hpp> 
//using namespace __gnu_pbds; 
//#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
struct node{
    int mn,mx,sum,lz_v;
    node()
    {mn=0;mx=0;sum=0;lz_v=0;}
};
typedef struct q_ans{int mn,mx,sum;}qn;
class ST{
    public:
    vector<node> tree;
    int _min(int a,int b){if(a<b)return a;return b;}
    int _max(int a,int b){if(a>b)return a;return b;}
    //tree  size initialization
    ST(int x){tree.resize(x);}
    //built the tree
    void creat(vector<int> &v,int pr,int lt,int rt)
    {
        if(lt==rt)
        {
            tree[pr].mn=v[lt],tree[pr].mx=v[lt],tree[pr].sum=v[lt];return;
        }
        int left_node=pr*2,mid=(lt+rt)/2,right_node=pr*2+1;
        creat(v,left_node,lt,mid);
        creat(v,right_node,mid+1,rt);
        tree[pr].mn=_min(tree[left_node].mn,tree[right_node].mn);
        tree[pr].mx=_max(tree[left_node].mx,tree[right_node].mx);
        tree[pr].sum=tree[left_node].sum+tree[right_node].sum;
    }
    //updaed on the tree
    void update(int pr,int trl,int trr,int upl,int upr,int valu)
    {
        if(trl>=upl&&trr<=upr){tree[pr].lz_v=tree[pr].lz_v+valu;return;}
        if(trl>upr||trr<upl)return;
        int mid=(trl+trr)/2,left_node=pr*2,right_node=pr*2+1;
        tree[left_node].lz_v=tree[pr].lz_v+tree[left_node].lz_v;
        tree[right_node].lz_v=tree[pr].lz_v+tree[right_node].lz_v;
        tree[pr].lz_v=0;
        update(left_node,trl,mid,upl,upr,valu);
        update(right_node,mid+1,trr,upl,upr,valu);
        tree[pr].sum=tree[left_node].sum+(tree[left_node].lz_v*(mid-trl+1))+tree[right_node].sum+tree[right_node].lz_v*(trr-mid);
        tree[pr].mn=_min(tree[left_node].mn+tree[left_node].lz_v,tree[right_node].mn+tree[right_node].lz_v);
        tree[pr].mx=_max(tree[left_node].mx+tree[left_node].lz_v,tree[right_node].mx+tree[right_node].lz_v);
    }
    // quary on tree
    qn quary(int pr,int trl,int trr,int ql,int qr,int cary)
    {
        if(trl>qr||trr<ql)
        {
            qn nd;nd.mn=MX,nd.mx=MN,nd.sum=0;return nd;
        }
        if(trl>=ql&&trr<=qr)
        {  qn nd;
            nd.mn=tree[pr].mn+cary+tree[pr].lz_v;
            nd.mx=tree[pr].mx+cary+tree[pr].lz_v;
            nd.sum=tree[pr].sum+(cary+tree[pr].lz_v)*(trr-trl+1);
            return nd;
        }
        int mid=(trl+trr)/2,left_node=pr*2,right_node=pr*2+1;
        cary+=tree[pr].lz_v;
        qn a,b,c;
        a=quary(left_node,trl,mid,ql,qr,cary);
        b=quary(right_node,mid+1,trr,ql,qr,cary);
        c.mn=_min(a.mn,b.mn),c.mx=_max(a.mx,b.mx),c.sum=a.sum+b.sum;return c;
    }
};
void sol()
{
    int n,m;
    cin>>n>>m;
   vector<pair<int,pair<int,int> > > v;
    v.push_back({MN,{1,1}});
    for(int i=1;i<=n;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        v.push_back({w,{x,y}});
    }
    sort(v.begin(),v.end());
 /* for(int i=0;i<n;i++)
    {
        cout<<v[i].ff<<" "<<v[i].ss.ff<<" "<<v[i].ss.ss<<"\n";
    }*/
    int rn=1e6;
    ST tr(4*(rn+5));
    int ans=1e9;
    int  j=0;
    struct q_ans u;
       for( int i=1;i<=n;i++)
        {
           u=tr.quary(1, 1,1e6+3,1,m-1,0);
          //  bool h=false;
           // if(u.mn>0)h=true;
            while (u.mn<= 0 and j < n)
            { j++;
                tr.update(1,1,1e6+3,v[j].ss.ff,v[j].ss.ss-1,1LL);
                u= tr.quary(1, 1,1e6+3,1,m-1,(int)0);
                //cout<<u.mn<<"\n";
            }
            // cout << i << " " << j << " " << mn << "\n";
            //j--;
          //  if(h==true)j
            if (u.mn > 0)ans = min(ans, v[j].first - v[i].first);
            tr.update(1, 1,1e6+3, v[i].ss.ff, v[i].ss.ss- 1, -1LL);
        }
        cout << ans << "\n";
  /* for(int i=1; ;i++)
    {
        int l,r,x;
        cin>>l>>r>>x;
        tr.update(1,1,rn,l,r-1,x);
        qn a=tr.quary(1,1,rn,1,m-1,0);
        cout<<a.mn<<" "<<a.mx<<" "<<a.sum<<"\n";
        
    }*/
    
 }
int32_t main() { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t=1;
    //cin>>t;
    while(t--)
    {
        sol();
    }
       return 0;
}
