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

int n;
int k[MAX], x1[MAX], x2[MAX];
vector<int> l[MAX]; int sumAll[MAX];

int remainW[MAX];
vector<int> startingPos[MAX];
void build() {
	FOR(int, i, 1, n) remainW[i] = x2[i] - x1[i] - sumAll[i];
	FOR(int, i, 1, n) {
		startingPos[i].reserve(k[i]+1);
		int start = x1[i]; startingPos[i].push_back(start);
		for (int w: l[i]) startingPos[i].push_back(start += w);
	}
}

int values[MAX], cntValue;
vector<pii> events[MAX];
void compress() {
	FOR(int, i, 1, n) for (int pos: startingPos[i]) values[++cntValue] = pos;
	sort(values + 1, values + 1 + cntValue);
	cntValue = unique(values + 1, values + 1 + cntValue) - values - 1;

	FOR(int, i, 1, n) {
		int prv = INT_MIN;
		for (int pos: startingPos[i]) {
			int j = lower_bound(values + 1, values + 1 + cntValue, pos) - values;
			if (prv != INT_MIN) events[j].push_back({i, -prv});
			events[j].push_back({i, pos}); prv = pos;
		}
	}
}

multiset<int> L, R;
void process() {
	ll answer = 0;
	FOR(int, _, 1, cntValue) {
		for (auto [i, posL]: events[_]) {
			int posR = abs(posL) + remainW[i];
			if (posL < 0)
				L.erase(L.find(-posL)), R.erase(R.find(posR)); // only posL negative
			else
				L.insert(posL), R.insert(posR);
		}
		assert((L.size() == R.size()));
		if ((int)L.size() == n) {
			int maxL = *L.rbegin(), minR = *R.begin();
			maximize(answer, minR - maxL);
		}
	}
	cout << answer << '\n';
}

void input();
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	build();
	compress();
	process();
}
void input() {
	cin >> n;
	FOR(int, i, 1, n) {
		cin >> k[i] >> x1[i] >> x2[i]; x1[i]++, x2[i]++;
		l[i] = vector<int>(k[i]);
		FOR(int, j, 1, k[i]) {cin >> l[i][j-1]; sumAll[i] += l[i][j-1];}
	}
}
