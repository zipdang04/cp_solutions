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

#define MAX 1000001

#define fi first
#define se second

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define REV(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define CURRENT_TIMESTAMP chrono::steady_clock::now().time_since_epoch().count()
#define randomize mt19937_64 mt(CURRENT_TIMESTAMP)

struct Matrix{
    int MOD;
    ll mat[2][2];
    ll* operator[] (int i) {
        return mat[i];
    }
    Matrix(int MOD) {
        this -> MOD = MOD;
        memset(mat, false, sizeof(mat));
    }
};
Matrix operator * (Matrix a, Matrix b) {
    assert((a.MOD == b.MOD));
    int MOD = a.MOD;
    Matrix ans(MOD);
    FOR(int, i, 0, 1)
    FOR(int, j, 0, 1)
    FOR(int, k, 0, 1)
        ans[i][j] += a[i][k] * b[k][j] % MOD,
        ans[i][j] %= MOD;
    return ans;
}
Matrix operator ^ (Matrix a, ll b) {
    int MOD = a.MOD;
    Matrix ans(MOD);
    ans[0][0] = ans[1][1] = 1;

    while (b) {
        if (b & 1) ans = ans * a;
        a = a * a; b >>= 1;
    }
    return ans;
}
ll power(ll a, ll n, ll mod) {
    ll ans = 1;
    while (n) {
        if (n & 1) ans = ans * a % mod;
        a = a * a % mod; n >>= 1;
    }
    return ans;
}
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    const int MOD = 1e9+7;
    Matrix baseM7(MOD), baseM6(MOD - 1);
    baseM7[0][1] = baseM7[1][0] = baseM7[1][1] = 1;
    baseM6[0][1] = baseM6[1][0] = baseM6[1][1] = 1;
    FOR(int, __, 1, t) {
        int n; cin >> n;
        if (n == 0) {cout << 0 << '\n'; continue;}
        if (n == 1) {cout << 1 << '\n'; continue;}
        if (n == 2) {cout << 3 << '\n'; continue;}

        Matrix fnM6 = baseM6 * (baseM6 ^ n);
        Matrix fnM7 = baseM7 * (baseM7 ^ n);
        ll a = (fnM7[0][1] + MOD - 1) % MOD;
        a = a * power(2, (fnM6[0][1] + (MOD - 1) - 2), MOD) % MOD;
        a += power(2, (fnM6[0][1] + (MOD - 1) - 1), MOD);
        a %= MOD;
        a = a * fnM7[0][0] % MOD;
        cout << a << '\n';
    }
}