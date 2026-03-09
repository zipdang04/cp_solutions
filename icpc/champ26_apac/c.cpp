#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2> bool minimize(T1 &a, T2 b) {
	return (b < a) ? ((a=b), true) : false;
}
template<class T1, class T2> bool maximize(T1 &a, T2 b) {
	return (b > a) ? ((a=b), true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 200'005
#ifdef HIEU
	#define IMPOSSIBLE {assert(false); cout << "impossible"; exit(0);}
#else
	#define IMPOSSIBLE {cout << "impossible"; exit(0);}
#endif

int n, m;
vector<pii> graph[MAX];
int p[MAX], prio[MAX];

void buildPrio() {
	if (p[1] != 1) IMPOSSIBLE;
	prio[1] = 1;
	FOR(int, i, 2, n) prio[p[i]] = i;

	FOR(int, u, 1, n) 
		sort(graph[u].begin(), graph[u].end(), [](pii u, pii v) {
			return prio[u.fi] < prio[v.fi];
		});
}

bool visited[MAX];
vector<int> lvl[MAX];
int dep[MAX];
int par[MAX], parEdge[MAX];
void dfsByPrio(int u, int depth) { 
	dep[u] = depth;
	visited[u] = true; lvl[depth].push_back(u);
	for (auto[v, _]: graph[u]) {
		if (visited[v]) continue;
		if (prio[u] > prio[v]) IMPOSSIBLE; 
		
		par[v] = u; parEdge[v] = _;
		dfsByPrio(v, depth + 1);
	}
}

ll cost[MAX];
void buildCost() {
	FOR(int, depth, 1, n) {
		// cerr << depth << ": ";
		ll curCost = 100'000'000 * 1ll * depth;
		// int prv = 1e9;
		for (int u: lvl[depth]) {
			// cerr << u << ' ';
			// curCost -= prv < u;
			assert(cost[u] == 0);
			cost[u] = curCost--;
			// prv = u;
		}
		// cerr << '\n';
	}
}

ll ans[MAX];
void buildEdge() {
	FOR(int, u, 2, n) {
		int p = par[u], i = parEdge[u];
		assert(dep[p] + 1 == dep[u]);
		// assert(cost[u] <= dep[u] * 100'000'000);
		// assert(cost[u] > (dep[u]-1) * 100'000'000);
		ans[i] = cost[u] - cost[p];
	}
	FOR(int, i, 1, m) if (ans[i] == 0) ans[i] = 1;
}

// void wrongDoing() {
// 	FOR(int, u, 1, n) {
// 		vector<pii> par;
// 		for (auto [v, i]: graph[u]) if (prio[v] < prio[u]) 
// 			par.push_back({v, i});
		
// 		const int sz = par.size();
// 		if (sz <= 1) continue;

// 		sort(par.begin(), par.begin(), [](pii u, pii v) {return prio[u.fi] < prio[v.fi];});
// 		FOR(int, i, 1, sz-1)
// 			ans[par[i].se]--;
// 		return;
// 	}
// 	IMPOSSIBLE;
// }
int ptrCheck = 1;
void lastCheck(int u) {
	// cerr << u << ' ';
	if (u != p[ptrCheck++]) IMPOSSIBLE;
	for (auto [v, _]: graph[u])
		if (par[v] == u)
			lastCheck(v);
	// if (u == 1) cerr << '\n';
}

void input(), clear();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();
	buildPrio();
	dfsByPrio(1, 0); FOR(int, i, 1, n) if (not visited[i]) IMPOSSIBLE;
	buildCost(); 
	buildEdge();
	lastCheck(1);
	// wrongDoing();
	// FOR(int, i, 1, n) cerr << i << '.' << cost[i] << " \n"[i == n];
	FOR(int, i, 1, m) cout << ans[i] << " \n"[i == m];
}
void input() {
	cin >> n >> m;
	FOR(int, i, 1, m) {
		int u, v; cin >> u >> v;
		graph[u].push_back({v, i});
		graph[v].push_back({u, i});
	}
	FOR(int, i, 1, n) cin >> p[i];
} 
void clear() {}