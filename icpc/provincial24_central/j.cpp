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
#define MOD 1000000007

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

int n, q;
vector<int> tree[MAX];
int par[MAX], lvl[MAX];
void dfs(int node, int parent = 0) {
    par[node] = parent; 
    lvl[node] = lvl[parent] + 1;
    for (int child: tree[node]) if (child != parent)
        dfs(child, node);
}

#define BIT 16
int rmq[BIT + 1][MAX];
void buildRMQ() {
    FOR(int, i, 1, n) rmq[0][i] = par[i];
    FOR(int, bit, 1, BIT)
        FOR(int, i, 1, n)
            rmq[bit][i] = rmq[bit - 1][rmq[bit - 1][i]];
}
int jump(int u, int dist) {
    for (int bit = 0; dist; bit++, dist >>= 1)
        if (dist & 1) u = rmq[bit][u];
    return u;
}
int lca(int u, int v) {
    if (lvl[u] > lvl[v]) swap(u, v);
    v = jump(v, lvl[v] - lvl[u]);
    if (u == v) return u;

    REV(int, bit, BIT, 0)
        if (rmq[bit][u] != rmq[bit][v])
            u = rmq[bit][u],
            v = rmq[bit][v];
    return par[u];
}

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    FOR(int, i, 1, n - 1) {
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(1); buildRMQ();

    FOR(int, _, 1, q) {
        int x, y, z; cin >> x >> y >> z;

        int xy = lca(x, y);
        int yz = lca(y, z);
        int xz = lca(x, z);
        if (xz == y) {
            cout << "YES\n"; continue;
        }

        if (xy == x || xy != y) {
            if (yz == y) cout << "YES\n";
            else cout << "NO\n";
        } else {
            if (lvl[xz] <= lvl[y]) cout << "YES\n";
            else cout << "NO\n";
        } 
    }
}