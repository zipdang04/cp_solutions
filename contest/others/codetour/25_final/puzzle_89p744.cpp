#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
template <class T> using PQMax = std::priority_queue<T>;
template <class T> using PQMin = std::priority_queue<T, std::vector<T>, std::greater<T>>;
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
#define log2(n) (31 - __builtin_clz(n))
#define log2ll(n) (63 - __builtin_clzll(n))
#define CURRENT_TIMESTAMP std::chrono::steady_clock::now().time_since_epoch().count()
#define randomize std::mt19937_64 mt(CURRENT_TIMESTAMP)
randomize;
class Randomize {
	public:
	double next(double lim) {
		return lim * ((mt() % 1'000'000'000) / (double)1'000'000'000);
	}
} rnd;

#define MAX 1000001
#define MOD 1000000007

class Exception: public std::exception {
	protected:
		std::string message;
	private:
		std::string prefix;
		const char* what() const throw() override {
			return (prefix + ": " +  message).c_str();
		}
	public:
		Exception(std::string prefix, std::string message) {
			this -> prefix = prefix;
			this -> message = message;
		}
};

class NotImplementedException: public Exception {
	inline static const std::string PREFIX = "NotImplementedException";
	public:
		NotImplementedException(std::string message): Exception(PREFIX, message) {}
};

template<typename State>
struct Transition {
	std::string action;
	State state;
	double cost;
	Transition(std::string action, State state, double cost)
	: action(action), state(state), cost(cost) {}
};
template<typename State>
class Problem {
	protected:
		State SOURCE, DESTINATION;
	public:
		Problem(State SOURCE, State DESTINATION) {
			this -> SOURCE = SOURCE;
			this -> DESTINATION = DESTINATION;
		}
		State getSource() { return SOURCE; }
		State getDestination() { return DESTINATION; }

		virtual double heuristic(State state) {
			throw NotImplementedException("no heuristics implemented");
		}
		virtual std::vector<Transition<State>> getAdjacent(State state) {
			throw NotImplementedException("no adjacent-finding functions implemented");
		}
};

class BoardMove {
	private:
		BoardMove(std::string c, int diffX, int diffY): c(c), diffX(diffX), diffY(diffY) {}
	public:
		std::string c; int diffX, diffY;

		static BoardMove GET_L() { return BoardMove("L", 0, -1); }
		static BoardMove GET_R() { return BoardMove("R", 0, +1); }
		static BoardMove GET_U() { return BoardMove("U", -1, 0); }
		static BoardMove GET_D() { return BoardMove("D", +1, 0); }
		static std::vector<BoardMove> ALL() {
			static const std::vector<BoardMove> ALL = {
				GET_L(), GET_U(), GET_R(), GET_D()
			};
			return ALL;
		}

		std::pair<int, int> from(int x, int y) {
			return {x + diffX, y + diffY};
		}
};

class Board {
	private:
		static bool DEBUG_MODE;

		int blankX, blankY;
		std::vector<int> board;

		void _selfMove(BoardMove move);
		static inline int getIndex(int row, int col) { return row * SIZE_COL + col; }
	public:
		static void DEBUG() { DEBUG_MODE = true; }

		static const int BLANK = 0, NaN = -1;
		static int SIZE_ROW, SIZE_COL, MAX_VALUE;
		static inline void changeSize(int sizeRow, int sizeCol);

		Board(std::string tmp) {if (tmp != "NOT_INIT") throw NotImplementedException("Not initialized yet");}
		Board();
		Board(int size);
		Board(std::vector<int> board, int blankX, int blankY);

		inline int operator[] (int idx) const;
		inline int get(int row, int col) const;
		inline bool operator != (Board board) const;
		inline bool operator == (Board board) const;
		inline bool operator < (Board board) const;
		inline bool operator > (Board board) const;

		inline int X() { return blankX; }
		inline int Y() { return blankY; }
		inline bool isSolved();
		inline bool isSolvable();

