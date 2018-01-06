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
#include <climits>
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

//macros
typedef long long ll;
typedef complex<double> point;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector< vector<int> > vvi;




#define FOR(k,a,b) for(int k=(a); k<=(b); ++k)
#define REP(k,a) for(int k=0; k<(a);++k)
#define SZ(a) int((a).size())
#define ALL(c) (c).begin(),(c).end()
#define PB push_back
#define MP make_pair
#define INF 1000000001
#define INFLONG 1000000000000000000
#define MOD 1000000007
#define MAX 100
#define ITERS 100
#define MAXM 200000
#define MAXN 1000000
#define _gcd __gcd
#define eps 1e-7
#define PI 3.1415926535897932384626

struct TBIT{
    ll tr[1001][1001];
    int MAXO = 1001;
    void upd(int x, int y, ll v){
        x++; y++;
        while(x<MAXO){
            int y0 = y;
            while(y0<MAXO){
                tr[x][y0] += v;
                y0 += (y0 & -y0);
            }
            x += (x & -x);
        }
    }
    ll query(int x, int y){
        x++; y++;
        ll ans = 0;
        while(x>0){
            int y0 = y;
            while(y0>0){
                ans += tr[x][y0];
                y0 -= (y0 & -y0);
            }
            x -= (x & -x);
        }
        return ans;
    }
    void updRange(int x1, int y1, int x2, int y2, int v){
        upd(x1,y1,v);
        upd(x1,y2+1,-v);
        upd(x2+1,y1,-v);
        upd(x2+1,y2+1,v);
    }
};
int arr[1000][1000];
bool appears[1000001];
int minx[1000001];
int miny[1000001];
int maxx[1000001];
int maxy[1000001];
TBIT bit;
bool bad[1000001];
int main() {

    ifstream fin("art.in");
    ofstream fout("art.out");
    int n;
    fin >> n;
    REP(i,n*n+1){
        minx[i]=INF;
        miny[i]=INF;
        maxx[i]=-INF;
        maxy[i]=-INF;
    }
    REP(i,n){
        REP(j,n){
            fin >> arr[i][j];
            appears[arr[i][j]]=true;
            int col = arr[i][j];
            minx[col]=min(minx[col],j);
            maxx[col]=max(maxx[col],j);
            miny[col]=min(miny[col],i);
            maxy[col]=max(maxy[col],i);
        }
    }
    int cntappear = 0;
    for(int i = 1; i <= n*n;i++){
        if(appears[i]) cntappear++;
    }
    if(cntappear==1 && n!=1){
        fout << n*n-1 << endl;
        fout.close();
        fin.close();
        return 0;
    }
    int cnt = 0;
    for(int color = 1; color <=n*n; color++){
        if(!appears[color]){
            cnt++;
            continue;
        }
        //find bounding box
        int x1 = minx[color];
        int y1 = miny[color];
        int x2 = maxx[color];
        int y2 = maxy[color];
        bit.updRange(x1,y1,x2,y2,1);
    }
    REP(i,n){
        REP(j,n){
            int col = arr[i][j];
            if(bad[col]) continue;
            if(col==0) continue;
            int tims = bit.query(j,i);
            if(tims!=1) bad[col]=true;
        }
    }

    for(int col = 1; col <= n*n; col++){
        if(appears[col] && !bad[col]){
            cnt++;
        }
    }
    fout << cnt << endl;
    fout.close();
    fin.close();
    return 0;
}
