

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

int n;
int prec[2][300][300];
vector<pair<int,int> > pts;
bool clock(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3){
    pair<int,int> v1 = MP(p1.first-p2.first,p1.second-p2.second);
    pair<int,int> v2 = MP(p3.first-p2.first,p3.second-p2.second);
    ll qq = (ll)v1.first*v2.second - (ll)v1.second*v2.first;
    assert(qq!=0);
    if(qq>0){
        return true; // is clockwise
    }else{
        return false;
    }
}
int ans[305];
int main(){
    ifstream fin("triangles.in");
    ofstream fout("triangles.out");
    fin >> n;
    REP(i,n){
        int x,y;
        fin >> x >> y;
        pts.PB(MP(x,y));
    }
    sort(ALL(pts));
    REP(i,n){
        for(int j=i+1;j<n;j++){
           double slope = (pts[j].second-pts[i].second) / (double(pts[j].first-pts[i].first));
           double b = pts[i].second - slope*pts[i].first;

           for(int k=0;k<n;k++){
                if(k==i || k==j) continue;
                if(pts[k].first>pts[i].first && pts[k].second < slope*pts[k].first+b){
                    if(pts[k].first<=pts[j].first) prec[0][i][j]++;
                    if(pts[k].first < pts[j].first) prec[1][i][j]++;
                }
           }
        }
    }

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            for(int k=j+1;k<n;k++){
                vector<pair<pair<int,int>,int> > pointo;
                pointo.PB(MP(pts[i],i));
                pointo.PB(MP(pts[j],j));
                pointo.PB(MP(pts[k],k));
                sort(ALL(pointo));
                int i1 = pointo[0].second;
                int i2 = pointo[1].second;
                int i3 = pointo[2].second;

                int quant=0;
                if(clock(pointo[0].first,pointo[1].first,pointo[2].first)){
                    //add 2 subtract 1
                    quant = prec[0][i1][i2] + prec[1][i2][i3] - prec[1][i1][i3];
                }else{
                    quant = prec[1][i1][i3] - prec[0][i1][i2] - prec[1][i2][i3] - 1;
                    if(pointo[1].first.first==pointo[2].first.first){
                        quant++;
                    }
                }

                ans[quant]++;
            }
        }
    }
    REP(i,n-2){
        fout << ans[i] << endl;
    }
    fout.close();

}