		inline Board move(BoardMove move);
		std::string toString() const;
};

class InvalidMoveException: public Exception {
	inline static const std::string PREFIX = "InvalidMoveException";
	public:
		InvalidMoveException(Board board, BoardMove move): Exception(PREFIX, "") {
			message = "Tried to move " + move.c + " at board " + board.toString();
		}
};
class InvalidBoardException: public Exception {
	inline static const std::string PREFIX = "InvalidBoardException";
	public:
		InvalidBoardException(std::string message): Exception(PREFIX, message) {}
};


template<>
inline double Problem<Board>::heuristic(Board);

template<>
std::vector<Transition<Board>> Problem<Board>::getAdjacent(Board);

//========================================================================================================================================================================

int Board::SIZE_ROW = 0;
int Board::SIZE_COL = 0;
int Board::MAX_VALUE = 0;

void Board::changeSize(int sizeRow, int sizeCol) {
	if (SIZE_ROW != 0)
		throw InvalidBoardException("Board SIZE already defined");
	SIZE_ROW = sizeRow, SIZE_COL = sizeCol; MAX_VALUE = sizeRow * sizeCol;
}

Board::Board() {
	if (SIZE_ROW == 0)
		throw InvalidBoardException("Board SIZE not yet defined");
	board = std::vector<int>(MAX_VALUE);
	blankX = 0, blankY = 0;
	std::iota(board.begin(), board.end(), 0);
}
Board::Board(int size) {
	if (size == 0)
		throw InvalidBoardException("Init size must be different than 0");
	changeSize(size, size);

	blankX = 0, blankY = 0;
	board = std::vector<int>(MAX_VALUE);
	std::iota(board.begin(), board.end(), 0);
}
Board::Board(std::vector<int> board, int blankX = 0, int blankY = 0) {
	if (SIZE_ROW == 0)
		throw InvalidBoardException("Board SIZE not yet defined");
	if (MAX_VALUE != (int)board.size())
		throw InvalidBoardException("The board inputed did not match the required size");
	this->board = board;
	if (this->get(blankX, blankY) != BLANK)
		for (int x = 0; x < SIZE_ROW; x++) for (int y = 0; y < SIZE_COL; y++) {
			if (this->get(x, y) == BLANK) {
				blankX = x, blankY = y;
				break;
			}
		}

	this -> blankX = blankX;
	this -> blankY = blankY;
}

int Board::operator[] (int idx) const { return board[idx]; }
int Board::get(int row, int col) const { return board[getIndex(row, col)]; }
bool Board::operator < (Board board) const {
	for (int i = 0; i < MAX_VALUE; i++)
		if (this->board[i] != board[i])
			return this->board[i] < board[i];
	return false;
}
bool Board::operator > (Board board) const {
	for (int i = 0; i < MAX_VALUE; i++)
		if (this->board[i] != board[i])
			return this->board[i] > board[i];
	return false;
}
bool Board::operator == (Board board) const {
	for (int i = 0; i < MAX_VALUE; i++)
		if (this->board[i] != board[i])
			return false;
	return true;
}
bool Board::operator != (Board board) const {
	return not (*this == board);
}


void Board::_selfMove(BoardMove move) {
	auto [newX, newY] = move.from(blankX, blankY);
	if (newX < 0 or newY < 0 or newX >= SIZE_ROW or newY >= SIZE_COL)
		throw InvalidMoveException(*this, move);
	// ADD check no move in -1
	if (get(newX, newY) == -1)
		throw InvalidMoveException(*this, move);

	std::swap(board[getIndex(blankX, blankY)], board[getIndex(newX, newY)]);
	blankX = newX, blankY = newY;
}

Board Board::move(BoardMove move) {
	Board board = *this;
	board._selfMove(move);
	return board;
}
std::string Board::toString() const {
	std::string s = "";
	// std::string s = "[";
	int ptr = 0;
	for (int row = 0; row < SIZE_ROW; row++) {
		std::string ending = " ";
		ending += "\n";
		// ending +=  char((row == SIZE_ROW - 1) ? ']' : ';');
		for (int col = 0; col < SIZE_COL; col++)
			s += std::to_string(board[ptr++]) + ending[col == SIZE_COL - 1];
	}
	return s;
}

bool Board::isSolved() {
	// TODO
	assert(false);
	// for (int i = 0; i < MAX_VALUE; i++)
	// 	if (board[i] != i) return false;
	// return true;
}

bool Board::isSolvable() {
	return true;
	// the board is reversed
}

template<>
struct std::hash<Board> {
	std::size_t operator()(const Board &p) const
    {
        unsigned long long num = 0;
		for (int i = 0; i < Board::MAX_VALUE; i++)
			num = (num << 5) | p[i];
		return num;
    }
};

namespace Heuristic {
	int destRow[100], destCol[100];
	inline double ManhattanDistance(Board board) {
		int ptr = 0, answer = 0;
		for (int row = 0; row < Board::SIZE_ROW; row++)
		for (int col = 0; col < Board::SIZE_COL; col++, ptr++){
			int value = board.get(row, col);
			if (value < 0) continue;
			int vRow = destRow[value], vCol = destCol[value];
			answer += (value > 0) * (std::abs(row - vRow) + std::abs(col - vCol));
		}
		return answer;
	}
}
template<>
double Problem<Board>::heuristic(Board board) {
	// return Heuristic::LinearConflictDistance(board);
	return Heuristic::ManhattanDistance(board);
}
template<>
std::vector<Transition<Board>> Problem<Board>::getAdjacent(Board board) {
	std::vector<BoardMove> validMoves = BoardMove::ALL();
	std::vector<Transition<Board>> v;
	for (BoardMove move: validMoves) {
		try {
			v.emplace_back(move.c, board.move(move), 1);
		} catch (InvalidMoveException ex) {}
	}
	return v;
}

template<class State>
struct StateInfo {
	State state; double f, g, h, hFocal;
	StateInfo(State state, double f, double g, double h, double hFocal): state(state), f(f), g(g), h(h), hFocal(hFocal) {}

