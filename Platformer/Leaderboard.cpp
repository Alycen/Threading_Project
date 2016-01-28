#include "Leaderboard.h"
using namespace std;
#include <iostream>

Leaderboard::Leaderboard()
{
	ifstream highscoreFile("Highscore.txt");
	if (!highscoreFile) //Always test the file open.
	{
		cout << "Error opening High Score file" << endl;
	}

	vector<string> result;
	while (std::getline(highscoreFile, line))
	{
		result.push_back(line);
	}

	cout << "Finished" << endl;
}