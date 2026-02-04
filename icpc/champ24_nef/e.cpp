#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2> 
bool minimize(T1 &a, T2 b) {
	return (b < a) ? (a = b, true) : false;
}
template<class T1, class T2> 
bool maximize(T1 &a, T2 b) {
	return (b > a) ? (a = b, true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define cntBit(n) __builtin_popcountll(n)
#define testBit(n, bit) (((n) >> (bit)) & 1)

#define NaN -1
#define MAX
#define MOD

// ll convert(string &&s) {
// 	if (s.empty() or (int)s.length() > 10 or s[0] == '0') return NaN;
// 	ll answer = 0; for (char c: s) answer = answer * 10 + (c - '0');
// 	return answer;
// }
bool evaluate(string s) {
	ll sumOne = 0;
	ll sum = 0, cur = 0, len = 0; char sign = '+';
	// cerr << "eval " << s << '\n';
	#define push(nxt) {\
		sum += (sign == '+') ? (+cur) : (-cur); \
		cur = len = 0; sign = nxt;\
	}
	for (char c: s) {
		if (c == '=') {
			if (len == 0) return false;
			push('+'); sumOne = sum; sum = 0;
			continue;
		}
		if (c == '+' or c == '-') {
			if (len == 0) return false;
			push(c);
			continue;
		} 
		// now is a number
		// cerr << c << ' ' << cur << ' ' << len << '\n';
		if (cur == 0 and len > 0) return false;
		
		if (len == 10) return false;
		cur = cur * 10 + (c - '0'); len++;
	}
	push(0);
	// cerr << "finished " << sumOne << ' ' << sum << '\n';
	return sumOne == sum;
}

void input(), clear();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	string s; cin >> s; int len = s.length();
	if (evaluate(s)) {cout << "Correct\n"; return 0;}
	for (int i = 0; i < s.length(); i++) {
		char c = s[i];
		if (not isdigit(c)) continue;
		string newS = s.substr(0, i) + s.substr(i+1, len-(i+1));
		for (int j = 0; j <= newS.length(); j++) {
			string s2 = newS;
			s2.insert(s2.begin() + j, c);
			if (evaluate(s2)) {
				cout << s2 << '\n'; return 0;
			}
		}
	}

	cout << "Impossible\n";
}
void input() {} 
void clear() {}