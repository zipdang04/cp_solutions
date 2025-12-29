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

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	ll n; cin >> n;
	vector<ll> all;
	while (n > 0) {
		ll chunk = n & 0b0111'1111; n >>= 7;
		cerr << bitset<7>(chunk) << ' ';
		if (not all.empty()) chunk |= 0b1000'0000;
		all.push_back(chunk);
	}
	if (all.empty()) all = {0};
	reverse(all.begin(), all.end());
	for (ll i: all) cout << i << ' ';
}
void input() {}
void clear() {}
