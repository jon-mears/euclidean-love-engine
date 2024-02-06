#ifndef GRIDOBJECTCOMPONENT_H
#define GRIDOBJECTCOMPONENT_H

#include <vector>
#include <utility>

#include "component.h"
#include "grid.h"

typedef std::pair<int, int> Cell;

class GridObjectComponent : public Component {
private:
	std::vector<Cell> cells_to_add;
	std::vector<Cell> cells_to_remove;

public:
	void add_cell(Cell c);
	void remove_cell(Cell c);
	void clear_stamp();
};

#endif