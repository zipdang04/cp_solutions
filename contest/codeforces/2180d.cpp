#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
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

#define MAX 2000001
#define MOD 1000000007

ll n, x[MAX], mini[MAX], maxi[MAX];

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll tests; cin >> tests;
	FOR(ll, _, 1, tests) {
		cin >> n; FOR(ll, i, 1, n) cin >> x[i];
		// FOR(ll, i, 1, n) mini[i] = 0;
		// maxi[1] = x[2] - x[1]; maxi[n] = x[n] - x[n-1];
		// FOR(ll, i, 2, n-1) maxi[i] = min(x[i+1] - x[i], x[i] - x[i-1]);
		// FOR(ll, i, 1, n-1)
		// 	maximize(mini[i], x[i+1] - x[i] - maxi[i+1]);
		// FOR(ll, i, 2, n)
		// 	maximize(mini[i], x[i] - x[i-1] - maxi[i-1]);

		// ll ans = 0;
		// FOR(ll, i, 1, n) cout << mini[i] << '/' << maxi[i] << " \n"[i == n];
		ll l = 0, r = x[2] - x[1];
		ll ans = 0;
		stack<pll> st;
		st.push({l, r});
		FOR(ll, i, 2, n) {
			ll newL = max((x[i] - x[i-1]) - r, 0ll),
				newR = max((x[i] - x[i-1]) - l, 0ll);
			// cerr << _ << '|' << i << ' ' << newL << ' ' << newR << '\n';
			if (newL >= newR) {
				st.pop(); l = 0, r = x[i] - x[i-1];
				st = stack<pll>();

			} else {
				ans++, tie(l, r) = tie(newL, newR);
				st.push({l, r});
			}
		}
		cout << ans << '\n';
	}
}
