#include <bits/stdc++.h>
using namespace std;

typedef __int128_t ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

template<class T1, class T2> 
bool minimize(T1 &a, T2 b) {
	return (b < a) ? (a = b, true) : false;
}
template<class T1, class T2> 
bool maximize(T1 &a, T2 b) {
	return (b > a) ? (a = b, true) : false;
}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define cntBit(n) __builtin_popcountll(n)
#define testBit(n, bit) (((n) >> (bit)) & 1)

#define sofi(x) (((x) == 0) ? 0 : (((x) < 0) ? -1 : +1))

#define MAX 2005
#define MOD

struct num{
	ll r, i;
	num() {r = i = 0;}
	num(ll r, ll i): r(r), i(i) {}

	num div_sqrt2() const {
		assert(r % 2 == 0);
		return {i, r / 2};
	}
	num div_2() const {
		assert((r % 2 == 0 and i % 2 == 0));
		return {r / 2, i / 2};
	}
	int sign() const {
		// cerr << "sign" << ' ' << (long long)(r) << ' ' << (long long)(i) << ' ' << ((i == 0 or r*i > 0) ? sofi(r) : ((r == 0) ? sofi(i) : sofi((r*r - 2*i*i) * sofi(r)))) << '\n';
		if (i == 0 or r*i > 0) return sofi(r);
		if (r == 0) return sofi(i);
		ll res = (r*r - 2*i*i) * sofi(r);
		return sofi(res);
	}
	#ifndef ONLINE_JUDGE
	// string toString() const {cerr; return std::format("({})", r + i * sqrt(2));}
	// string toString() const {cerr; return std::format("({}{}{}i)", r, ((i < 0) ? '-' : '+'), (i < 0) ? -i : i);}
	#endif
};

inline num operator + (num a, num b) {return {a.r + b.r, a.i + b.i};}
inline num operator - (num a, num b) {return {a.r - b.r, a.i - b.i};}
inline num operator * (num a, ll b) {return {a.r * b, a.i * b};}
inline num operator / (num a, ll b) {assert(b == 2); return {a.r / 2, a.i / 2};} // change to b if necessary
inline num operator * (num a, num b) {return {
	a.r * b.r + 2 * a.i * b.i, 
	a.r * b.i + a.i * b.r
};} 

inline bool operator < (num a, num b) {return (a-b).sign() < 0;}
inline bool operator > (num a, num b) {return (a-b).sign() > 0;}
inline bool operator <= (num a, num b) {return (a-b).sign() <= 0;}
inline bool operator >= (num a, num b) {return (a-b).sign() >= 0;}
inline bool operator == (num a, num b) {return a.r == b.r and a.i == b.i;}
inline bool operator != (num a, num b) {return not (a == b);}


struct Point{
	num x, y;
	Point() {x = y = num();}
	Point(num x, num y): x(x), y(y) {}
	Point rotate() const {
		return {(x - y).div_sqrt2(), (x + y).div_sqrt2()};
	}
	
	// string toString() const {cerr; return std::format("({}x {}y)", x.toString(), y.toString());}
};
typedef Point Vec;

inline bool operator < (Vec a, Vec b) {return a.x != b.x ? a.x < b.x : a.y < b.y;}
inline bool operator > (Vec a, Vec b) {return a.x != b.x ? a.x > b.x : a.y > b.y;}
inline bool operator <= (Vec a, Vec b) {return a.x != b.x ? a.x <= b.x : a.y <= b.y;}
inline bool operator >= (Vec a, Vec b) {return a.x != b.x ? a.x >= b.x : a.y >= b.y;}
inline bool operator == (Vec a, Vec b) {return a.x == b.x and a.y == b.y;}
inline bool operator != (Vec a, Vec b) {return not (a == b);}
inline Vec operator + (Vec a, Vec b) {return {a.x + b.x, a.y + b.y};}
inline Vec operator - (Vec a, Vec b) {return {a.x - b.x, a.y - b.y};}
inline Vec operator * (Vec a, ll b) {return {a.x * b, a.y * b};} 


#define CNT_DIREC 8
#define UNIT 64
const Vec DIREC[CNT_DIREC] = {
	Vec(num(2*UNIT, 0), num(0, 0)),
	Vec(num(0, UNIT), num(0, UNIT)),
	Vec(num(0, 0), num(2*UNIT, 0)),
	Vec(num(0, -UNIT), num(0, UNIT)),
	Vec(num(-2*UNIT, 0), num(0, 0)),
	Vec(num(0, -UNIT), num(0, -UNIT)),
	Vec(num(0, 0), num(-2*UNIT, 0)),
	Vec(num(0, UNIT), num(0, -UNIT)),
};
void ensureDIREC() {
	FOR(int, i, 0, 7) {
		assert((DIREC[i].rotate() == DIREC[(i+1) % 8]));
	}
}

