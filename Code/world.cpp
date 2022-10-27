#include "world.h"
#include <stdexcept>
#include <algorithm> // std::find
#include <vector>

Location::Location(std::map<Cell, ID> layout){
	std::map<Cell, ID>::iterator it;
	for (it = layout.begin(); it != layout.end(); ++it) {
		if (it->second == NULL_OBJECT_ID) {
			layout_.insert(std::make_pair(it->first, it->second));
		}
		else  {
			if (placed_id_.find(it->second) != placed_id_.end()) {
				throw std::invalid_argument("Invalid layout: Layout must contain only unique IDs.");
			}
			layout_.insert(std::make_pair(it->first, it->second));
			placed_id_.insert(it->second);
		}
	}
}

bool Location::absolute_place(const ID & newID, const Cell & newCell){
	if (placed_id_.size() > 0 && placed_id_.find(newID) != placed_id_.end()) return false;
	if (!is_available(newCell) || newID == NULL_OBJECT_ID) return false;

	layout_.at(newCell) = newID;
	placed_id_.insert(newID);
	return true;
}

bool Location::relative_place(const ID& newID, const ID& referenceID, Direction dir){
	if (placed_id_.size() > 0 && placed_id_.find(newID) != placed_id_.end()) return false;
	if (newID == NULL_OBJECT_ID || referenceID == NULL_OBJECT_ID) return false;
	
	Cell oldCell;
	if (!get_cell(referenceID, oldCell)) return false;

	Cell newCell = direction_transformation(oldCell, dir);
	if (!is_available(newCell)) return false;
	
	layout_.at(newCell) = newID;
	placed_id_.insert(newID);
	return true;
}

bool Location::remove(const ID& removeID){
	if (placed_id_.find(removeID) == placed_id_.end()) return false;
	if (removeID == NULL_OBJECT_ID) return false;

	std::map<Cell, ID>::iterator it;
	for (it = layout_.begin(); it != layout_.end(); ++it) {
		if (it->second == removeID) {
			it->second = NULL_OBJECT_ID;
			break;
		}
	}

	placed_id_.erase(removeID);
	return true;
}

bool Location::move(const ID& moveID, Direction dir){
	Cell oldCell;
	if (!get_cell(moveID, oldCell)) return false;

	Cell newCell = direction_transformation(oldCell, dir);
	if (!is_available(newCell)) return false;

	layout_.at(oldCell) = NULL_OBJECT_ID;
	layout_[newCell] = moveID;
	return true;
}

std::vector<ID> Location::in_range(const ID& referenceID, Direction dir, unsigned lenght) const{
	std::vector<ID>inRange;
	Cell currentCell;
	if (!get_cell(referenceID, currentCell)) throw std::invalid_argument("Invalid referenceID: No such ID in layout");
	for (unsigned i = 0; i < lenght; i++) {
		currentCell = direction_transformation(currentCell, dir);
		if (!in_boundries(currentCell)) return inRange;
		inRange.push_back(layout_.at(currentCell));
	}
	return inRange;
}

std::map<Cell, ID> Location::get_layout() const{
	return layout_;
}

bool Location::is_available(const Cell& newCell) const{
	if (!in_boundries(newCell)) return false;
	return (layout_.at(newCell) == 0) ? true : false;
}

bool Location::in_boundries(const Cell& cell) const{
	return layout_.count(cell); // As map can contain each key max one time this is basically boolean.
}

Cell Location::direction_transformation(const Cell& cell, const Direction& dir) const {
	Cell newCell = cell;
	switch (dir) {
	case Direction::Forward :
		newCell.y--;
		break;
	case Direction::Backward :
		newCell.y++;
		break;
	case Direction::Left :
		newCell.x--;
		break;
	case Direction::Right :
		newCell.x++;
		break;
	case Direction::FLeft :
		newCell.y--;
		newCell.x--;
		break;
	case Direction::FRight:
		newCell.y--;
		newCell.x++;
		break;
	case Direction::BLeft:
		newCell.y++;
		newCell.x--;
		break;
	case Direction::BRight:
		newCell.y++;
		newCell.x++;
		break;
	}
	return newCell;
}

bool Location::get_cell(const ID& desiredID, Cell& cellContainer) const{ // Slowest thing in the whole white world.
	if (desiredID == NULL_OBJECT_ID || placed_id_.find(desiredID) == placed_id_.end()) return false;

	std::map<Cell, ID>::const_iterator it;
	for (it = layout_.begin(); it != layout_.end(); ++it) {
		if (it->second == desiredID) {
			cellContainer = it->first;
			break;
		}
	}
	return true;
}

bool Cell::operator==(const Cell& other) const {
	return (this->x == other.x && this->y == other.y);
}

bool Cell::operator<(const Cell& other) const {
	if (this->y == other.y) {
		return this->x < other.x;
	}
	return this->y < other.y;
}
