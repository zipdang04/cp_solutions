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
#define pf push_front
#define pb push_back

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORD(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

struct Point{
    int x, y;
};
inline Point operator + (Point a, Point b){return {a.x + b.x, a.y + b.y};}
inline Point operator - (Point a, Point b){return {a.x - b.x, a.y - b.y};}

struct Range{
    int l, r;
};
inline Range merge(Range a, Range b){return {min(a.l, b.l), max(a.r, b.r)};}

int n, m, l;
Point bombs[MAX];
vector<int> graph[MAX];

void buildGraph12(){
    FOR(int, i, 1, m) FOR(int, j, i + 1, m){
        Point diff = bombs[i] - bombs[j];
        if (abs(diff.x) <= l and abs(diff.y) <= l){
            graph[i].push_back(j),
            graph[j].push_back(i);
        }
    }
}
int grIdx[MAX], cntGr;
bool grAns[MAX];
pair<Range, Range> dfs(int node, int group){
    grIdx[node] = group;
    Point curP = bombs[node];
    Range rX = {max(0, curP.x - l), min(n, curP.x + l)}, 
          rY = {max(0, curP.y - l), min(n, curP.y + l)};

    for (int child: graph[node]){
        if (grIdx[child]) continue;

        pair<Range, Range> tmp = dfs(child, group);
        rX = merge(rX, tmp.fi), rY = merge(rY, tmp.se);
    }
    return {rX, rY};
}
void sub12(){
    buildGraph12();
    FOR(int, i, 1, m){
        if (grIdx[i]) continue;
        ++cntGr; pair<Range, Range> tmp = dfs(i, cntGr);
        // cerr << tmp.fi.l << ' ' << tmp.fi.r << '|' << tmp.se.l << ' ' << tmp.se.r << '\n';
        if ((tmp.fi.l == 0 and tmp.fi.r == n) or (tmp.se.l == 0 and tmp.se.r == n))
            grAns[cntGr] = true;
        if ((tmp.fi.l == 0 and tmp.se.l == 0) or (tmp.fi.r == n and tmp.se.r == n))
            grAns[cntGr] = true;
    }
    // FOR(int, i, 1, m) cerr << grIdx[i] << " \n"[i == m];

    vector<int> ansBomb;
    FOR(int, i, 1, m) if (grAns[grIdx[i]])
        ansBomb.push_back(i);
    
    cout << ansBomb.size() << '\n';
    for (int i: ansBomb){
        cout << bombs[i].x << ' ' << bombs[i].y << '\n';
    }
}


void input();
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    input();
    sub12();
}
void input(){
    cin >> n >> m >> l;
    FOR(int, i, 1, m){
        int x, y; cin >> x >> y;
        bombs[i] = {x, y};
    }
}