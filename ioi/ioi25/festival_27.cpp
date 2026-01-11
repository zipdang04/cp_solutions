#include "festival.h"

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
#define oo 1'000'000'000'000'000ll

struct Coupon {
	int idx; ll p, t;
	Coupon() {idx = p = t = 0;}
	Coupon(int idx, ll p, int t): idx(idx), p(p), t(t) {}
};

ll A; int n;
Coupon coupons[MAX];

int getSubtask() {
	bool is1 = true, is2 = n <= 3000, is3 = true;
	FOR(int, i, 1, n)
		is1 &= coupons[i].t == 1,
		is2 &= coupons[i].t <= 2,
		is3 &= coupons[i].t <= 2;
	if (is1) return 1;
	if (is2) return 2;
	if (is3) return 3;
	if (n <= 70) return 4;
	return 5;
}


namespace Subtask1 {
	vector<Coupon> prices[3];
	vector<int> solve() {
		FOR(int, i, 1, n)
			prices[coupons[i].t].push_back(coupons[i]);


		vector<int> answer;
		int ptr[3] = {};
		while (A > 0 and ptr[1] < prices[1].size() and ptr[2] < prices[2].size()) {
			Coupon one = prices[1][ptr[1]],
				   two = prices[2][ptr[2]];
			ll newA1 = A - one.p,
			   newA2 = (A - two.p) * 2;
			// cerr << prices[1][ptr[1]] << ' ' << prices[2][ptr[2]] << ' ' << newA1 << ' ' << newA2 << '\n';
			if (newA1 < 0 and newA2 < 0) break;
			if (newA2 > newA1)
				A = newA2, answer.push_back(two.idx), ptr[2]++;
			else
				A = newA1, answer.push_back(one.idx), ptr[1]++;
			minimize(A, oo);
		}
		FOR(int, type, 1, 2)
			while (A > 0 and ptr[type] < prices[type].size()) {
				Coupon coupon = prices[type][ptr[type]++];
				if (A < coupon.p) break;
				answer.push_back(coupon.idx); A = (A - coupon.p) * type;
				minimize(A, oo);
			}


		return answer;
	}
}


namespace Subtask2 {
	ll f[3002][3002][2][2];
	Coupon trace[3002][3002][2][2];
	int cnt[5];
	vector<Coupon> prices[5];

	void preprocess() {
		FOR(int, i, 1, 4) prices[i].push_back(Coupon());
		FOR(int, i, 1, n) {
			Coupon coupon = coupons[i];
			++cnt[coupon.t], prices[coupon.t].push_back(coupon);
		}
	}

	struct State{
		int i1, i2, i3, i4;
		void _selfadd(int pos, int amount) {
			if (pos == 1) i1 += amount;
			if (pos == 2) i2 += amount;
			if (pos == 3) i3 += amount;
			if (pos == 4) i4 += amount;
		}

		State add(int pos) {
			State haha = *this;
			haha._selfadd(pos, 1);
			return haha;
		}
		State del(int pos) {
			State haha = *this;
			haha._selfadd(pos, -1);
			return haha;
		}
		int sum() {
			return i1 + i2 + i3 + i4;
		}
		static int getFrom(int choice, int x1, int x2, int x3, int x4) {
			if (choice == 1) return x1;
			if (choice == 2) return x2;
			if (choice == 3) return x3;
			if (choice == 4) return x4;
			assert(false);
		}
	};
	State ans = {0, 0, 0, 0};
	vector<int> solve() {
		preprocess();
		// FOR(int, i, 1, 4) cerr << cnt[i] << '\n';
		f[0][0][0][0] = A;
		for(int i1 = 0, newi1 = 1; i1 <= cnt[1]; i1++, newi1++)
		for(int i2 = 0, newi2 = 1; i2 <= cnt[2]; i2++, newi2++)
		for(int i3 = 0, newi3 = 1; i3 <= cnt[3]; i3++, newi3++)
		for(int i4 = 0, newi4 = 1; i4 <= cnt[4]; i4++, newi4++) {
			const ll curA = f[i1][i2][i3][i4];
			// cerr << i1 << ' ' << i2 << ' ' << i3 << ' ' << i4 << "=>" << curA << '\n';
			State curState = {i1, i2, i3, i4};
			FOR(int, type, 1, 4) {
				int i = State::getFrom(type, i1, i2, i3, i4);
				if (i >= cnt[type])  continue;

				const Coupon coupon = prices[type][i+1];
				// cerr << "> " << coupon.t << '|' << coupon.idx << ' ' << coupon.p << "\n";
				if (curA < coupon.p) continue;
				// cerr << ">> inside\n";
				ll newA = (curA - coupon.p) * type; minimize(newA, oo);

				State newState = curState.add(type);
				if (newState.sum() > ans.sum()) ans = newState;

				// cerr << ">> newState" << ' ' << newState.i1 << ' ' << newState.i2 << ' ' << newState.i3 << ' ' << newState.i4 << '\n';
				ll &posF = f[newState.i1][newState.i2][newState.i3][newState.i4];
				Coupon &posTrace = trace[newState.i1][newState.i2][newState.i3][newState.i4];
				if (newA >= posF) posF = newA, posTrace = coupon;
				// cerr << "done\n";
			}
		}

		vector<int> result;
		while (ans.sum() > 0) {
			Coupon coupon = trace[ans.i1][ans.i2][ans.i3][ans.i4];
			result.push_back(coupon.idx);
			ans = ans.del(coupon.t);
		}
		reverse(result.begin(), result.end());
		return result;
	}
}
namespace Subtask4 {
	ll f[71][71][71][71];
	Coupon trace[71][71][71][71];
	int cnt[5];
	vector<Coupon> prices[5];

