#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define first fi
#define second se

template <class T1, class T2> bool minimize(T1& a, T2 b) {return b < a ? (a=b, true) : false;}
template <class T1, class T2> bool maximize(T1& a, T2 b) {return b > a ? (a=b, true) : false;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)
#define all(v) v.begin(), v.end()
#define all(v, l, r) v.begin() + l, v.begin() + r + 1

#define MAX 1005
#define MOD

int n, m;
string s[MAX];

bool hI[MAX][2], hP[MAX][2], vI[MAX][2], vP[MAX][2], hC[MAX][2], vC[MAX][2];
void buildICPC() {
	memset(hI, true, sizeof(hI));
	memset(vI, true, sizeof(vI));
	memset(hP, true, sizeof(hP));
	memset(vP, true, sizeof(vP));
	memset(hC, true, sizeof(hC));
	memset(vC, true, sizeof(vC));

	FOR(int, row, 1, n) FOR(int, col, 1, m) {
		bool mightI = s[row][col] == 'I' or s[row][col] == '?';
		bool mightP = s[row][col] == 'P' or s[row][col] == '?';
		bool mightC = s[row][col] == 'C' or s[row][col] == '?';
		hI[row][col & 1] &= mightI;
		hI[row][~col & 1] &= mightC;
		hP[row][col & 1] &= mightP;
		hP[row][~col & 1] &= mightC;
		hC[row][col & 1] &= mightC;
		hC[row][~col & 1] &= s[row][col] != 'C';
		
		vI[col][row & 1] &= mightI;
		vI[col][~row & 1] &= mightC;
		vP[col][row & 1] &= mightP;
		vP[col][~row & 1] &= mightC;
		vC[col][row & 1] &= mightC;
		vC[col][~row & 1] &= s[row][col] != 'C';
	}
}

