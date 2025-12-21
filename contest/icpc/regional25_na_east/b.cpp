#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template <class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template <class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX_NODES 100'005
#define MAX_LVL 25
#define MOD

enum NodeType{ NODE_AND, NODE_OR };
struct Node {
	NodeType type; int len;
	int cntT = false, cntF = false;
	vector<int> children;

	Node() {}
	Node(NodeType type, int len): type(type), len(len), cntT(false), cntF(false) {children.clear();}
} nodes[MAX_NODES]; int cntNode = 0;
int n;
vector<string> all[MAX_LVL];

vector<int> levels[MAX_LVL];

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	input();
}

pair<bool, int> dp(int u) {
	int totalT = nodes[u].cntT, totalF = nodes[u].cntF;
	int costF2T = totalF, costT2F = totalT;
	int minF2T = totalF ? 1 : INT_MAX, minT2F = totalT ? 1 : INT_MAX;
	for (int v: nodes[u].children) {
		auto [eval, cost] = dp(v);
		if (eval == true)
			totalT++, costT2F += cost, minimize(minT2F, cost);
		else
			totalF++, costF2T += cost, minimize(minF2T, cost);
	}

	if (nodes[u].type == NODE_AND) {
		if (totalF > 0)
			return {false, costF2T};
		assert(minT2F != INT_MAX);
		return {true, minT2F};
	} else { // OR
		if (totalT > 0)
			return {true, costT2F};
		assert(minF2T != INT_MAX);
		return {false, minF2T};
	}
}

void print() {
	FOR(int, i, 1, cntNode) {
		cerr << i << ' ' << (nodes[i].type == NODE_AND ? "AND" : " OR") << '|' << nodes[i].cntT << "T " << nodes[i].cntF << "F|";
		for (int child: nodes[i].children) cerr << child << ' ';
		cerr << '\n';
	}
}

void input(){
	nodes[0] = Node(NODE_AND, 1); levels[0].push_back(0);
	char _tmpC; NodeType type;
	cin >> n >> _tmpC;
	type = _tmpC == 'A' ? NODE_AND : NODE_OR;
	FOR(int, lvl, 1, n) {
		for (const int par: levels[lvl-1]) {
			FOR(int, i, 1, nodes[par].len) {
				string s; cin >> s;
				if (isalpha(s[0]))
					nodes[par].cntF += s[0] == 'F',
					nodes[par].cntT += s[0] == 'T';
				else {
					const int len = stoi(s), child = ++cntNode;
					levels[lvl].push_back(child);
					nodes[child] = Node(type, len);
					nodes[par].children.push_back(child);
				}
			}
		}
		type = (type == NODE_AND) ? NODE_OR : NODE_AND;
	}
	auto [eval, cost] = dp(1);
	cout << cost << '\n';
}
void clear(){}
