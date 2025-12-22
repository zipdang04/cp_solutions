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
	ll p, q; cin >> p >> q;
	FOR(ll, r, 1, 1'000'000) {
		ll a = p, b = 2 * r * (p-q) - p, c = p * r * (r - 1);
		ll delta = b * b - 4 * a * c;
		if (delta < 0) continue;

		ll sqrtDelta = max(0ll, (ll)sqrt(delta) - 5);
		while ((sqrtDelta+1) * (sqrtDelta+1) <= delta) sqrtDelta++;
		if (sqrtDelta * sqrtDelta != delta) continue;

		ll g = -1;
		ll one = -b - sqrtDelta, two = -b + sqrtDelta;
		if (one % (2*a) != 0 and two % (2*a) != 0) continue;
		if (one > 0 and one % (2*a) == 0) g = one / (2 * a);
		else if (two > 0 and two % (2*a) == 0) g = two / (2 * a);
		else continue;
		cout << r << ' ' << g << '\n';
		return 0;

	}
	cout << "impossible\n";
}
void input(){}
void clear(){}
