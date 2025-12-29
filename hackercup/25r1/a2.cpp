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

#define MAX 1000001
#define MOD 1000000007

struct DSU {
	vector<int> p;
	DSU() {}
	DSU(int len) {
		p.resize(len, -1);
	}
	int par(int u) { return p[u] < 0 ? u : p[u] = par(p[u]);}
	bool join(int u, int v) {
		u = par(u), v = par(v);
		if (u == v) return false;
		if (-p[u] < -p[v]) swap(u, v);
		p[u] += p[v], p[v] = u;
		return true;
	}
} dsu;

int n;
int a[MAX];
vector<tuple<int, int, int>> edges;

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		cin >> n; FOR(int, i, 1, n) cin >> a[i];
		edges.clear(); dsu = DSU(n + 1);
		FOR(int, i, 1, n) edges.push_back({a[i], 0, i});
		FOR(int, i, 1, n-1) edges.push_back({abs(a[i]-a[i+1]), i, i+1});
		sort(edges.begin(), edges.end());

		int ans = 0;
		for (auto [cost, u, v]: edges) {
			if (dsu.join(u, v)) ans = cost;
			// cerr << cost << ' ' << u << ' ' << v << ' ' << ans << '\n';
		}
		cout << "Case #" << _ << ": " << ans << '\n';
		// cerr << '\n';
	}
}