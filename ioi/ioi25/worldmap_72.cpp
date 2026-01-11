#include "worldmap.h"

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

#define MAX 50
#define MOD 1000000007
randomize;
struct Rand {
	ll next(ll n) {
		return mt() % n;
	}
	ll next(ll l, ll r) {
		return l + next(r-l+1);
	}
} rnd;

int n, m;
vector<int> graph[MAX];

namespace Subtask12 {
	vector<int> euler;
	void dfs(int u, int p) {
		// cerr << u << ' ' << p << '\n';
		euler.push_back(u);
		bool oke = false;
		for (int v: graph[u]) if (v != p)
			dfs(v, u), euler.push_back(u);
	}
	vector<vector<int>> solve() {
		dfs(1, 0);
		int sz = euler.size();
		return vector<vector<int>>(sz, euler);
	}
}
namespace Subtask3 {
	vector<vector<int>> answer;
	vector<vector<int>> solve() {
		vector<int> allnum;
		for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++)
			allnum.push_back(i), allnum.push_back(j);

		answer = vector<vector<int>>(40, vector<int>(40, 1));
		int ptr = 0;
		for (int row = 0; row < 40; row++) {
			if (ptr > 0) ptr--;
			int from = (row % 2 == 0) ? 0 : 39;
			int to = 39 - from;
			int add = (row % 2 == 0) ? 1 : -1;
			for (int col = from; col >= 0 and col <= 39; col += add) {
				if (ptr == (int)allnum.size()) break;
				answer[row][col] = allnum[ptr++];
			}
			if (ptr == (int)allnum.size()) break;
		}
		return answer;
	}
}

namespace Subtask4 {
	vector<vector<int>> answer;
	vector<vector<int>> solve() {
		answer = vector<vector<int>>(100, vector<int>(100, 1));
		for (int i = 2, row = 0; i <= n; i++, row += 2) {
			int ptr = 0;
			answer[row][ptr++] = i;
			for (int j: graph[i]) {
				answer[row][ptr++] = j;
				answer[row][ptr++] = i;
			}
		}
		return answer;
	}
}

namespace Subtask56 {
	void clear();
	vector<vector<int>> answer;
	vector<bool> visited;
	vector<int> buildArray(int u) {
		vector<int> ans;
		for (int v: graph[u]) if (not visited[v]) {
			ans.push_back(u);
			ans.push_back(v);
		}
		return ans;
	}
	void dfs(int u, int p) {
		visited[u] = true;
		vector<int> tmp = buildArray(u);
		if (not tmp.empty()) {
			answer.push_back(tmp);
			answer.push_back(vector<int>{u});
		}

		for (int v: graph[u]) {
			if (visited[v]) continue;
			answer.push_back(vector<int>{v});
			dfs(v, u);
			answer.push_back(vector<int>{u});
		}
		// answer.pop_back();
	}
	vector<vector<int>> trying() {
		clear();
		if (n == 1) return vector<vector<int>>(1, {1});
		visited.resize(n+1, false);
		int root = rnd.next(1, n);
		dfs(root, 0);
		while ((int) answer.rbegin() -> size() == 1) answer.pop_back();
		// cerr << "oke" << ' ' << answer.size() << endl;;

		int maxWidth = answer.size();
		for (vector<int> &v: answer)
			maximize(maxWidth, (int)v.size());
		// cerr << maxWidth << endl;

		answer.resize(maxWidth, vector<int> {(*answer.rbegin())[0]});
		for (vector<int> &v: answer)
			v.resize(maxWidth, v[0]);
		// cerr << maxWidth << endl;

		return answer;
	}
	vector<vector<int>> solve() {
		vector<vector<int>> answer = trying();
		FOR(int, i, 1, 15) {
			vector<vector<int>> tmp = trying();
			if (tmp.size() < answer.size()) answer = tmp;
		}
		return answer;
	}
	void clear() {
		answer.clear();
		visited.clear();
	}
}

void clear();
std::vector<std::vector<int>> create_map(int _N, int _M, std::vector<int> _A, std::vector<int> _B) {
	clear();
	n = _N, m = _M;
	for (int i = 0; i < m; i++) {
		int u = _A[i], v = _B[i];
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	return Subtask56::solve();
	// return ans;
}

void clear(){
	Subtask12::euler.clear();
	Subtask3::answer.clear();
	Subtask4::answer.clear();
	Subtask56::clear();
	FOR(int, i, 1, n) graph[i].clear();
	n = m =0;
}
