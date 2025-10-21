#include <bits/stdc++.h>
using namespace std;

int main() {
	string s, s1;

	cin >> s >> s1;

	if (s == "Rock" && s1 == "Scissors") {
		cout << "Player 1";
	}
	
	if (s == "Rock" && s1 == "Paper") {
		cout << "Player 2";
	}

	if (s == "Rock" && s1 == "Rock") {
		cout << "Draw";
	}

	if (s == "Scissors" && s1 == "Scissors") {
		cout << "Draw";
	}

	if (s == "Scissors" && s1 == "Rock") {
		cout << "Player 2";
	}

	if (s == "Scissors" && s1 == "Paper") {
		cout << "Player 1";
	}

	if (s == "Paper" && s1 == "Scissors") {
		cout << "Player 2";
	}

	if (s == "Paper" && s1 == "Rock") {
		cout << "Player 1";
	}

	if (s == "Paper" && s1 == "Paper") {
		cout << "Draw";
	}
	
}