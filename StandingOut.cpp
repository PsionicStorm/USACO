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

pair<vector<int>,vector<int> > buildSA(string s){
    vector<int> SAIdx[18];
    REP(i,18){
        REP(j,s.length()) SAIdx[i].PB(0);
    }

    REP(i,s.length()){
        SAIdx[0][i] = s[i]-'a';
    }
    int order = 1;
    int fini = -1;
    int i = 1;
    while (order < s.length()){
        fini = i;
        vector<pair<pair<int,int>,int> > srto;
        for(int j = 0; j < s.length(); j++){
            if(j+order< s.length()) srto.PB(MP(MP(SAIdx[i-1][j],SAIdx[i-1][j+order]),j));
            else srto.PB(MP(MP(SAIdx[i-1][j],-1),j));
        }
        sort(ALL(srto));
        for(int j=0; j < s.length(); j++){
            if(j==0) SAIdx[i][srto[j].second] = 0;
            else if(srto[j].first.first==srto[j-1].first.first && srto[j].first.second==srto[j-1].first.second){
                SAIdx[i][srto[j].second] = SAIdx[i][srto[j-1].second];
            }else{
                SAIdx[i][srto[j].second] = SAIdx[i][srto[j-1].second] + 1;
            }
        }
        order*=2;
        i++;
    }
    vi sa(s.length());
    REP(i,s.length()){
        sa[SAIdx[fini][i]] = i;
    }
    vi lcp(s.length());
    int ptr = 0;
    //implement kasai's algo
    REP(i,s.length()){
        if(SAIdx[fini][i]==s.length() - 1){
            ptr = 0; continue;
        }
        int j = sa[SAIdx[fini][i]+1];
        while(i+ptr<s.length() && j+ptr<s.length() && s[i+ptr]==s[j+ptr]) ptr++;
        lcp[SAIdx[fini][i]]=ptr;

        if(ptr>0) ptr--;
    }
    return MP(sa,lcp);
}
vector<string> words;
vi megasa;
int rev[130005];
vi megalcp;
int type[130005];
int pos[130005];

int lst[130005];
multiset<pair<int,int> > manager;
int L[130005];
int R[130005];

ll ans[130005];

int seg[524291];
void build(int no, int b, int e){
    //cout << no << endl;
    if(b==e){
        seg[no]=megalcp[b];
    }else{
        int mid = (b+e)/2;
        build(2*no,b,mid), build(2*no+1,mid+1,e), seg[no]=min(seg[2*no],seg[2*no+1]);
    }
}
int query(int no, int b, int e, int l, int r){
    if(b>r || e<l) return 100000000;
    if(l<=b && e<=r) return seg[no];
    int mid = (b+e)/2;
    return min(query(2*no,b,mid,l,r),query(2*no+1,mid+1,e,l,r));
}
int lcpquery(int i, int j){
    assert(i!=j);
    int ri = rev[i];
    int rj = rev[j];
    if(ri>rj) swap(ri,rj);
    return query(1,0,SZ(megalcp)-1,ri,rj-1);
}
int sL[130005];
int main(){
    ifstream fin("standingout.in");
    ofstream fout("standingout.out");
    int n;
    fin >> n;
    string mega = "";
    REP(i,n){
        string nxt;
        fin >> nxt;
        words.PB(nxt);
        for(int j = 0; j < nxt.length(); j++){
            type[mega.length()+j]=i;
            pos[mega.length()+j]=j;
        }
        if(i==n-1) mega=mega+nxt;
        else{
            mega = mega+nxt+"$";
            type[mega.length()-1]=-1;
            pos[mega.length()-1]=-1;
        }
    }
    pair<vi,vi> pp = buildSA(mega);
    //cout << SZ(pp.second)<<endl;
    REP(i,SZ(pp.first)) megasa.PB(pp.first[i]);
    REP(i,SZ(pp.second)) megalcp.PB(pp.second[i]);
    //cout << megalcp.size() << endl;
    //megasa=pp.first, megalcp=pp.second;
    REP(i,SZ(megasa)){
        rev[megasa[i]]=i;
    }
    //REP(i,SZ(megalcp)) cout << i << ": " << megalcp[i] << endl;
    //if(n>=1000) return 0;
    //cout << "HI " << SZ(megalcp) << endl;
    build(1,0,SZ(megalcp)-1);
    //cout << "HI"<<endl;
    REP(i,130005){
        lst[i]=-1;
        L[i]=-1;
        R[i]=-1;
        sL[i]=-1;
    }
    for(int i = megasa.size()-1;i>=0;i--){
        int num = type[megasa[i]];
        if(num==-1) continue;
        if(lst[num]!=-1){
            manager.erase(manager.find(MP(lst[num],num)));
        }
        if(manager.size()>0){
            multiset<pair<int,int> >::iterator it = manager.begin();
            //cout << "HEH " << i << " " << it->first << " " << it->second << endl;
            R[i] = it->first;
        }else{
            R[i] = -1;
        }

        lst[num] = i;
        //cout << i << " pushed " << num << " " << i << endl;
        manager.insert(MP(i,num));
    }
    manager.clear();
    REP(i,130005) lst[i]=-1;
    for(int i=0;i < megasa.size(); i++){
        int num = type[megasa[i]];
        if(num==-1) continue;
        if(lst[num]!=-1){
            sL[i] = lst[num];
            manager.erase(manager.find(MP(lst[num],num)));
        }
        if(SZ(manager)>0){
            multiset<pair<int,int> >::iterator it = --manager.end();
            L[i] = it->first;
        }else{
            L[i] = -1;
        }

        lst[num] = i;
        manager.insert(MP(i,num));
    }
   // REP(i,megasa.size()){
        //cout << i << " " << mega.substr(megasa[i],1000) << " " << type[megasa[i]] << " " << L[i] << " " << R[i] << endl;
    //}
    REP(i,megasa.size()){
        if(type[megasa[i]]==-1) continue;
        int q1 = 0, q2 = 0;
        if(L[i]!=-1){
            q1 = lcpquery(megasa[L[i]],megasa[i]);
        }
        if(R[i]!=-1){
            q2 = lcpquery(megasa[i],megasa[R[i]]);
        }
        int q3=0;

        if(sL[i]!=-1){
            q3 = lcpquery(megasa[sL[i]],megasa[i]);
        }
        //cout << i << " " << q1 << " " << q2 << " " << q3 << " " << words[type[megasa[i]]] << " " << pos[megasa[i]] << endl;
        //cout << "HELLO " << (int)words[type[megasa[i]]].length() - pos[megasa[i]] - max(max(q1,q2),q3) << " " << pos[megasa[i]]<<endl;
        ans[type[megasa[i]]]+= max((int)words[type[megasa[i]]].length() - pos[megasa[i]] - max(max(q1,q2),q3),0);
    }
    REP(i,SZ(words)){
        fout << ans[i] << endl;
        //cout << ans[i] << " ";
    }
    //cout << endl;

    int c1=0,c2=0;

    fout.close();

}
