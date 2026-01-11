#include "jumps.h"
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
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef map<int, int> mii;
typedef unordered_map<int, int> umii;
typedef map<ll, ll> mll;
typedef unordered_map<ll, ll> umll;

template<class T>
void minimize(T &a, T b){
	if (b < a) a = b;
}
template<class T>
void maximize(T &a, T b){
	if (b > a) a = b;
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

#define MAX 200005
#define MOD 1000000007

#define fi first
#define se second
#define pf push_front
#define pb push_back

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORR(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

const int oo = 1e9;
bool flagSub1 = true;

int n;
int h[MAX];
int L[MAX], R[MAX], best[MAX];

void buildBest(){
	stack<int> st;

	st.push(0);
	FOR(int, i, 1, n){
		while (h[st.top()] <= h[i]) st.pop();
		L[i] = st.top(); st.push(i);
	}
	while (!st.empty()) st.pop();

	st.push(0);
	FORR(int, i, n, 1){
		while (h[st.top()] <= h[i]) st.pop();
		R[i] = st.top(); st.push(i);
	}
	FOR(int, i, 1, n)
		if (L[i] == 0) best[i] = R[i];
		else if (R[i] == 0) best[i] = L[i];
		else best[i] = (h[L[i]] > h[R[i]]) ? L[i] : R[i];
}

const int BIT = 17;
int rmqL[BIT + 1][MAX],
	rmqR[BIT + 1][MAX],
	rmqB[BIT + 1][MAX];
void buildRMQ(){
	FOR(int, i, 1, n)
		rmqL[0][i] = L[i],
		rmqR[0][i] = R[i],
		rmqB[0][i] = best[i];
	FOR(int, bit, 1, BIT)
		FOR(int, i, 1, n)
			rmqL[bit][i] = rmqL[bit - 1][rmqL[bit - 1][i]],
			rmqR[bit][i] = rmqR[bit - 1][rmqR[bit - 1][i]],
			rmqB[bit][i] = rmqB[bit - 1][rmqB[bit - 1][i]];
}

void init(int N, std::vector<int> H) {
	n = N;
	FOR(int, i, 0, n - 1)
		h[i + 1] = H[i];

	h[0] = h[n + 1] = oo;
	buildBest();
	buildRMQ();

	FOR(int, i, 2, n)
		if (h[i] != i) flagSub1 = false;
}

queue<int> q;
int t[MAX];
void clear(){
	FOR(int, i, 1, n) t[i] = oo;
}

int sub1(int a, int b, int c, int d){
	if (d < a) return -1;
	if (b < c) return c - b;
	return 0;
}

int sub5(int from, int to){
	int ans = 0;
	FORR(int, bit, BIT, 0)
		if (h[rmqB[bit][from]] <= h[to])
			from = rmqB[bit][from],
			ans |= 1 << bit;
	// if (from == to) return ans;

	if (h[L[from]] <= h[to]){
		FORR(int, bit, BIT, 0)
			if (h[rmqL[bit][from]] <= h[to])
				from = rmqL[bit][from],
				ans += 1 << bit;
	} else {
		FORR(int, bit, BIT, 0)
			if (h[rmqR[bit][from]] <= h[to])
				from = rmqR[bit][from],
				ans += 1 << bit;
	}
	return (from != to) ? -1 : ans;
}

class SegTree{
	private:
		set<pii> it[MAX * 4];
		int len;
		void update(int ind, int lo, int hi, int pos, int val){
			it[ind].insert({val, pos});
			if (lo == hi) return;

			int y = ind << 1, mid = (lo + hi) >> 1;
			if (pos <= mid) update(y, lo, mid, pos, val);
			else update(y + 1, mid + 1, hi, pos, val);
		}
	public:
		SegTree(int len): len(len){
			FOR(int, i, 1, len * 4) it[i].clear();
		}
};

int sub6(int fromL, int fromR, int to){
	//
}

int minimum_jumps(int A, int B, int C, int D) {
	A++, B++, C++, D++;
	if (flagSub1) return sub1(A, B, C, D);
	if (A == B && C == D)
		return sub5(A, C);

	clear();
	FOR(int, i, A, B)
		t[i] = 0, q.push(i);
	while (!q.empty()){
		int node = q.front(); q.pop(); int curT = t[node];
		int c1 = L[node], c2 = R[node];
		if (c1 != 0 && t[c1] == oo){
			t[c1] = curT + 1; q.push(c1);
		}
		if (c2 != n + 1 && t[c2] == oo){
			t[c2] = curT + 1; q.push(c2);
		}
	}

	int ans = oo;
	FOR(int, i, C, D)
		minimize(ans, t[i]);
	if (ans == oo) ans = -1;
	return ans;
}
