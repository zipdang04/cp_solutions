#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template <class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template <class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 52
#define MOD

ll w, d;
int a[MAX];
void build(ll num) {
	REV(int, i, w, 1)
		a[i] = num % 3, num /= 3;
}
bool check() {
	int cnt[3] = {};
	int cur = a[1], same = 1; cnt[cur]++;
	FOR(int, i, 2, w) {
		if (not(cur == 1 or cur != a[i])) return false;
		same = a[i] == a[i-1] ? (same + 1) : 1;
		if (cur == 1 and same > 2) return false;
		cur = a[i]; cnt[cur]++;
	}

	if (abs(cnt[0] - cnt[1]) > d or abs(cnt[2] - cnt[1]) > d or abs(cnt[0] - cnt[2]) > d)
		return false;

	FOR(int, i, 1, w/2) if (a[i] != a[w-i+1]) return true;
	return false;
}

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> w >> d;
	ll total = 1; FOR(int, i, 1, w) total *= 3;
	cerr << total << '\n';

	ll ans = 0;
	FOR(int, num, 0, total-1) {
		build(num);
		if (check()) {
			ans++;
			// FOR(int, i, 1, w) cerr << a[i] <<  ' ';
			// cerr << '\n';
		}
			// FOR(int, i, 1, w) cout << char('A' + a[i]);
	}
	cout << ans << '\n';
}
void input(){}
void clear(){}
