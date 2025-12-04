#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i++)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define cntBit(n) __builtin_popcountll(1ll*n)
#define log2(n) (63-__builtin_clzll(1ll*n))

#define MAX

string a, b;
string getperm(string s, int pos) {
	FOR(int, i, 2, pos)
		next_permutation(s.begin(), s.end());
	return s;
}

void input();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		int sz = a.size();
		int A = 0, B = 0;
		FOR(int, i, 0, sz-1)
			A += a[i] == b[i];
		B = sz-A;
		cout << A << "A" << B << "B" << '\n';
	}
}
void input(){
	string s; int j, k; cin >> s >> j >> k;
	a = getperm(s, j), b = getperm(s, k);
}