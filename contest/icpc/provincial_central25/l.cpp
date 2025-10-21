#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
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

#define MAX 1000001
#define MOD 1000000007
vector<pll> adj[MAX];
ll deg[MAX], f[MAX];
ll n, m, V, start, finish;


void Djikstra(ll x) {
	PQMin<pll> q;
	memset(f, 0x3f, sizeof f);
	f[x] = 0;
	q.push(pll(0, x));

	while (!q.empty()) {
		pll u = q.top();
		q.pop();
	
		for (pll v : adj[u.se]) {
			if (v.se == finish && f[v.se] > f[u.se] + v.fi) {
				f[v.se] = f[u.se] + v.fi;
				q.push(pll(f[v.se], v.se));
				continue;
			}

			if (f[v.se] > f[u.se] + v.fi + max(0ll, deg[v.se] - 2) * V) {
				f[v.se] = f[u.se] + v.fi + max(0ll, deg[v.se] - 2) * V;
				q.push(pll(f[v.se], v.se));
			}
		}
	} 
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> V;

	for (ll i = 1; i <= m; i++) {
		ll u, v, c; cin >> u >> v >> c;
		adj[u].push_back(pll(c, v));
		adj[v].push_back(pll(c, u));
		deg[u]++;
		deg[v]++;
	}


	cin >> start >> finish;

	Djikstra(start);

	cout << fixed << setprecision(6) << f[finish] / (ld)V;
	
}