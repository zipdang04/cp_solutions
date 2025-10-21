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

#define MAX 200001
#define MOD 1000000007

int n;
string s;
// int sum[26][MAX];

int same1() {
	int consec = 0, ans = 0;
	FOR(int, i, 1, n) {
		consec = (s[i] == s[i-1]) ? consec+1 : 1;
		maximize(ans, consec);
	}
	return ans;
}
int same2() {
	vector<int> tmp(n+1, 0);
	vector<int> sum(n+1, 0);
	FOR(int, i, 1, n)
		sum[i] = sum[i-1] + (s[i] == s[1] ? 1 : -1);
	map<int, int> prv;
	int ans = 0;
	FOR(int, i, 1, n) {
		if (sum[i] == 0) ans = i;
		else if (prv[sum[i]])
			maximize(ans, i - prv[sum[i]]);
		// cerr << sum[i] << ' ' << prv[sum[i]] << '\n';
		if (prv[sum[i]] == 0)
			prv[sum[i]] = i;
	}
	return ans;
}


main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> s; n = s.length(); s = " " + s;
	// FOR(int, i, 1, n) {
		// FOR(int, j, 0, 25) sum[i][j] = sum[i-1][j];
		// sum[i][s[i]-'a']++;
	// }
	int ans = max(same1(), same2());
	if (n <= 50000) {
		FOR(int, i, 1, n) {
			int cnt[26] = {};
			int maxi = 0, diff = 0, all = 26;
			FOR(int, j, i, n) {
				if (cnt[s[j]-'a']++ == 0) diff++;
				if (cnt[s[j]-'a'] > maxi) 
					maxi = cnt[s[j]-'a'], all = 1;
				else if (cnt[s[j]-'a'] == maxi) 
					all++;
				if (maxi * diff == j-i+1)
					maximize(ans, j-i+1);
				if (diff <= 5) break;
				if (maxi * diff > n) break;
			}
		}
	}
	cout << ans << '\n';
}