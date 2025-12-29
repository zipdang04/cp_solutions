#include "bits/stdc++.h"
using namespace std;

template<class T1, class T2>
void minimize(T1&a, T2 b) { if (b < a) a = b; }
template<class T1, class T2>
void maximize(T1&a, T2 b) { if (b > a) a = b; }

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define cntBit(num) __builtin_popcountll(num)
#define testBit(num, bit) ((num) >> (bit) & 1)

#define MAX 105

void input();
int main() {
	long long a, b; cin >> a >> b;
	long long ans = a;
	while (a <= b) {
		if (cntBit(a) < cntBit(ans)) ans = a;
		a += a & ll(-a);
	}
	cout << ans << '\n';
}
void input() {
	//
}
