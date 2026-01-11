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

int root = 1;
int askAdj(int u){
    cout << "adj " << u << endl;
    int x; cin >> x; 
    if (x == -1) exit(0);
    return x;
}
int askSubtree(int u){
    cout << "subtree " << u << endl;
    int x; cin >> x; 
    return x;
}
void move(int u){
    cout << "move " << u << endl;
    int x; cin >> x; 
    if (x == -1) exit(0);
    root = u;
}

int n;
int THRESHOLD;

vector<int> vList;
void init(){
    FOR(int, i, 2, n) vList.push_back(i);
}

map<int, bool> isBranch;
vector<int> childs[MAX];

bool found = false;

void sub1(){
    while (not found){
        for (int node: vList){
            int branchRoot = askAdj(node);
            isBranch[branchRoot] = true;
            if (branchRoot != node)
                childs[branchRoot].push_back(node);
        }

        int nextRoot = 0;
        for (auto xxx: isBranch){
            int node = xxx.first;
            if (childs[node].size() + 1 > n / 2){
                nextRoot = node; break;
            }
        }

        if (nextRoot == 0) found = true;
        else {
            move(nextRoot);
            vList = childs[nextRoot];
            
            for (auto xxx: isBranch)
                childs[xxx.first].clear();
            isBranch.clear();
        }
    }
}

vector<int> leaves;
vector<int> graph[MAX];
int parent[MAX];
int branchSize[MAX];
void dfs2(int u){
    branchSize[u] = 1;
    for (int v: graph[u]){
        dfs2(v);
        branchSize[u] += branchSize[v];
    }
}
void sub2(){
    FOR(int, i, 2, n)
        if (askSubtree(i) == 1) 
            leaves.push_back(i);
    for(int leaf: leaves){
        while (root != leaf){
            int u = askAdj(leaf);
            parent[u] = root;
            move(u);
        }
        // cerr << "done down\n";
        while (root != 1)
            move(askAdj(1));
    }

    FOR(int, i, 2, n) 
        graph[parent[i]].push_back(i);
    dfs2(1);
    while (true){
        int nextRoot = 0;
        for (int child: graph[root])
            if (branchSize[child] > THRESHOLD){
                nextRoot = child;
                break;
            }
        if (nextRoot == 0) break;
        move(nextRoot);
    }
}

main()
{
    ios_base::sync_with_stdio(0);
    cin >> n;
    THRESHOLD = n / 2;
    init();

    // sub1();
    sub2();
    
    cout << "found" << endl;
}