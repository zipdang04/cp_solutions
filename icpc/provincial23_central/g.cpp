#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
template <class T> using PQMax = priority_queue<T>;
template <class T> using PQMin = priority_queue<T, vector<T>, greater<T>>;
template <class T1, class T2>
void maximize(T1 &a, T2 b){
    if (b > a) a = b;
}
template <class T1, class T2>
void minimize(T1 &a, T2 b){
    if (b < a) a = b;
}
template <class T>
void read(T &number)
{
    bool negative = false;
    register int c;
    number = 0;
    c = getchar();
    while (c != '-' && !isalnum(c)) c = getchar();
    if (c=='-'){
        negative = true;
        c = getchar();
    }
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;
    if (negative)
        number *= -1;
}
template <class T, class ...Ts>
void read(T &a, Ts& ... args){
    read(a);
    read(args...);
}

/*
struct Node
{
    int node, len;
    Node() {node = len = 0;}
    Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
*/

#define MAX 10000
#define MOD 1000000007

#define fi first
#define se second

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORD(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int f[MAX + 1];

struct MEX{
    int cnt[32768];
    vector<int> used;
    int mex;
    
    
    void clear(){
        for (int num: used)
            cnt[num] = 0;
        used.clear();
        mex = 0;
    }
    void add(int num){
        cnt[num]++; used.push_back(num);
        while (cnt[mex]) mex++;
    }
    
    MEX(){clear();}
} mex;

void preCal(){
    f[1] = 1; 
    FOR(int, i, 2, MAX){
        mex.clear();
        FOR(int, j, 0, i - 1)
            mex.add(f[j]);
        for (int j = 1; j <= i - j; j++)
            mex.add(f[j] ^ f[i - j]);
        f[i] = mex.mex;
        // cerr << i << ' ' << f[i] << "|";
        // for (int i: mex.used) cerr << i << ' '; 
        // cerr << '\n';
    }
}
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    preCal();

    int n; cin >> n;
    int ans = 0;
    FOR(int, i, 1, n){
        int a; cin >> a;
        ans ^= f[a];
    }
    cout << (ans ? "Alice" : "Bob");
}