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

#define MAX_N 101
#define MAX_K 1001
#define MOD 1000000007

#define fi first
#define se second

#define FOR(type, i, a, b) for(type i = (a); i <= (b); i++)
#define FORD(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());


map<int, int> numDepth;
map<int, int> lastAppear;
int n, k;
int sheet[MAX_N][MAX_K];
bool isLeaf[MAX_N];
int need[MAX_N];

void input();
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    input(); memset(isLeaf, true, sizeof(isLeaf));

    FOR(int, i, 1, n) {
        FOR(int, j, 1, k) {
            int num = sheet[i][j], prevI = lastAppear[num];
            if (prevI != i) isLeaf[prevI] = false;
            lastAppear[num] = i; numDepth[num]++;
        }
    }
    cout << fixed << setprecision(7);
    int total = 0;

    for (auto xx: lastAppear) {
        int num = xx.first;
        int pos = lastAppear[num];
        int cnt = numDepth[num];
        need[pos] += cnt; total += cnt;
    }

    FOR(int, i, 1, n)
        cout << need[i] /(ld)total << "\n\n"[i == n];
}
void input(){
    cin >> n >> k;
    FOR(int, i, 1, n) FOR(int, j, 1, k) cin >> sheet[i][j];
}

