#include <algorithm>
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
	static int c;
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

#define MAX 155
#define MOD 1000000007

int P, Q, R;
bitset<MAX> state[MAX][MAX], _save[MAX][MAX];
void transform() {
	FOR(int, i, 1, P) FOR(int, j, 1, Q)
		_save[i][j] = state[i][j];
	FOR(int, i, 1, P) FOR(int, j, 1, Q) state[i][j] = 0;

	int _P = Q, _Q = R, _R = P;
	FOR(int, i, 1, _P) FOR(int, j, 1, _Q) FOR(int, k, 1, _R)
		state[i][j][k] = _save[k][i][j];
	FOR(int, i, 1, P) FOR(int, j, 1, Q) _save[i][j] = 0;
	P = _P, Q = _Q, R = _R;
}

int nxtR[MAX][MAX][MAX], nxtD[MAX][MAX][MAX], f[MAX][MAX][MAX];
void build() {
	memset(nxtR, false, sizeof nxtR);
	memset(nxtD, false, sizeof nxtD);
	memset(f, false, sizeof f);
	REV(int, x, P, 1) REV(int, y, Q, 1) REV(int, z, R, 1) {
		if (not state[x][y][z]) continue;
		nxtR[x][y][z] = nxtR[x][y][z+1] + 1;
		nxtD[x][y][z] = nxtD[x][y+1][z] + 1;
		f[x][y][z] = min({
			f[x][y+1][z+1] + 1,
			nxtR[x][y][z],
			nxtD[x][y][z]
		});
	}
}

int arr[MAX] = {};
int fL[MAX], fR[MAX];
stack<int> st;
int cal(int y, int z) {
	FOR(int, x, 1, P) arr[x] = f[x][y][z];
	FOR(int, x, 1, P) {
		while (not st.empty() and arr[st.top()] > arr[x]) {
			fR[st.top()] = x-1; st.pop();
		}
		st.push(x);
	}
	while (not st.empty()) { fR[st.top()] = P; st.pop(); }
	REV(int, x, P, 1) {
		while (not st.empty() and arr[st.top()] > arr[x]) {
			fL[st.top()] = x+1; st.pop();
		}
		st.push(x);
	}
	while (not st.empty()) { fL[st.top()] = 1; st.pop(); }
	int ans = 0;
	FOR(int, x, 1, P)
		maximize(ans, arr[x] * (fR[x]-fL[x]+1));
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> P >> Q >> R;
	FOR(int, j, 1, Q) FOR(int, i, 1, P) {
		string s; cin >> s;
		FOR(int, k, 1, R) state[i][j][k] = s[k-1] == 'N';
	}

	int ans = 0;
	FOR(int, _, 1, 3) {
		build();
		FOR(int, y, 1, Q) FOR(int, z, 1, R) {
			int cur = cal(y, z);
			maximize(ans, cur);
		}
		transform();
	}
	cout << ans*4;
}
