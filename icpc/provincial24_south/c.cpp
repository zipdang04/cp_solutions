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

#define MAX 1000005
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

int n;
int w[MAX], p[MAX];
int a[MAX], b[MAX];
int pos[MAX];
bool visited[MAX];

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    FOR(int, i, 1, n) cin >> w[i];
    FOR(int, i, 1, n) cin >> a[i];
    FOR(int, i, 1, n) cin >> b[i];

    FOR(int, i, 1, n) pos[b[i]] = i;
    FOR(int, i, 1, n) p[i] = pos[a[i]];
    
    int xxx = 1;
    FOR(int, i, 1, n)
        if (w[a[i]] < w[a[xxx]])
            xxx = i;
    int wA = w[a[xxx]];
    
    ll answer = 0;
    FOR(int, i, 1, n) if (not visited[i]) {
        vector<int> nums;
        int num = i; bool contain = false;
        do {
            contain |= num == xxx;
            nums.push_back(w[a[num]]);
            visited[num] = true;
            // cerr << w[a[num]] <<  ' ';
            num = p[num];
        } while (num != i);
        // cerr  << '\n';
        sort(nums.begin(), nums.end());
        
        int sz = nums.size();
        int wB = nums[0];

        ll tmp = 0;
        if (contain || 1ll * wA * (sz + 1) >= 1ll * wB * (sz - 3)) {
            // cerr << "one ";
            FOR(int, i, 1, sz - 1)
                tmp += wB + nums[i];
        }
        else {
            // cerr << "two ";
            tmp = wA + wB;
            for (int i: nums) tmp += wA + i;
        } 
        // cerr << tmp << '\n';
        answer += tmp;
    } 
    cout << answer;
}