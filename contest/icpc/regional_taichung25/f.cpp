#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define cntBit(n) __builtin_popcountll(1ll*n)
#define log2(n) (63-__builtin_clzll(1ll*n))

#define MAX 200'005

int n, a[MAX], gL[MAX], gR[MAX];

void input();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();
	FOR(int, i, 1, n) gL[i] = __gcd(gL[i-1], a[i]);
	REV(int, i, n, 1) gR[i] = __gcd(gR[i+1], a[i]);

	ll ans = gL[n];
	FOR(int, i, 2, n-1)
		ans += min(gL[i], gR[i]);
	cout << ans << '\n';
}
void input(){
	cin >> n; FOR(int, i, 1, n) cin >> a[i];
}