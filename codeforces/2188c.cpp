#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
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

// struct Diff {
// 	inline static unordered_map<int, int> cnt;
// 	inline static int diff = 0;
// 	void add(int num) {
// 		diff += cnt[num] == 0;
// 		cnt[num]++;
// 		diff -= cnt[num] == 0;
// 	}
// 	void del(int num) {
// 		diff += cnt[num] == 0;
// 		cnt[num]--;
// 		diff -= cnt[num] == 0;
// 	}
// 	void clear() {
// 		diff = 0; cnt.clear();
// 	}
// } nums;
ll n, a[MAX], sorted[MAX];
ll sameL, sameR;
constexpr ll OO = 1e9+7;

bool check(ll d) {
	ll mini = sorted[1], maxi = sorted[n];
	// cerr << "check " << l << ' ' << r << ' ' << d << '|' << maxi << '-' << mini << '=' << range << '\n';
	// if (d * 2 <= range) return true;

	ll keepL = 1, keepR = n;
	while (keepL <= n and sorted[keepL] + d <= maxi) keepL++;
	while (keepR >= 1 and sorted[keepR] - d >= mini) keepR--;
	if (keepL > keepR) return true;

	FOR(ll, i, keepL, keepR)
		if (a[i] != sorted[i]) {
			if (sameR - sorted[i] >= d or sorted[i] - sameL >= d) continue;
			return false;
		}
	return true;
}
ll cal() {
	ll lo = 1, hi = OO, ans = 0;
	while (lo <= hi) {
		ll mid = lo + (hi - lo) / 2;
		if (check(mid))
			ans = mid, lo = mid + 1;
		else
			hi = mid - 1;
	}
	// cerr << "cal " << l << ' ' << r << '=' << ans << '\n';
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll t; cin >> t;
	FOR(ll, _, 1, t) {
		// nums.clear();
		cin >> n; FOR(ll, i, 1, n) cin >> a[i];
		FOR(ll, i, 1, n) sorted[i] = a[i];
		sort(sorted + 1, sorted + 1 + n);

		ll ptr = 0; sameL = OO, sameR = -OO;
		FOR(ll, i, 1, n)
			if (a[i] != sorted[i])
				a[++ptr] = a[i];
			else
				sameR = a[i], sameL = (sameL == OO) ? a[i] : sameL;
		n = ptr;

		if (n <= 1) { cout << "-1\n"; continue; }
		FOR(ll, i, 1, n) sorted[i] = a[i];
		sort(sorted + 1, sorted + 1 + n);


		// FOR(ll, i, 1, n) cerr << a[i] << ".|"[i == n];
		// FOR(ll, i, 1, n) cerr << sorted[i] << ".\n"[i == n];

		ll ans = cal();
		// FOR(ll, i, 1, n) {
		// 	nums.add(a[i]); nums.del(sorted[i]);
			// cerr << _ << ' ' << i << ' ' << nums.diff << '\n';
		// 	if (nums.diff == 0) {
		// 		minimize(ans, cal(prv + 1, i));
		// 		prv = i;
		// 	}
		// }
		if (ans == OO) ans = -1;

		cout << ans << '\n';
		// assert(nums.diff == 0);
	}
}
