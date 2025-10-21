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

#define MAX 100005
#define MOD 1000000007

int n;
vector<pair<int, int>> graph[MAX];
int cnt[MAX][2], par[MAX];

void dfs(int u, int p, int bit) {
	par[u] = p;
	cnt[u][0] = 1;
	for (auto [v, w]: graph[u]) {
		if (v == p) continue;
		w = testBit(w, bit);
		// cerr << u << "---" << w << "-->" << v << '\n';
		assert(0 <= w and w <= 1);

		dfs(v, u, bit);
		cnt[u][0^w] += cnt[v][0],
		cnt[u][1^w] += cnt[v][1];
	}
} 

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	ll answer = 0;
	FOR(int, bit, 0, 26) {
		memset(par, false, sizeof(par));
		memset(cnt, false, sizeof(cnt));
		dfs(1, 0, bit);
		// cerr << "bit " << bit << '\n';
		// FOR(int, i, 1, n) cerr << cnt[i][0] << '.' << cnt[i][1] << " \n"[i == n];
		ll count = 0;
		FOR(int, u, 1, n) {
			int uCnt[2] = {};
			for (auto [v, w]: graph[u]) if (v != par[u]){
				w = testBit(w, bit);
				
				int vCnt[2] = {};
				vCnt[0^w] = cnt[v][0],
				vCnt[1^w] = cnt[v][1];

				count += vCnt[1]
					   + 1ll * uCnt[0] * vCnt[1] 
					   + 1ll * uCnt[1] * vCnt[0];
				uCnt[0] += vCnt[0],
				uCnt[1] += vCnt[1];
			}
		}
		// cerr << "+= 2p" << bit << '*' << count << '\n';
		answer += count * (1ll << bit);
	}
	cout << answer << '\n';
}
void input() {
	cin >> n;
	FOR(int, i, 1, n-1) {
		int u, v, w; cin >> u >> v >> w;
		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}
}