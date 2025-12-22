#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 800005

int n, k, a[MAX];
int cnt[MAX];

set<int> zeroes;
map<int, int> excess;
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		zeroes.clear(), excess.clear();
		cin >> n >> k; FOR(int, i, 1, n) cin >> a[i];
		FOR(int, i, 0, 4*n) cnt[i] = 0;

		FOR(int, i, 1, n) cnt[a[i]]++;
		int maxi = 1; FOR(int, i, 1, n) maximize(maxi, a[i]);
		FOR(int, value, 1, 4*n) if (cnt[value] == 0) zeroes.insert(value);

		int ans = 0;
		REV(int, value, maxi, 1) {
			if (cnt[value] <= k) {
				if (cnt[value] > 1) excess[value] = cnt[value] - 1;
				continue;
			}

			int pos = value, remain = cnt[value] - 1; cnt[pos] = 1;
			int countIteration = 0;
			while (++countIteration) {
				auto itZero = zeroes.upper_bound(pos);
				auto itExcs = excess.upper_bound(pos);
				// zero < excess
				if (itExcs == excess.end() or *itZero < itExcs -> first) {
					int newPos = *itZero; zeroes.erase(itZero);
					countIteration += newPos - pos - 1;
					// at this point, cnt[newPos] = remain
					if (remain <= k) {
						cnt[newPos] = remain;
						if (remain > 1) excess[newPos] = remain - 1;
						break;
					}
					// otherwise still moving
					cnt[newPos] = 1; remain--;
					pos = newPos; continue;
				}
				// excess < zero => accumulate to "remain"
				auto [newPos, curCnt] = *itExcs;
				countIteration += newPos - pos - 1;
				remain += curCnt; cnt[newPos] = 1;
				pos = newPos; excess.erase(newPos);
			}
			maximize(ans, countIteration);
		}
		cout << ans << '\n';
	}
}
