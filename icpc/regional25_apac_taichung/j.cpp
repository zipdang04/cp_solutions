#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

#define MAX 500005
#define MOD 1000000007

int n, H[MAX];
pii a[MAX], h[MAX];
vector<int> pos[MAX];
pbds_set<int> over, mids;
map<int, int> added;

ll ans[MAX];
void process(int l, int r, int hFloor, int hCeil) {
	// cerr << "prc " << l << ' ' << r << ' ' << hFloor << ' ' << hCeil << '\n';
	vector<int> cols, hs;
	auto it = added.lower_bound(l);
	for (; it != added.end() and it -> fi <= r; it++)
		cols.push_back(it -> fi),
		hs.push_back(it -> se);


	sort(hs.begin(), hs.end(), greater<int>());
	hs.push_back(hFloor);

	int curH = hCeil, cnt = 0;
	auto it1 = over.lower_bound(l), it2 = over.upper_bound(r);
	if (it1 != over.end()) {
		cnt = (it2 == over.end() ? over.size() : over.order_of_key(*it2))
			- over.order_of_key(*it1);
	}
	for (int h: hs) {
		if (curH == h) {cnt++; continue;}
		// cerr << curH << '|' << cnt << ' ';
		ans[r-cnt+1] += curH - h;
		ans[r+1] += h - curH;

		curH = h, cnt++;
	}
	// cerr << '\n';

	for (int _: cols) added.erase(_);
	for (int _: cols) over.insert(_);
}

void input();
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	mids.insert(n); mids.insert(0);
	int ptr = n;
	FOR(int, i, 1, n-1) {
		int mid = h[i].se;
		// cerr << mid << ' ' << H[mid] << '\n';
		while (ptr > 0 and a[ptr].fi > H[mid]) {
			added[a[ptr].se] = a[ptr].fi;
			// cerr << "+ " << a[ptr].fi << ' ' << a[ptr].se << '\n';
			ptr--;
		}
		if (H[mid] == 0) continue;

		int l = *(--mids.upper_bound(mid)) + 1;
		int r = *mids.upper_bound(mid);
		process(l, r, H[mid], min(H[l-1], H[r]));
		// if (i == n-1 or H[mid] != h[i+1].fi)
		// 	process(mid+1, r, H[mid], H[r]);

		mids.insert(mid);
		// FOR(int, i, 1, n) cerr << ans[i] << ".\n"[i == n];
	}
	while (ptr > 0 and a[ptr].fi > 0) {
		added[a[ptr].se] = a[ptr].fi;
		// cerr << "+ " << a[ptr].fi << ' ' << a[ptr].se << '\n';
		ptr--;
	}
	int sz = mids.size();
	FOR(int, i, 1, sz-1) {
		int l = (*mids.find_by_order(i-1)) + 1;
		int r = *mids.find_by_order(i);
		// cerr << l << ' ' << r << '\n';
		process(l, r, 0, min(H[l-1], H[r]));
		// FOR(int, i, 1, n) cerr << ans[i] << ".\n"[i == n];
	}

	FOR(int, i, 1, n) ans[i] += ans[i-1];
	FOR(int, i, 1, n) cout << ans[i] << " \n"[i == n];

}
void input() {
	cin >> n;
	FOR(int, i, 1, n) {cin >> a[i].fi; a[i].se = i;}
	FOR(int, i, 1, n-1) {cin >> H[i]; h[i] = {H[i], i};}
	H[0] = H[n] = n;

	sort(a+1, a+1+n);
	sort(h+1, h+n, [](pii a, pii b){return (a.fi != b.fi ? a.fi > b.fi : a.se < b.se);});
	FOR(int, i, 1, n) pos[a[i].fi].push_back(a[i].se);

}
