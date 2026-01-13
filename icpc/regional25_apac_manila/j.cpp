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

int n, m;
vector<int> graph[MAX];

unordered_map<int, bool> edge[MAX];

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	FOR(int, i, 1, m) {
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
		edge[u][v] = edge[v][u] = true;
	}

	int ans = 0;
	FOR(int, u, 1, n) {
		if (graph[u].size() >= 4) {ans++; continue;}
		if (graph[u].size() <= 1) continue;
		unordered_set<int> avoid(graph[u].begin(), graph[u].end());
		avoid.insert(u);

		int cnt1 = 0, cnt2 = 0;
		for (int v: graph[u]) {
			int tmp = graph[v].size();
			for (int v2: avoid) tmp -= edge[v][v2];
			cnt1 += tmp >= 1;
			cnt2 += tmp >= 2;
		}

		if (graph[u].size() == 2 and cnt2 == 2) ans++;
		else if (graph[u].size() == 3 and cnt1 >= 2) ans++;
	}

	cout << ans << '\n';
}
