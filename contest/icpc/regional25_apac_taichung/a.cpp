#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i++)

main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int g, c, l; cin >> g >> c >> l;
	if (g > c) swap(g, c);
	if (g > l) swap(g, l);
	if (c > l) swap(c, l);
	if (l-g >= 10) cout << "check again";
	else cout << "final " << c;
}