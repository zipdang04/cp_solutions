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

#define MAX 10004
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

ll n, l1, l2, c, d;
ll a[MAX], sumA;

namespace sub1 {
    bool check() {
        return l1 == l2;
    }
    void solve() {
        ll answer = 0;
        ll remain = 0;
        FOR(int, i, 1, n) {
            if (remain > 0) answer += d;
            remain += a[i];

            ll segs = remain / l1; remain %= l1;
            answer += c * max(segs - 1, 0ll);
        }
        cout << answer << '\n';
    }
}

namespace sub23 {
    #define MAX_BUF 300
    const ll oo = 1e18;

    bool check() {
        int maxA = a[1]; FOR(int, i, 2, n) maximize(maxA, a[i]);
        if (sumA <= 20) return true;
        if (maxA <= 100 and n <= 100 and l1 <= 100 and l2 <= 100) return true;
        return false;
    }

    ll f[MAX][MAX_BUF + 1];
    void solve() {
        memset(f, 0x3f, sizeof(f));
        f[0][0] = 0;

        for (int i = 0, nxt = 1; i <= n; i++, nxt++) {
            FORD(int, buffer, MAX_BUF, 0) if (f[i][buffer] < oo) {
                if (buffer >= l1)
                    minimize(f[i][buffer - l1], f[i][buffer] + c * (buffer != l1)); // cat
                if (buffer >= l2)
                    minimize(f[i][buffer - l2], f[i][buffer] + c * (buffer != l2)); // cat
            }
            if (i == n) break;

            FOR(int, buffer, 0, MAX_BUF) if (f[i][buffer] < oo) {
                const ll val = f[i][buffer];
                if (buffer + a[nxt] <= MAX_BUF)
                    minimize(f[nxt][buffer + a[nxt]], f[i][buffer] + d * !!buffer); // dan
            }
        }

        cout << f[n][0] << '\n';
    }
}

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    #ifndef HIEU
    freopen("wpro.inp", "r", stdin);
    freopen("wpro.out", "w", stdout);
    #endif
    cin >> n >> l1 >> l2 >> c >> d;
    FOR(int, i, 1, n) {
        cin >> a[i];
        sumA += a[i];
    }

    if (sub1::check()) return sub1::solve(), 0;
    if (sub23::check()) return sub23::solve(), 0;
}