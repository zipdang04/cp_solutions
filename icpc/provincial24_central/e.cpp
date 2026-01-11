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

#define MAX 105
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

#define SHRINE 'S'
#define MNTAIN '#'

template<class T> struct Point{
    T x, y; 
    Point(T x, T y): x(x), y(y) {}
    Point(): Point(0, 0) {}
};
template<class T> using Vector = Point<T>;
Vector<int> operator + (Vector<int> a, Vector<int> b) {return {a.x + b.x, a.y + b.y};}
const Vector<int> DIREC[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int r, c, n;
char s[MAX][MAX];
Point<int> shrines[MAX]; int cntShrines = 0;
bool satisfied(Point<int> p) {
    return 1 <= p.x && p.x <= r && 1 <= p.y && p.y <= c;
}

#define oo 1'000'000'000
int visited[MAX][MAX];
void bfs(Point<int> root) {
    memset(visited, 0x3f, sizeof(visited));
    queue<Point<int>> q;
    
    visited[root.x][root.y] = 0; 
    q.push(root);
    while (!q.empty()) {
        Point<int> cur = q.front(); q.pop();
        int curDist = visited[cur.x][cur.y];

        for (Vector<int> d: DIREC) {
            Point<int> nxt = cur + d;
            if (not satisfied(nxt) || s[nxt.x][nxt.y] == MNTAIN || visited[nxt.x][nxt.y] < oo)
                continue;
            visited[nxt.x][nxt.y] = curDist + 1;
            q.push(nxt);
        }
    }
}

int dist[MAX][MAX];
int f[1 << 15][MAX];

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> r >> c >> n;
    FOR(int, i, 1, r) cin >> (s[i] + 1);

    FOR(int, i, 1, r) FOR(int, j, 1, c)
        if (s[i][j] == SHRINE)
            shrines[cntShrines++] = {i, j};
    
    memset(dist, 0x3f, sizeof(dist));
    FOR(int, i, 0, n - 1) {
        bfs(shrines[i]);
        FOR(int, j, 0, n - 1)
            dist[i][j] = visited[shrines[j].x][shrines[j].y];
    }

    memset(f, 0x3f, sizeof(f));
    bfs({1, 1});
    FOR(int, i, 0, n - 1) 
        f[1 << i][i] = visited[shrines[i].x][shrines[i].y];
    const int ALL = (1 << n) - 1;
    FOR(int, mask, 1, ALL) FOR(int, u, 0, n - 1)
        if (testBit(mask, u) && f[mask][u] < oo) {
            FOR(int, v, 0, n - 1) if (testBit(mask, v) == false && dist[u][v] >= 0)
                minimize(f[flipBit(mask, v)][v], f[mask][u] + dist[u][v]);
        }
    
    int answer = INT_MAX;
    FOR(int, u, 0, n - 1)
        minimize(answer, f[ALL][u]);
    if (answer >= oo) answer = -1;
    cout << answer;
}