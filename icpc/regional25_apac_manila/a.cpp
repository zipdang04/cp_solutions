#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> bool minize(T1 &a, T2 b) {return b < a ? ((a = b), true) : false;}
template<class T1, class T2> bool maxize(T1 &a, T2 b) {return b > a ? ((a = b), true) : false;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i++)

#define MAX
#define MOD

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	string s; cin >> s;
	int n = s.length(); if (n & 1) cout << s[n / 2]; else cout << ":)";
}
void input(){
	//
}
void clear(){
	//
}
