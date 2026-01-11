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

#define MAX 200005
#define BIT 17
#define ROOT 1
#define MOD 1000000007

int n, k;
int w[MAX];
pii missions[MAX];
vector<int> graph[MAX];

namespace LCA{
	int par[MAX], lvl[MAX];
	void buildTree(int node, int parent = 0) {
		par[node] = parent; lvl[node] = lvl[parent] + 1;
		for (int child: graph[node]) if (child != parent) buildTree(child, node);
	}

	int rmq[BIT + 1][MAX];
	int rmqMax[BIT + 1][MAX];
	void buildRMQ() {
		buildTree(ROOT);
		// cerr << "par: "; FOR(int, i, 1, n) cerr << par[i] << " \n"[i == n];
		// // cerr << "lvl: "; FOR(int, i, 1, n) cerr << lvl[i] << " \n"[i == n];

		FOR(int, i, 1, n)
			rmq[0][i] = par[i], rmqMax[0][i] = max(w[i], w[par[i]]);
		FOR(int, bit, 1, BIT) FOR(int, i, 1, n) {
			int j = rmq[bit - 1][i];
			rmq[bit][i] = rmq[bit - 1][j],
			rmqMax[bit][i] = max(rmqMax[bit - 1][i], rmqMax[bit - 1][j]);
		}

		// cerr << "rmq: \n";
		// FOR(int, bit, 0, 3) FOR(int, i, 1, n)  cerr << rmq[bit][i] << '.' << rmqMax[bit][i] << " \n"[i == n];
	}

	pii jump(int node, int dist) {
		int maxi = w[node];
		for (int bit = 0; dist > 0; bit++, dist >>= 1)
			if (dist & 1) {
				maximize(maxi, rmqMax[bit][node]);
				node = rmq[bit][node];
			}
		return {node, maxi};
	}

	int calPath(int u, int v) {
		int answer = max(w[u], w[v]);
		if (lvl[u] > lvl[v]) swap(u, v);
		pii cur = jump(v, lvl[v] - lvl[u]);
		// cerr << u << ' ' << v << '|' << cur.fi << ' ' << cur.se << '\n';
		v = cur.fi; maximize(answer, cur.se);
		if (u == v) return answer;

		REV(int, bit, BIT, 0) if (rmq[bit][u] != rmq[bit][v]) {
			maximize(answer, rmqMax[bit][u]);
			maximize(answer, rmqMax[bit][v]);
			u = rmq[bit][u], v = rmq[bit][v];
		}
		return max(answer, w[par[u]]);
	}
}

int wMiss[MAX];
ll f[MAX];
namespace Sub124{
	void solve() {
		missions[0].se = 1;
		for (int i = 0; i < k; i++) {
			int node = missions[i].se;
			FOR(int, nxt, i + 1, k) if (missions[nxt].fi == node)
				maximize(f[nxt], f[i] + wMiss[nxt]);
		}

		ll answer = 0;
		FOR(int, i, 1, k) maximize(answer, f[i]); // tasks
		cout << answer;
	}
}
namespace Sub35{
	void solve() {
		memset(f, -0x3f, sizeof(f));
		f[1] = 0;
		FOR(int, i, 1, k) {
			int u = missions[i].fi, v = missions[i].se;
			// if (f[u] >= 0) cerr <<f[u] + wMiss[i] << ' ';
			// else cerr << "-1";
			// cerr << " \n"[i == k];
			if (f[u] >= 0)
				maximize(f[v], f[u] + wMiss[i]);
		}

		ll answer = 0;
		FOR(int, i, 1, n) maximize(answer, f[i]); // vertices
		cout << answer;
	}
}

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input(); LCA::buildRMQ();
	FOR(int, i, 1, k) {
		int u = missions[i].fi, v = missions[i].se;
		wMiss[i] = LCA::calPath(u, v);
	}
	// FOR(int, i, 1, k) cerr << wMiss[i] << " \n"[i == k];

	Sub35::solve();
}
void input(){
	#ifndef HIEU
	freopen("ship.inp", "r", stdin);
	freopen("ship.out", "w", stdout);
	#endif
	cin >> n; FOR(int, i, 1, n) cin >> w[i];
	FOR(int, _, 1, n - 1) {
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	cin >> k;
	FOR(int, i, 1, k) {
		int u, v; cin >> u >> v;
		missions[i] = {u, v};
	}
}
