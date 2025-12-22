#include "bits/stdc++.h"
using namespace std;

template<class T1, class T2>
void minimize(T1&a, T2 b) { if (b < a) a = b; }
template<class T1, class T2>
void maximize(T1&a, T2 b) { if (b > a) a = b; }

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define cntBit(num) __builtin_popcount(num)
#define testBit(num, bit) ((num) >> (bit) & 1)

const int MAX = 3e5 + 5;
#define II pair<ll, ll>
#define fi first
#define se second

vector<II> adj[MAX];
ll f[MAX], p[MAX];

int n, m;


void djikstra(int node) {
	priority_queue<II, vector<II>, greater<II>> q;


	memset(f, 0x3f, sizeof f);
	f[node] = 0;

	q.push(II(0, node));

	while (!q.empty()) {
		II u = q.top();
		q.pop();
		if (u.fi != f[u.se]) continue;


		for (II v : adj[u.se]) {

			if (f[v.se] > f[u.se] + v.fi) {
				f[v.se] = f[u.se] + v.fi;
				q.push(II(f[v.se], v.se));
			}
		}
	}
}

void input() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> p[i];
	for (int i = 1; i <=m; i++) {
		int u, v, q; cin >> u >> v >> q;
 		adj[u].push_back({q, v});
	 	adj[v].push_back({q, u});
	}

	djikstra(1);

	ll ans = 0;

	for (int i = 2; i <= n; i++) ans += f[i] * p[i];

	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();
}
