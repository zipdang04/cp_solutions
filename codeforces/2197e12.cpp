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
bool maximize(T1 &a, T2 b){
	return (b > a) ? (a = b, true) : false;
}
template <class T1, class T2>
bool minimize(T1 &a, T2 b){
	return (b < a) ? (a = b, true) : false;
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

vector<int> ASK(ll index) {
	assert(1 <= index);
	assert(index <= (1 << 30));
	cout << "? " << index << endl;

	int q; cin >> q;
	vector<int> ans(q);
	for (int &i: ans) cin >> i;
	return ans;
}
int n; vector<int> graph[MAX];
void ANSWER() {
	int m = 0;
	FOR(int, i, 1, n) m += graph[i].size();
	cout << "! " << m << '\n';
	FOR(int, u, 1, n) for (int v: graph[u]) cout << u << ' ' << v << '\n';
	cout.flush();
}

bool finalized[MAX];
ll f[MAX];

ll qIdx = 1;
vector<int> current;
void newAsk() {
	vector<int> next = ASK(++qIdx);
	// cerr << qIdx << " => "; for (int i: next) cerr << i << ' '; cerr << endl;
	if (next.size() > current.size())
		assert(int(next.size()) == int(current.size()) + 1);

	while (not current.empty() and current.size() >= next.size()) {
		int u = current.back(); current.pop_back();
		finalized[u] = true;

		f[u] = 1;
		// cerr << "pop " << u << ':';
		// for (int v: graph[u]) cerr << v << ' '; cerr << '\n';
		for (int v: graph[u]) f[u] += f[v];
	}

	current = next; int sz = current.size();
	if (sz > 1) {
		int u = current[sz - 2], v = current[sz-1];
		// cerr << "add edge" << u << "->" << v << '\n';
		graph[u].push_back(v);
	}
	if (current.empty()) return;
	int u = current.back(); if (finalized[u]) qIdx += f[u] - 1;
}

void clear();
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		cin >> n; current = {1};
		while (not current.empty()) {
			newAsk();
			// cerr << "==> "; FOR(int, i, 1, n) cerr << (finalized[i] ? f[i] : -1) << " \n"[i == n];
		}

		ANSWER();
		clear();
	}
}
void clear() {
	qIdx = 1;
	FOR(int, i, 1, n) graph[i].clear();
	FOR(int, i, 1, n) finalized[i] = 0;
	FOR(int, i, 1, n) f[i] = 0;
}
