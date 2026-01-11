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

#define MAX 10000
#define MOD 1000000007

int _bit[MAX + 5];
struct BIT {
    BIT() {
        memset(_bit, false, sizeof(_bit));
    }
    void update(int idx, int add) {
        while (idx <= MAX) {
            maximize(_bit[idx], add);
            idx += idx & -idx;
        }
    }
    int get(int idx) {
        int answer = 0;
        while (idx) {
            maximize(answer, _bit[idx]);
            idx -= idx & -idx;
        }
        return answer;
    }
} bit;

struct Data{
    int weight, intel, value;
};
bool operator < (Data a, Data b) {
    return (a.weight != b.weight) ? (a.weight < b.weight) : (a.intel < b.intel);
}

int n;
Data a[MAX];

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    FOR(int, i, 1, n) {
        int weight, intel, value; cin >> weight >> intel >> value;
        a[i] = {weight, intel, value};
    }
    sort(a + 1, a + 1 + n);

    int answer = 0;
    FOR(int, i, 1, n) {
        int cur = bit.get(a[i].intel) + a[i].value;
        // cerr << a[i].weight << ' ' << a[i].intel << ' ' << a[i].value << "|" << cur << '\n';
        maximize(answer, cur);
        bit.update(a[i].intel, cur);
    }
    cout << answer;
}