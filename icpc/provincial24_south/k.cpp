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

#define MAX 1000001
#define MOD 1000000007

#define fi first
#define se second

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define REV(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define CURRENT_TIMESTAMP chrono::steady_clock::now().time_since_epoch().count()
#define randomize mt19937_64 mt(CURRENT_TIMESTAMP)

struct Point{
    int x, y; 
    Point(){x=y=0;}
    Point(int x, int y): x(x), y(y){}
};
typedef Point Vector;

int n, p, m;
Vector operator + (Vector a, Vector b) {
    return {(a.x + b.x) % n, (a.y + b.y) % n};
}
Vector operator * (Vector a, int b) {
    return {1ll * a.x * b % n, 1ll * a.y * b % n};
}
Vector direc[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

Point points[MAX];
vector<int> group[4];
Vector offset[4];
int d[MAX];
bool existZ = false;

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> p >> m;
    FOR(int, i, 0, 3)
        direc[i].x = (direc[i].x + n) % n,
        direc[i].y = (direc[i].y + n) % n;

    FOR(int, i, 1, p) {
        int x, y, dd; cin >> x >> y >> dd;
        points[i] = {x, y};
        dd %= 4;
        d[i] = dd;
        group[dd].push_back(i);
    }

    FOR(int, i, 0, 3) d[i] = i;

    FOR(int, _, 1, m){
        char c; int k; cin >> c >> k;
        if (c == 'A') {
            FOR(int, i, 0, 3)
                offset[i] = offset[i] + (direc[d[i]] * k);
        } else if (c == 'R') {
            FOR(int, i, 0, 3)
                d[i] = (d[i] + k) % 4;
        } else {
            existZ = true;
            FOR(int, i, 0, 3)
                offset[i] = Point(k / n, k % n);
        }
    }

    FOR(int, i, 0, 3)
        for (int pos: group[i]) {
            // cerr << i << '|' << pos << '\n';
            if (existZ)
                points[pos] = offset[i];
            else
                points[pos] = points[pos] + offset[i];
        }
    FOR(int, i, 1, p)
        cout << points[i].x << ' ' << points[i].y << '\n';

}