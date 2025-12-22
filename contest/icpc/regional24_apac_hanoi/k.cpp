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
int a[MAX];

ll lowF(int d) {
	ll ans = 0;
	FOR(int, i, 1, n) ans += a[i] / d;
	ans += int(lower_bound(a + 1, a + 1 +n, d) - a) - 1;
	return ans;
}
int findMinD() {
	int hi = a[n], lo = a[1]/2 + a[1]%2;
	int ans = hi+1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		ll fMid = lowF(mid);
		if (fMid <= 2*n) 
			ans = mid,
			hi = mid-1;
		else
			lo = mid+1;
	}
	return max(ans-2, 1);
}

unordered_map<int, int> cnt;
pii events[MAX*10]; int cntEvent = 0;
void buildEvents(int minD) {
	FOR(int, i, 1, n) {
		const int VALUE = a[i];
		if (VALUE % minD == 0) cnt[minD]++;
		int res = VALUE / minD + !!(VALUE % minD);

		while (--res > 0) {
			int theChange = VALUE / res + !!(VALUE % res);
			if (VALUE % res == 0) cnt[theChange]++;
			events[++cntEvent] = {theChange, 1};
		}
	}
	sort(events + 1, events + 1 + cntEvent);
	int ptr = 1;
	FOR(int, i, 2, cntEvent) {
		if (events[i].fi == events[ptr].fi)
			events[ptr].se += events[i].se;
		else
			events[++ptr] = events[i];
	}
	cntEvent = ptr;
}

ll fastCal(const int d, ll &prevVal, int &ptr) {
	while (ptr <= cntEvent) {
		auto [curD, nums] = events[ptr];
		if (curD > d) break; ptr++;
		prevVal -= nums;
	}
	return prevVal + n-cnt[d];
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tests; read(tests);
	FOR(int, _, 1, tests) {
		cnt.clear(); cntEvent = 0;
		read(n); FOR(int, i, 1, n) read(a[i]); 
		sort(a+1, a+1+n);
		int minD = findMinD(); buildEvents(minD);
		
		ll val = 0;
		FOR(int, i, 1, n) val += a[i] / minD + !!(a[i] % minD);

		ll ans = LLONG_MAX; int ptr = 1;
		FOR(int, i, 1, n) if (a[i] >= minD) {
			ll cur = fastCal(a[i], val, ptr);
			minimize(ans, cur);
		}
		cout << ans << '\n';
	}
}
