#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template <class T1, class T2> bool minimize(T1 &a, T2 b) {
	if (b < a) return a = b, true; return false;
}
template <class T1, class T2> bool maximize(T1 &a, T2 b) {
	if (b > a) return a = b, true; return false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX_B 36
#define MAX_LEN 60
#define MOD

constexpr ll oo = 1e18 + 100;
constexpr char* DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string allowed;
ll n, k, m, D, pw[MAX_LEN+1];
inline ll mul(ll a, ll b) {
	if (a > oo / b) return oo;
	return a*b;
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int t; cin >> t;
	FOR(int, __, 1, t)  {
		cin >> n >> k >> m;
		allowed = string(DIGITS).substr(0, n);
		FOR(int, i, 1, m) {
			char c; cin >> c;
			int pos = 0; while (allowed[pos] != c) pos++;
			allowed.erase(allowed.begin() + pos);
		}
		D = n-m; assert((D == (int)allowed.size()));
		pw[0] = 1;
		FOR(int, i, 1, 60) pw[i] = mul(pw[i-1], D);
		// cerr << "hehe\n";

		if (allowed[0] == '0') k++;
		int len = 1; while (pw[len] < k) len++;
		string ans = "";
		REV(int, pos, len-1, 0) {
			int i = 0; while (k > pw[pos]) i++, k -= pw[pos];
			ans += allowed[i];
		}
		cout << ans << '\n';
	}

}
