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
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef map<int, int> mii;
typedef unordered_map<int, int> umii;
typedef map<ll, ll> mll;
typedef unordered_map<ll, ll> umll;
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
inline void read(T &a, Ts& ... args){
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

#define MAX 1000001
#define MOD 1000000007

#define fi first
#define se second
#define pf push_front
#define pb push_back

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORD(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int tests;
int n, l, k;
int a[MAX], s[MAX], c[MAX], b[MAX];

ll f[MAX][11];
const ll NaN = -1e18;
void sub1(){
    memset(f, -0x3f, sizeof(f));
    f[0][0] = 0;
    for (int day = 0, nxtDay = 1; nxtDay <= n; day++, nxtDay++){
        FOR(int, cntCrick, 0, l) if (f[day][cntCrick] > NaN){
            const ll curProfit = f[day][cntCrick];
            // cerr << day << ' ' << cntCrick << ' ' << curProfit << '\n';
            // mua
            FOR(int, add, 0, min(l - cntCrick, a[nxtDay])){
                ll newProfit = curProfit - add * s[nxtDay];
                ll newCrick = cntCrick + add;
                newProfit -= newCrick * k;
                // cerr << "++ " << add << ' ' << newCrick << ' ' << newProfit << '\n';
                maximize(f[nxtDay][newCrick], newProfit);
            }
            FOR(int, del, 0, min(cntCrick, c[nxtDay])){
                ll newProfit = curProfit + del * b[nxtDay];
                ll newCrick = cntCrick - del;
                newProfit -= newCrick * k;
                // cerr << "-- " << del << ' ' << newCrick << ' ' << newProfit << '\n';
                maximize(f[nxtDay][newCrick], newProfit);
            }
        }
    }
    cout << f[n][0] << '\n';
}

void sub2(){
    PQMax<pll> pq;
    FOR(int, day, 1, n){
        while ()
    }
}

void input();
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    read(tests);
    FOR(int, _,1, tests){
        input();
        // cerr << n << ' ' << l << ' ' << k << '\n';
        // cerr << "done test " << _ << '\n';
        sub1();
    }
}
void input(){
    read(n, l, k);
    FOR(int, i, 1, n) read(a[i], s[i], c[i], b[i]);
}