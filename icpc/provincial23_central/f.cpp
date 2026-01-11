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
    int node, idx;
    Node() {node = idx = 0;}
    Node(int node, int idx) {this -> node = node, this -> idx = idx;}
};

#define MAX 1000001
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

struct Edge{
    int u, v, c1, c2;
};

int n;
vector<Node> graph[MAX];
Edge edges[MAX];

int par[MAX], lvl[MAX];
int c1[MAX], c2[MAX];
void dfs(int node, int parent){
    for (Node ch: graph[node]){
        int child = ch.node;
        if (child == parent) continue;

        par[child] = node;
        lvl[child] = lvl[node] + 1;
        c1[child] = edges[ch.idx].c1;
        c2[child] = edges[ch.idx].c2;

        dfs(child, node);
    }
}

const int BIT = 16;
int rmq[BIT + 1][MAX];
void buildRMQ(){
    FOR(int, i, 1, n) rmq[0][i] = par[i];
    FOR(int, bit, 1, BIT)
        FOR(int, i, 1, n)
            rmq[bit][i] = rmq[bit - 1][rmq[bit - 1][i]];
}

int jump(int node, int dist){
    for (int bit = 0; dist > 0; bit++, dist >>= 1)
        if (dist & 1)
            node = rmq[bit][node];
    return node;
}

int lca(int u, int v){
    if (lvl[u] < lvl[v]) swap(u, v);
    u = jump(u, lvl[u] - lvl[v]);
    if (u == v) return u;

    FORD(int, bit, BIT, 0)
        if (rmq[bit][u] != rmq[bit][v])
            u = rmq[bit][u], v = rmq[bit][v];
    return par[u];
}

int cnt[MAX];
void dpCnt(int node, int parent){
    for (Node ch: graph[node]){
        int child = ch.node;
        if (child == parent) continue;

        dpCnt(child, node);
        cnt[node] += cnt[child];
    }
}
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    FOR(int, i, 1, n - 1){
        int u, v, c1, c2; cin >> u >> v >> c1 >> c2;
        edges[i] = {u, v, c1, c2};
        graph[u].push_back(Node(v, i));
        graph[v].push_back(Node(u, i));
    }

    dfs(1, 0);
    buildRMQ();
    FOR(int, i, 1, n - 1){
        int j = i + 1;
        int p = lca(i, j);
        cnt[i]++, cnt[j]++, cnt[p] -= 2;
    }

    dpCnt(1, 0);
    ll answer = 0;
    FOR(int, i, 1, n)
        answer += min(
            1ll * c1[i] * cnt[i],
            1ll * c2[i]
        );
    cout << answer;
}