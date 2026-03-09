#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2> bool minimize(T1 &a, T2 b) {
	return (b < a) ? (a = b, true) : false;
}
template<class T1, class T2> bool maximize(T1 &a, T2 b) {
	return (b > a) ? (a = b, true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 
#define MOD

// nhận xét: số giá trị khác nhau không quá sqrt(n)

int n; string s; 
unordered_map<ll, int> cntH, cntV;
void build (const string &s, unordered_map<ll, int> &cnt) {
	int ptr = 1;
	for (char c: s) 
		if (c == '0') ptr++;
		else {cnt[ptr]++; ptr = 1;}
	cnt[ptr]++;
	
	// appear even times => remove
	vector<int> removing;
	for (auto [key, value]: cnt)
		if (value % 2 == 0) removing.push_back(key);
	
	for (int key: removing)
		cnt.erase(key);
}

void input(), clear();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	cin >> s; build(s, cntH);
	cin >> s; build(s, cntV);

	ll ans = 0;
	for (auto [k1, _]: cntH)
	for (auto [k2, _]: cntV) 
		ans ^= k1 * k2;
	
	cout << ans << '\n';
}
void input() {}
void clear() {}