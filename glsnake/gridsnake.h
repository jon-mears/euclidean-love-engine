#ifndef GRIDSNAKE_H
#define GRIDSNAKE_H

#include <utility>
#include <queue>
#include <vector>

class GridSnake {
private:
	enum class Direction {
		NORTH,
		EAST,
		SOUTH,
		WEST
	};

	std::pair<int, int> head;
	std::pair<int, int> tail;
	std::pair<int, int> new_tail_loc;
	
	std::vector<std::pair<int, int>> add;
	std::vector<std::pair<int, int>> remove;

	Direction head_dir;
	Direction tail_dir;
	int length;

	std::queue<Direction> dirs;

	void grow();

public:
	GridSnake(int row, int col, int length = 1);
	void update();
};
#endif