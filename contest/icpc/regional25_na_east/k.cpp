#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template <class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template <class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 55
#define A 0
#define B 1
#define C 2
#define BB 3
#define MID B

string to_string(__int128 num) {
	if (num == 0) return "0";
	if (num < 0) return "-" + to_string(-num);
	string ans = "";
	while (num)
		ans += char(num % 10 + '0'),
		num /= 10;
	reverse(ans.begin(), ans.end());
	return ans;
}

ll w, d;
__int128 f[MAX][MAX][MAX][4];

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	auto checkParams = [](int a, int b, int c, int prv) -> bool {
		return (prv == A and a > 0)
			or (prv == B and b > 0)
			or (prv == C and c > 0)
			or (prv == BB and b >= 2);
	};
	auto checkQuanti = [](int a, int b, int c, int D) -> bool {
		return (abs(a-b) <= D)
			and (abs(a-c) <= D)
			and (abs(b-c) <= D);
	};

	f[1][0][0][A] = f[0][1][0][B] = f[0][0][1][C] = 1;
	for (int iLen = 1, nxtLen = 2; nxtLen <= 53; iLen++, nxtLen++)
	FOR(int, iA, 0, iLen) for (int iB = 0, iC = iLen - iA; iC >= 0; iB++, iC--)
	FOR(int, prv, A, BB) {
		// checkParams eligibility
		if (not checkParams(iA, iB, iC, prv)) continue;
		if (f[iA][iB][iC][prv] == 0) continue;

		FOR(int, nxt, A, BB) {
			// a -> b, c; b -> a, c, bb; c -> a, b; bb -> a, c
			if (prv == nxt) continue;					// a-a, b-b, c-c, bb-bb
			if (prv != B and nxt == BB) continue;		// a-bb, c-bb, bb-bb
			if (prv == BB and nxt == B) continue;		// bb-b

			int nxtA = iA, nxtB = iB, nxtC = iC;
			if (nxt == A) nxtA++;
			if (nxt == B or nxt == BB) nxtB++;
			if (nxt == C) nxtC++;
			f[nxtA][nxtB][nxtC][nxt] += f[iA][iB][iC][prv];
		}
	}

	cin >> w >> d;
	__int128 answer = 0;
	FOR(int, iA, 0, w) for (int iB = 0, iC = w-iA; iC >= 0; iB++, iC--) FOR(int, i, A, BB) {
		if (not checkParams(iA, iB, iC, i)) continue;
		if (not checkQuanti(iA, iB, iC, d)) continue;
		answer += f[iA][iB][iC][i];
	}

	bool isEven = w % 2 == 0;
	FOR(int, iA, 0, w) FOR(int, iB, 0, w) FOR(int, iC, 0, w) FOR(int, i, A, BB){
		if (not checkParams(iA, iB, iC, i)) continue;

		const int a = iA * 2, b = iB * 2, c = iC * 2;
		if (a + b + c + !isEven != w) continue;

		if (isEven) {
			if (i != B) continue;					// ....A|A.... or C or BB is not allowed
			if (not checkQuanti(a, b, c, d)) continue;
			answer -= f[iA][iB][iC][i];
			continue;
		}
		assert((not isEven));
		// isOdd
		FOR(int, nxt, A, C) {
			if (i == nxt) continue;					// a-a, b-b, c-c
			if (i == BB and nxt == B) continue;		// bb-b
			//
			int newA = a, newB = b, newC = c;
			if (nxt == A) newA++;
			if (nxt == B) newB++;
			if (nxt == C) newC++;
			if (not checkQuanti(newA, newB, newC, d)) continue;
			answer -= f[iA][iB][iC][i];
		}
	}
	cout << to_string(answer) << '\n';
}
void input(){}
void clear(){}
