#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
#define fi first
#define se second
template <class T1, class T2> bool minimize(T1 &a, T2 b) {
	if (b < a) return a = b, true; return false;
}
template <class T1, class T2> bool maximize(T1 &a, T2 b) {
	if (b > a) return a = b, true; return false;
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

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 200000
#define MOD

void merge(const vector<int> &a, const vector<int> &b, vector<int> &res);
vector<int> merge(const vector<int> &a, const vector<int> &b) {
	vector<int> c; merge(a, b, c); return c;
}
class SegTree {
	inline static vector<int> it[(MAX+2) * 4];
	inline static bool stop[(MAX+2) * 4];
	int len;

	void update(int idx, int lo, int hi, int posL, int posR, int value) {
		if (hi < posL or posR < lo) return;
		if (posL <= lo and hi <= posR) {
			it[idx] = {value}; stop[idx] = true;
			return;
		}

		int y = idx << 1, mid = (lo + hi) / 2;
		if (stop[idx]) {
			// assert((int)it[idx].size() == 1);
			stop[idx] = false; stop[y] = stop[y+1] = true;
			it[y] = it[y+1] = it[idx];
		}
		update(y, lo, mid, posL, posR, value);
		update(y+1, mid+1, hi, posL, posR, value);
		merge(it[y], it[y+1], it[idx]);
	}
	vector<int> get(int idx, int lo, int hi, int posL, int posR) {
		if (hi < posL or posR < lo) return {};
		if (stop[idx] or (posL <= lo and hi <= posR)) return it[idx];
		int y = idx << 1, mid = (lo + hi) / 2;
		return merge(
			get(y, lo, mid, posL, posR),
			get(y+1, mid+1, hi, posL, posR)
		);
	}

public:
	SegTree() {}
	SegTree(int len): len(len) {
		it[1] = {}; stop[1] = true;
	}
	void update(int posL, int posR, int value) {update(1, 1, len, posL, posR, value);}
	vector<int> get(int posL, int posR) {return get(1, 1, len, posL, posR);}

	string toString() const {
		string ans = "(";
		FOR(int, i, 1, len*4) {
			ans += to_string(i) + ": {";
			for (int num: it[i]) ans += to_string(num) + ((num == *it[i].rbegin()) ? "" : " ");
			ans += "} ";
		}
		ans += ")"; return ans;
	}
} seg(MAX);

int n;
int l[MAX + 5], r[MAX + 5], h[MAX + 5];
ll pos[MAX + 5];
vector<pll> blocked[MAX + 5];
void update(int col, pll cur) {
	if (blocked[col].empty()) {blocked[col].push_back(cur); return;}
	auto it  = blocked[col].rbegin();
	if (it -> second == cur.first) it -> second = cur.second;
	else blocked[col].push_back(cur);
}
bool intersected(int col, pll cur) {
	constexpr auto check = [](pll a, pll b) {return not (a.se < b.fi or b.se < a.fi);};
	if (blocked[col].empty()) return false;
	auto it = lower_bound(blocked[col].begin(), blocked[col].end(), pll(cur.first, 0));

	if (it != blocked[col].end() and check(cur, *it) and it -> first <= cur.first) return true;
	if (it == blocked[col].begin()) return false;
	it--; return check(cur, *it) and it -> first <= cur.first;
}
int cntSide(int col, pll cur) {
	if (blocked[col].empty()) return false;

	auto [l, r] = cur;
	int it1 = lower_bound(blocked[col].begin(), blocked[col].end(), pll(l, 0)) - blocked[col].begin();
	int it2 = int(lower_bound(blocked[col].begin(), blocked[col].end(), pll(r+1, 0)) - blocked[col].begin()) - 1;
	if (it1 == (int)blocked[col].size()) return 0;
	while (it1 > 0 and blocked[col][it1-1].se >= l) it1--;
	if (it1 > it2) return 0;
	int ans = it2 - it1;
	ans += blocked[col][it1].fi > l;
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	read(n);
	FOR(int, i, 1, n) read(l[i], r[i], h[i]);
	FOR(int, i, 1, n) l[i]++;

	int ans = 0;
	FOR(int, i, 1, n) {
		vector<int> all = seg.get(l[i], r[i]);
		int minL = INT_MAX, maxR = INT_MIN, prvJ = -1;
		ll maxPos = 0, cntPos = 0;
		for (int j: all) {
			if (maximize(maxPos, pos[j])) minL = INT_MAX, maxR = INT_MIN, cntPos = 1, prvJ = j;
			else if (maxPos == pos[j]) cntPos += (l[j] - r[prvJ]) > 1, prvJ = j;

			if (pos[j] == maxPos)
				minimize(minL, l[j]), maximize(maxR, r[j]);
		}
		ans += max(0ll, cntPos - 1);
		pos[i] = maxPos + h[i]; seg.update(l[i], r[i], i);
		pll newRange(maxPos, pos[i]);
		ans += cntSide(l[i]-1, newRange);
		ans += cntSide(r[i]+1, newRange);

		if (minL != INT_MAX and l[i] < minL)
			ans += intersected(l[i]-1, newRange);
		if (maxR != INT_MIN and maxR < r[i])
			ans += intersected(r[i]+1, newRange);

		update(l[i], newRange);
		if (r[i] != l[i]) update(r[i], newRange);
	}

	cout << ans << '\n';
}

void merge(const vector<int> &a, const vector<int> &b, vector<int> &res) {
	int lenA = a.size(), lenB = b.size(), iA = 0, iB = 0;
	res.clear(); res.reserve(lenA + lenB);
	while (iA < lenA and iB < lenB)
		if (a[iA] == b[iB]) res.push_back(a[iA++]), iB++;
		else if (l[a[iA]] < l[b[iB]]) res.push_back(a[iA++]);
		else res.push_back(b[iB++]);
	while (iA < lenA) res.push_back(a[iA++]);
	while (iB < lenB) res.push_back(b[iB++]);
}
