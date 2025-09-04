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

#define fi first
#define se second

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define REV(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define log2(n) (31 - __builtin_clz(n))
#define log2ll(n) (63 - __builtin_clzll(n))
#define CURRENT_TIMESTAMP chrono::steady_clock::now().time_since_epoch().count()
#define randomize mt19937_64 mt(CURRENT_TIMESTAMP)

#define MAX 1005
#define MOD 1000000007
 
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
 
    pair<int, int> addEdge(int from, int dest, ll capa){
        edges.push_back({from, dest, m + 1, capa});
        edges.push_back({dest, from, m    , 0});
        graph[from].push_back(m),
        graph[dest].push_back(m + 1);
		pii ans = {m+1, m}; m += 2;
		return ans;
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
};

int n, m, k;
int dist[MAX][MAX], p[MAX], q[MAX];

void F_W() {
	FOR(int, mid, 1, n) FOR(int, u, 1, n) FOR(int, v, 1, n) 
		minimize(dist[u][v], dist[u][mid] + dist[mid][v]);
}


Flow flow;
int match[MAX];
bool check(int limit) {
	#define START 0
	#define ONE(x) (x)
	#define TWO(x) ((x) + k)
	#define END (2*k+1)
	flow.init(END + 1, START, END);

	FOR(int, i, 1, k)
		flow.addEdge(START, ONE(i), 1),
		flow.addEdge(TWO(i), END, 1);
	FOR(int, u, 1, k) FOR(int, v, 1, k) {
		if (dist[p[u]][q[v]] <= limit)
			flow.addEdge(ONE(u), TWO(v), 1);
	}

	if (flow.calculate() < k) return false;
    FOR(int, u, 1, k) 
        for (int ptr: flow.graph[ONE(u)]) {
            const Flow::Edge &edge = flow.resi[ptr];
            if (edge.capa) continue;
            match[edge.dest - k] = u; break;
        }
    return true;
}

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input(); F_W();

	int lo = 0, hi = 1e9, ans = 0;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (check(mid))
			ans = mid,
            hi = mid - 1;
		else
			lo = mid + 1;
	}
	cout << ans << '\n';
    FOR(int, i, 1, k) cout << match[i] << " \n"[i == n];
}
void input() {
	cin >> n >> m >> k;
	memset(dist, 0x3f, sizeof(dist));
	FOR(int, i, 1, n) dist[i][i] = 0;
	FOR(int, i, 1, m) {
		int u, v, w; cin >> u >> v >> w;
		dist[u][v] = dist[v][u] = w;
	}
	FOR(int, i, 1, k) cin >> p[i];
	FOR(int, i, 1, k) cin >> q[i];
}