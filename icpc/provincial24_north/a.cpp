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
#define CURRENT_TIMESTAMP chrono::steady_clock::now().time_since_epoch().count()
#define randomize mt19937_64 mt(CURRENT_TIMESTAMP)

#define MAX 10001
#define oo 1000000007


int n, D, H;
int h[MAX];

multiset<int, greater<int>> maxSet[MAX];

int _it[MAX * 4];
class SegTree{
    private:
        int len;
        void update(int idx, int lo, int hi, int pos, int add) {
            // cerr << "update " <<  idx << ' ' << lo << ' ' << hi << ' ' << pos << ' ' << add << '\n';
            if (lo == hi) {
                int pos = lo;
                if (add > 0) 
                    maxSet[pos].insert(add);
                else
                    maxSet[pos].erase(maxSet[pos].find(-add));
                _it[idx] = maxSet[pos].empty() ? oo : *maxSet[pos].begin();
                return;
            }
            int y = idx << 1, mid = (lo + hi) / 2;
            if (pos <= mid)
                update(y, lo, mid, pos, add);
            else
                update(y + 1, mid + 1, hi, pos, add);
            _it[idx] = min(_it[y], _it[y + 1]);
        }
        int get(int idx, int lo, int hi, int posL, int posR) {
            // cerr << "get " <<  idx << ' ' << lo << ' ' << hi << ' ' << posL << ' ' << posR << '\n';
            if (hi < posL || posR < lo) return oo;
            if (posL <= lo && hi <= posR) return _it[idx];
            int y = idx << 1, mid = (lo + hi) >> 1;
            return min(
                get(y, lo, mid, posL, posR),
                get(y + 1, mid + 1, hi, posL, posR)
            );
        }
    public:
        SegTree(int len = 0) {
            this -> len = len;
            memset(_it, 0x3f, sizeof(_it));
        }
        void update(int pos, int add) {
            // cerr << "update " << pos << ' ' << add << '\n';
            update(1, 1, len, pos, add);
        }
        int get(int posL, int posR) {
            int tmp =  get(1, 1, len, posL, posR);
            // cerr << "get " << posL << ' ' << posR << '=' << tmp << '\n';
            return tmp;
        }
} seg;
int f[MAX];


main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> D >> H;
    FOR(int, i, 1, n) cin >> h[i];

    memset(f, 0x3f, sizeof(f));
    f[1] = h[1];
    FOR(int, i, 2, n) {
        FOR(int, j, max(1, i - D), i - 1){

            if (f[j] < oo && abs(h[j] - h[i]) <= H) 
                minimize(f[i], f[j] + h[i]);
        }
    }
    cout << (f[n] < oo ? f[n] : -1);


    // seg = SegTree(10000);

    // ll answer = 0;
    // f[1] = h[1]; seg.update(h[1], f[1]);
    // FOR(int, i, 2, n) {
    //     if (i > D + 1){
    //         int delPos = i - (D + 1);
    //         if (f[delPos])
    //             seg.update(h[delPos], -f[delPos]);
    //     }
    //     int lo = max(h[i] - H, 1), hi = min(h[i] + H, 10000);
    //     int tmp = seg.get(lo, hi);
    //     if (tmp >= 1e9) continue;
    //     f[i] += tmp + h[i];
    //     // cerr << i << ' ' << f[i] << '\n';

    //     maximize(answer, f[i]);
    //     seg.update(h[i], f[i]);
    // }
    // cout << ((f[n] == 0) ? -1 : f[n]) ;
}