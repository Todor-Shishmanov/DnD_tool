#include "CppUnitTest.h"
#include "..\Code\map.h"
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
typedef std::pair<Cell, ID> pair;

namespace UnitTest
{
	TEST_CLASS(TestRoom)
	{
		/* Test room layout:
				| 0 | 0 | 0 |
				| 0 | 0 | 0 |
				| 0 | 1 | 2 | 3 |
				| 0 |
				| 0 |
				| 0 | 0 | 0 |
		*/
		std::map <Cell, ID> layout_ =  {pair(Cell(0, 0), NULL_OBJECT_ID), pair(Cell(1, 0), NULL_OBJECT_ID), pair(Cell(2, 0), NULL_OBJECT_ID),
										pair(Cell(0, 1), NULL_OBJECT_ID), pair(Cell(1, 1), NULL_OBJECT_ID), pair(Cell(2, 1), NULL_OBJECT_ID),
										pair(Cell(0, 2), NULL_OBJECT_ID), pair(Cell(1, 2), ID(1)),			pair(Cell(2, 2), ID(2)),          pair(Cell(3, 2), ID(3)),
										pair(Cell(0, 3), NULL_OBJECT_ID),
										pair(Cell(0, 4), NULL_OBJECT_ID),
										pair(Cell(0, 5), NULL_OBJECT_ID), pair(Cell(1, 5), NULL_OBJECT_ID), pair(Cell(2, 5), NULL_OBJECT_ID)
		};


		TEST_METHOD(constructor_valid)
		{
			Logger::WriteMessage(L"Testing Room::Room() with valid input.");

			Room room(layout_);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsTrue(layout == layout_, L"Error in function Room::Room(): Layout is changed.");
		}

		TEST_METHOD(constructor_invalid)
		{
			std::map <Cell, ID> invalidLayout = { pair(Cell(0, 0), ID(1)), pair(Cell(1, 0), NULL_OBJECT_ID), pair(Cell(2, 0), ID(1)) };
			Logger::WriteMessage(L"Testing Room::Room() with invalid input.");
			try {
				Room room(invalidLayout);
			}
			catch (const std::invalid_argument& e) {
				if (e.what() == std::string("Invalid layout: Layout must contain only unique IDs.")) return; // This passes the test.
			}
			catch (...) { Assert::Fail(L"Error in Room::Room() - Wrong exception thrown."); }
			Assert::Fail(L"Error in Room::Room() - No exception thrown.");
		}
		TEST_METHOD(absolute_place_valid)
		{
			Logger::WriteMessage(L"Testing Room::absolute_place() with valid input.");

			Room room(layout_);
			ID validID = 9;
			Cell validCell(1, 1);

			bool placed = room.absolute_place(validID, validCell);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsTrue(placed, L"Error in function Room::absolute_place(): Did not return true.");
			Assert::AreEqual(validID, layout.at(validCell), L"Error in function Room::absolute_place(): ID was not placed in the cell.");
		}


		TEST_METHOD(absolute_place_invalid_cell)
		{
			Logger::WriteMessage(L"Testing Room::absolute_place() with invalid input - Invalid Cell.");
		
			Room room(layout_);
			ID validID = 2;
			Cell invalidCell(1, 15); // Check layout_

			bool placed = room.absolute_place(validID, invalidCell);
			std::map<Cell, ID> layout = room.get_layout();
		
			Assert::IsFalse(placed, L"Error in function Room::absolute_place(): Did not return false.");
			Assert::IsTrue(layout_ == layout, L"Error in function Room::absolute_place(): Layout was changed.");
		}

		TEST_METHOD(absolute_place_invalid_id_1)
		{
			Logger::WriteMessage(L"Testing Room::absolute_place() with invalid input: Placing ID that is already in the room.");
		
			Room room(layout_);
			ID alreadyPlacedID = 1; // Check layout_
			Cell validCell(0, 4);

			bool placed = room.absolute_place(alreadyPlacedID, validCell);
			std::map<Cell, ID> layout = room.get_layout();
		
			Assert::IsFalse(placed, L"Error in function Room::absolute_place(): Did not return false.");
			Assert::IsTrue(layout_ == layout, L"Error in function Room::absolute_place(): Layout was changed.");
		}

		TEST_METHOD(absolute_place_invalid_id_2)
		{
			Logger::WriteMessage(L"Testing Room::absolute_place() with invalid input: Placing NULL_OBJECT_ID.");
		
			Room room(layout_);
			ID invalidID = NULL_OBJECT_ID;
			Cell validCell(0, 1);

			bool placed = room.absolute_place(invalidID, validCell);
			std::map<Cell, ID> layout = room.get_layout();
		
			Assert::IsFalse(placed, L"Error in function Room::absolute_place(): Did not return false.");
			Assert::IsTrue(layout_ == layout, L"Error in function Room::absolute_place(): Layout was changed.");
		}

		TEST_METHOD(relative_place_valid)
		{
			Logger::WriteMessage(L"Testing Room::relative_place() with valid input.");

			Room room(layout_);
			ID validNewID = 9;
			ID validRelativeID = 1;
			Direction direction = Direction::FRight; 
			Cell expectedCell(2, 1); // Check layout_

			bool placed = room.relative_place(validNewID, validRelativeID, direction);
			std::map<Cell, ID> layout = room.get_layout();
			

			Assert::IsTrue(placed, L"Error in function Room::relative_place(): Did not return true");
			Assert::AreEqual(validNewID, layout[expectedCell], L"Error in function Room::relative_place(): ID was not placed in the cell");
		}

		TEST_METHOD(relative_place_invalid_direction_1)
		{
			Logger::WriteMessage(L"Testing Room::relative_place() with invalid direction - Outside of layout.");

			Room room(layout_);
			ID validNewID = 9;
			ID validReferenceID = 1;
			Direction invalidDirection = Direction::Backward; // Check layout_

			bool placed = room.relative_place(validNewID, validReferenceID, invalidDirection);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsFalse(placed, L"Error in function Room::relative_place(): Did not return false.");
			Assert::IsTrue(layout_ == layout, L"Error in function Room::relative_place(): Layout was changed.");
		}

		TEST_METHOD(relative_place_invalid_direction_2)
		{
			Logger::WriteMessage(L"Testing Room::relative_place() with invalid direction - Cell is occupied by another ID.");

			Room room(layout_);
			ID validNewID = 9;
			ID validReferenceID = 1;
			Direction invalidDirection = Direction::Right; // Check layout_

			bool placed = room.relative_place(validNewID, validReferenceID, invalidDirection);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsFalse(placed, L"Error in function Room::relative_place(): Did not return false.");
			Assert::IsTrue(layout_ == layout, L"Error in function Room::relative_place(): Layout was changed.");
		}

		TEST_METHOD(relative_place_invalid_reference_id_1)
		{
			Logger::WriteMessage(L"Testing Room::relative_place() with invalid reference: referenceID is not on map:");

			Room room(layout_);
			ID validNewID = 9;
			ID invalidReferenceID = 5; // Check layout_
			Direction direction = Direction::Forward; 

			bool placed = room.relative_place(validNewID, invalidReferenceID, direction);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsFalse(placed, L"Error in function Room::relative_place(): Did not return false.");
			Assert::IsTrue(layout_ == layout, L"Error in function Room::relative_place(): Layout was changed.");
		}

		TEST_METHOD(relative_place_invalid_reference_id_2)
		{
			Logger::WriteMessage(L"Testing Room::relative_place() with invalid reference: NULL_OBJECT_ID as referenceID.");

			Room room(layout_);
			ID validNewID = 9;
			ID invalidRelativeID = NULL_OBJECT_ID;
			Direction direction = Direction::Forward;

			bool placed = room.relative_place(validNewID, invalidRelativeID, direction);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsFalse(placed, L"Error in function Room::relative_place(): Did not return false.");
			Assert::IsTrue(layout_ == layout, L"Error in function Room::relative_place(): Layout was changed.");
		}

		TEST_METHOD(relative_place_invalid_new_id_1)
		{
			Logger::WriteMessage(L"Testing Room::relative_place() with invalid new ID: New ID is NULL_OBJECT_ID");

			Room room(layout_);
			ID invalidNewID = NULL_OBJECT_ID; // Check layout_
			ID validRelativeID = 1; 
			Direction direction = Direction::Forward;

			bool placed = room.relative_place(invalidNewID, validRelativeID, direction);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsFalse(placed, L"Error in function Room::relative_place(): Did not return false.");
			Assert::IsTrue(layout_ == layout, L"Error in function Room::relative_place(): Layout was changed.");
		}

		TEST_METHOD(relative_place_invalid_new_id_2)
		{
			Logger::WriteMessage(L"Testing Room::relative_place() with invalid new ID: Placing ID that is already in the room.");
			Room room(layout_);
			ID invalidNewID = 2; // Check layout_
			ID validRelativeID = 1; 
			Direction direction = Direction::Left;

			bool placed = room.relative_place(invalidNewID, validRelativeID, direction);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsFalse(placed, L"Error in function Room::relative_place(): Did not return false.");
			Assert::IsTrue(layout_ == layout, L"Error in function Room::relative_place(): Layout was changed.");
		}

		TEST_METHOD(remove_valid)
		{
			Logger::WriteMessage(L"Testing Room::remove() with valid input.");
			Room room(layout_);
			ID validID = 1;
			Cell removedCell(1, 2); // Check layout_

			bool removed = room.remove(validID);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsTrue(removed, L"Error in function Room::remove(): Did not return true.");
			Assert::IsTrue(layout.at(removedCell) == NULL_OBJECT_ID, L"Error in function Room::remove(): The ID wasn't removed.");
		}

		TEST_METHOD(remove_invalid_id_1)
		{
			Logger::WriteMessage(L"Testing Room::remove() with invalid input - Removing NULL_OBJECT_ID");
			Room room(layout_);
			ID invalidID = NULL_OBJECT_ID;

			bool removed = room.remove(invalidID);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsFalse(removed, L"Error in function Room::remove(): Did not return false.");
			Assert::IsTrue(layout == layout_, L"Error in function Room::remove(): Layout was changed.");
		}
		
		TEST_METHOD(remove_invalid_id_2)
		{
			Logger::WriteMessage(L"Testing Room::remove() with invalid input - Removing ID that is not in the layout of the Room.");
			Room room(layout_);
			ID invalidID = 9; // Check layout_

			bool removed = room.remove(invalidID);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsFalse(removed, L"Error in function Room::remove(): Did not return false.");
			Assert::IsTrue(layout == layout_, L"Error in function Room::remove(): Layout was changed.");
		}

		TEST_METHOD(move_valid)
		{
			Logger::WriteMessage(L"Testing Room::move() with valid input.");
			Room room(layout_);
			ID validID = 1;
			Direction validDirection = Direction::Forward; // Check layout_
			Cell originalCell(1, 2);
			Cell forwardCell(1, 1);

			bool moved = room.move(validID, validDirection);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsTrue(moved, L"Error in function Room::move(): Did not return true.");
			Assert::IsTrue(layout.at(forwardCell) == validID, L"Error in function Room::remove(): The ID wasn't moved.");
			Assert::IsTrue(layout.at(originalCell) == NULL_OBJECT_ID, L"Error in function Room::remove(): Old Cell still has the ID.");
		}

		TEST_METHOD(move_invalid_direction_1)
		{
			Logger::WriteMessage(L"Testing Room::move() with invalid input - Outside of layout.");
			Room room(layout_);
			ID validID = 1;
			Direction invalidDirection = Direction::Backward; // Check layout_

			bool moved = room.move(validID, invalidDirection);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsFalse(moved, L"Error in function Room::move(): Did not return false.");
			Assert::IsTrue(layout == layout_, L"Error in function Room::remove(): Layout was changed.");
		}

		TEST_METHOD(move_invalid_direction_2)
		{
			Logger::WriteMessage(L"Testing Room::move() with invalid input - Cell is occupied by another ID.");
			Room room(layout_);
			ID validID = 1;
			Direction invalidDirection = Direction::Right; // Check layout_

			bool moved = room.move(validID, invalidDirection);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsFalse(moved, L"Error in function Room::move(): Did not return false.");
			Assert::IsTrue(layout == layout_, L"Error in function Room::remove(): Layout was changed.");
		}

		TEST_METHOD(move_invalid_id_1)
		{
			Logger::WriteMessage(L"Testing Room::move() with invalid input - ID is NULL_OBJECT_ID.");
			Room room(layout_);
			ID invalidID = NULL_OBJECT_ID;
			Direction validDirection = Direction::Forward; // Check layout_

			bool moved = room.move(invalidID, validDirection);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsFalse(moved, L"Error in function Room::move(): Did not return true.");
			Assert::IsTrue(layout == layout_, L"Error in function Room::remove(): Layout was changed.");
		}

		TEST_METHOD(move_invalid_id_2)
		{
			Logger::WriteMessage(L"Testing Room::move() with invalid input - Moving ID that doesn't exist");
			Room room(layout_);
			ID invalidID = 9;
			Direction validDirection = Direction::Forward; // Check layout_

			bool moved = room.move(invalidID, validDirection);
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsFalse(moved, L"Error in function Room::move(): Did not return true.");
			Assert::IsTrue(layout == layout_, L"Error in function Room::remove(): Layout was changed.");
		}

		TEST_METHOD(in_range_valid_1)
		{
			Logger::WriteMessage(L"Testing Room::in_range() with valid input: multiple IDs in range");
			Room room(layout_);
			ID validReferenceID = 1;
			Direction validDirection = Direction::Right; // Check layout_

			std::vector<ID> inRange = room.in_range(validReferenceID, validDirection, 5);
			std::vector<ID> expected = { ID(2), ID(3) };
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsTrue(inRange == expected, L"Error in function Room::in_range(): Did not return the expected values.");
			Assert::IsTrue(layout == layout_, L"Error in function Room::remove(): Layout was changed.");
		}

		TEST_METHOD(in_range_valid_2)
		{
			Logger::WriteMessage(L"Testing Room::in_range() with valid input: No Cell in range.");
			Room room(layout_);
			ID validReferenceID = 3;
			Direction validDirection = Direction::Right; // Check layout_

			std::vector<ID> inRange = room.in_range(validReferenceID, validDirection, 5);
			std::vector<ID> expected = {};
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsTrue(inRange == expected, L"Error in function Room::in_range(): Did not return the expected values.");
			Assert::IsTrue(layout == layout_, L"Error in function Room::remove(): Layout was changed.");
		}

		TEST_METHOD(in_range_valid_3)
		{
			Logger::WriteMessage(L"Testing Room::in_range() with valid input: Nothing in range");
			Room room(layout_);
			ID validReferenceID = 1;
			Direction validDirection = Direction::Forward; // Check layout_

			std::vector<ID> inRange = room.in_range(validReferenceID, validDirection, 2);
			std::vector<ID> expected = {ID(0), ID(0)};
			std::map<Cell, ID> layout = room.get_layout();

			Assert::IsTrue(inRange == expected, L"Error in function Room::in_range(): Did not return the expected values.");
			Assert::IsTrue(layout == layout_, L"Error in function Room::remove(): Layout was changed.");
		}

		TEST_METHOD(in_range_invalid_1)
		{
			Logger::WriteMessage(L"Testing Room::in_range() with invalid input: ReferenceID doesn't exist");
			Room room(layout_);
			ID invalidReferenceID = 9;
			Direction validDirection = Direction::Forward; // Check layout_
			try {
				std::vector<ID> inRange = room.in_range(invalidReferenceID, validDirection, 2);
				Assert::Fail(L"Error in Room::in_range() - No exception thrown."); // If no exception is thrown
			}
			catch (const std::invalid_argument& e) {
				if (e.what() != std::string("Invalid referenceID: No such ID in layout")) { Assert::Fail(L"Error in Room::in_range() - Wrong error message, correct error type."); }
			}
			catch (...) {
				Assert::Fail(L"Error in Room::in_range() - Wrong exception thrown.");
			}

			std::map<Cell, ID> layout = room.get_layout();
			Assert::IsTrue(layout == layout_, L"Error in function Room::in_range(): Layout was changed.");
		}
	};
}
