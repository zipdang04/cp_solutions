#include "obstacles.h"

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

int nT, nH;
int T[MAX];
int H[MAX];
int subtask;
void calSubtask() {
	if (nT == 1) {subtask = 1; return;}
	if (nT == 3 and T[1] == 2 and T[2] == 1 and T[3] == 3) {subtask = 3; return;}
	subtask = 2; return;
}

namespace Subtask12 {
	bool firstTime = true;

	vector<int> prv;
	void preprocess() {
		prv.resize(nH + 1, 0);
		FOR(int, i, 1, nH)
			prv[i] = (T[nT] <= H[i]) ? 0 : (
				(prv[i-1] == 0) ? i : prv[i-1]
			);
	}

	bool solve(int S, int D){
		if (firstTime) {
			firstTime = false;
			preprocess();
		}

		return (prv[D] <= S);
	}
}

namespace Subtask3 {
	int _dsu[MAX * 3];
	struct DSU{
		void clear(int sz) {
			FOR(int, i, 0, sz) _dsu[i] = -1;
		}
		int par(int u) {
			return _dsu[u] < 0 ? u : (_dsu[u] = par(_dsu[u]));
		}
		bool join(int u, int v) {
			u = par(u), v = par(v);
			if (u == v) return false;

			if (-_dsu[u] < -_dsu[v]) swap(u, v);
			_dsu[u] += _dsu[v]; _dsu[v] = u;
			return true;
		}
	} dsu;
	int getIndex(int row, int col) {
		return (row-1) * nH + (col-1);
	}

	void preprocess() {
		dsu.clear(nT * nH);
		FOR(int, col, 1, nH) FOR(int, row, 1, nT-1)
			if (T[row] > H[col] and T[row + 1] > H[col])
				dsu.join(getIndex(row, col), getIndex(row + 1, col));
		FOR(int, row, 1, nT) FOR(int, col, 1, nH-1){
			if (T[row] > H[col] and T[row] > H[col + 1])
				dsu.join(getIndex(row, col), getIndex(row, col + 1));
		}
	}

	bool firstTime = true;
	bool solve(int S, int D) {
		if (firstTime) {
			firstTime = false; preprocess();
		}

		return dsu.par(getIndex(1, S)) == dsu.par(getIndex(1, D));
	}
}

namespace Subtask45 {
	//
}

void initialize(std::vector<int> _T, std::vector<int> _H) {
	nT = _T.size(), nH = _H.size();
	FOR(int, i, 1, nT) T[i] = _T[i-1];
	FOR(int, i, 1, nH) H[i] = _H[i-1];
	calSubtask();
	return;
}

bool can_reach(int L, int R, int S, int D) {
	S++, D++; if (S > D) swap(S, D);        // 1S -> 1D
	switch (subtask) {
		case 1:
		case 2:
			return Subtask12::solve(S, D);
		case 3:
			return Subtask3::solve(S, D);
	}
}
