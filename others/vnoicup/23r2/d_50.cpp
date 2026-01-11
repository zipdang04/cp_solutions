#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

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

#define MAX 80005
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

int n, m, len;
int *h[MAX];

int val[MAX];
int* it[MAX * 2];
int lenIt[MAX * 2];
inline void shapeArray(){
    FOR(int, i, len, 2 * len){
        lenIt[i] = 1; it[i] = new int[1];
    }
    FORD(int, i, len-1, 1){
        lenIt[i] = lenIt[i << 1] + lenIt[i << 1 | 1];
        it[i] = new int[lenIt[i]];
    }
}
inline void merge(int one, int two, int ans){
    const int *arrOne = it[one], *arrTwo = it[two];
    int *arrAns = it[ans];
    int lenOne = lenIt[one], lenTwo = lenIt[two], lenAns = lenOne + lenTwo;
    int i = 0, j = 0, k = 0;
    while (i < lenOne && j < lenTwo){
        if (arrOne[i] < arrTwo[j]) arrAns[k++] = arrOne[i++];
        else arrAns[k++] = arrTwo[j++];
    }
    while (i < lenOne) arrAns[k++] = arrOne[i++];
    while (j < lenTwo) arrAns[k++] = arrTwo[j++];
}
inline void buildTree(){
    FOR(int, i, 1, len)
        it[i+len-1][0] = val[i];
    FORD(int, i, len-1, 1)
        merge(i << 1, i << 1 | 1, i);
}
inline int query(int qLo, int qHi, int val){
    qLo--, qHi;
    int ans = 0;
    for (qLo += len, qHi += len; qLo < qHi; qLo >>= 1, qHi >>= 1){
        if (qLo & 1){
            ans += upper_bound(it[qLo], it[qLo] + lenIt[qLo], val) - it[qLo];
            qLo++;
        }
        if (qHi & 1){
            qHi--;
            ans += upper_bound(it[qHi], it[qHi] + lenIt[qHi], val) - it[qHi];
        }
    }
    return ans;
}

void input();
main()
{
    input(); 
    len = m;
    shapeArray();

    ll answer = 0;
    FOR(int, r1, 1, n) FOR(int, r2, r1 + 1, n){
        memset(val, 0x3f, sizeof(val));
        FOR(int, c, 1, m){
            if (h[r1][c] < r2 - r1) continue;
            val[c] = c - h[r2][c];
        }
        buildTree();

        FOR(int, cLo, 1, m){
            if (h[r2][cLo] < r2 - r1) continue;
            int cHi = min(m, cLo + h[r1][cLo]);
            answer += query(cLo + 1, cHi, cLo);
        }
    }
    cout << answer;
}
void input(){
    read(n, m);
    if (n <= m){
        FOR(int, i, 1, n) h[i] = new int[(m+2)];
        FOR(int, i, 1, n)
            FOR(int, j, 1, m) read(h[i][j]);
    } else {
        FOR(int, i, 1, m) h[i] = new int[(n+2)];
        FOR(int, i, 1, n)
            FOR(int, j, 1, m) read(h[j][n - i + 1]);
        swap(m, n);
    }
}
