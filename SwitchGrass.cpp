#include <queue>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <complex>
#include <fstream>
#include <cstring>
#include <string>
#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <unordered_map>
using namespace std;
using namespace __gnu_pbds;

//macros
typedef long long ll;
typedef complex<double> point;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector< vector<int> > vvi;
typedef tree<
pair<int,int>,
null_type,
less<pair<int,int> >,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;



#define FOR(k,a,b) for(int k=(a); k<=(b); ++k)
#define REP(k,a) for(int k=0; k<(a);++k)
#define SZ(a) int((a).size())
#define ALL(c) (c).begin(),(c).end()
#define PB push_back
#define MP make_pair
#define INF 99999999
#define MOD 1000000007
#define MAX 15383
#define ITERS 100
#define pi 3.1415926
#define _gcd __gcd
#define f first
#define s second

using namespace std;
#define EPS 1e-9
#define ERR -987654321
#define MAXN 2250005
class DSU{
	public:
		int size[200001];
		int parent[200001];
		void createSet(int n){
			for(int i=0; i < n; i++){
				size[i]=1;
				parent[i]=i;
			}
		}
		int findSet(int x){
			if(x!= parent[x]) parent[x] = findSet(parent[x]);
			return parent[x];
		}
		void mergeSet(int a, int b){
			int rep1 = findSet(a);
			int rep2 = findSet(b);
			int sz1 = size[rep1];
			int sz2 = size[rep2];
			if(sz1 > sz2){
				parent[rep2] = rep1;
				size[rep1] += size[rep2];
			}
			else{
				parent[rep1] = rep2;
				size[rep2] += size[rep1];
			}
		}
		bool cycleMerge(int a, int b){
			if(findSet(a)==findSet(b)){
				return true;
			}
			mergeSet(a,b);
			return false;
		}
};

int n,m,k,q;
vector<pair<int,int> > adj[200000];
vector<pair<int,pair<int,int> > > edges;
unordered_map<int,multiset<int> > local[200000];
multiset<int> global;
int par[200000];
int pdist[200000];
int color[200000];
bool ugly = true;
void dfs(int no, int p){
    par[no] = p;
    int cntr=0;
    REP(i,SZ(adj[no])){
        int to = adj[no][i].first;
        if(to==p) continue;
        cntr++;
        dfs(to,no);
        pdist[to]=adj[no][i].second;
        local[no][color[to]].insert(pdist[to]);
    }
    if(cntr>10) ugly = false;
    for(unordered_map<int,multiset<int> >::iterator it = local[no].begin(); it!=local[no].end(); ++it){
        if(it->first!=color[no]){
            global.insert(*it->second.begin());
        }
    }

}
ifstream fin("grass.in");
ofstream fout("grass.out");

void naivebs(){
    multiset<int> hammertime;
    REP(i,n){
        REP(j,SZ(adj[i])){
            int to = adj[i][j].first;
            if(to!=par[i] && color[to]!=color[i]){
                hammertime.insert(pdist[to]);
            }
        }
    }
    REP(query, q){
        int no,col;
        fin >> no >> col;
        no--; col--;
        if(color[no]!=col){
            REP(i,SZ(adj[no])){
                int to = adj[no][i].first;
                if(to==par[no]) continue;
                if(color[to]==color[no]){
                    hammertime.insert(pdist[to]);
                }
                else if(color[to]==col){
                    hammertime.erase(hammertime.find(pdist[to]));
                }
            }
            //parent
            if(par[no]!=-1){
                int pp = par[no];
                if(color[pp]==color[no]){
                    hammertime.insert(pdist[no]);
                }else if(color[pp]==col){
                    hammertime.erase(hammertime.find(pdist[no]));
                }
            }
            color[no] = col;
        }
        fout << *hammertime.begin() << endl;

    }
    fout.close();
    exit(0);
}
int main(){

    fin >> n >> m >> k >> q;
    //cin >> n >> m >> k >> q;

    REP(i,m){
        int a,b,l;
        fin >> a >> b>>l;
        //cin >> a >> b >> l;
        a--; b--;
        edges.PB(MP(l,MP(a,b)));
    }
    DSU dsu;
    dsu.createSet(n);
    sort(ALL(edges));
    int cnt = 0;
    REP(i,SZ(edges)){
        if(!dsu.cycleMerge(edges[i].second.first,edges[i].second.second)){
            adj[edges[i].second.first].PB(MP(edges[i].second.second,edges[i].first));
            adj[edges[i].second.second].PB(MP(edges[i].second.first,edges[i].first));
            cnt++;
            if(cnt==n-1) break;
        }
    }
    REP(i,n){
        fin >>color[i];
        //cin >> color[i];
        color[i]--;
    }
    //MST graph constructed

    dfs(0,-1);
    if(ugly){
        naivebs();
        return 0;
    }
    REP(query,q){
        int no,col;
        fin >> no >> col;

        no--; col--;
        if(col!=color[no]){
            //fix children
            multiset<int>* ms = &local[no][col];
            if(ms->size()>0){
                global.erase(global.find(*ms->begin()));
            }
            ms = &local[no][color[no]];
            if(ms->size()>0){
                global.insert(*ms->begin());
            }
            //fix parent
            if(par[no]!=-1){
                //color[no] to col
                //remove color[no]'s top

                int pp = par[no];
                ms = &local[pp][color[no]];
                if(color[pp]!=color[no]) global.erase(global.find(*ms->begin()));
                ms->erase(ms->find(pdist[no]));
                if(color[no] != color[pp] && ms->size()>0){
                    global.insert(*ms->begin());
                }
                ms = &local[pp][col];
                if(ms->size()>0 && color[pp]!=col){
                    global.erase(global.find(*ms->begin()));
                }
                ms->insert(pdist[no]);
                if(col!=color[pp]){
                    global.insert(*ms->begin());
                }

            }
        }
        color[no] = col;
        fout << *global.begin() << endl;
    }
    fout.close();
}
