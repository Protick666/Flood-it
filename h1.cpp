#include <bits/stdc++.h>
using namespace std;
#define  ll  long long int
#define max3(a, b, c) max(a, b) > max(b, c) ? max(a, b) : max(b, c)
#define min3(a, b, c) min(a, b) < min(b, c) ? min(a, b) : min(b, c)
#define digit(c) (c - '0')
#define cc(c) (c - 'a')
#define pb push_back
#define mp make_pair
#define fi first+
#define se second
#define flag(i) cout<<"case "<<i<<endl;


//#define maxx 10000000000000000
#define all(X) X.begin(), X.end()
#define loop(i,n) for ( i=0; i<ll(n); i++ )
#define fr(i,x,y) for ( i=x; i<=y; i++ )
#define fur(i,x,y) for ( i=x; i>=y; i-- )
#define out(x) printf("%I64d ",x);

#define in(x) scanf("%lld",&x);
#define in2(x,y) scanf("%lld%lld",&x,&y);


#define REP1(i,a,b) for ( ll i=(a); i<=ll(b); i++ )
#define FOR(it,c) for ( auto it=(c).begin(); it!=(c).end(); it++ )
#define mp make_pair
#define ex  exit(0)
#define LSOne(S) (S & (-S))
#define INF INT_MAX //Infinity
#define cont continue
#define nl cout<<endl
#define modd 1000000007
#define jj(x,y,v) v[x].pb(y);v[y].pb(x)
ll a[30][30];
ll temp[30][30];
ll col[16];
ll n;
ll nb[2000][2000];
ll vis[100][100];
ll viss[2000];

ll co1[]={0,0,1,-1};
ll co2[]={1,-1,0,0};
vector<ll> v[2000];
class UF    {
    ll *id, cnt, *sz;
public:
	// Create an empty union find data structure with N isolated sets.
    UF(ll N)   {
        cnt = N;
	id = new ll[N+1];
	sz = new ll[N+1];
        for(ll i=1; i<=N; i++)	{
            id[i] = i;
	    sz[i] = 1;
	}
    }
    ~UF()	{
	delete [] id;
	delete [] sz;
    }
	// Return the id of component corresponding to object p.
    ll find(ll p)	{
       ll root = p;
        while (root != id[root])
            root = id[root];
        while (p != root) {
           ll newp = id[p];
            id[p] = root;
            p = newp;
        }
        return root;
    }
	// Replace sets containing x and y with their union.
    void merge(ll x, ll y)	{
       ll i = find(x);
        ll j = find(y);
        if (i == j) return;

		// make smaller root point to larger one
        if   (sz[i] < sz[j])	{
		id[i] = j;
		sz[j] += sz[i];
	} else	{
		id[j] = i;
		sz[i] += sz[j];
	}
        cnt--;
    }
	// Are objects x and y in the same set?
    bool connected(ll x, ll y)    {
        return find(x) == find(y);
    }
	// Return the number of disjoint sets.
    ll count() {
        return cnt;
    }
};
ll ckval(ll x,ll y)
{
    if(x>n || x<1 || y>n || y<1)
        return 0;
    return 1;
}
void clr()
{
    for(ll i=0;i<=n;i++)
    {
        for(ll j=0;j<=n;j++)
            vis[i][j]=0;
    }
}
void proc(ll x,ll y)
{
    nb[x][y]=1;
    nb[y][x]=1;
    v[x].pb(y);
    v[y].pb(x);
}
void dfs1(ll x,ll y)
{
    ll i;
    vis[x][y]=1;
    ll tx,ty;
    fr(i,0,3)
    {
       tx=x+co1[i];
       ty=co2[i]+y;
       if(ckval(tx,ty)==0)
            cont;
       if(a[tx][ty]!=a[x][y])
         col[a[tx][ty]]=1;
       else
       {
           if(vis[tx][ty]==0)
              dfs1(tx,ty);
       }
    }
}

ll col_ck(){

   ll i,j;
   clr();
   fr(i,0,14)
     col[i]=-1;

   dfs1(1,1);
   ll sum=0;
   fr(i,1,n)
   {
       if(col[i]==1)
         sum++;

   }
   return sum;

}

