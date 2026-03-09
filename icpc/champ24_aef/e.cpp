#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long ld;
typedef pair<int, int> pii;
typedef pair<string, string> pss;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2>
bool minimize(T1 &a, T2 b) {
	return (b < a) ? (a=b, true) : false;
}
template<class T1, class T2>
bool maximize(T1 &a, T2 b) {
	return (b > a) ? (a=b, true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX_M 15
#define MOD

int n, m;

vector<pss> probs;
void parse(string s) {
	probs.clear();
	string num = "", tries = "";
	bool isNum = true;
	for (char c: s) {
		if (isdigit(c) and not isNum) {
			probs.push_back({num, tries});
			num = tries = "";
		}
		isNum = isdigit(c);
		if (isNum) num += c;
		else tries += c;
	}

	if (tries == "") return;
	probs.push_back({num, tries});
}

#define SUCCESS 0
int probSolved, penSum;
int pens[MAX_M + 5], subs[MAX_M + 5];
void testProb(int pos, const int solved = 0, const int sum = 0) {
	if (pos == probs.size()) {
		if (solved == probSolved and penSum == sum) 
			throw SUCCESS;
		return;
	}

	auto [nums, sTries] = probs[pos];
	int tries = 0; const bool singular = sTries == "try";
	for (int tryLen = 1, p10 = 1; tryLen <= 3 and nums.length() > 0; tryLen++, p10 *= 10) {
		char cur = *nums.rbegin() - '0';
		tries = tries + p10 * cur; nums.pop_back();
		if (tries > 100 or (tries > 1 and singular)) break;
		if (cur == 0) continue;
		if (not singular and tries == 1) continue;
		
		int pen = nums.empty() ? -1 : stoi(nums);
		if ((nums.size() > 1 and nums[0] == '0') or pen > 299) continue;
		
		int newSolved = solved + (pen >= 0),
		newSum = sum + (pen >= 0) * (pen + (tries-1) * 20);
		if (newSolved > probSolved or newSum > penSum) continue;
		pens[pos] = pen, subs[pos] = tries;
		testProb(pos + 1, newSolved, newSum);
	}
}
void testNum() {
	string tmp = probs[0].fi; int tmpLen = tmp.length();
	FOR(int, cntLen, 1, min(2, tmpLen-1)) {
		probSolved = stoi(tmp.substr(0, cntLen));
		assert((probSolved <= probs.size()));
		
		string remain = tmp.substr(cntLen, tmpLen - cntLen);

		// if (probSolved == 0) {
		// 	probs[0].fi = remain;
		// 	testProb(0);
		// 	continue;
		// }
		
		int remLen = remain.length();
		FOR(int, penLen, 1, min(5, remLen-1)) {
			if (penLen > 1 and remain[0] == '0') continue;
			penSum = stoi(remain.substr(0, penLen));
			probs[0].fi = remain.substr(penLen, remLen - penLen);
			testProb(0);
		}
	}
}

void print() {
	cout << probSolved << ' ' << penSum << ' ';
	int sz = probs.size();
	ll s1 = 0, s2 = 0;
	FOR(int, i, 0, sz-1) {
		if (pens[i] >= 0)
			cout << pens[i] << ' ';
		cout << subs[i] << ' ' << (subs[i] > 1 ? "tries" : "try") << " \n"[i == sz-1];
		
		assert(subs[i] > 0);
		assert(subs[i] <= 100);
		assert(pens[i] <= 299);
		s1 += pens[i] >= 0;
		 
		s2 += pens[i] >= 0 ? (pens[i] + (subs[i]-1) * 20) : 0;
	}
	assert(s1 == probSolved); assert(s2 == penSum);
}

string s;
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	FOR(int, _,1, n) {
		cin >> s;
		parse(s);
		if (probs.empty()) {
			cout << "0 0\n";
			continue;
		}
		bool done = false;
		try {testNum();}
		catch(int code) {
			assert(code == SUCCESS);
			done = true;
			print();
		}
		assert(done);
	}
}