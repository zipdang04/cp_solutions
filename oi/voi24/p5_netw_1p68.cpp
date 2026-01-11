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

struct Node
{
    int node, len;
    Node() {node = len = 0;}
    Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;

#define MAX 1000001
#define MOD 998244353

#define fi first
#define se second

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORD(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int n;
int w[MAX];
vector<Node> graph[MAX];

namespace sub1 {
    const int oo = 1e9+7;
    
    ll dfs(ll node, ll parent, ll lvl, ll cMin) {
        ll answer = cMin * lvl % MOD * lvl % MOD;
        for (Node ch: graph[node]) {
            int child = ch.node; 
            if (child == parent) continue;

            answer += dfs(child, node, lvl + 1, min(cMin, ll(ch.len)));
            answer %= MOD;
        }
        return answer;
    }

    bool check() {
        return n <= 5000;
    }
    void solve() {
        FOR(int, i, 1, n) cout << dfs(i, i, 0, oo) << "\n";
    }
}

namespace sub3 {
    #define root 1

    bool check() {
        FOR(int, i, 1, n)
            if (w[i] != 1) return false;
        return true;
    }

    struct Arith{
        ll sum, add;
        inline void add2add(int amount) {add += amount, add %= MOD;}
        inline void doAdd() {sum += add, sum %= MOD;}
        inline void doMod() {sum %= MOD, add %= MOD;}
    };

    Arith ariths[MAX];
    int sz[MAX];
    void dfs(int node, int parent) {
        sz[node] = 1;
        ariths[node] = {0, 1};
        for (Node ch: graph[node]) {
            int child = ch.node;
            if (child == parent) continue;

            dfs(child, node);
            sz[node] += sz[child];
            Arith childArith = ariths[child];
            childArith.doAdd();
            childArith.add2add(sz[child] * 2);
            ariths[node].sum += childArith.sum;
            ariths[node].add += childArith.add;
        }
        
        ariths[node].doMod();
    }

    ll finalAnswer[MAX];
    void reDfs(int node, int parent, Arith prevArith) {
        prevArith.doAdd();
        finalAnswer[node] = ariths[node].sum + prevArith.sum;
        prevArith.add2add(2 * (sz[root] - sz[node]));
        // prevArith.doAdd();
        for (Node ch: graph[node]) {
            int child = ch.node;
            if (child == parent) continue;

            Arith add2prev = ariths[node];
            Arith childArith = ariths[child];
            childArith.doAdd();
            childArith.add2add(sz[child] * 2);
            add2prev.sum += MOD - childArith.sum;
            add2prev.add += MOD - childArith.add;
            add2prev.doMod();

            Arith newPrev = prevArith;
            newPrev.sum += add2prev.sum;
            newPrev.add += add2prev.add;
            newPrev.doMod();
            reDfs(child, node, newPrev);
        }
    }
    void solve() {
        dfs(root, root);
        reDfs(root, root, {0, 0});
        FOR(int, i, 1, n) cout << finalAnswer[i] << '\n';
    }
}

void input();
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    #ifndef HIEU
    freopen("netw.inp", "r", stdin);
    freopen("netw.out", "w", stdout);
    #endif
    input();

    if (sub1::check()) return sub1::solve(), 0;
    if (sub3::check()) return sub3::solve(), 0;
}
void input() {
    cin >> n;
    FOR(int, i, 1, n - 1) {
        int u, v; cin >> u >> v >> w[i];
        graph[u].push_back({v, w[i]});
        graph[v].push_back({u, w[i]});
    }
}