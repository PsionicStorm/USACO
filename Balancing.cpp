
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
#define INF 99999999
#define MOD 1000000007
#define MAX 15383
#define ITERS 100
#define pi 3.1415926
#define MAXN 50000
#define _gcd __gcd
#define f first
#define s second

using namespace std;
#define EPS 1e-9
#define ERR -987654321

struct bit{
	int tr[1000001];
	void upd(int y, int v){
		while(y<1000001){
			tr[y]+=v;
			y+=y&-y;
		}
	}
	int query(int y){
		int ret = 0;
		while(y>0){
			ret+=tr[y];
			y-=y&-y;
		}
		return ret;
	}
};
bit lef, righ;
vector<pair<int,int> > pts;
int n;
int main(){
	ifstream fin("balancing.in");
	ofstream fout("balancing.out");
	fin >> n;
	REP(i,n){
		int x,y;
		fin >> x >> y;
		pts.PB(MP(x,y));
		righ.upd(y,1);
	}
	sort(ALL(pts));
	int ptr = 0;
	int inleft = 0;
	int ret = n;
	while(ptr<n){
		int x0 = pts[ptr].first;
		int old = ptr;
		while(ptr<n && pts[ptr].first==x0) ptr++;
		ptr--;
		for(int itr = old; itr <= ptr; itr++){
			righ.upd(pts[itr].second,-1);
			lef.upd(pts[itr].second,1);
			inleft++;
		}

		int lo = 0;
		int hi = 1000000;
		while(lo<hi){
			int mid = (lo+hi)/2;
			//by sweeping upward
			//number in top is decreasing
			//number in bottom is increasing
			//max of top 2 is decreasing
			//max of bottom 2 is increasing
			int botleft = lef.query(mid);
			int topleft = inleft - botleft;
			int botright = righ.query(mid);
			int topright = (n-inleft)-botright;

			if(max(topleft, topright) > max(botleft, botright)){
				//move fence up
				lo = mid+1;
			}else{
				hi = mid;
			}
		}
		int botleft = lef.query(lo);
		int botright = righ.query(lo);
		ret = min(ret, max(max(botleft,inleft-botleft),max(botright,n-inleft-botright)));
		ptr++;
	}
	fout << ret << endl;
	fout.close();
}
