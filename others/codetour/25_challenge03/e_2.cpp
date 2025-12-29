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

int N, M, Q;
vector<int> v[MAX];
tuple<int, ll, vector<int>> queries[MAX];

ll dist(vector<int> &a, vector<int> &b) {
	// cerr << "in " << a.size() << ' ' << b.size();
	ll ans = 0, tmp;
	FOR(int, i, 0, M-1) {
		// cerr << i << '\n';
		tmp = a[i] - b[i];
		ans += tmp * tmp;
	}
	// cerr << "out\n";
	return ans;
}

pair<ll, int> all[MAX];
vector<int> q1(int K, vector<int> &V){
	vector<int> ans;
	FOR(int, i, 0, N-1)
		all[i] = {dist(V, v[i]), i};
	// cerr << "here\n";
	sort(all, all + N);
	FOR(int, i, 0, min(N, K)-1)
		ans.push_back(all[i].second);
	sort(ans.begin(), ans.end());
	return ans;
}
vector<int> q2(ll D, vector<int> &V){
	D *= D;
	vector<int> ans;
	FOR(int, i, 0, N-1)
		if (dist(V, v[i]) <= D)
			ans.push_back(i);
	return ans;
}

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	// cerr << "done\n";
	FOR (int, _, 1, Q) {
		// cerr << _ << '\n';
		auto &[type, val, v] = queries[_];
		if (type == 1) {
			vector<int> res = q1(val, v);
			for (int i: res) cout << i << ' '; cout << '\n';
		}
		else {
			vector<int> res = q2(val, v);
			for (int i: res) cout << i << ' '; cout << '\n';
		}
	}
}
void input() {
	read(N, M, Q);
	FOR(int, i, 0, N-1) {
		v[i].resize(M);
		FOR(int, j, 0, M-1) read(v[i][j]);
	}
	FOR(int, i, 1, Q) {
		int a, b; vector<int> c(M);
		read(a, b); FOR(int, i, 0, M-1) read(c[i]);
		// // cerr << a << ' ' << b << '|'; FOR(int, i, 0, M-1) cerr << c[i] << " \n"[i == M-1];
		queries[i] = {a, b, c};
	}
}