void dfs2(ll x,ll y,ll c)
{
    ll i;
    vis[x][y]=1;
    temp[x][y]=c;
    ll tx,ty;
    fr(i,0,3)
    {
       tx=x+co1[i];
       ty=co2[i]+y;
       if(ckval(tx,ty)==0)
            cont;
       if(a[tx][ty]!=a[x][y])
         cont;
       else
       {
           if(vis[tx][ty]==0)
              dfs2(tx,ty,c);
       }
    }
}
void init(UF* p,ll x,ll y)
{
    ll i;
    vis[x][y]=1;
    //temp[x][y]=c;
    ll tx,ty;
    fr(i,0,3)
    {
       tx=x+co1[i];
       ty=co2[i]+y;
       if(ckval(tx,ty)==0)
            cont;
       if(temp[tx][ty]!=temp[x][y])
         cont;
       else
       {
           if(vis[tx][ty]==0)
              {
                  p->merge(x*100+y,tx*100+ty);

                  init(p,tx,ty);

              }
       }
    }
}
void finish(UF* p,ll x,ll y)
{
    ll i;
    vis[x][y]=1;
    ll tx,ty;
    fr(i,0,3)
    {
       tx=x+co1[i];
       ty=co2[i]+y;
       if(ckval(tx,ty)==0)
            cont;
       if(temp[tx][ty]!=temp[x][y])
         {
             ll source=x*100+y;
             ll dest=tx*100+ty;
             source=p->find(source);
             dest=p->find(dest);
             if(nb[source][dest]==0)
             {
                proc(source,dest);
             }
         }


        if(vis[tx][ty]==0)
              finish(p,tx,ty);
    }
}
ll ckproper()
{
  UF pa(2000);
  ll i,j;
  clr();
   for(i=1;i<=n;i++)
   {
       for(j=1;j<=n;j++)
       {
           if(vis[i][j]==0)
                init(&pa,i,j);

       }
   }
   clr();
    ll x,y;
    fr(i,1,n)
      fr(j,1,n)
        fr(x,1,n)
            fr(y,1,n)
                  nb[i*100+j][x*100+y]=0;
    fr(i,1,n){
      fr(j,1,n)
        {viss[i*100+j]=0;
         v[i*100+j].clear();
        }
        }


   finish(&pa,1,1);
   ll ans=0;
   queue<pair<ll,ll> > q;
   pair<ll,ll> t;
   t=mp(pa.find(101),0);
   q.push(t);
   viss[101]=1;
   while(q.size()!=0)
   {
       t=q.front();
       q.pop();
       ll k=t.first;
       viss[k]=1;
       ll val=t.second;

       for(i=0;i<v[k].size();i++)
       {
           ll x=v[k][i];
           if(viss[x]==1)
            cont;
           t=mp(x,val+1);
           ans=max(ans,val+1);
           q.push(t);
       }
   }

   return ans;
}
ll ck(ll x)
{
    ll i,j;
   clr();
   fr(i,0,n)
   {
       fr(j,0,n)
          temp[i][j]=a[i][j];
   }
   dfs2(1,1,x);
   return ckproper();
}

void chng(ll x,ll y,ll ans)
{
    ll i;
    vis[x][y]=1;
    //temp[x][y]=c;
    ll tx,ty;
    fr(i,0,3)
    {
       tx=x+co1[i];
       ty=co2[i]+y;
       if(ckval(tx,ty)==0)
            cont;
       if(a[tx][ty]!=a[x][y])
         cont;
       else
       {
           if(vis[tx][ty]==0)
              chng(tx,ty,ans);
       }
    }
    a[x][y]=ans;
}
void pro()
{
    ll i,j;

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            cout<<a[i][j]<<" ";

        cout<<endl;
    }
        cout<<endl<<endl;

}

int main()
{

    ll i,j,k,l,m,x,y,sum,ans,c,turn,t;
    //cin>>t;
    while(1)
    {
        turn=0;
        cin>>n;
        if(n==0)
            break;
        fr(i,1,n)
        {
            fr(j,1,n)
                cin>>a[i][j];
        }
        cout<<endl;
        pro();

        while(1)
        {
            ll tot=col_ck();//checks neighboring different colors
            if(tot==0)
            {
                //pro();
                break;// all covered
            }
            sum=100000000000;
            //cout<<tot<<endl;
            //cin>>tot;

            for(i=1; i<=14; i++)
            {
                if(col[i]!=1)
                    cont;
                x=i;
                tot=ck(x);
                if(tot<sum)
                {
                    ans=x;
                    sum=tot;
                }
            }
            clr();
            chng(1,1,ans);
            turn++;
            cout<<"choosen color is "<<a[1][1]<<endl;
            pro();
        }
        cout<<"total turns needed  "<<turn<<endl<<endl;
    }

    cin>>n;
}