	void preprocess() {
		FOR(int, i, 1, 4) prices[i].push_back(Coupon());
		FOR(int, i, 1, n) {
			Coupon coupon = coupons[i];
			++cnt[coupon.t], prices[coupon.t].push_back(coupon);
		}
	}

	struct State{
		int i1, i2, i3, i4;
		void _selfadd(int pos, int amount) {
			if (pos == 1) i1 += amount;
			if (pos == 2) i2 += amount;
			if (pos == 3) i3 += amount;
			if (pos == 4) i4 += amount;
		}

		State add(int pos) {
			State haha = *this;
			haha._selfadd(pos, 1);
			return haha;
		}
		State del(int pos) {
			State haha = *this;
			haha._selfadd(pos, -1);
			return haha;
		}
		int sum() {
			return i1 + i2 + i3 + i4;
		}
		static int getFrom(int choice, int x1, int x2, int x3, int x4) {
			if (choice == 1) return x1;
			if (choice == 2) return x2;
			if (choice == 3) return x3;
			if (choice == 4) return x4;
			assert(false);
		}
	};
	State ans = {0, 0, 0, 0};
	vector<int> solve() {
		preprocess();
		// FOR(int, i, 1, 4) cerr << cnt[i] << '\n';
		f[0][0][0][0] = A;
		for(int i1 = 0, newi1 = 1; i1 <= cnt[1]; i1++, newi1++)
		for(int i2 = 0, newi2 = 1; i2 <= cnt[2]; i2++, newi2++)
		for(int i3 = 0, newi3 = 1; i3 <= cnt[3]; i3++, newi3++)
		for(int i4 = 0, newi4 = 1; i4 <= cnt[4]; i4++, newi4++) {
			const ll curA = f[i1][i2][i3][i4];
			// cerr << i1 << ' ' << i2 << ' ' << i3 << ' ' << i4 << "=>" << curA << '\n';
			State curState = {i1, i2, i3, i4};
			FOR(int, type, 1, 4) {
				int i = State::getFrom(type, i1, i2, i3, i4);
				if (i >= cnt[type])  continue;

				const Coupon coupon = prices[type][i+1];
				// cerr << "> " << coupon.t << '|' << coupon.idx << ' ' << coupon.p << "\n";
				if (curA < coupon.p) continue;
				// cerr << ">> inside\n";
				ll newA = (curA - coupon.p) * type; minimize(newA, oo);

				State newState = curState.add(type);
				if (newState.sum() > ans.sum()) ans = newState;

				// cerr << ">> newState" << ' ' << newState.i1 << ' ' << newState.i2 << ' ' << newState.i3 << ' ' << newState.i4 << '\n';
				ll &posF = f[newState.i1][newState.i2][newState.i3][newState.i4];
				Coupon &posTrace = trace[newState.i1][newState.i2][newState.i3][newState.i4];
				if (newA >= posF) posF = newA, posTrace = coupon;
				// cerr << "done\n";
			}
		}

		vector<int> result;
		while (ans.sum() > 0) {
			Coupon coupon = trace[ans.i1][ans.i2][ans.i3][ans.i4];
			result.push_back(coupon.idx);
			ans = ans.del(coupon.t);
		}
		reverse(result.begin(), result.end());
		return result;
	}
}

std::vector<int> max_coupons(int _A, std::vector<int> _P, std::vector<int> _T) {
	A = _A;
	n = _P.size();
	FOR(int, i, 1, n) coupons[i] = {i, _P[i-1], _T[i-1]};
	sort(coupons + 1, coupons + 1 + n, [](Coupon one, Coupon two){ return one.p < two.p; });
	// FOR(int, i, 1, n) cerr << P[i] << " \n"[i == n];
	// FOR(int, i, 1, n) cerr << T[i] << " \n"[i == n];

	vector<int> answer;
	int subtask = getSubtask();
	switch (subtask) {
		case 1:
		case 3:
			answer = Subtask1::solve(); break;
		case 2:
			answer = Subtask2::solve(); break;
		case 4:
			answer = Subtask4::solve(); break;
	}
	for (int &value: answer) value -= 1;
	return answer;
}
