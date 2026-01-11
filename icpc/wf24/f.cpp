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

// /*
struct Point
{
    int x, y;
    Point() {x = y = 0;}
    Point(int x, int y) {this -> x = x, this -> y = y;}
};
typedef vector<Point> vg;
// */

#define MAX 1000
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






Point operator - (Point a, Point b) {return {a.x - b.x, a.y - b.y};}
ll dist2(Point p) {return 1ll * p.x * p.x + 1ll * p.y * p.y;}

int n;
Point points[MAX + 1];

struct DSU {
    int dsu[MAX + 1];
    void clear() {
        FOR(int, i, 0, MAX) dsu[i] = -1;
    }
    DSU() {clear();}

    int findPar(int u) {
        return dsu[u] < 0 ? u : dsu[u] = findPar(dsu[u]);
    }
    bool join(int u, int v) {
        u = findPar(u), v = findPar(v);
        if (u == v) return false;
        if (-dsu[u] < -dsu[v]) swap(u, v);
        dsu[u] += dsu[v]; dsu[v] = u;
        return true;
    }
} dsu;
bitset<MAX + 1> bs;

bool check(ll d2) { 
    dsu.clear(); bs = 1;
    FOR(int, i, 1, n * 2) FOR(int, j, i + 1, n * 2)
        if (dist2(points[i] - points[j]) < d2) {
            dsu.join(i, j);
        }

    vector<int> allSegment;
    FOR(int, i, 1, n * 2)
        if (dsu.dsu[i] < 0)
            allSegment.push_back(-dsu.dsu[i]);
    for (int num: allSegment)
        bs |= bs << num;
    return bs[n];
}

vector<int> group[MAX + 1];
int a[MAX + 1];
bitset<MAX + 1> f[MAX + 1];
bitset<MAX + 1> trace[MAX + 1];















main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n; FOR(int, i, 1, n * 2) cin >> points[i].x >> points[i].y;

    __int128_t lo = 0, hi = 9e18;
    ll ans = 0;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (check(mid))
            ans = mid, lo = mid + 1;
        else
            hi = mid - 1;
    }
    cout << fixed << setprecision(7);

    check(ans); // build lại mảng DSU

    FOR(int, i, 1, n * 2) {
        a[dsu.findPar(i)]++;
        group[dsu.findPar(i)].push_back(i);
    }

    f[0][0] = 1;
    for (int i = 0, nxt = 1; nxt <= n * 2; i++, nxt++) {
        trace[nxt] = f[i] << a[nxt];
        f[nxt] = f[i] | trace[nxt];
    }

    cout << sqrt(ans) << '\n';
    int sum = n;
    FORD(int, i, n * 2, 1) {    
        if (trace[i][sum]) {
            sum -= a[i];
            for (int pos: group[i])
                cout << pos << '\n';
        }
    }
}