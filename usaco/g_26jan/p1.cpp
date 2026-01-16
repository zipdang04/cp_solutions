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
#define MOD 1000000007

struct DSU {
	inline static int dsu[MAX] = {};
	inline static int val[MAX] = {};
	inline static int n;
	DSU(){}
	DSU(int n) {
		this -> n = n;
		FOR(int, i, 1, n) dsu[i] = -1;
	}

	int par(int u) {return dsu[u] < 0 ? u : (dsu[u] = par(dsu[u]));}
	bool join(int u, int v) {
		u = par(u), v = par(v);
		if (u == v) return false;
		if (-dsu[u] < -dsu[v]) swap(u, v);
		dsu[u] += dsu[v], dsu[v] = u;
		return true;
	}
	int sz(int u) {return -dsu[par(u)];}
	void assign(int u, int value) {val[par(u)] = value;}
	int getVal(int u) {return val[par(u)];}
} dsu;

int n, m;
int a[MAX]; stack<char> used[MAX];
tuple<bool, int, char> events[MAX];

bool visited[MAX];
void dfs(int u) {
	if (visited[u] or not used[u].empty()) return;
	visited[u] = true;
	dsu.join(u, a[u]);
	dfs(a[u]);
}

tuple<int, int, int> answer[MAX];
int sum[256];

void input();
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	dsu = DSU(n); FOR(int, i, 1, n) dfs(i);

	FOR(int, i, 1, n) if (not used[i].empty())
		dsu.assign(i, i),
		sum[used[i].top()] += (dsu.sz(i));


	REV(int, _, m, 1) {
		answer[_] = tuple<int, int, int>(sum['C'], sum['O'], sum['W']);

		auto [first, c, v] = events[_];
		sum[v] -= dsu.sz(c); used[c].pop();

		if (not first) {
			char newV = used[c].top();
			sum[newV] += dsu.sz(c);
			continue;
		}

		int newC = dsu.getVal(a[c]); if (used[newC].empty()) continue;
		char newV = used[newC].top();
		sum[newV] -= dsu.sz(newC);
		dsu.join(c, a[c]); dsu.assign(c, newC);
		sum[newV] += dsu.sz(newC);
	}
	FOR(int, i, 1, m) {
		auto [a, b, c] = answer[i];
		cout << a << ' ' << b << ' '<< c << '\n';
	}
}
void input() {
	cin >> n; FOR(int, i, 1, n) cin >> a[i];
	cin >> m; FOR(int, i, 1, m) {
		int c; char v; cin >> c >> v;
		events[i] = {used[c].empty(), c, v};
		used[c].push(v);
	}
}
