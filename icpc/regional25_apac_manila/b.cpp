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

#define MAX_K 26
#define MAX_Q 100'005

struct Data {
	inline static ll K;
	inline static ll get(ll pos) {
		ll c = (pos / K + pos % K) % K;
		return c;
	}

	ll cnt[MAX_K] = {};
	ll start = 0, len = 0;
	Data(): start(0), len(0) {};
	Data(ll start, ll len): start(start), len(len) {

		char c = get(start);
		while (start % K and len > 0)
			cnt[c]++, len--, (c += 1) %= K, start++;
		if (len == 0) return;
		ll pkg = len / K; c = get(start + pkg*K), len %= K;
		FOR(ll, i, 0, K-1) cnt[i] += pkg;
		FOR(ll, i, 0, len-1) cnt[c]++, (c += 1) %= K;

	}
	inline static Data combine(const Data one, const Data two) {
		Data ans;
		FOR(ll, i, 0, K-1) ans.cnt[i] = one.cnt[i] + two.cnt[i];
		return ans;
	}
};

struct Query {
	char type; ll i, a, b;
} queries[MAX_Q];

ll n, k, q;
ll start[MAX_Q*2], cntStart;

inline static Data _it[MAX_Q*2*4];
class SegTree {
private:
	ll len;
	void update(ll idx, ll lo, ll hi, ll posL, ll posR, ll st) {
		if (posR < lo or hi < posL) return;
		if (posL <= lo and hi <= posR) {
			ll len = start[hi+1] - start[lo];
			_it[idx] = Data(st + (start[lo]-start[posL]), len);
			return;
		}

		const ll y = idx << 1, mid = (lo + hi) >> 1;
		const ll lenL = start[mid+1] - start[lo];
		if (_it[idx].len > 0) {
			ll oriStart = _it[idx].start;
			_it[y] = Data(oriStart, lenL);
			_it[y+1] = Data(oriStart + lenL, start[hi+1] - start[mid+1]);
		}
		update(y, lo, mid, posL, posR, st);
		update(y+1, mid+1, hi, posL, posR, st);
		_it[idx] = Data::combine(_it[y], _it[y+1]);
	}
	Data get(ll idx, ll lo, ll hi, ll posL, ll posR) {
		if (hi < posL or posR < lo) return Data();
		if (posL <= lo and hi <= posR) return _it[idx];
		if (_it[idx].len > 0) {
			ll L = max(start[posL], start[lo]), R = min(start[posR+1]-1, start[hi+1]-1);
			return Data(_it[idx].start + L-start[lo], R-L+1);
		}

		ll y = idx << 1, mid = (lo + hi) >> 1;
		return Data::combine(
			get(y, lo, mid, posL, posR),
			get(y+1, mid+1, hi, posL, posR)
		);
	}
public:
	SegTree() {}
	SegTree(ll len): len(len) {FOR(ll, i, 1, len*4) _it[i] = Data();}
	void update(ll posL, ll posR, ll sta) {update(1, 1, len, posL, posR, sta);}
	Data get(ll posL, ll posR) {return get(1, 1, len, posL, posR);}
} seg;

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();

	seg = SegTree(cntStart);
	FOR(ll, i, 1, q) {
		auto [type, pos, a, b] = queries[i];
		if (type == '+')
			seg.update(a, b, pos);
		else {
			Data ans = seg.get(a, b);
			FOR(ll, i, 0, k-1) cout << ans.cnt[i] << " \n"[i == k-1];
		}
	}
}
void input(){
	cin >> k >> n >> q; Data::K = k;
	FOR(ll, i, 1, q) {
		char type; int pos, a, b;
		cin >> type;
		if (type == '+') {cin >> pos; pos--;}
		cin >> a >> b;
		queries[i] = {type, pos, a, b};
		start[++cntStart] = a;
		start[++cntStart] = b+1;
	}

	sort(start + 1, start + 1 + cntStart);
	cntStart = unique(start + 1, start + 1 + cntStart) - start - 1;
	auto find = [&](int value) {return lower_bound(start+1, start+1+cntStart, value) - start;};
	FOR(int, i, 1, q) {
		queries[i].a = find(queries[i].a);
		queries[i].b = find(queries[i].b+1) - 1;
	}
}
