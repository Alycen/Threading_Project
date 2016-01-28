#ifndef Leaderboard_H
#define Leaderboard_H

#include <fstream>
#include <iostream> 
#include <vector>
#include <string>

class Leaderboard
{
public:
	Leaderboard();
	bool WriteHighScore();
	bool GetHighScore();
	bool SortHighScore();

private:
	std::string line;
};

#endif