struct Line{
	Point p1, p2;
	Line() {p1 = p2 = Point();}
	Line(Point p1, Point p2) {
		if (p1 > p2) swap(p1, p2);
		this -> p1 = p1, this -> p2 = p2;
	}
	// string toString() const {cerr;  return std::format("[{} -> {}]", p1.toString(), p2.toString()); }
	Line rotate(Point center) const {
		Point new1 = p1 - center, new2 = p2 - center;
		return {center + new1.rotate(), center + new2.rotate()};
	}
};
bool operator < (Line a, Line b) {return a.p1 != b.p1 ? a.p1 < b.p1 : a.p2 < b.p2;}
bool isParallel(Line l1, Line l2) {
	Vec v1 = l1.p2 - l1.p1, 
		v2 = l2.p1 - l1.p1,
		v3 = l2.p2 - l1.p1;
	for (auto [u, v]: {pair<Vec, Vec>(v1, v2), pair<Vec, Vec>(v1, v3)})
		if (u.x * v.y != u.y * v.x) return false;
	return true;
}
bool doesIntersect(Line l1, Line l2) {
	// cerr << "intersect" << ' ' << l1.toString() << ' ' << l2.toString() << '\n';
	// cerr << isParallel(l1, l2) << '\n';
	return (
		l1.p1 == l2.p1 and l1.p2 == l2.p2
	) or (
		isParallel(l1, l2) and not(
			l1.p2 < l2.p1
			or l2.p2 < l1.p1
		)
	);
}
Line join(Line l1, Line l2) {
	// assert(doesIntersect(l1, l2));
	// cerr << "join: " << l1.toString() << ' ' << l2.toString() << '\n';
	// return l1.p1 <= l2.p2 ? Line(l1.p1, l2.p2) : Line(l2.p1, l1.p2);
	return Line(min(l1.p1, l2.p1), max(l1.p2, l2.p2));
}

int cntCommands;
Line lines[MAX]; int n;
int diff[MAX];
struct DSU{
	int n;
	inline static int dsu[MAX];
	DSU() {}
	DSU(int n): n(n) {
		FOR(int, i, 1, n) dsu[i] = -1;
	}
	int par(int u) {return dsu[u] < 0 ? u : dsu[u] = par(dsu[u]);}
	bool join(int u, int v) {
		u = par(u), v = par(v);
		if (u == v) return false;
		dsu[u] += dsu[v], dsu[v] = u;
		return true;
	}
} dsu;
void group() {
	dsu = DSU(n);
	// int ptr = 0;
	// FOR(int, i, 1, n) cerr << lines[i].toString() << " \n"[i == n];
	// cerr.flush();
	FOR(int, i, 1, n) {
		// bool getNew = true;
		FOR(int, j, 1, i-1) if (doesIntersect(lines[i], lines[j])) {
			dsu.join(i, j);
			// lines[i] = join(lines[i], lines[j]); getNew = false;
		}
		// if (not getNew) continue;
		// lines[++ptr] = lines[i];
	}
	FOR(int, i, 1, n) {
		int p = dsu.par(i);
		lines[p] = join(lines[p], lines[i]);
		// cerr << p << ' ' << i << ' ' << lines[p].toString() << endl;
	}
	// FOR(int, i, 1, n) cerr << lines[i].toString() << " \n"[i == n];
	int ptr = 0;
	// // FOR(int, i, 1, n) if (dsu.par(i) == i) cerr << i << ' '; cerr << '\n';
	FOR(int, i, 1, n) if (dsu.par(i) == i){
		lines[++ptr] = lines[i];
		// cerr << ptr << ' ' << i << '\n';
	}
	n = ptr;
	// FOR(int, i, 1, n) cerr << lines[i].toString() << " \n"[i == n];


	// n = ptr;
}

Point center;
void buildCenter() {
	num minX (LLONG_MAX, LLONG_MAX), minY = minX, 
		maxX (LLONG_MIN, LLONG_MIN), maxY = maxX;
	FOR(int, i, 1, n) {
		minimize(minX, min(lines[i].p1.x, lines[i].p2.x));
		minimize(minY, min(lines[i].p1.y, lines[i].p2.y));
		maximize(maxX, max(lines[i].p1.x, lines[i].p2.x));
		maximize(maxY, max(lines[i].p1.y, lines[i].p2.y));
	}
	center = Point((minX + maxX) / 2, (minY + maxY) / 2);
	// cerr << minX.toString()<< maxX.toString() << ' ' << minY.toString() << maxY.toString() << ' '<< center.toString() << '\n';
}

map<Line, bool> appear;

int calculate() {
	FOR(int, i, 1, n) appear[lines[i]] = true;

	bool oke[3] = {true, true, true};
	FOR(int, i, 1, n) {
		Line cur = lines[i];
		cur = cur.rotate(center); oke[0] &= appear[cur]; // 45
		cur = cur.rotate(center); oke[1] &= appear[cur]; // 90
		cur = cur.rotate(center); cur = cur.rotate(center); 
		oke[2] &= appear[cur]; // 180
		if (not oke[0] and not oke[1] and not oke[2]) return 360;
	}
	if (oke[0]) return 45;
	if (oke[1]) return 90;
	if (oke[2]) return 180;
	return 360;
}

void draw(), clear();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	// #ifndef ONLINE_JUDGE
	// cerr << fixed << setprecision(2);
	ensureDIREC();
	// #endif
	draw();
	group();
	buildCenter();
	cout << calculate();
}
void draw() {
	Point p = Point(num(), num()); int d = 0;
	cin >> cntCommands;
	
	string command; int num;
	FOR(int, _, 1, cntCommands) {
		cin >> command >> num;
		if (command == "rotate") {
			num /= 45; d = (d + num) % CNT_DIREC;
			continue;
		}
		Point old = p;
		p = old + (DIREC[d] * num);
		// cerr << old.toString() << " -> " << p.toString() << '\n';
		if (command == "draw")
			lines[++n] = Line(old, p);
	}
} 
void clear() {}
