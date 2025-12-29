#include <bits/stdc++.h>
using namespace std;

template<class T1, class T2> bool minimize(T1 &a, T2 b) {return b < a ? (a = b, true) : false;}
template<class T1, class T2> bool maximize(T1 &a, T2 b) {return b > a ? (a = b, true) : false;}

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define fi first
#define se second

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 16
ll f[MAX + 5][MAX + 5];
void dp() {
	memset(f, -0x3f, sizeof f);
	f[1][1] = 0;
	f[1][2] = 0;
	FOR(int, len, 2, MAX) {
		f[len][1] = 0;
		// cerr << len << '|';
		FOR(int, pw, 2, len+1) {
			if (f[len-1][pw-1] >= 0)
				f[len][pw] = f[len][pw-1] + f[len-1][pw-1] + (1 << pw);
			// cerr << f[len][pw] << " \n"[pw == len+1];
		}
	}
}
bitset<1'000'005> avail;
vector<pii> trace[1'000'005];
int best = 0;
void build(int k) {
	avail[0] = true;
	FOR(int, len, 2, k) {
		REV(int, val, 999'999, 0) if (avail[val]) {
			FOR(int, pw, 2, len+1) {
				int newVal = val + f[len][pw] / 4;
				if (avail[newVal]) continue;
				maximize(best, newVal * 4);
				avail[newVal] = true; trace[newVal].push_back({len, pw});
			}
		}
	}
	cerr << best << '\n';
}

vector<pii> test(ll sum) {
	if (sum / 4 > best) return {};
	if (not avail[sum / 4]) return {};
	vector<pii> ans;
	int prvLen = 100;
	while (sum > 0) {
		int i = (int)trace[sum/4].size() - 1;
		while (trace[sum/4][i].fi >= prvLen) i--;
		auto [len, pw] = trace[sum / 4][i];
		sum -= f[len][pw]; ans.push_back({len, 1 << pw});
		prvLen = len;
	}
	sort(ans.begin(), ans.end(), greater<pii>());
	return ans;
}

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests, k; cin >> tests >> k;
	dp();
	build(k);
	FOR(int, _, 1, tests) {
		// cerr << _ << '\n';
		ll sum; cin >> sum;
		if (sum % 4 != 0 or sum > best) {cout << "-1\n"; continue;}
		vector<pii> ans = test(sum);
		while (ans.empty()) {sum += 4; ans = test(sum);}

		cout << ans.size() << ' ';
		for (auto [_, i]: ans) cout << i << ' ';
		cout << '\n';
	}
}
void input() {}
void clear() {}
