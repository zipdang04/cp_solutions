#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 105

int n;
int d[MAX];
int process(int l, int r, int minVal) {
	if (l > r) return 0;
	cerr << l << ' ' << r << ' ' << minVal << '\n';
	int pos = l;
	FOR(int, i, l, r) if (d[i] < d[pos]) pos = i;

	int ans = (minVal != d[pos]);
	ans += process(l, pos-1, d[pos]);
	ans += process(pos+1, r, d[pos]);
	return ans;
}

int main() {
	cin >> n; FOR(int, i, 1, n) cin >> d[i];
	cout << process(1, n, 0) << '\n';
}
