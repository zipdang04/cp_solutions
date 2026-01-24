#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> se;
#define fi first
#define se second

template <class T1, class T2> bool minimize(T1 &a, T2 b) {
	return b < a ? (a = b, true) : false;
}
template <class T1, class T2> bool maximize(T1 &a, T2 b) {
	return b > a ? (a = b, true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 100005
#define MOD

int n, k, extra = 0;
int a[MAX];


void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();

		int pairs = 0, l = 1, r = n;
		while (l < r) {
			if (a[l] + a[r] >= k) {r--; continue;}
			pairs++, l++, r--;
		}
		int best = n + extra;
		FOR(int, i, 0, pairs) {
			int p2 = i, p1 = n - p2*2, p3 = extra;

			int p23 = min(p2, p3);
			p2 -= p23, p3 -= p23;
			int p12 = min(p1, p2);
			p1 -= p12, p2 -= p12;
			int p13 = min(p1, p3);
			p1 -= p13, p3 -= p13;
			// self consume
			p1 = p1 / 2 + p1 % 2;

			int curAns = p1 + p2 + p3 + p23 + p12 + p13;
			minimize(best, curAns);
		}
		cout << best-1 << '\n';

		clear();
	}
}
void input(){
	cin >> n >> k;
	FOR(int, i, 1, n) cin >> a[i];

	sort(a+1, a+1+n);
	int first = lower_bound(a+1, a+1+n, k) - a;
	if (first <= n) {
		extra = n - first + 1;
		n = first-1;
	} else {
		extra = 0;
	}
}
void clear(){
	extra = 0;
}
