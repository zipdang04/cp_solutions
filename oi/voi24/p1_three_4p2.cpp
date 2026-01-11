#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/

typedef long long ll;
typedef __int128_t bignum;
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

#define MAX 100005
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

struct Point {
    int r, c; int i;
};

int n, m, q;
int r[MAX], c[MAX];
ll w[MAX];

int valR[MAX], cntR;
int valC[MAX], cntC;
void compress() {
    FOR(int, i, 1, m) valR[i] = r[i], valC[i] = c[i];
    sort(valR + 1, valR + 1 + m);
    sort(valC + 1, valC + 1 + m);
    cntR = unique(valR + 1, valR + 1 + m) - valR - 1;
    cntC = unique(valC + 1, valC + 1 + m) - valC - 1;

    FOR(int, i, 1, m) {
        r[i] = lower_bound(valR + 1, valR + 1 + cntR, r[i]) - valR;
        c[i] = lower_bound(valC + 1, valC + 1 + cntC, c[i]) - valC;
    }
}

// TODO: chỉnh lại kiểu dữ liệu
struct Bests{
    bignum best, scnd, thrd;
    Bests(bignum best = 0, bignum scnd = 0, bignum thrd = 0){
        this -> best = best, 
        this -> scnd = scnd,
        this -> thrd = thrd;
    }
    inline void addNum(bignum num) {
        if (num >= best) 
            thrd = scnd, scnd = best, best = num;
        else if (num >= scnd)
            thrd = scnd, scnd = num;
        else
            maximize(thrd, num);
    }
    inline void addNum(Bests bests) {
        addNum(bests.best); addNum(bests.scnd);
    }
    inline bignum sum(int cnt) {return best + scnd * (cnt >= 2) + thrd * (cnt >= 3);}
};
Bests combine(Bests a, Bests b) {
    a.addNum(b.best);
    a.addNum(b.scnd);
    return a;
}
Bests itR[MAX * 4], itC[MAX * 4];
class SegTree{
    private:
        int len;
        Bests *it;
        void update(int idx, int lo, int hi, int pos, bignum val) {
            if (lo == hi) {
                it[idx].best += val;
                return;
            }

            int y = idx << 1, mid = (lo + hi) >> 1;
            if (pos <= mid)
                update(y, lo, mid, pos, val);
            else
                update(y + 1, mid + 1, hi, pos, val);
            it[idx] = combine(it[y], it[y + 1]);
        }
        Bests get(int idx, int lo, int hi, int posL, int posR) {
            if (hi < posL || posR < lo) return Bests();
            if (posL <= lo && hi <= posR) return it[idx];

            int y = idx << 1, mid = (lo + hi) >> 1;
            return combine(
                get(y, lo, mid, posL, posR),
                get(y + 1, mid + 1, hi, posL, posR)
            );
        }

    public:
        SegTree(int len = 0, Bests *it = nullptr) {
            this -> len = len;
            this -> it = it;
        }
        void update(int pos, bignum val) {
            return update(1,1, len, pos, val);
        }
        Bests get(int posL, int posR) {
            return get(1, 1, len, posL, posR);
        }
};

vector<Point> allR[MAX], allC[MAX];
SegTree segR, segC;

bignum calculate(){
    bignum answer = max(
        segR.get(1, cntR).sum(3),
        segC.get(1, cntC).sum(3)
    );

    // for r find 2c
    FOR(int, row, 1, cntR) {
        bignum curAns = segR.get(row, row).best;
        // remove
        for (Point p: allR[row])
            segC.update(p.c, -w[p.i]);
        // calculate
        curAns += segC.get(1, cntC).sum(2);
        // add again
        for (Point p: allR[row])
            segC.update(p.c, w[p.i]);
        
        maximize(answer, curAns);
    }
    FOR(int, col, 1, cntC) {
        bignum curAns = segC.get(col, col).best;
        for (Point p: allC[col])
            segR.update(p.r, -w[p.i]);
        curAns += segR.get(1, cntR).sum(2);
        for (Point p: allC[col])
            segR.update(p.r, w[p.i]);
        maximize(answer, curAns);
    }
    return answer;
}

void clear() {
    FOR(int, i, 1, m * 4)
        itR[i] = itC[i] = 0;
    FOR(int, i, 1, m) allR[i].clear(), allC[i].clear();
}

inline ostream& operator << (ostream& out, bignum num) {
    ll ans = num;
    string s = ""; while (num) s += char('0' + num % 10), num /= 10;
    FORD(int,i, (int)s.size() - 1, 0) out << s[i];
    return out;
}

main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    #ifndef HIEU
    freopen("three.inp", "r", stdin);
    freopen("three.out", "w", stdout);
    #endif

    int tests; cin >> tests;
    FOR(int, _, 1, tests) {
        cin >> n >> m >> q;
        FOR(int, i, 1, m) cin >> r[i] >> c[i] >> w[i];
        
        compress();
        segR = SegTree(cntR, itR);
        segC = SegTree(cntC, itC);
        FOR(int, i, 1, m) {
            segR.update(r[i], w[i]);
            segC.update(c[i], w[i]);
            allR[r[i]].push_back({r[i], c[i], i});
            allC[c[i]].push_back({r[i], c[i], i});
        }

        cout << calculate() << '\n';
        FOR(int, qq, 1, q) {
            int t; ll d; cin >> t >> d;
            Point p = {r[t], c[t], 0};
            w[t] += d; segR.update(p.r, d); segC.update(p.c, d);
            cout << calculate() << '\n';
            w[t] -= d; segR.update(p.r, -d); segC.update(p.c, -d);
        }

        clear();
    }
}