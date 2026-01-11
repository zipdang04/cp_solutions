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
#define FORD(type, i, b, a) for(type i = (b); i >= (a); i--)

#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

struct Pair{int a, c;};

#define NEGA 0
#define POSI 1
#define oo 1'000'000'000'000'000'000

int n;
Pair pairs[MAX];

ll sumC[2][MAX], sumAC[2][MAX];

bool checkInf(){
    ll sumCoef = 0;
    FOR(int, i, 1, n) sumCoef += pairs[i].c;
    return sumCoef < 0;
}

ll calDiff(ll pos, ll *sumC, ll *sumAC) {
    ll sumPosi = sumAC[n] - sumAC[pos],
       cntPosi = sumC[n] - sumC[pos];
    ll sumNega = sumAC[pos - 1], 
       cntNega = sumC[pos - 1];

    sumPosi -= pairs[pos].a * cntPosi;
    sumNega -= pairs[pos].a * cntNega;
    return sumPosi - sumNega;
}
main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests; cin >> tests;
    FOR(int, _, 1, tests) {
        cin >> n;
        FOR(int, i, 1, n) cin >> pairs[i].a;
        FOR(int, i, 1, n) cin >> pairs[i].c;
        if (checkInf()) {cout << "-inf\n"; continue;}

        sort(pairs + 1, pairs + 1 + n, [](Pair a, Pair b){return a.a < b.a;});

        FOR(int, x, 0, 1) {
            FOR(int, i, 1, n) {
                bool doesAdd = (x == NEGA ? pairs[i].c < 0 : pairs[i].c > 0);
                ll a = pairs[i].a, c = abs(pairs[i].c);
                sumC[x][i] = sumC[x][i - 1] + (doesAdd ? c : 0);
                sumAC[x][i] = sumAC[x][i - 1] + (doesAdd ? a * c : 0);
            }
        }
        // FOR(int, i, 1, n)
        //     cerr << pairs[i].a << '|' << pairs[i].c << " \n"[i == n];
        // FOR(int, x, 0, 1)
        //     FOR(int, i, 1, n)
        //         cerr << sumC[x][i] << " \n"[i == n];
        // FOR(int, x, 0, 1)
        //     FOR(int, i, 1, n)
        //         cerr << sumAC[x][i] << " \n"[i == n];



        ll answer = oo, posAns = 0;
        FOR(int, i, 1, n) {
            ll current = calDiff(i, sumC[POSI], sumAC[POSI]) - calDiff(i, sumC[NEGA], sumAC[NEGA]);
            // cerr << i << '|' << current << " \n"[i == n];
            minimize(answer, current);
        }

        cout << answer << '\n';
    }
}