#ifndef DND_CHARACTER_HEADER_
#define DND_CHARACTER_HEADER_

#include <string>

namespace DnD {
	enum class Class {
		// Common classes
		Barbarian = 0,
		Bard,
		Cleric,
		Druid,
		Fighter,
		Monk,
		Paladin,
		Ranger,
		Rogue,
		Sorcerer,
		Warlock,
		Wizard
	};

	enum class Race {
		// Common and playable races
		Dragonborn,
		Dwarf,
		Elf,
		Gnome,
		Half_Elf,
		Half_Orc,
		Halfling,
		Human,
		Tiefling
	};

	enum class Background {
		Acolyte = 0,
		Charlatan,
		Criminal,
		Entertainer,
		Folk_hero,
		Gladiator,
		Guild_artisan,
		Hermit,
		Knight,
		Noble,
		Outlander,
		Pirate,
		Sage,
		Sailor,
		Soldier,
		Urchin
	};

	struct Stats {
		unsigned strength;
		unsigned dexterity;
		unsigned constitution;
		unsigned intelligence;
		unsigned wisdom;
		unsigned charisma;
	};

	struct CombatStats {
		unsigned armor_class;
		unsigned initiative;
		unsigned speed;
		unsigned HP;
		unsigned temporary_HP;
	};

	enum class Color {
		Black = 0,
		White,
		Grey,
		Red,
		Green,
		Blue,
		Brown,
		Yellow,
		Orange,
		Pink,
		Purple
	};

	struct Description {
		std::string player_name;
		std::string character_name;
		unsigned age;
		unsigned height;
		unsigned weight;
		Color eyes_color;
		Color hair_color;
		Color skin;
	};

	class Character {
	public:

	private:
		Stats stats_;
		CombatStats combat_stats_;
		unsigned level_;
		Description description_;
		Background background_;
	};

	// Player character creation
	Character character_creation();
}

#endif
