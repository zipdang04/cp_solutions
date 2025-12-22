#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template <class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template <class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 105
#define NaN 100

int n, pyr[MAX][MAX];

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	FOR(int, i,1, n) FOR(int, j, 1, i) cin >> pyr[i][j];

	bool stop = false;
	while (not stop){
		stop = true;
		FOR(int, row, 1, n-1) FOR(int, col, 1, row) {

			int &top = pyr[row][col], &dL = pyr[row+1][col], &dR = pyr[row+1][col+1];
			if ((top != NaN) + (dL != NaN) + (dR != NaN) == 3) {
				if (top != dL + dR) {
					cout << "no solution\n";
					return 0;
				}
			}
			if ((top != NaN) + (dL != NaN) + (dR != NaN) != 2) continue;

			int curVal = INT_MAX;
			if (top != NaN and dL != NaN)
				curVal = dR = top - dL;
			else if (top != NaN and dR != NaN)
				curVal = dL = top - dR;
			else if (dL != NaN and dR != NaN)
				curVal = top = dL + dR;

			assert (curVal != INT_MAX);
			if (curVal < -99 or curVal > 99) {
				cout << "no solution\n";
				return 0;
			}
			stop = false;
		}
	}

	FOR(int, row, 1, n) FOR(int, col, 1, row)
		if (pyr[row][col] == NaN) {
			cout << "ambiguous\n";
			return 0;
		}

	cout <<"solvable\n";
	FOR(int, row, 1, n) FOR(int, col, 1, row)
		cout << pyr[row][col] << " \n"[col == row];

}
void input(){}
void clear(){}
