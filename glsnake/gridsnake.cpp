#include "gridsnake.h"

GridSnake::GridSnake(int row, int col, int length = 1) : head({ row, col }), tail({ row, col }),
add({head}), remove({}), head_dir(Direction::NORTH), tail_dir(Direction::NORTH), length(length),
dirs{} {
	tail.first += (length-1);
}

void GridSnake::grow() {
	add.push_back(new_tail_loc);  // creates the new tail cell
	dirs.push(head_dir);
}

void GridSnake::update() {
	switch (head_dir) {
	case Direction::NORTH:
		head.first -= 1;
		break;
	case Direction::EAST:
		head.second += 1;
		break;
	case Direction::SOUTH:
		head.first += 1;
		break;
	case Direction::WEST:
		head.second -= 1;
		break;
	}

	dirs.push(head_dir);

	add.push_back(head);
	remove.push_back(tail);

	tail_dir = dirs.front();
	dirs.pop();

	new_tail_loc = tail;

	switch (tail_dir) {
	case Direction::NORTH:
		tail.first -= 1;
		break;
	case Direction::EAST:
		tail.second += 1;
		break;
	case Direction::SOUTH:
		tail.first += 1;
		break;
	case Direction::WEST:
		tail.second -= 1;
		break;
	}
}