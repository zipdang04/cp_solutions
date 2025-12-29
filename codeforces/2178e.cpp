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

int n;
ll ASK(int L, int R) {
	cout << "? " << L << " " << R << endl;
	static ll ans; cin >> ans; return ans;
}
void ANSWER(ll ans) {
	cout << "! " << ans << endl;
}
// ll ASK(int L, int M, int R, ll sum) {
// 	assert(M < R);
// 	if (saved[{L, M}] > 0) return saved[{L, M}];
// 	if (saved[{M+1, R}] > 0) return saved[{M+1, R}];
// 	ll cur = _ASK(L, M); saved[{M+1, R}] = sum - cur;
// 	return saved[{L, M}] = cur;
// }

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	FOR(int, _, 1, t) {
		cin >> n;
		ll sum = ASK(1, n), l = 1, r = n;
		while (l < r) {
			int lo = l, hi = r-1, ansMid = l; ll need = sum / 2;
			while (lo <= hi) {
				int mid = (lo + hi) / 2;
				ll cur = ASK(l, mid);
				if (cur <= need) ansMid = mid, lo = mid+1;
				else hi = mid-1;
				if (cur == need) break;
			}
			if (ansMid - l + 1 <= r - ansMid) r = ansMid;
			else l = ansMid + 1;
			sum /= 2;
		}

		ANSWER(sum);
	}
}
