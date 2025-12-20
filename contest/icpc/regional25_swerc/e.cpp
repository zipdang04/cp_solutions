#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 200005
#define MOD

string s;
int n, q, cnt8[MAX];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> q >> s;
	FOR(int, i, 1, n) cnt8[i] = cnt8[i-1] + (s[i-1] == '8');

	FOR(int, _, 1, q) {
		int l, r, x, y; cin >> l >> r >> x >> y;
		x = abs(x), y = abs(y);
		int len = r-l+1, dist = len + cnt8[r] - cnt8[l-1];
		if (x <= len and y <= len and x + y <= dist) cout << "YES\n";
		else cout << "NO\n";
	}
}
