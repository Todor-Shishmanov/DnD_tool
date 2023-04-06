#ifndef MAP_HEADER
#define MAP_HEADER
#include <map>
#include <vector>
#include <set>
/*
	Note for IDs:
	each object and character has it's own ID. Even if they are from the same type.
	Meaning that there can be ID 1 for Wall_1 and ID 2 for Wall_2.
	Also should be moved to Game
*/
typedef unsigned ID;
#define NULL_OBJECT_ID 0 // Used in the Room::layout_ as empty ID

enum class Direction {
	Forward = 0,
	Backward,
	Left,
	Right,
	
	// Diagonals
	FLeft,
	FRight,
	BLeft,
	BRight
};

struct Cell {
	Cell() : x(0), y(0) {}
	Cell(unsigned x, unsigned y) : x(x), y(y) {}

	unsigned x;
	unsigned y;

	bool operator==(const Cell& other) const;
	bool operator<(const Cell& other) const;
};

// For future references: layout can be a non-square shape, 
// meaning that size_x and size_y don't actually make much sence.
class Room {
public:

	Room(std::map<Cell, ID> layout);

	bool absolute_place(const ID& newID, const Cell& newCell);
	bool relative_place(const ID& newID, const ID& referenceID, Direction dir);
	bool remove(const ID& removeID);
	bool move(const ID& moveID, Direction dir);

	std::vector<ID> in_range(const ID& referenceID, Direction dir, unsigned lenght ) const;
	std::map<Cell, ID> get_layout() const;

private:
	
	Cell direction_transformation(const Cell&, const Direction& dir) const ;
	// Works like std::getline 
	bool get_cell(const ID&, Cell& cellContainer) const;
	// Returns true if an object can be placed in that cell, false otherwise.
	bool is_available(const Cell&) const;
	// Returns true if the cell is in the boundaries of the map
	bool in_boundries(const Cell&) const;

	std::set<ID> placed_id_; // Used to guarantee uniqueness
	std::map<Cell, ID> layout_; // As both Cell and ID are unique we might have to create our own data structure
};

/*
Map creates a "virtual" (meaning not real) connection between existing rooms.
It doesn't change rooms, nor does it create more rooms.
To manage a connection of rooms add them to the Map with add_room().
You can access the list of rooms that a specific one is connected to with get_adjacent().

Big problem : Map uses Room* to manage connections. This means that if a room goes out of scope or is destroyed without the knowleadge of Map then there will be an invalid pointer.
This is more of a design problem, which comes from the fact that there is no way to distingish two rooms with the same layout and entry_point. 
This design uses the fact that two different rooms will have two different addresses in memory.

Maybe this functionallity belongs to the future Game class?

TODO 10-08 Toto: Change the implementation of entry point. The logic must be handled by Map not by Room.
				 Think about the interaction between Room->Game->Object->Game. Example: Player wants to pass through door. Does he have key?
*/
#endif // MAP_HEADER