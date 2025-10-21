#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
template <class T> using PQMax = priority_queue<T>;
template <class T> using PQMin = priority_queue<T, vector<T>, greater<T>>;
template <class T1, class T2>
void maximize(T1 &a, T2 b){
	if (b > a) a = b;
}
template <class T1, class T2>
void minimize(T1 &a, T2 b){
	if (b < a) a = b;
}
template <class T>
void read(T &number)
{
	bool negative = false;
	register int c;
	number = 0;
	c = getchar();
	while (c != '-' && !isalnum(c)) c = getchar();
	if (c=='-'){
		negative = true;
		c = getchar();
	}
	for (; (c>47 && c<58); c=getchar())
		number = number *10 + c - 48;
	if (negative)
		number *= -1;
}
template <class T, class ...Ts>
void read(T &a, Ts& ... args){
	read(a);
	read(args...);
}

/*
struct Node
{
	int node, len;
	Node() {node = len = 0;}
	Node(int node, int len) {this -> node = node, this -> len = len;}
};
typedef vector<Node> vg;
*/

#define fi first
#define se second

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define REV(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define log2(n) (31 - __builtin_clz(n))
#define log2ll(n) (63 - __builtin_clzll(n))
#define CURRENT_TIMESTAMP chrono::steady_clock::now().time_since_epoch().count()
#define randomize mt19937_64 mt(CURRENT_TIMESTAMP)

#define MAX 1000001
#define MOD 1000000007

typedef vector<char> bigint;
inline istream& operator >> (istream& inp, bigint& num) {
	string s; inp >> s;
	num.resize(s.size());
	reverse(s.begin(), s.end());
	for (int i = 0; i < s.size(); i++)
		num[i] = s[i] -'0';
	return inp;
}
inline ostream& operator << (ostream& out, bigint& num) {
	for (int i = (int)num.size() - 1; i >= 0; i--)
		out << int(num[i]);
	return out;
}
inline void add (bigint &a, const bigint &b) {
	int nho = 0;
	for (int i = 0; i < b.size(); i++) {
		a[i] += b[i] + nho;
		if (a[i] > 9) nho = 1, a[i] -= 10; else nho = 0;
	}
	if (nho) a.push_back(1);
}
inline bigint convert(int number) {
	if (number == 0) return {0};
	bigint finalAns;
	while (number)
		finalAns.push_back(number % 10),
		number /= 10;
	return finalAns;
}
inline bool check(const bigint &number) {
	int size = number.size();
	for (int i = 0; i < size-i-1; i++)
		if (number[i] != number[size-1-i])
			return false;
	return true;
}

main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	bigint number; cin >> number;
	int n, m; cin >> n >> m;

	if (check(number)) {
		cout << "YES\n0\n" << number << '\n';
		return 0;
	}
	int turn = 0;
	for (int _ = 1; _ <= n and number.size() <= m; _++) {
		turn++;
		bigint num2 = number;
		reverse(num2.begin(), num2.end());
		add(number, num2);
		if (check(number)) {
			cout << "NO\n";
			cout << _ << '\n';
			cout << number << '\n';
			return 0;
		}
	}
	cout << "YES\n";
	cout << turn << '\n';
	cout << number << '\n';
}