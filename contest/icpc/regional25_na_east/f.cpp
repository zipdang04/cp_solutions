#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template <class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template <class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX
#define MOD

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	ll n; cin >> n;
	ll tmp = sqrt(n) / 2;
	while ((tmp+1) * (tmp+2) / 2 <= n) tmp++;
	if (tmp * (tmp + 1) / 2 == n) {
		cout << tmp;
		if (tmp > 1) cout << ' ' << (tmp-1) << '/' << tmp;
		cout << '\n';
	} else {
		n -= tmp * (tmp + 1) / 2 + 1; tmp++;
		ll g = __gcd(tmp, n);
		cout << tmp;
		if (n > 0) cout << ' ' <<n / g << '/' << tmp / g << '\n';
		cout << '\n';
	}
}
void input(){}
void clear(){}
