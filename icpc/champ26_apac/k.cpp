#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2> bool minimize(T1 &a, T2 b) {
	return (b < a) ? ((a=b), true) : false;
}
template<class T1, class T2> bool maximize(T1 &a, T2 b) {
	return (b > a) ? ((a=b), true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 
#define MOD 

int n;
string s;

bool check(const int ans, int zeroes, int ones, int dH, int dM) {
	buildH:
	int remainH = ans;
	// build 06 07 07 08 09
	int H = min({zeroes, dM, remainH});
	zeroes -= H, dM -= H, remainH -= H;
	if (remainH == 0) goto buildM;
	
	if (zeroes == 0) {
		// build 11
		H = min(remainH, ones / 2);
		remainH -= H, ones -= H * 2;
	} else { // dM == 0
		// build 02 03 04 05
		H = min({zeroes, dH, remainH});
		remainH -= H, zeroes -= H, dH -= H;
		// build 12 13 14 15
		H = min({ones, dH, remainH});
		remainH -= H, ones -= H, dH -= H;
		// build 00 01 10 11
		H = min(remainH, (ones+zeroes) / 2);
		remainH -= H; 
		if (H*2 <= zeroes) zeroes -= H*2;
		else {ones -= H*2 - zeroes; zeroes = 0;}
	}

	if (remainH) return false;
//=========//=========//=========//=========//=========//=========
	buildM:
	int l = zeroes + ones + dH, r = dM;
	int res = min(l, r); l -= res, r -= res;
	res += l / 2;
	return res >= ans;
}

void input(), clear();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		int cnt[10] = {};
		for (char c: s) cnt[c - '0']++;
		int ones = cnt[1], zeroes = cnt[0];
		int dH = cnt[2] + cnt[3] + cnt[4] + cnt[5];
		int dM = cnt[6] + cnt[7] + cnt[8] + cnt[9];


		int ans = 0;
		while (check(ans+1, zeroes, ones, dH, dM)) ans++;
		cout << ans << '\n';
	}
}
void input() {
	cin >> n >> s;
} 
void clear() {}