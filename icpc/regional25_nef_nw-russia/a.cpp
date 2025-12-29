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

#define MAX 2005
#define SUM 1'000'005

int n;
int eqA[MAX], addA[MAX], cntE, cntA;
pair<int, bool> addLast[MAX]; int cntLast, eqS;
void clear() {
	FOR(int, i, 1, cntLast) {
		auto [num, isAsync] = addLast[i];
		if (isAsync) addA[++cntA] = num;
	}
	cntLast = 0;
}

bitset<SUM> sumA, all, result;
void buildSum() {
	#define HIHI 50
	sumA[0] = true;
	FOR(int, i, 1, cntA) {
		int num = addA[i];
		sumA |= sumA << num;
	}

	all = sumA;
	int plus = 0;
	FOR(int, i, 1, cntLast) plus += addLast[i].fi;
	result = sumA << (plus + eqS);
	FOR(int, i, 1, cntLast) {
		all |= sumA << plus;

		auto [num, isAsync] = addLast[i];
		plus -= num;
		if (isAsync) sumA |= sumA << num;
	}
	all |= sumA;

	FOR(int, i, 1, cntE)
		result |= all << eqA[i];
	cout << result.count();
}

void input();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();
	buildSum();
}
void input() {
	cin >> n;
	FOR(int, i, 1, n) {
		char c; int num; string s;
		cin >> c >> num >> s;
		if (s == "sync") {
			if (c == '=') eqS = num, clear();
			else addLast[++cntLast] = {num, false};
		} else {
			if (c == '=') eqS = eqA[++cntE] = num, clear();
			else addLast[++cntLast] = {num, true};
		}
	}
}
