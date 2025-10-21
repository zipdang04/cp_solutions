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

/*
 * gonna be like
 *     1      3
 *     1      3
 * 0000x000000x000000
 *     1      3
 *     1      3
 *     1      3
 * 2222x222222x222222
 *     1      3
 *     1      3
 */
int calculate(vector<vector<int>> digits) {
	int len[4]; FOR(int, i, 0, 3) len[i] = digits[i].size();

	int i[4] = {};
	int answer = 0;
	for (i[0] = 0; i[0] < len[0]; i[0]++)
	for (i[1] = 0; i[1] < len[1]; i[1]++)
	for (i[2] = 0; i[2] < len[2]; i[2]++)
	for (i[3] = 0; i[3] < len[3]; i[3]++) 
	for (int w = 2; i[0] + w < len[0] and i[2] + w < len[2]; w++) 
	for (int h = 2; i[1] + h < len[1] and i[3] + h < len[3]; h++) 
	{
		if (digits[0][i[0]] != digits[1][i[1]]) continue;
		if (digits[0][i[0] + w] != digits[3][i[3]]) continue;
		if (digits[2][i[2]] != digits[1][i[1] + h]) continue;
		if (digits[2][i[2] + w] != digits[3][i[3] + h]) continue;
		// cerr << ">" << i[0] << ' ' << i[1] << ' ' << i[2] << ' ' << i[3] << ' ' << w << ' ' << h << '\n';
		answer++;
	}
	return answer;
}



main()
{
	vector<vector<int>> digits(4);
	ios_base::sync_with_stdio(0); cin.tie(0);
	FOR(int, i, 0, 3) {
		string s; cin >> s;
		digits[i] = vector<int>(s.begin(), s.end());
	}
	int answer = 0;
	int perm[4] = {0, 1, 2, 3};
	do {
		// FOR(int, i, 0, 3) cerr << perm[i] << " \n"[i == 3];
		answer += calculate({
			digits[perm[0]],
			digits[perm[1]],
			digits[perm[2]],
			digits[perm[3]]
		});
		// cerr << answer << '\n';
	} while (next_permutation(perm, perm+4));
	cout << answer << '\n';
}