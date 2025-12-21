#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

template <class T1, class T2> void minimize(T1 &a, T2 b) {if (b < a) a = b;}
template <class T1, class T2> void maximize(T1 &a, T2 b) {if (b > a) a = b;}

#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define REV(type, i, a, b) for (type i = (a); i >= (b); i--)

#define MAX 15
#define MOD

enum PieceType{ KNIGHT, BISHOP, ROOK, QUEEN, KING };
PieceType getPieceType(char c) {
	switch (c) {
		case 'N': return KNIGHT;
		case 'B': return BISHOP;
		case 'R': return ROOK;
		case 'Q': return QUEEN;
		case 'K': return KING;
	}
	assert(false);
}
char getPieceChar(PieceType p) {
	switch(p) {
		case KNIGHT: return 'N';
		case BISHOP: return 'B';
		case ROOK: return 'R';
		case QUEEN: return 'Q';
		case KING: return 'K';
	}
	assert(false);
}

struct Point{
	int r, c;
	Point() {r = c = 0;}
	Point(int r, int c): r(r), c(c) {}
	Point(string s) {r = s[0] - 'A'+1, c = s[1] - '0';}
	string getS() const {
		string ans = "";
		ans += char('A' + r-1);
		ans += char('0' + c);
		return ans;
	}
};
Point operator - (Point a, Point b) {return {a.r - b.r, a.c - b.c};}
bool operator < (Point a, Point b) {return (a.r != b.r) ? (a.r < b.r) : (a.c < b.c);}
bool operator > (Point a, Point b) {return (a.r != b.r) ? (a.r > b.r) : (a.c > b.c);}
bool operator == (Point a, Point b) {return (a.r == b.r) and (a.c == b.c);}

struct Piece{
	PieceType type;
	Point pos;
	bool eatable(Point p) const {
		const Point diff = p - pos;
		switch (type){
			case KNIGHT: return abs(diff.r) + abs(diff.c) == 3 and diff.r != 0 and diff.c != 0;
			case BISHOP: return abs(diff.r) == abs(diff.c);
			case ROOK: return diff.r == 0 or diff.c == 0;
			case QUEEN: return abs(diff.r) == abs(diff.c) or diff.r == 0 or diff.c == 0;
			case KING: return abs(diff.r) <= 1 and abs(diff.c) <= 1;
		}
		assert(false);
	}
	bool eatable(Piece p) const {return eatable(p.pos);}
} pieces[MAX]; int n, m;

vector<pair<Piece, Piece>> moves,answer;
void reAssign() {
	if (answer.empty()) answer = moves;
	else {
		FOR(int, i, 0, m-2) {
			if (moves[i].first.pos > answer[i].first.pos) return;
			if (moves[i].first.pos == answer[i].first.pos and moves[i].second.pos == answer[i].second.pos) return;
		}
		cerr << "fucked!";
		answer = moves;
	}
}
void print() {
	for (auto [_1, _2]: answer) {
		auto [type, p1] = _1;
		auto [_, p2] = _2;
		cout << getPieceChar(type) << ": " << p1.getS() << " -> " << p2.getS() << '\n';
	}
}
bool found = false;
void dqql(int iter) {

	if (iter == m) {

		reAssign();
		print(); exit(0);
		return;
	}

	FOR(int, pos, 1, m) if (pieces[pos].pos.r > 0)
	FOR(int, nxt, 1, m) if (pos != nxt and pieces[nxt].pos.r > 0) {
		if (not pieces[pos].eatable(pieces[nxt])) continue;
		const Piece oldPos = pieces[pos], oldNxt = pieces[nxt];
		bool oke = true;
		if (oldPos.type == ROOK or oldPos.type == QUEEN or oldPos.type == BISHOP)
			FOR(int, i, 1, m) if (i != pos and i != nxt and pieces[i].pos.r > 0 and oldPos.eatable(pieces[i])) {
				Point dNxt = oldNxt.pos - oldPos.pos, dI = pieces[i].pos - oldPos.pos;

				if (dNxt.r != dI.r and dNxt.r * dI.r == 0) continue;
				if (dNxt.c != dI.c and dNxt.c * dI.c == 0) continue;
				if (dNxt.r * dI.r < 0) continue;
				if (dNxt.c * dI.c < 0) continue;

				if (dNxt.r > 0) {assert(dI.r > 0); if (dI.r >= dNxt.r) continue;}
				if (dNxt.c > 0) {assert(dI.c > 0); if (dI.c >= dNxt.c) continue;}
				oke = false; break;
			}
		if (not oke) continue;

		moves.push_back({oldPos, oldNxt});
		pieces[pos].pos = {0, 0}, pieces[nxt].type = oldPos.type;

		dqql(iter+1);

		pieces[pos] = oldPos; pieces[nxt] = oldNxt;
		moves.pop_back();
	}
}

void input();
void clear();
int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	FOR(int, i, 1, m) {
		char type; string pos; cin >> type >> pos;
		pieces[i] = {getPieceType(type), Point(pos)};
	}
	sort(pieces + 1, pieces + 1 + m, [](Piece a, Piece b) {return a.pos < b.pos;});
	dqql(1);
	if (answer.empty())
		cout << "No solution\n";
	else
		print();
}
void input(){}
void clear(){}