	bool operator < (StateInfo a) const {
		return (f != a.f) ? (f < a.f) : (
			(g != a.g) ? (g < a.g) : (
				(h != a.h) ? (h < a.h) : (
					(hFocal != a.hFocal) ? (hFocal < a.hFocal) : (state < a.state)
				)
			)
		);
	}
	bool operator > (StateInfo a) const {
		return (f != a.f) ? (f > a.f) : (
			(g != a.g) ? (g > a.g) : (
				(h != a.h) ? (h > a.h) : (
					(hFocal != a.hFocal) ? (hFocal > a.hFocal) : (state > a.state)
				)
			)
		);
	}
	bool operator == (StateInfo a) const {
		return state == a.state
			&& f == a.f
			&& g == a.g
			&& h == a.h
			&& hFocal == a.hFocal;
	}
};
using duration = std::chrono::_V2::high_resolution_clock::duration;
class Algorithm{
	private:
		inline static const int MICROSECONDS = 1'000'000;
		inline static long long TIME_LIMIT = 600ll * MICROSECONDS;
		duration beginTime, endTime;
	protected:
		// static
		std::string algoName;
		bool hasRun = false;

		virtual void execute() {
			throw NotImplementedException("No Algorithm::execute() yet");
		};
	public:
		std::string getName() {return algoName;}
		Algorithm* changeName(std::string name) {algoName = name; return this;}
		inline static void changeTimeLimit(long long seconds) {TIME_LIMIT = seconds * MICROSECONDS;}

		double measure() {
			execute();
			return 1;
		};
		virtual ~Algorithm() {};
};
template<class State>
class SearchingAlgorithm: public Algorithm {
	private:
		inline static const int TLCHECK_CYCLE = 2'000;
		bool FINISHED = false;
		long long iteration = 0, modulo = 0;
		long long maxSize = 0;
		double answer = 0; State ansState;
	protected:
		Problem<State> statement;
		std::unordered_map<State, double> g;
		std::unordered_map<State, std::string> actionTrace;

