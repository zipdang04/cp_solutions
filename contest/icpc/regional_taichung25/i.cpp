#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template<class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template<class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i++)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define cntBit(n) __builtin_popcountll(1ll*n)
#define log2(n) (63-__builtin_clzll(1ll*n))

#define MAX 200'005

struct Point {
	ll x, y;
	Point(ll x, ll y): x(x), y(y) {}
	Point(): Point(0, 0) {}

	Point operator + (Point a) const {return {x + a.x, y+a.y};}
	Point operator - (Point a) const {return {x - a.x, y-a.y};}
	ll cross(Point a) const {return x * a.y - y * a.x;}
	string toString() const {return "(" + to_string(x) + "," + to_string(y) + ")";}
	ll dist2() const {return x*x + y*y;}
	ld dist() const {return sqrt((ld)dist2());}
};
bool operator < (Point a, Point b) {return a.x != b.x ? a.x < b.x : a.y < b.y;}
bool operator == (Point b, Point a) { return b.x == a.x and b.y == a.y;}

ld lineDist(const Point a, const Point b, const Point p) {
	return ld((b-a).cross(p-a) / (b-a).dist());
}

int n; ll r; 
Point pts[MAX];

void input();
main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input(); pts[++n] = {0, 0};
	sort(pts + 1, pts + 1 + n);
	// FOR(int, i, 1, n) cerr << pts[i].toString() << " \n"[i == n];
	n = unique(pts + 1, pts + 1 + n) - pts - 1;

	sort(pts + 2, pts + 1 + n, [](Point a, Point b) {return (a - pts[1]).cross(b - pts[1]) > 0;});
	// cerr << "oke\n";
	vector<Point> convex = {pts[1], pts[2]};
	// FOR(int, i, 1, n) cerr << pts[i].toString() << " \n"[i == n];
	FOR(int, i, 3, n) {
		const Point p = pts[i]; 
		while (convex.size() >= 2) {
			Point p1 = *convex.rbegin(), p2 = *(++convex.rbegin());
			// cerr << p.toString() << '|' << (p1-p2).toString() << ' ' << (p-p1).toString() << '\n';
			if ((p1-p2).cross(p-p1) > 0) break;
			convex.pop_back();
		}
		convex.push_back(p);
	}
	while (convex.size() > 2) {
		Point p1 = *convex.rbegin(), p2 = *(++convex.rbegin());
		if ((p1-p2).cross(convex[0]-p1) > 0) break;
		convex.pop_back();
	}

	for (Point p: convex) cerr << p.toString() << '\n';

	int len = convex.size(); convex.push_back(convex[0]);
	ld d = r; 
	
	if (len == 1) d = 0; else {
		FOR(int, i, 0, len-1) {
			// cerr << convex[i].toString() << ' ' << convex[i+1].toString() << ' ' << lineDist(convex[i], convex[(i+1)%len], {0, 0}) << '\n';
			minimize(d, abs(lineDist(convex[i], convex[(i+1)%len], {0, 0})));
		}
	}

	// cerr << len << ' ' << acos(0) << '|' << d << ' ' << r << '\n';
	if (d == r) d = 0;


	ld ans = acos(d/r) * r*r - d * sqrt(r*r-d*d);
	cout << fixed << setprecision(6) << ans << '\n';
}
void input(){
	cin >> n >> r;
	FOR(int, i, 1, n) cin >> pts[i].x >> pts[i].y;
}