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

#define MAX 5005
#define oo 1'000'000'007

template<class T>
struct Range{
	T l, r; 
	Range(){l=r=0;} 
	Range(T l, T r): l(l), r(r){} 
	T sz(){return max((T)0, r-l);}
};
template<class T>
Range<T> merge(Range<T> a, Range<T> b) {return Range<T>(max(a.l, b.l), min(a.r, b.r));}

int n, k;
Range<int> allRanges[MAX];

int checkSubtask() {
	if (n <= 200) return 1;
	if (n <= 2000 and k <= 20) return 2;
	if (n <= 20000) return 3;
	if (k <= 500) return 4;
	return 5;
}

// int coor[MAX], cntCoor;
// void compress() {
// 	// boundary
// 	coor[++cntCoor] = 0;
// 	coor[++cntCoor] = n;
// 	// blockages
// 	FOR(int, i, 1, n) 
// 		coor[++cntCoor] = allRanges[i].l,
// 		coor[++cntCoor] = allRanges[i].r;
// 	// uniquify
// 	sort(coor + 1, coor + 1  + cntCoor);
// 	cntCoor = unique(coor + 1, coor + 1 + cntCoor) - coor - 1;
// 	// reindexed
// 	FOR(int, i, 1, n)
// 		allRanges[i].l = lower_bound(coor + 1, coor + 1 + cntCoor, allRanges[i].l) - coor,
// 		allRanges[i].r = lower_bound(coor + 1, coor + 1 + cntCoor, allRanges[i].r) - coor;
// }
// int prefSum[MAX];
// void init() {
// 	FOR(int, i, 1, k) {
// 		int l = allRanges[i].l; int r = allRanges[i].r;
// 		prefSum[l]++, prefSum[r + 1]--;
// 	}
// 	FOR(int, i, 1, cntCoor) prefSum[i] += prefSum[i - 1];
// 	// duyệt cntCoor - 1 đoạn: đoạn i (coor[i] -> coor[i + 1])
// }
Range<ll> frees[MAX]; int cntFree = 0;
void init(){
	if (allRanges[1].l > 0)
		frees[++cntFree] = Range<ll>(0, allRanges[1].l);
	FOR(int, i, 1, k) {
		int l = allRanges[i].r, r = (i == k) ? n : allRanges[i + 1].l;
		if (l < r) frees[++cntFree] = Range<ll>(l, r);
	}
	FOR(int, i, 1, cntFree) frees[i].l *= 2, frees[i].r *= 2;
}

namespace Sub3{
	const int MAX_SUB_2 = 60001;

	typedef bitset<MAX_SUB_2> landmark;
	landmark original;
	void solve() {
		FOR(int, i, 1, cntFree) {
			Range<ll> range = frees[i];
			// cerr <<range.l << '-' << range.r  << " \n"[i == cntFree];
			FOR(int, pos, range.l, range.r - 1) original[pos] = true;
		}
		// // FOR(int, i, 0, 10) cerr << original[i]; cerr << '\n';

		int answer = original.count();
		FOR(int, shift, 1, n) {
			landmark currentResult = original | (original << shift);
			maximize(answer, (int)currentResult.count());
		}

		cout << answer;
	}
}
namespace Sub4 {
	ll shiftable[MAX * MAX], cntShift;
	void buildAllShift() {
		FOR(int, i, 1, cntFree) {
			FOR(int, j, i, cntFree)
				shiftable[++cntShift] = frees[j].l + frees[i].sz() - frees[i].r;
			FOR(int, j, i + 1, cntFree)
				shiftable[++cntShift] = frees[j].l - frees[i].r;
			shiftable[++cntShift] = n * 2 - frees[i].r;
		}
		shiftable[++cntShift] = n;
		sort(shiftable + 1, shiftable + 1 + cntShift);
		cntShift = unique(shiftable + 1, shiftable + 1 +cntShift) - shiftable - 1;
	}

	Range<ll> newRanges[MAX];
	void copy() {
		FOR(int, i, 1, k) newRanges[i] = {allRanges[i].l * 2, allRanges[i].r * 2};
	}
	// có bao nhiêu tọa độ trên các đoạn free sau khi shift thì đè lên ranges
	ll tryShift(ll shift) {
		// cerr << "== tryShift " << shift << '\n';
		int ptr = 1;
		ll answer = 0;
		FOR(int, iFree, 1, cntFree) {
			Range<ll> cur = frees[iFree]; cur.l -= shift, cur.r -= shift;
			// cerr << cur.l << ' ' << cur.r << '|';
			while (ptr <= k) {
				answer += merge(cur, newRanges[ptr]).sz();
				// cerr << iFree << '.' << ptr << '.' << answer << ' ';
				if (newRanges[ptr].r > cur.r) break;
				ptr++;
			}
			// cerr << '\n';
		}
		return answer;
	}
	void solve() {
		buildAllShift();
		copy();

		// cerr << "init:\n";
		// FOR(int, i, 1, k) cerr << newRanges[i].l << '-' << newRanges[i].r << " \n"[i == k];
		// FOR(int, i, 1, cntFree) cerr << frees[i].l << '-' << frees[i].r << " \n"[i == cntFree];
		// FOR(int, i, 1, cntShift) cerr << shiftable[i] << " \n"[i == cntShift];
		ll answer = 0;
		FOR(int, i, 1, cntShift) {
			maximize(answer, tryShift(shiftable[i]));
		}
		FOR(int, i, 1, cntFree) answer += frees[i].sz();

		cout << answer << '\n';
	}
	// 
}

void input();
main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	#ifndef HIEU
	freopen("roai.inp", "r", stdin);
	freopen("roai.out", "w", stdout);
	#endif
	input();
	init();

	Sub3::solve();
}
void input(){
	cin >> n >> k;
	FOR(int, i, 1, k){
		int l, r; cin >> l >> r;
		allRanges[i] = {l, r};
	}
}