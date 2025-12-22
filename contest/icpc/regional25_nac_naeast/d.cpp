#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template <class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template <class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 20
#define MOD

int n;
ll a[MAX];

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n; FOR(int, i, 1, n) cin >> a[i];
	sort(a + 1, a + 1 + n, greater<ll>());
	ll total = 0; FOR(int, i, 1, n) total += a[i];
	ll THRESHOLD = total / 2 + 1;
	int rounds = 0;
	REV(int, i, n, 3) {
		rounds++; a[2] += a[i];
		if (a[2] >= THRESHOLD) {
			cout << rounds << '\n';
			return 0;
		}
	}
	cout << "IMPOSSIBLE TO WIN\n";
}
void input(){}
void clear(){}
