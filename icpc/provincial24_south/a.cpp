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

int n, m;
ll bit3d[MAX][MAX][MAX];
int old[MAX][MAX][MAX];
void update(int x, int y, int z, int add) {
    for (int xx = x; xx <= n; xx += xx & -xx)
        for (int yy = y; yy <= n; yy += yy & -yy)
            for (int zz = z; zz <= n; zz += zz & -zz)  {
                bit3d[xx][yy][zz] += add;
            }
}
ll get(int x, int y, int z) {

    ll answer = 0;
    for (int xx = x; xx > 0; xx -= xx & -xx) {
        for (int yy = y; yy > 0; yy -= yy & -yy)
            for (int zz = z; zz > 0; zz -= zz & -zz) {
                answer += bit3d[xx][yy][zz];
            }
    }
    return answer;
}

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    FOR(int, ___, 1, t) {
        memset(bit3d, 0, sizeof(bit3d));
        memset(old, 0, sizeof(old));

        cin >> n >> m;
        FOR(int, _, 1, m) {
            string query; cin >> query;
            if (query == "UPDATE") {
                int x, y, z, w; cin >> x >> y >> z >> w;
                update(x,  y,  z, w - old[x][y][z]);
                old[x][y][z] = w;
            } else {
                int x, y, z, x1, y1, z1;
                cin >> x >> y >> z >> x1 >> y1 >> z1;
                ll answer =  0;
                FOR(int, i, 0, 1) FOR(int, j, 0, 1) FOR(int, k, 0, 1) {
                    int xx = i ? x1 : (x - 1);
                    int yy = j ? y1 : (y - 1);
                    int zz = k ? z1 : (z - 1);
                    answer += get(xx, yy, zz) * (((i+j+k) & 1) ? 1 : -1);
                }
                cout << answer << '\n';
            }
        }
    }
}