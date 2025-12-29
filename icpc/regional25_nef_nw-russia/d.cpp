#include <bits/stdc++.h>
using namespace std;

template<class T1, class T2> bool minimize(T1 &a, T2 b) {return b < a ? (a = b, true) : false;}
template<class T1, class T2> bool maximize(T1 &a, T2 b) {return b > a ? (a = b, true) : false;}

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define fi first
#define se second

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 5005
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
int a, b, c, oldA, oldB, oldC;
char one = 'a', two = 'b', three = 'c';
void update() {
	int add = mt() % 25;
	while (add < 3) add = mt() % 25;
	one = (one - 'a' + add) % 25 + 'a';
	two = (two - 'a' + add) % 25 + 'a';
	three = (three - 'a' + add) % 25 + 'a';
}
string S, T, U;

int fST[MAX][MAX];
int check(const string &s, const string &t) {
	int lenS = s.length(), lenT = t.length();
	fST[0][0] = 0;
	FOR(int, i, 1, lenT) fST[0][i] = i;
	FOR(int, i, 1, lenS) fST[i][0] = i;
	FOR(int, iS, 1, lenS) FOR(int, iT, 1, lenT) {
		fST[iS][iT] = min({
			fST[iS-1][iT] + 1,
			fST[iS][iT-1] + 1,
			fST[iS-1][iT-1] + (s[iS-1] != t[iT-1])
		});
	}
	// cerr << s << ' ' << t << ' ' << f[len][len] << '\n';
	return fST[lenS][lenT];
}

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	// memset(fST, 0x3f, sizeof(fST));
	// memset(fSU, 0x3f, sizeof(fSU));
	// memset(fTU, 0x3f, sizeof(fTU));
	cin >> a >> b >> c;

	auto [A, B, C] = tuple<int, int, int>(a, b, c);
	if (A > B) swap(A, B);
	if (A > C) swap(A, C);
	if (B > C) swap(B, C);
	if (A + B < C) {
		cout << "No\n";
		return 0;
	}

	S = T = U = "h";

	if ((A+B+C)%2 == 1) {
		if (A == 0) {cout << "No\n"; return 0;}
		S += 'a'; T += 'b'; U += 'c';
		A--, B--, C--;
	}
	while (A + B > C) {
		T += 'd', U += 'd', S += 'e';
		A--, B--;
	}
	FOR(int, i, 1, A) S += 'z';
	FOR(int, i, 1, C) U += 'z';
	tie(A, B, C) = tuple<int, int, int>(a, b, c);
	if (A > B) swap(A, B);
	if (A > C) swap(A, C);
	if (B > C) swap(B, C);
	// cerr << S << ' ' << T << ' ' << U << ' ' << A << ' ' << B << ' ' << C << ' ' << a << b << c << '\n';
	assert(check(S, T) == A and check(S, U) == B and check(T, U) == C);
	assert((
		(A == a and B == b and C == c) or
		(A == a and B == c and C == b) or
		(A == b and B == c and C == a) or
		(A == b and B == a and C == c) or
		(A == c and B == a and C == b) or
		(A == c and B == b and C == a)
	));
	cout << "Yes\n";
	for (auto [one, two, three]: vector<tuple<string, string, string>>{
		{S, T, U},
		{S, U, T},
		{T, S, U},
		{T, U, S},
		{U, T, S},
		{U, S, T},
	}) {
		if(check(one, two) == a and check(one, three) == b and check(two, three) == c)
			return (cout << one << '\n' << two << '\n' << three << '\n'), 0;
	}
	// assert(false);
	// tie(oldA, oldB, oldC) = tie(a, b, c);
	// FOR(int, i, 1, 110) {
	// 	tie(a, b, c) = tie(oldA, oldB, oldC);
	// 	S = T = U = "a";
	// 	if (a > 0 and b > 0 and c > 0 and (a+b+c) % 2 == 1)
	// 		a--, b--, c--, S += one, T += two, U += three, update();
	// 	// cerr << a << ' ' << b << ' ' << c << ' ' << S << " " << T << " " << U << '\n';
	// 	int oldS = 0, oldT = 0, oldU = 0;
	// 	bool oke = true;
	// 	while (a > 0 or b > 0 or c > 0) {
	// 		if (a == 0)
	// 			S += 'z', T += 'z';
	// 		else if (b == 0)
	// 			S += 'z', U += 'z';
	// 		else if (c == 0)
	// 			T += 'z', U += 'z';
	// 		else if (a <= b and a <= c)
	// 			S += one, T += one, U += two;
	// 		else if (b <= a and b <= c)
	// 			S += two, U += two, T += three;
	// 		else
	// 			T += three, U += three, S += one;
	// 		a = oldA - checkST(S, T, oldS, oldT);
	// 		b = oldB - checkSU(S, U, oldS, oldU);
	// 		c = oldC - checkTU(T, U, oldT, oldU);
	// 		oldS = S.length(), oldT = T.length(), oldU = U.length();
	// 		if (oldS > 5000) {
	// 			assert(false);
	// 			return 0;
	// 		}
	// 		// cerr << a << ' ' << b << ' ' << c << ' ' << S << " " << T << " " << U << '\n';
	// 		update();
	// 		if (a < 0 or b < 0 or c < 0) {oke = false; break;}
	// 	}
	// 	if (oke) {
	// 		cout << "Yes\n" << S << '\n' << T << '\n' << U << '\n';
	// 		return 0;
	// 	}
	// }
	// cout << "No\n";
	// // if (!!a + !!b + !!c == 1) { cout << "No\n"; return 0; }
	// // if (!!a + !!b + !!c == 2) {
	// // 	if (a != b and b != c and c != a) {cout << "No\n"; return 0;}
	// // 	int len = (a+b+c) / 2; string s1, s2;
	// // 	FOR(int, i, 1, len) s1 += one, s2 += two, update();
	// // 	if (a == 0) S += s1, T += s1, U += s2;
	// // 	else if (b == 0) S += s1, U += s1, T += s2;
	// // 	else /*c==0*/ T += s1, U += s1, S += s2;
	// // }
	// // while (true) {
	// // 	a = oldA - checkST(S, T, oldS, oldT);
	// // 	b = oldB - checkSU(S, U, oldS, oldU);
	// // 	c = oldC - checkTU(T, U, oldT, oldU);
	// // 	if (a == 0 and b == 0 and c == 0) break;
	// // 	cerr << a << ' ' << b << ' ' << c << '\n';
	// // 	while (a > 0 or b > 0 or c > 0) {
	// // 		// assert(a == 0 or b == 0 or c == 0);
	// // 		if (a <= b and a <= c)
	// // 			S += one, T += one, U += two, b--, c--;
	// // 		else if (b <= a and b <= c)
	// // 			S += two, U += two, T += three, a--, c--;
	// // 		else
	// // 			T += three, U += three, S += one, a--, b--;
	// // 		// cerr << a << ' ' << b << ' ' << c << ' ' << S << " " << T << " " << U << '\n';
	// // 		update();
	// // 	}
	// }
}
void input() {}
void clear() {}
