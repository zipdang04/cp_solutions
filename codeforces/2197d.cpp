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

#define MAX 200005
#define MOD 1000000007

// vector<int> divs[MAX + 5];
// void buildDiv() {
// 	FOR(int, i, 1, MAX)
// 		for (int j = i; j <= MAX; j += i)
// 			divs[j].push_back(i);
// }

int n, a[MAX]; vector<int> pos[MAX];
ll cnt(vector<int> &vI, vector<int> &vJ, int diff) {
	ll ans = 0;
	if (vI.size() < vJ.size()) {
		for (int i: vI) {
			int j = i + diff;
			if (j > n) break;
			auto it = lower_bound(vJ.begin(), vJ.end(), j);
			if (it != vJ.end() and *it == j) ans++;
		}
	} else {
		for (auto tmp = vJ.rbegin(); tmp != vJ.rend(); tmp++) {
			int j = *tmp; int i = j - diff;
			if (i < 1) break;
			auto it = lower_bound(vI.begin(), vI.end(), i);
			if (it != vI.end() and *it == i) ans++;
		}
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		cin >> n; FOR(int, i, 1, n) cin >> a[i];

		FOR(int, i, 1, n) {
			if (a[i] >= n) continue;
			pos[a[i]].push_back(i);
		}

		ll ans = 0;
		FOR(int, ai, 1, n) FOR(int, aj, 1, n/ai)
			ans += cnt(pos[ai], pos[aj], ai*aj);
		cout << ans << '\n';

		FOR(int, i, 1, n) pos[i].clear();
	}
}
