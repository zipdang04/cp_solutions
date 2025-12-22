#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define log2ll(n) (63 - __builtin_clzll(1ll*n))

#define MAX 500005
#define ALP 26

/*
 * what we need:
 * - how frequently each letter appears => prefix sum
 * - how similar from two consecutive same char
 * - get those two
 */

int n, q;
string s;

int sum[MAX][ALP + 1];
vector<int> pos[ALP + 1];
vector<int> similar[ALP + 1];
void buildSimilar() {
	FOR(int, i, 1, n) {
		FOR(int, c, 1, ALP) sum[i][c] = sum[i-1][c];
		sum[i][s[i]]++;
	}
	FOR(int, i, 1, n) pos[s[i]].push_back(i);
	FOR(int, c, 1, ALP) {
		int sz = pos[c].size();
		similar[c].reserve(sz);
		FOR(int, i, 0, sz - 2) {
			int p1 = pos[c][i], p2 = pos[c][i+1], same = 1;
			while (p1 + same < p2 and s[p1 + same] == s[p2 + same]) same++;
			similar[c].push_back(same);
		}
	}
}

#define BIT 18
vector<int> rmq[ALP + 1][BIT + 1];
void buildRMQ() {
	FOR(int, c, 1, ALP) {
		const int len = similar[c].size();
		FOR(int, bit, 0, BIT) rmq[c][bit].resize(len);

		FOR(int, i, 0, len-1) rmq[c][0][i] = similar[c][i];
		FOR(int, bit, 1, BIT) {
			int FULL = 1 << bit; int HALF = FULL >> 1;
			for (int l = 0, r = FULL-1; r < len; l++, r++)
				rmq[c][bit][l] = min(
					rmq[c][bit-1][l],
					rmq[c][bit-1][l + HALF]
				);
		}
	}
}
int get(int c, int l, int r) {
	int len = r-l+1, bit = log2ll(len);
	assert((1 << (bit)) <= len);
	assert((1 << (bit+1)) >= len);
	return min(
		rmq[c][bit][l],
		rmq[c][bit][r-(1<<bit)+1]
	);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> q >> s;
	s = " " + s; FOR(int, i, 1, n) {s[i] -= 'a'; s[i]++;}
	FOR(int, i, 1, n) assert((1 <= s[i] and s[i] <= ALP));
	// FOR(int, i, 1, n) cerr << int(s[i]) << " \n"[i == n];

	buildSimilar();
	buildRMQ();

	FOR(int, _, 1, q) {
		int l, r; cin >> l >> r;
		int best = 0; FOR(int, c, 1, ALP) maximize(best, sum[r][c] - sum[l-1][c]);
		// cerr << _ << ' ' << best << '\n';
		assert(best > 0);
		if (best == 1) { cout << r-l+1 << '\n'; continue; }

		int ans = 0;
		FOR(int, c, 1, ALP) if (sum[r][c] - sum[l-1][c] == best) {
			// cerr << "> " << c << '\n';
			int i1 = lower_bound(pos[c].begin(), pos[c].end(), l) - pos[c].begin(),
				i2 = upper_bound(pos[c].begin(), pos[c].end(), r) - pos[c].begin() - 1;
			assert(i1 < i2); assert(l <= pos[c][i1]); assert(pos[c][i2] <= r);
			assert((i2 - i1 + 1 == best));
			int curLFS = get(c, i1, i2-1);
			int last = pos[c][i2], same = similar[c][i2-1];
			if (last + same - 1 > r) same = r-last+1;
			minimize(curLFS, same);
			// FOR(int, i, i1, i2-1) minimize(curLFS, similar[c][i]);
			maximize(ans, curLFS);
		}
		cout << ans << '\n';
	}
}
