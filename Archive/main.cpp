#include "map.h"
typedef std::pair<Cell, ID> pair;

std::map <Cell, ID> layout_ = { pair(Cell(0, 0), NULL_OBJECT_ID), pair(Cell(1, 0), NULL_OBJECT_ID), pair(Cell(2, 0), NULL_OBJECT_ID),
								pair(Cell(0, 1), NULL_OBJECT_ID), pair(Cell(1, 1), NULL_OBJECT_ID), pair(Cell(2, 1), NULL_OBJECT_ID),
								pair(Cell(0, 2), NULL_OBJECT_ID), pair(Cell(1, 2), ID(1)),			pair(Cell(2, 2), ID(2)),          pair(Cell(3, 2), ID(3)),
								pair(Cell(0, 3), NULL_OBJECT_ID),
								pair(Cell(0, 4), NULL_OBJECT_ID),
								pair(Cell(0, 5), NULL_OBJECT_ID), pair(Cell(1, 5), NULL_OBJECT_ID), pair(Cell(2, 5), NULL_OBJECT_ID)
};
int main() {
	Room r(layout_);
	return 0;
}