#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2> bool minize(T1 &a, T2 b) {return b < a ? ((a = b), true) : false;}
template<class T1, class T2> bool maxize(T1 &a, T2 b) {return b > a ? ((a = b), true) : false;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i++)

//{x}
// {x, y}
// {x, x+2, x+2+p}
// {x, x+p, x+p+2}

#define MAX 10'000'000
#define EST 1'000'005
#define MOD 10'420'6969

bitset<MAX+10> check;
int primes[EST], cntP;
int twins[EST], cnt2;
int triples[EST], cnt3;
ll sum[EST], sum2[EST], sum3[EST];
void sieve() {
	for (ll i = 2; i <= MAX; i++) if (not check[i]) {
		primes[++cntP] = i;
		for (ll j = i*i; j <= MAX; j += i) check[j] = true;
	}

	FOR(int, i, 2, cntP)
		if (primes[i] - primes[i-1] == 2)
			twins[++cnt2] = primes[i];
	FOR(int, i, 3, cntP)
		if (primes[i] - primes[i-1] == 2 and primes[i-1] - primes[i-2] == 2)
			triples[++cnt3] = primes[i];


	FOR(int, i, 1, cntP) sum[i] = (sum[i-1] + primes[i]) % MOD;
	FOR(int, i, 1, cnt2) sum2[i] = (sum2[i-1] + twins[i]) % MOD;
	FOR(int, i, 1, cnt3) sum3[i] = (sum3[i-1] + triples[i]) % MOD;

}
int find(int num, int *arr, int cnt) {
	return upper_bound(arr+1, arr+1+cnt, num) - arr - 1;
}

ll n, k;

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	sieve();
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		cin >> n >> k;
		if (k == 1) {cout << n % MOD << '\n'; continue;}
		if (k > 4) {cout << "0\n"; continue;}
		if (k == 2) {
			int cnt = find(n-1, primes, cntP);
			ll ans = n * cnt + MOD - sum[cnt];
			cout << ans % MOD << '\n'; continue;
		}
		if (k == 3) {
			int cnt = find(n-1, twins, cnt2);
			ll ans = n * cnt + MOD - sum2[cnt];
			cerr << n << ' ' << cnt << ' ' << ans << '\n';
			(ans *= 2) %= MOD;
			cout << ans % MOD << '\n'; continue;
		}
		int cnt = find(n-1, triples, cnt3);
		ll ans = n * cnt + MOD - sum3[cnt];
		cout << ans % MOD << '\n'; continue;
	}
}
void input(){
	//
}
void clear(){
	//
}
