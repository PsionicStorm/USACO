#include <bits/stdc++.h>
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
#define _gcd __gcd
#define eps 1e-7
#define PI 3.1415926535897932384626

priority_queue<ll, vector<ll>, greater<ll> > addq, remq;
int main(){
    int n, x, y, z;
    ifstream fin("landscape.in");
    ofstream fout("landscape.out");
    fin >> n >> x >> y >> z;
    ll ans = 0;
    REP(i,n){
        int a,b;
        fin >> a >> b;
        if(a>b){
            while(a>b){
                ll mycost = y; //at worst, we can just remove
                //we can also undo some previous addition and use this to add to that instead
                if(!addq.empty() && addq.top()+(ll)i*z < mycost){
                    mycost =addq.top() + (ll)i*z;
                    addq.pop();
                }
                ans += mycost;
                remq.push(-mycost - i*z);
                a--;
            }
        }else{
            while(a<b){
                ll mycost = x;
                if(!remq.empty() && remq.top() + (ll)i*z < mycost){
                    mycost = remq.top() + (ll)i*z;
                    remq.pop();
                }
                ans += mycost;
                addq.push(-mycost - i*z);
                a++;
            }
        }
    }
    fout << ans << endl;
    fout.close();
    return 0;
}