bool checkHori(bool isInotP) {
	bool canIP[2]; const bool ori = isInotP;
	for (int row = 1; row <= n; row++, isInotP = !isInotP) {
		FOR(int, i, 0, 1)
			canIP[i] = (isInotP ? hI[row][i] : hP[row][i]) and hC[row][!i];
		if (not (canIP[0] or canIP[1])) return false;
	}

	isInotP = ori;
	for (int row = 1; row <= n; row++, isInotP = !isInotP) {
		FOR(int, i, 0, 1)
			canIP[i] = (isInotP ? hI[row][i] : hP[row][i]) and hC[row][!i];
		bool i = canIP[0] ? 0 : 1;
		char IP = isInotP ? 'I' : 'P';
		for (int col = 1; col <= m; col++, i = !i) {
			char need = i ? IP : 'C';
			if (s[row][col] == '?') s[row][col] = need;
			else assert(s[row][col] == need);
		}
	}
	return true;
}
bool checkVert(bool isInotP) {
	bool canIP[2], ori = isInotP;
	for (int col = 1; col <= m; col++, isInotP = !isInotP) {
		FOR(int, i, 0, 1)
			canIP[i] = (isInotP ? vI[col][i] : vP[col][i]) and vC[col][!i];
		if (not (canIP[0] or canIP[1])) return false;
	}

	isInotP = ori;
	for (int col = 1; col <= m; col++, isInotP = !isInotP) {
		FOR(int, i, 0, 1)
			canIP[i] = (isInotP ? vI[col][i] : vP[col][i]) and vC[col][!i];
		bool i = canIP[0] ? 0 : 1;
		char IP = isInotP ? 'I' : 'P';
		for (int row = 1; row <= n; row++, i = !i) {
			char need = i ? IP : 'C';
			if (s[row][col] == '?') s[row][col] = need;
			else assert(s[row][col] == need);
		}
	}
	return true;
}
bool stripeHori(const bool oddC) {
	// cerr << "stripeHori " << oddC << '\n';
	bool nowC = oddC;
	vector<char> store(n+1, 0);
	for (int row = 1; row <= n; row++, nowC = !nowC) {
		// cerr << "cur row" << row << ' ' << nowC << '\n';
		if (nowC) {
			FOR(int, col, 1, m) 
				if (s[row][col] != 'C' and s[row][col] != '?')
					return false;
			continue;
		}
		char need = 0;
		for (int col = 1; col <= m; col++, need = (need == 0) ? 0 : (need == 'I' ? 'P' : 'I')) {
			// cerr << row << ' ' << col << ' ' << (need == 0 ? 'x' : need) << '\n';
			if (s[row][col] == 'C') return false;
			if (s[row][col] == '?') continue;
			if (need == 0) {need = s[row][col]; continue;}
			if (s[row][col] != need) return false;
		}
		// cerr << "pass\n";
		if (need == 0) need = 'I'; 
		else if (m & 1) need = (need == 'I' ? 'P' : 'I');
		store[row] = need;
	}

	nowC = oddC;
	for (int row = 1; row <= n; row++, nowC = !nowC) {
		if (nowC) {
			FOR(int, col, 1, m)
				if (s[row][col] == '?') s[row][col] = 'C';
				else assert(s[row][col] == 'C');
			continue;
		}
		char need = store[row];
		for (int col = 1; col <= m; col++, need = (need == 'I') ? 'P' : 'I')
			if (s[row][col] == '?') s[row][col] = need;
			else assert(s[row][col] == need);
	}
	return true;
}
bool stripeVert(const bool oddC) {
	// cerr << "stripeVert " << oddC << '\n';
	bool nowC = oddC;
	vector<char> store(m+1, 0);
	for (int col = 1; col <= m; col++, nowC = !nowC) {
		if (nowC) {
			bool oke = true;
			FOR(int, row, 1, n) oke &= s[row][col] == 'C' or s[row][col] == '?';
			if (oke) continue;
			return false;
		}
		char need = 0;
		for (int row = 1; row <= n; row++, need = (need == 0) ? 0 : (need == 'I' ? 'P' : 'I')) {
			if (s[row][col] == 'C') return false;
			if (s[row][col] == '?') continue;
			if (need == 0) {need = s[row][col]; continue;}
			if (s[row][col] != need) return false;
		}
		// cerr << "pass\n";
		if (need == 0) need = 'I'; 
		else if (n & 1) need = (need == 'I' ? 'P' : 'I');
		store[col] = need;
	}

	nowC = oddC;
	for (int col = 1; col <= m; col++, nowC = !nowC) {
		if (nowC) {
			FOR(int, row, 1, n)
				if (s[row][col] == '?') s[row][col] = 'C';
				else assert(s[row][col] == 'C');
			continue;
		}
		char need = store[col];
		for (int row = 1; row <= n; row++, need = (need == 'I') ? 'P' : 'I')
			if (s[row][col] == '?') s[row][col] = need;
			else assert(s[row][col] == need);
	}
	return true;
}
void input(), clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int tests; cin >> tests;
	FOR(int, _, 1, tests) {
		input();
		buildICPC();
		bool oke = false;
		if (not oke) oke = checkHori(false);
		if (not oke) oke = checkHori(true);
		if (not oke) oke = checkVert(false);
		if (not oke) oke = checkVert(true);
		if (not oke) oke = stripeHori(true);
		if (not oke) oke = stripeHori(false);
		if (not oke) oke = stripeVert(true);
		if (not oke) oke = stripeVert(false);
		

		if (not oke) cout << "no\n";
		else {
			FOR(int, i, 1, n-1) FOR(int, j, 1, m-1) {
				int cnt[3] = {};
				for (char c: {s[i][j], s[i+1][j], s[i][j+1], s[i+1][j+1]})
					cnt[(c == 'I') ? 0 : ((c == 'P') ? 1 : 2)]++;
				// assert(cnt[0] == 1);
				// assert(cnt[1] == 1);
				// assert(cnt[2] == 2);
			}
			cout << "yes\n";
			FOR(int, i, 1, n) cout << s[i].substr(1, m) << '\n';
		}
	}
}
void input() {
	cin >> n >> m;
	FOR(int, i, 1, n) cin >> s[i];
	FOR(int, i, 1, n) s[i] = " " + s[i];
}
void clear() {
	// 
}