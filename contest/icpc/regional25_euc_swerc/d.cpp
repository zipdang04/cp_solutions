#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 1005
int n;
int cnt[MAX];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n; FOR(int, i,1, n)  {
		int num; cin >> num;
		cnt[num]++;
	}

	int ans = 0;
	FOR(int, i, 0, 1000)
		if (cnt[i] < i) ans += cnt[i];
		else ans += cnt[i] - i;
	cout << ans << '\n';
}
