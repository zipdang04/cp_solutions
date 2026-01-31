#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define first fi
#define second se

template <class T1, class T2> bool minimize(T1& a, T2 b) {return b < a ? (a=b, true) : false;}
template <class T1, class T2> bool maximize(T1& a, T2 b) {return b > a ? (a=b, true) : false;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)
#define all(v) v.begin(), v.end()
#define all(v, l, r) v.begin() + l, v.begin() + r + 1

#define MAX
#define MOD

#define b00 0
#define b01 1
#define b02 2
#define b10 3
#define b11 4
#define b12 5
#define b20 6
#define b21 7
#define b22 8

int ans[9], cur[9] = {};
void copy() {
	FOR(int, i, 0, 8) ans[i] = cur[i];
}
void do00(ll times) {
	if (times == 0) return;
	memset(cur, 0x3f, sizeof cur);
	
	cur[b00] = cur[b22] = min({
		ans[b00], ans[b11], ans[b12], ans[b21], ans[b22]
	});
	cur[b02] = min({
		ans[b01] + 1, ans[b10], ans[b20]
	});
	cur[b20] = min({
		ans[b10] + 1, ans[b01], ans[b02]
	});
	
	if (--times & 1) swap(cur[b02], cur[b20]);
	copy();
}
void do01(ll ________times = 0) {
	assert(________times == 0);
	memset(cur, 0x3f, sizeof cur);

	cur[b00] = cur[b22] = min({
		ans[b01] + 2, ans[b10] + 1, ans[b20] + 1
	});
	cur[b01] = min({
		ans[b00], ans[b11], ans[b12], ans[b21], ans[b22]
	});
	cur[b20] = cur[b01] + 1;
	cur[b21] = min({
		ans[b01], ans[b02], ans[b10]
	});
	copy();
}
void do10(ll ________times = 0) {
	assert(________times == 0);
	memset(cur, 0x3f, sizeof cur);

	cur[b00] = cur[b22] = min({
		ans[b10] + 2, ans[b01] + 1, ans[b02] + 1
	});
	cur[b10] = min({
		ans[b00], ans[b11], ans[b21], ans[b12], ans[b22]
	});
	cur[b02] = cur[b10] + 1;
	cur[b12] = min({
		ans[b10], ans[b20], ans[b01]
	});
	copy();
}
void do11(ll ________times = 0) {
	assert(________times == 0);
	memset(cur, 0x3f, sizeof cur);

	cur[b00] = cur[b22] = ans[b00] + 2;
	
	cur[b01] = min({
		ans[b01] + 1, ans[b02] + 1, ans[b10] + 2
	});
	cur[b10] = min({
		ans[b10] + 1, ans[b20] + 1, ans[b01] + 2
	});

	cur[b02] = min({
		ans[b01] + 3, ans[b10] + 2, ans[b20] + 2
	});
	cur[b20] = min({
		ans[b10] + 3, ans[b01] + 2, ans[b02] + 2
	});

	cur[b11] = min({
		ans[b00], ans[b11], ans[b12], ans[b21], ans[b22],
	});

	copy();
}

ll n, l;
map<ll, int> state;

void input();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> l;
	FOR(int, i, 1, n) {
		ll r, c; cin >> r >> c; r--;
		state[c] += 1 << r;
	}
	state[l] += 0;
	
	memset(ans, 0x3f, sizeof ans);
	ans[b22] = 0; ll pos = 0;
	for (auto [where, type]: state) {
		// cerr << where << ' ' << type << '\n';
		do00(pos - where - 1);
		// FOR(int, i, 0, 8) cerr << i/3<< i % 3 << '.' << (ans[i] > 1e9 ? "_" : to_string(ans[i])) << " \n"[i == 8];
		if (type == 0b01) do01();
		else if (type == 0b10) do10();
		else do11();
		// FOR(int, i, 0, 8) cerr << i/3<< i % 3 << '.' << (ans[i] > 1e9 ? "_" : to_string(ans[i])) << " \n"[i == 8];
		// cerr.flush();
		pos = where;
	}
	ll answer = min({
		ans[b12], ans[b21], ans[b11], ans[b22]
	});
	if (answer > 1e9) cout << "no\n";
	else cout << answer << '\n';
}
void input() {
	// 
}