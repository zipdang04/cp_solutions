#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type,less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<class T1, class T2>
void minimize(T1&a, T2 b) { if (b < a) a = b; }
template<class T1, class T2>
void maximize(T1&a, T2 b) { if (b > a) a = b; }

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define cntBit(num) __builtin_popcount(num)
#define testBit(num, bit) ((num) >> (bit) & 1)

#define MAX 100'005
// Hilbert
// ) (
// | |
// U-U

struct Range {
	int l, r, i;
	Range(){} Range(int l, int r, int i): l(l), r(r), i(i) {}
	bool operator < (Range oth) const {
		return (l != oth.l) ? (l < oth.l) : (r < oth.r);
	}
} allRanges[MAX];

vector<int> divs[MAX+1];
void buildDivs() {
	for (int i = 1; i < MAX; i++)
		for (int j = i; j < MAX; j += i)
			divs[j].push_back(i);
}

int n, q;
int a[MAX], ans[MAX];

class SegQuery{
	inline static int it[MAX*4] = {};
	int len = 0;
	void update(int idx, int l, int r, int pos, int event) {
		if (l == r) {
			minimize(it[idx], event);
			return;
		}

		int y = idx << 1, mid = (l+r)/2;
		if (pos <= mid)
			update(y, l, mid, pos, event);
		else
			update(y+1, mid+1, r, pos, event);
		it[idx] = min(it[y], it[y+1]);
	}
	int get(int idx, int l, int r, int posL, int posR) {
		if (r < posL || posR < l) return 1e9;
		if (posL <= l && r <= posR) return it[idx];
		int y = idx << 1, mid = (l+r)/2;
		return min(
			get(y, l, mid, posL, posR),
			get(y+1, mid+1, r, posL, posR)
		);
	}
public:
	SegQuery() {}
	SegQuery(int len): len(len) {
		memset(it, 0x3f, sizeof(it));
	}

	void update(int pos, int event) {update(1, 1, len, pos, event);}
	int get(int l, int r) {return get(1,1,len,l,r);}
} segQuery;

vector<int> posis[MAX+1];
vector<pii> events[MAX];
void buildEvent() {
	FOR(int, i, 1, n) {
		int num = a[i];
		for (int d: divs[num])
			posis[d].push_back(i);
	}

	segQuery = SegQuery(n);

	REV(int, d, MAX-1, 1) {
		int sz = posis[d].size();
		FOR(int, i, 0, sz-2) {
			int l = posis[d][i], r = posis[d][i+1];
			if (segQuery.get(l, r) <= r) continue;
			segQuery.update(l, r);
			events[1].push_back({r,+d});
			events[l+1].push_back({r,-d});
		}
	}
}



class SegTree{
	inline static int it[MAX*4] = {};
	inline static multiset<int> nums[MAX] = {};
	int len = 0;
	void update(int idx, int l, int r, int pos, int event) {
		if (l == r) {
			if (event > 0) nums[pos].insert(event);
			else nums[pos].erase(nums[pos].find(-event));
			it[idx] = nums[pos].empty() ? 0 : *nums[pos].rbegin();
			return;
		}

		int y = idx << 1, mid = (l+r)/2;
		if (pos <= mid)
			update(y, l, mid, pos, event);
		else
			update(y+1, mid+1, r, pos, event);
		it[idx] = max(it[y], it[y+1]);
	}
	int get(int idx, int l, int r, int posL, int posR) {
		if (r < posL || posR < l) return 0;
		if (posL <= l && r <= posR) return it[idx];
		int y = idx << 1, mid = (l+r)/2;
		return max(
			get(y, l, mid, posL, posR),
			get(y+1, mid+1, r, posL, posR)
		);
	}
public:
	SegTree() {}
	SegTree(int len): len(len) {
		memset(it, 0, sizeof(it));
	}

	void update(int pos, int event) {update(1, 1, len, pos, event);}
	int get(int l, int r) {return get(1,1,len,l,r);}
} seg;
void processEvents() {
	int ptr = 1;
	int cnt = 0;
	FOR(int, curL, 1, n) {
		for (auto [posR, event]: events[curL]) {
			seg.update(posR, event); cnt++;
		}

		while (ptr <= q) {
			auto [l, r, i] = allRanges[ptr];
			if (l > curL) break; ptr++;
			ans[i] = seg.get(l,r);
		}
	}
}

void input();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();
	buildDivs();
	buildEvent();
	processEvents();

	FOR(int, i, 1, q) cout << ans[i] << "\n";
}
void input() {
	cin >> n; FOR(int, i, 1, n) cin >> a[i];
	cin >> q; FOR(int, i, 1, q) {
		int l, r; cin >> l >> r;
		allRanges[i] = {l, r, i};
	}
	seg = SegTree(n);
	sort(allRanges + 1, allRanges + 1 + q);

}