		inline void FINISH_SEARCHING(State ansState) {
			this -> ansState = ansState;
			this -> answer = (this -> g)[ansState];
			FINISHED = true;
		}
		inline bool ITERATION_CHECK() {
			return false;
		}
		inline void UPDATE_SIZE(long long size) {
			if (size > this -> maxSize)
				this -> maxSize = size;
		}

		virtual inline StateInfo<State> buildStateInfo(State state, double g) {
			double h = statement.heuristic(state);
			double f = g + h;
			double hFocal = h;//g + 1.05 * h;
			return StateInfo<State>(state, f, g, h, hFocal);
		}

	public:
		SearchingAlgorithm(Problem<State> statement): statement(statement) {}
		virtual std::vector<std::string> getTrace() { throw NotImplementedException("no trace function found"); }
		long long getExpandedCount() { return g.size(); }
		long long getIterationCount() { return iteration; }
		long long getMaxSize() { return maxSize; }
		double getAnsState() { return ansState; }
		double getAnswer() { return answer; }
};



class InvalidTraceException: public Exception {
	inline static const std::string PREFIX = "InvalidTraceException";
	public:
		InvalidTraceException(std::string message): Exception(PREFIX, message) {}
};

template<>
std::vector<std::string> SearchingAlgorithm<Board>::getTrace() {
	if (not FINISHED) return {};

	Board board = statement.getDestination();
	std::vector<std::string> actions;

	while (board != statement.getSource()) {
		std::string action = actionTrace[board];
		// std::cerr << board.toString() << ' ' << action << '\n';
		actions.push_back(action);
		if (action == "L") board = board.move(BoardMove::GET_R());
		else if (action == "R") board = board.move(BoardMove::GET_L());
		else if (action == "U") board = board.move(BoardMove::GET_D());
		else if (action == "D") board = board.move(BoardMove::GET_U());
		else throw InvalidTraceException(std::format("There is an invalid move ({}) when tracing from {}", action, board.toString()));
	}

	std::reverse(actions.begin(), actions.end());
	return actions;
}
template<class State>
class ProbabilisticFocalSearch: public SearchingAlgorithm<State> {
	private:
		struct CompareF {
			bool operator() (StateInfo<State> a, StateInfo<State> b) const {
				if (a.f != b.f) return a.f < b.f;
				if (a.g != b.g) return a.g < b.g;
				if (a.h != b.h) return a.h < b.h;
				if (a.hFocal != b.hFocal) return a.hFocal < b.hFocal;
				return a.state < b.state;
			}
		};
		struct CompareH {
			bool operator() (StateInfo<State> a, StateInfo<State> b) const {
				if (a.hFocal != b.hFocal) return a.hFocal < b.hFocal;
				if (a.h != b.h) return a.h < b.h;
				if (a.g != b.g) return a.g < b.g;
				if (a.f != b.f) return a.f < b.f;
				return a.state < b.state;
			}
		};
		std::set<StateInfo<State>, CompareF> openList;
		std::set<StateInfo<State>, CompareH> focalList;

