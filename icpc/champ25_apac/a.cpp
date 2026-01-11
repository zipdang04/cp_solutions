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

#define MAX 2005
#define EMPTY false

int r, c;
string _s[MAX];

bitset<MAX> grid[MAX], gridT[MAX];
int cntRow[MAX], cntCol[MAX];
vector<int> allRow[MAX], allCol[MAX];

ll C(ll n, ll k) {
	if (k < 0) return 0;
	ll ans = 1;
	FOR(int, i, 1, k) ans = ans * (n-i+1) / i;
	return ans;
}

ll mul(vector<int> v) {
	// cerr << "mul: "; for (int i: v) cerr << i << ' '; cerr << '\n';
	ll sum = 0, res = 0;
	for (int i: v) {
		res += i * sum;
		sum += i;
	}
	return res;
}

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();

	FOR(int, i, 0, r-1) cntRow[i] = c - grid[i].count();
	FOR(int, i, 0, r-1) FOR(int, j, 0, c-1) cntCol[j] += grid[i][j] == EMPTY;
	// FOR(int, i, 0, r-1) FOR(int, j, 0, c-1) cerr << grid[i][j] << " \n"[j == c-1];
	// FOR(int, i, 0, r-1) cerr << cntRow[i] << " \n"[i == r-1];
	// FOR(int, j, 0, c-1) cerr << cntCol[j] << " \n"[j == c-1];
	
	ll ans1 = 0;
	FOR(int, i, 0, r-1) ans1 += C(cntRow[i], 4);
	FOR(int, i, 0, c-1) ans1 += C(cntCol[i], 4);
	ans1 *= 24; // 4!
	// cerr << ans1 << '\n';
	
	ll ans2 = 0;
	FOR(int, row, 0, r-1) FOR(int, col, 0, c-1) if (grid[row][col] == EMPTY) {
		int curRow = cntRow[row] - 1, curCol = cntCol[col] - 1;
		ans2 += C(curRow, 1) * C(curCol, 2) 
		  	  + C(curRow, 2) * C(curCol, 1);
		
		allCol[col].push_back(curRow); 
		allRow[row].push_back(curCol);
	}
	ans2 *= 4;
	// cerr << ans2 << '\n';
	
	ll ans3 = 0;
	FOR(int, i, 0, r-1) ans3 += mul(allRow[i]);
	FOR(int, i, 0, c-1) ans3 += mul(allCol[i]);
	ans3 *= 2;
	// cerr << ans3 << '\n';
	
	// square
	ll ans4 = 0;
	// FOR(int, r1, 0, r-1) FOR(int, r2, r1 + 1, r-1) {
	// 	ll same = r - (grid[r1] | grid[r2]).count();
	// 	ans4 += same * (same - 1) / 2;
	// }
	cout << ans1 + ans2 + ans3;
	// cerr << ans1 << ' ' << ans2 << ' ' << ans3 << ' ' << ans4 << '\n';
	// cout << answer;
}
void input() {
	cin >> r >> c;
	FOR(int, i, 0, r-1) cin >> _s[i];
	FOR(int, i, 0, r-1) FOR(int, j, 0, c-1) grid[i][j] = _s[i][j] == '#';
}