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

#define MAX 100005
#define MOD 

ll n;
ll a[MAX];
ll newA[MAX];

void input(), clear();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	ll n; cin >> n;
	FOR(ll, i, 1, n) cin >> a[i];
	newA[1] = a[1];
	FOR(ll, i, 2, n) newA[i] = newA[i-1] + abs(a[i] - a[i-1]);
	FOR(int, i, 1, n) cerr << newA[i] << '\n';
	
	ll diff = newA[n] - newA[1];
	
	ll d = 0;
	FOR(int, i, 2, n) d = __gcd(d, abs(a[i] - a[i-1]));
	cerr << (d*=2) << '\n';
	ll ans = newA[1];
	if (d) {ans %= d; if (ans == 0) ans = d;}
	ans += diff; cout << ans << '\n';
}
void input() {} 
void clear() {}