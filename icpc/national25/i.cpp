#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef long long ll;
typedef unsigned long long ull;
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

// #define MOD 1000000007

typedef unsigned long long ull;
struct modint{
	inline static /*const*/ ll MOD = 998244353;
	int v;
	static inline ll mod(ll num) {
		ll val=num-ull((__uint128_t(-1ULL/MOD)*num)>>64)*MOD;
		return val-(val>=MOD)*MOD;
	}
	modint inv() const{
		ll answer = 1, a = v, n = MOD - 2;
		while (n) {
			if (n & 1) answer = mod(answer * a);
			a = mod(a * a); n >>= 1;
		}
		return answer;
	}

	modint(ll a = 0)
		{ v=(a<0)?(MOD-mod(-a)):mod(a);v-=(v>=MOD)*MOD; }
	inline modint& operator += (modint b)
		{ v+=b.v; v-=(v>=MOD)*MOD; return *this; }
	inline modint& operator -= (modint b)
		{ v+=MOD-b.v; v-=(v>=MOD)*MOD; return*this; }
	inline modint& operator *= (modint b)
		{ v = mod(1ll * v * b.v); return *this; }
	inline modint& operator /= (modint b)
		{ return (*this)*=b.inv(); }
	inline modint& operator ^= (ll n) {
		modint a = v; v = 1;
		while (n) {if (n & 1) *this *= a; a *= a, n >>= 1;}
		return *this;
	}
};
#define NEWOP(op, op2) inline modint operator op\
(modint a, modint b) {return a op2 b;}
NEWOP(+,+=);NEWOP(-,-=);NEWOP(*,*=);NEWOP(/,/=);
#define NEWCMP(op) inline bool operator op\
(modint a, modint b) {return a.v op b.v;}
NEWCMP(==);NEWCMP(!=);NEWCMP(<);NEWCMP(>);NEWCMP(<=);NEWCMP(>=);
inline modint operator - (modint a){return -a.v;}
inline modint operator^(modint a, ll n){return a^=n;}
inline istream& operator >> (istream& s, modint &i)
	{ ll tmp; s >> tmp; i = tmp; return s; }
inline ostream& operator << (ostream& s, modint i)
	{return s << i.v;}

struct Matrix {
	modint mat[3][3];
	Matrix() { memset(mat, false, sizeof false); }
	inline static Matrix makeUnit() {
		Matrix m;
		m.mat[0][0] = m.mat[1][1] = m.mat[2][2] = 1;
		return m;
	}
	inline static Matrix makeLine(modint a, modint b, modint c) {
		Matrix m;
		m.mat[0][0] = b*b; // 1-aa
		m.mat[0][1] = -a*b;
		m.mat[0][2] = -a*c;
		m.mat[1][0] = -a*b;
		m.mat[1][1] = a*a;	// 1-bb
		m.mat[1][2] = -b*c;
		m.mat[2][2] = a*a+b*b;
		return m * (1 / (a*a+b*b));
	}
	inline static Matrix makeLine(char m, modint a, modint b, modint c) {
		Matrix ans = makeLine(a, b, c);
		if (m == 'D') ans = ans*2 - makeUnit();
		return ans;
	}
	inline static Matrix makePoint(modint x, modint y) {
		Matrix m;
		m.mat[0][0] = x;
		m.mat[1][0] = y;
		m.mat[2][0] = 1;
		return m;
	}
	Matrix operator * (const Matrix b) const {
		Matrix ans;
		FOR(int, k, 0, 2) FOR(int, i, 0, 2) FOR(int, j, 0, 2)
			ans.mat[i][j] += mat[i][k] * b.mat[k][j];
		return ans;
	}
	Matrix operator * (const modint coef) const {
		Matrix ans = *this;
		FOR(int, i, 0, 2) FOR(int, j, 0, 2)
			ans.mat[i][j] *= coef;
		return ans;
	}
	Matrix operator + (const Matrix b) const {
		Matrix ans = *this;
		FOR(int, i, 0, 2) FOR(int, j, 0, 2)
			ans.mat[i][j] += b.mat[i][j];
		return ans;
	}
	Matrix operator - () const {
		Matrix ans = *this;
		FOR(int, i, 0, 2) FOR(int, j, 0, 2)
			ans.mat[i][j] = -ans.mat[i][j];
		return ans;
	}
	Matrix operator - (const Matrix b) const {
		return (*this) + (-b);
	}
	string toString() {
		string s = "[";
		FOR(int, i, 0, 2) {
			s += '[';
			FOR(int, j, 0, 2) s += to_string(mat[i][j].v) + ",]"[j==2];
			s += ",]"[i==2];
		}
		return s;
	}
};

#define MAX 200005
class SegTree {
	int len;
	inline static Matrix it[MAX*4];
	void buildTree(Matrix *arr, int idx, int lo, int hi) {
		if (lo == hi) {
			it[idx] = arr[lo]; return;
		}
		int y = idx << 1, mid = (lo + hi) / 2;
		buildTree(arr, y, lo, mid); buildTree(arr, y+1, mid+1, hi);
		it[idx] = it[y+1] * it[y];
	}
	void update(int idx, int lo, int hi, int pos, Matrix val) {
		if (lo == hi) { it[idx] = val; return; }
		int y = idx << 1, mid = (lo + hi) / 2;
		
		if (pos <= mid) update(y, lo, mid, pos, val);
		else update(y+1, mid+1, hi, pos, val);
		
		it[idx] = it[y+1] * it[y];
	}
	Matrix get(int idx, int lo, int hi, int posL, int posR) {
		if (hi < posL or posR < lo) return Matrix::makeUnit();
		if (posL <= lo and hi <= posR) return it[idx];

		int y = idx << 1, mid = (lo + hi) / 2;
		return get(y+1, mid+1, hi, posL, posR) * get(y, lo, mid, posL, posR);
	}
public:
	SegTree() {}
	SegTree(int len): len(len) {}
	void buildTree(Matrix *arr) {buildTree(arr, 1, 1, len);}
	Matrix get(int posL, int posR) {
		return get(1, 1, len, posL, posR);
	}
	void update(int pos, Matrix val) {
		update(1, 1, len, pos, val);
	}
} seg;
int n, q;
Matrix lines[MAX];

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	FOR(int, i, 1, n) {
		char m; int a, b, c; cin >> m >> a >> b >> c;
		lines[i] = Matrix::makeLine(m, a, b, c);
	}
	seg = SegTree(n);
	seg.buildTree(lines);
	FOR(int, _, 1, q) {
		int type; cin >> type;
		if (type == 1) {
			int j, a, b, c; char m; cin >> j >> m >> a >> b >> c;
			seg.update(j, Matrix::makeLine(m, a, b, c));
		} else {
			int x, y, l, r; cin >> x >> y >> l >> r;
			Matrix ans = seg.get(l, r) * Matrix::makePoint(x, y);
			cout << ans.mat[0][0] << ' ' << ans.mat[1][0] << '\n';
		}
	}

}
