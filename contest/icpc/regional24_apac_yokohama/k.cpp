#include "bits/stdc++.h"
using namespace std;

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

#define MAX 105
const pair<int, int> MINIMUM = {INT_MIN, INT_MIN};
struct Best{
	pii one = MINIMUM, two = MINIMUM;
	Best(pii one, pii two): one(one), two(two) {}
	Best(pii one): one(one), two(MINIMUM) {}
	Best(): Best(MINIMUM, MINIMUM) {}
	void add(pii num) {
		if (num >= one) {two = one; one = num;}
		else maximize(two, num);
	}
	void add(Best best) {
		add(best.one); add(best.two);
	}
};

int n, m, ALL;
Best f[1 << 20], g[1 << 20];

void input();
int main() {
	input();
	REV(int, mask, ALL, 0) {
		g[mask] = f[mask];
		FOR(int, bit, 0, m-1) if (testBit(mask, bit) == false) {
			int newMask = mask | (1 << bit);
			g[mask].add(g[newMask]);
		}
	}

	int total = 0, ans1 = 0, ans2 = 0;
	auto change = [&] (pii one, pii two) {
		if (one == MINIMUM or two == MINIMUM) return;

		auto [cnt1, pos1] = one; pos1 = -pos1;
		auto [cnt2, pos2] = two; pos2 = -pos2;
		if (pos1 == pos2) return;
		if (pos1 > pos2) swap(pos1, pos2);

		if (cnt1 + cnt2 < total) return;
		if (cnt1 + cnt2 > total) {
			total = cnt1 + cnt2, ans1 = pos1, ans2 = pos2;
			return;
		}

		if (pii(pos1, pos2) < pii(ans1, ans2))
			tie(ans1, ans2) = tie(pos1, pos2);
	};
	FOR(int, mask, 0, ALL) {
		if (f[mask].one == MINIMUM) continue;
		Best one = f[mask], two = g[ALL ^ mask];
		change(one.one, two.one);
		change(one.one, two.two);
		change(one.two, two.one);
		change(one.two, two.two);
	}
	if (total == 0) cout << "No\n";
	else cout << ans1 << ' ' << ans2 << '\n';
}
void input() {
	cin >> n >> m; ALL = (1 << m)-1;
	FOR(int, i, 0, ALL) f[i] = Best();
	FOR(int, i, 1, n) {
		string s; cin >> s;
		int mask = 0; FOR(int, j, 0, m-1) mask = (mask << 1) | int(s[j] == 'Y');
		f[mask].add({cntBit(mask), -i});
	}
}