		void updateFocal(double oldBound, double newBound) {
			auto it = openList.lower_bound(StateInfo<State>(State(), oldBound, 0, 0, 0));
			while (it != openList.end() and it -> f <= newBound) {
				focalList.insert(*it); it++;
			}
		}
		void execute() override {
			State _start = (this -> statement).getSource();
			StateInfo<State> _startInfo = this -> buildStateInfo(_start, 0);

			(this -> g)[_start] = 0;
			(this -> actionTrace)[_start] = "";
			openList.insert(StateInfo<State>(_startInfo));
			focalList.insert(StateInfo<State>(_startInfo));

			while (not openList.empty()) {
				this -> UPDATE_SIZE(openList.size() + focalList.size());

				double fMin = openList.begin() -> f;
				StateInfo<State> node = focalList.empty() ? *openList.begin() : (
					(rnd.next(1.0) < probFocal) ? *focalList.begin() : *openList.begin()
				);
				focalList.erase(node); openList.erase(node);
				if (node.state == this -> statement.getDestination()) {
					this -> FINISH_SEARCHING(node.state);
					return;
				}
				if (this -> ITERATION_CHECK() == true) return;

				for (auto [action, newState, cost]: (this -> statement).getAdjacent(node.state)) {
					StateInfo<State> newNode = this -> buildStateInfo(newState, node.g + cost);

					auto itG = (this -> g).find(newState);
					if (itG != (this -> g).end()) {
						double oldG = itG -> second;
						if (oldG <= newNode.g) continue;

						StateInfo<State> oldNode = this -> buildStateInfo(newState, oldG);
						openList.erase(oldNode);
						focalList.erase(oldNode);
					}

					(this -> g)[newState] = newNode.g;
					(this -> actionTrace)[newState] = action;

					openList.insert(newNode);
					if (newNode.f <= fMin * eps)
						focalList.insert(newNode);
				}

				if (not openList.empty()) {
					int fHead = openList.begin() -> f;
					if (fHead > fMin)
						updateFocal(fMin * eps, fHead * eps);
				}
			}
		}
	public:
		double eps, probFocal;
		ProbabilisticFocalSearch(Problem<State> statement, double eps, double probFocal): SearchingAlgorithm<State>(statement), eps(eps), probFocal(probFocal) {
			this -> algoName = std::format("Probabilistic Focal Search with eps = {}; pFocal = {}", eps, probFocal);
		}
};

Board _INIT("NOT_INIT");

int ROW, COL;
std::vector<int> start, finish;

void input() {
	std::ios_base::sync_with_stdio(false);
	std::cin >> ROW >> COL;
	Board::changeSize(ROW, COL);
	start.resize(ROW * COL); finish.resize(ROW * COL);

	for (int& i: start) std::cin >> i;
	for (int& i: finish) std::cin >> i;

	int ptr = 0;
	for (int row = 0; row < ROW; row++)
		for (int col = 0; col < COL; col++, ptr++)
			if (finish[ptr] >= 0)
				Heuristic::destRow[finish[ptr]] = row,
				Heuristic::destCol[finish[ptr]] = col;
}

Algorithm* algorithm;
int main(int argc, char**argv){
	Algorithm::changeTimeLimit(100);

	input();

	double w = 1.05,
		   p = 0.7,
		   C = 2;

	Problem<Board> statement = Problem<Board>(Board(start), Board(finish));
	algorithm = new ProbabilisticFocalSearch(statement, w, p);
	// std::cerr << algorithm->getName() << std::endl;
	// std::cout << "start " << algorithm -> getName() << std::endl;
	double timeUsed = algorithm -> measure();
	// std::cout << "count of expanded nodes: " << ((SearchingAlgorithm<Board>*) algorithm) -> getExpandedCount() << std::endl;
	// std::cout << "count of expanded iterations: " << ((SearchingAlgorithm<Board>*) algorithm) -> getIterationCount() << std::endl;
	// std::cout << "count of max size: " << ((SearchingAlgorithm<Board>*) algorithm) -> getMaxSize() << std::endl;
	// std::cout << "steps: ";
	// for (std::string s: ((SearchingAlgorithm<Board>*) algorithm) -> getTrace()) std::cout << s;

	Board board(start);
	std::cout << board.toString() << "-\n";
	for (std::string c: ((SearchingAlgorithm<Board>*) algorithm) -> getTrace()) {
		// std::cerr << c << '\n';
		if (c == "L") board = board.move(BoardMove::GET_L());
		else if (c == "D") board = board.move(BoardMove::GET_D());
		else if (c == "R") board = board.move(BoardMove::GET_R());
		else if (c == "U") board = board.move(BoardMove::GET_U());
		std::cout << board.toString() << "-\n";
	}
	// std::cout << std::endl;
	// std::cout << "steps: " << ((PuzzleAlgorithm*) algorithm) -> makeStep() << std::endl;
	// std::cout << "execution time: " << timeUsed << std::endl;
}
