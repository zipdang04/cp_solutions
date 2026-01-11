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

#define MAX 3000000
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




#define DAYS_IN_YEAR 365
#define ADD 400000
int days_past_month[12] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};

int date2int(string s) {
    int year = (int)(s[0] - '0') * 1000
             + (int)(s[1] - '0') * 100
             + (int)(s[2] - '0') * 10
             + (int)(s[3] - '0');
    int month = (int)(s[5] - '0') * 10 + (s[6] - '0') - 1;
    int day = (int)(s[8] - '0') * 10 + (s[9] - '0') - 1;
    return year * DAYS_IN_YEAR + days_past_month[month] + day + ADD;
}
string int2date(int day) {
    day -= ADD;
    int year = day / DAYS_IN_YEAR; day %= DAYS_IN_YEAR;
    int month = upper_bound(days_past_month, days_past_month + 12, day) - days_past_month - 1;
    day -= days_past_month[month];
    month++, day++;
    string sYear = to_string(year); while (sYear.length() < 4) sYear = "0" + sYear;
    string sMonth = to_string(month); while (sMonth.length() < 2) sMonth = "0" + sMonth;
    string sDay = to_string(day); while (sDay.length() < 2) sDay = "0" + sDay;
    return sYear + "-" + sMonth + "-" + sDay;
}







int n, y, d;
int sum[MAX + 1];

bool check(int date) {
    FOR(int, year, 1, y) {
        if (sum[date] - sum[date - DAYS_IN_YEAR] > d) return false;
        date -= DAYS_IN_YEAR;
    }
    return true;
}

main()
{
    FOR(int, i, 1, 11) days_past_month[i] += days_past_month[i - 1];
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n >> y >> d; d = DAYS_IN_YEAR - d;
    int ans = 0;
    FOR(int, _, 1, n) {
        string s1, s2; cin >> s1 >> s2;
        int d1 = date2int(s1), d2 = date2int(s2);
        FOR(int, i, d1, d2)
            sum[i] = 1;
        maximize(ans, max(d1, d2));
    }
    FOR(int, i, 1, MAX) sum[i] += sum[i - 1];
    while (not check(ans)) ans++;

    cout << int2date(ans + 1);
}