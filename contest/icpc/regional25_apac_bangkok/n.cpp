#include <bits/stdc++.h>
using namespace std;

template<class T1, class T2> void minimize(T1& a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1& a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int n, a, b; cin >> n >> a >> b;
	a++, b = n-b;
	cout << abs(a-b)-1;
}