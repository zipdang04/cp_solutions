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
    int node; ll len;
    Node() {node = len = 0;}
    Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;

#define MAX 300005
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
    int u, v; ll w;
};

int n, m, p;
vector<Node> graph[MAX];
Edge edges[MAX];

ll dist[MAX];
PQMin<pll> pq;
void dijkstra(int root){
    memset(dist, 0x3f, sizeof(dist));
    dist[root] = 0; pq.push({0, root});
    while (pq.empty() == false) {
        pll cur = pq.top(); pq.pop();
        const int node = cur.se; const ll nodeDist = cur.fi;
        if (dist[node] != nodeDist) continue;

        for (Node ch: graph[node]) {
            int child = ch.node; ll childDist = nodeDist + ch.len;
            if (childDist < dist[child]) {
                dist[child] = childDist;
                pq.push({childDist, child});
            }
        }
    }
}

pll values[MAX];
pair<pll, pll> changes[MAX];

pair<pll, pll> change(int t, ll w){
    int u = edges[t].u, v = edges[t].v;
    const pll valU = values[u], valV = values[v];
    pll newU = valU, newV = valV;
    minimize(newU.fi, valV.fi + w);
    minimize(newU.se, valV.se + w);
    minimize(newV.fi, valU.fi + w);
    minimize(newV.se, valU.se + w);
    return {newU, newV};
}

ll valX[MAX], cntX;
ll valY[MAX], cntY;

ll find(ll* arr, ll len, ll value) {
    return lower_bound(arr + 1, arr + 1 + len, value) - arr;
}
void compress() {
    FOR(int, i, 1, n)
        valX[++cntX] = values[i].fi,
        valY[++cntY] = values[i].se;
    FOR(int, i, 1, p) {
        pll valU = changes[i].fi, valV = changes[i].se;
        valX[++cntX] = valU.fi;
        valX[++cntX] = valV.fi;
        valY[++cntY] = valU.se;
        valY[++cntY] = valV.se;
    }

    sort(valX + 1, valX + 1 + cntX);
    cntX = unique(valX + 1, valX + 1 + cntX) - valX - 1;
    sort(valY + 1, valY + 1 + cntY);
    cntY = unique(valY + 1, valY + 1 + cntY) - valY - 1;
    FOR(int, i, 1, n)
        values[i].fi = find(valX, cntX, values[i].fi),
        values[i].se = find(valY, cntY, values[i].se);
    FOR(int, i, 1, p) {
        pll &valU = changes[i].fi, &valV = changes[i].se;
        valU.fi = find(valX, cntX, valU.fi);
        valV.fi = find(valX, cntX, valV.fi);
        valU.se = find(valY, cntY, valU.se);
        valV.se = find(valY, cntY, valV.se);
    }
}
vector<int> valsY[MAX];
vector<int> bit2d[MAX];
struct BIT2D{
    void fakeUpdate(pll pos) {
        int X = pos.fi, Y = pos.se;
        for (int x = X; x <= cntX; x++)
            for (int y = Y; y <= cntY; y++)
                valsY[x].push_back(y);
    }
    void build() {
        FOR(int, i, 1, cntX) {
            valsY[i].push_back(0);
            sort(valsY[i].begin(), valsY[i].end());
            int sz = unique(valsY[i].begin(), valsY[i].end()) - valsY[i].begin();
            valsY[i].resize(sz);
            bit2d[i] = vector<int>(sz);
        }
    }
    int get(pll pos){
        int X = pos.fi, Y = pos.se, ans = 0;
        for (int x = X; x > 0; x -= x & -x) {
            int startY = upper_bound(valsY[x].begin(), valsY[x].end(), Y) - valsY[x].begin() - 1;
            for (int y = startY; y > 0; y -= y & -y){
                ans += bit2d[x][y];
            }
        }
        return ans;
    }
    void update(pll pos, int value) {
        int X = pos.fi, Y = pos.se;
        for (int x = X; x <= cntX; x += x & -x) {
            int startY = lower_bound(valsY[x].begin(), valsY[x].end(), Y) - valsY[x].begin();
            for (int y = startY; y < valsY[x].size(); y += y & -y){
                bit2d[x][y] += value;
            }
        }
    }
} bit;

int allT[MAX];

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    #ifndef HIEU
    freopen("impeval.inp", "r", stdin);
    freopen("impeval.out", "w", stdout);
    #endif
    cin >> n >> m >> p;
    FOR(int, i, 1, m) {
        int u, v; ll w; cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
        edges[i] = {u, v, w};
    }

    dijkstra(1);
    FOR(int, i, 1, n) values[i].fi = dist[i];
    dijkstra(2);
    FOR(int, i, 1, n) values[i].se = dist[i];

    FOR(int, i, 1, p) {
        int t; ll w; cin >> t >> w;
        allT[i] = t;
        changes[i] = change(t, w);
    }

    compress();
    FOR(int, i, 1, n) bit.fakeUpdate(values[i]);
    FOR(int, i, 1, p) 
        bit.fakeUpdate(changes[i].fi),
        bit.fakeUpdate(changes[i].se);
    bit.build();


    FOR(int, i, 1, n)
        bit.update(values[i], +1);
    FOR(int, i, 1, p) {
        int t = allT[i];
        int u = edges[t].u, v = edges[t].v;
        pll newU = changes[i].fi, newV = changes[i].se;
        bit.update(values[u], -1);
        bit.update(values[v], -1);
        bit.update(newU, +1);
        bit.update(newV, +1);

        cout << bit.get(newU) << ' ' << bit.get(newV) << '\n';
        bit.update(newU, -1);
        bit.update(newV, -1);
        bit.update(values[u], +1);
        bit.update(values[v], +1);
    }
}

/*
1|18 5|0 2|12 4|11 3|10
3 4         4 2
(2|12 3|11) (4|9 5|0)

1: -1 18 
2: -1 12 
3: -1 10 11 
4: -1 9 11 
5: -1 0 
*/