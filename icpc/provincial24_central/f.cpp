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

int n[3] = {}, N;
int state[MAX];
int cnt[8] = {};

int dec(int &a, int &b) {
    int x = min(a, b);
    a -= x, b -= x;
    return x;
}

struct Flow{
    struct Edge{int from, dest, oppo; ll capa;};
    
    const ll oo = 1ll << 60;
    vector<Edge> edges, resi;
    vector<vector<int>> graph;
    int n, m, s, t;
 
    const int NaN = -1;
    vector<int> level;
    vector<int> ptr;
 
    bool bfs(ll lim){
        level = vector<int>(n, NaN);
 
        queue<int> q; 
        
        q.push(s); level[s] = 0;
        while (!q.empty()){
            int node = q.front(); q.pop();
            int nodeLvl = level[node];
 
            for (int idx: graph[node]){
                Edge e = resi[idx];
                if (e.capa < lim || level[e.dest] != NaN) continue;
                
                q.push(e.dest); level[e.dest] = nodeLvl + 1;
            }
        }
 
        return level[t] != NaN;
    }
    
    bool dfs(int node, ll lim){
        if (node == t) return true;
        int currLevel = level[node];
 
        int &i = ptr[node], maxSize = graph[node].size();
        for (; i < maxSize; i++){
            int idx = graph[node][i];
            Edge e = resi[idx];
            if (e.capa < lim || level[e.dest] != currLevel + 1) continue;
 
            if (dfs(e.dest, lim)){
                resi[idx].capa -= lim;
                resi[e.oppo].capa += lim;
                return true;
            }
        }
 
        return false;
    }
 
    Flow(){
    }
 
    void init(int n, int s, int t){
        this -> n = n; this -> s = s; this -> t = t;
        m = 0; edges.clear();
        graph = vector<vector<int>>(n);
    }
 
    void addEdge(int from, int dest, ll capa){
        edges.push_back({from, dest, m + 1, capa});
        edges.push_back({dest, from, m    , 0});
        graph[from].push_back(m),
        graph[dest].push_back(m + 1);
        m += 2;
    }
 
    ll calculate(){
        resi = edges; ll answer = 0;
        ll tmp = oo;
        while (tmp){
            if (!bfs(tmp)){
                tmp >>= 1; continue;
            }
 
            ptr = vector<int>(n, 0);
            while (dfs(s, tmp))
                answer += tmp;
        }
        return answer;
    }
} flow;

#define SOURCE 0
#define IN(x) (1 + (x))
#define OUT(x) (9 + (x))
#define SINK 12

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    FOR(int, _, 1, t) {
        memset(state, false, sizeof(state));
        memset(cnt, false, sizeof(cnt));
        cin >> N >> n[0] >> n[1] >> n[2];
        FOR(int, bit, 0, 2) {
            int len; cin >> len;
            FOR(int, i, 1, len) {
                int worker; cin >> worker;
                state[worker] |= 1 << bit;
            }
        }
        FOR(int, i, 1, N) cnt[state[i]]++;

        flow.init(SINK + 1, SOURCE, SINK);
        FOR(int, i, 0, 7) flow.addEdge(SOURCE, IN(i), cnt[i]);
        FOR(int, i, 0, 2) flow.addEdge(OUT(i), SINK, n[i]);
        FOR(int, i, 0, 7) FOR(int, j, 0, 2)
            if (testBit(i, j))
            flow.addEdge(IN(i), OUT(j), 1e9);
        cout << flow.calculate() << '\n';
    }
}