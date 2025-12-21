#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i++)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define cntBit(n) __builtin_popcountll(1ll*n)
#define log2(n) (63-__builtin_clzll(1ll*n))

#define MAX 200'005

int n, m, k;
int a[MAX];
vector<int> graph[MAX];

int dist[MAX], ans[MAX];
queue<int> q;
void bfs() {
	const int ROOT = 1, oo = 1e9;
	memset(dist, 0x3f, sizeof dist);
	dist[ROOT] = 0; q.push(ROOT);
	while (not q.empty()) {
		int u = q.front(); q.pop();
		for (int v: graph[u]) if (dist[v] > oo) {
			dist[v] = dist[u] + 1, q.push(v);
		}
	}

	FOR(int, i, 1, n) cerr << dist[i] << " \n"[i == n];
	memset(ans, 0, sizeof ans);
	FOR(int, i, 1, n)
		maximize(ans[a[i]], dist[i]);
}

void input();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input(); bfs();
	FOR(int, i, 1, k) cout << ans[i] << " \n"[i == k];
}
void input(){
	cin >> n >> m >> k;
	FOR(int, i, 1, n) cin >> a[i];
	FOR(int, _, 1, m) {
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
}