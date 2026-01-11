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

randomize;
struct Rand {
	ll next(ll n) {
		return mt() % n;
	}
	ll next(ll l, ll r) {
		return l + next(r-l+1);
	}
} rnd;

int N, H[MAX], K;
int getSubtask() {
	if (N <= 100) return 1;
	if (N <= 2000) return 3;
	bool is2 = true;
	FOR(int, i,1, N) is2 &= H[i] <=10;
	if (is2) return 2;
	return 4;
}

bool check(int i, int j, int k) {
	// cerr << "checking: " <<  i << ' ' << j << ' ' << k << '\n';
	if (i < 0 or i >= N) return false;
	if (j < 0 or j >= N) return false;
	if (k < 0 or k >= N) return false;
	if (i == j or j == k or i == k) return false;
	// cerr << i << ' ' << j << ' ' << k << '|';
	int a = abs(k-i), b = abs(k-j), c = abs(j-i);
	i = H[i], j = H[j], k = H[k];
	// cerr << i << ' ' << j << ' ' << k << '|' << a << ' ' << b << ' ' << c << '\n';

	if (i > j) swap(i, j);
	if (i > k) swap(i, k);
	if (j > k) swap(j, k);
	if (a > b) swap(a, b);
	if (a > c) swap(a, c);
	if (b > c) swap(b, c);
	// cerr << (a == i and b == j and c == k ? "oke" : "failed") << '\n';
	return a == i and b == j and c == k;
}

namespace Subtask4 {
	ll solve() {
		// cerr << "here" << N << "\n";
		ll ans = 0;
		for (int k = 2; k < N; k++) {
			// H[k] = k-i
			int i = k - H[k];
			if (i < 0 or i > k-2) continue;

			// case 1: H[i] == j-i
			int j1 = H[i] + i;
			// cerr << "> " << i << j1 << k << '\n';
			if (i < j1 and j1 < k) ans += check(i, j1, k);
			// case 1: H[i] == k-j
			int j2 = k - H[i];
			// cerr << "> " << i << j2 << k << '\n';
			if (j2 != j1 and i < j2 and j2 < k) ans += check(i, j2, k);
		}
		return ans;
	}
}

namespace Subtask123 {
	set<pair<int, pair<int, int>>> all;
	void add(int i, int j, int k) {
		if (i > j) swap(i, j);
		if (i > k) swap(i, k);
		if (j > k) swap(j, k);
		all.insert({i, {j, k}});
	}
	ll solve(bool is2) {
		FOR(int, i, 0, N-1)
		FOR(int, j, i+1, is2 ? min(N-1, i+10) : N-1) {
			// H[i] = i-k
			int k = i - H[i];
			if (check(i, j, k)) add(i, j, k);
			// H[i] = k-i
			k = i + H[i];
			if (check(i, j, k)) add(i, j, k);
			// H[i] = j-k
			k = j - H[i];
			if (check(i, j, k)) add(i, j, k);
			// H[i] = k-j
			k = j + H[i];
			if (check(i, j, k)) add(i, j, k);
			// H[i] = |i-j|
			if (H[i] == abs(i - j)) {
				// H[j] = i-k
				k = i - H[j];
				if (check(i, j, k)) add(i, j, k);
				// H[j] = k-i
				k = i + H[j];
				if (check(i, j, k)) add(i, j, k);
				// H[j] = j-k
				k = j - H[j];
				if (check(i, j, k)) add(i, j, k);
				// H[j] = k-j
				k = j + H[j];
				if (check(i, j, k)) add(i, j, k);
			}
		}
		ll answer = all.size();
		return answer;
	}
}


long long count_triples(std::vector<int> _H) {
	N = _H.size(); FOR(int, i, 0, N-1) H[i] = _H[i];

	int subtask = getSubtask();
	switch (getSubtask()) {
		case 1:
		case 2:
		case 3:
			return Subtask123::solve(subtask == 2);
			break;
		default:
			return Subtask4::solve();
	}
}

std::vector<int> construct_range(int _M, int _K) {
	N = _M; K = _K;
	for (int i = 0; i < N; i++)
		H[i] = rnd.next(1, 3);
	return vector<int>(H, H + N);
}
