#ifndef DND_CHARACTER_HEADER_
#define DND_CHARACTER_HEADER_

#include <string>
#include <map>
#include <set>

namespace DnD {
	enum class Race {
		// Common and playable races
		Human = 0,
		Dragonborn,
		Dwarf,
		Elf,
		Gnome,
		Half_Elf,
		Half_Orc,
		Halfling,
		Tiefling
	};

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

	enum class AbilityScore {
		Strength = 0,
		Dexterity,
		Constitution,
		Intelligence,
		Wisdom,
		Charisma
	};

	enum class Skill {
		Acrobatics = 0,
		AnimalHandling,
		Arcana,
		Athletics,
		Deception,
		History,
		Insight,
		Intimidation,
		Investigation,
		Medicine,
		Nature,
		Perception,
		Performance,
		Persuasion,
		Religion,
		SleightOfHand,
		Stealth,
		Survival
	};

	enum class Language {
		Common = 0,
		Dwarvish,
		Elvish,
		Giant,
		Gnomish,
		Goblin,
		Halfing,
		Orc
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

	// TODO: Add backstory
	struct Description {
		Description(std::string name, unsigned age, unsigned height, unsigned weight, Color eyes_color, Color hair_color, Color skin);

		const std::string name;
		const unsigned age;
		const unsigned height;
		const unsigned weight;
		const Color eyes_color;
		const Color hair_color;
		const Color skin;
	};

	class CombatAttributes {
	public:
		CombatAttributes(unsigned armor_class, int initiative, unsigned speed, unsigned hp, unsigned temp_hp);

		bool hit(unsigned attack_roll, unsigned damage);
	private:
		unsigned HP_;
		unsigned temporary_HP_;
		int initiative_;
		unsigned speed_;
		unsigned armor_class_;
	};

	class Stats {
	public:
		Stats(std::map<AbilityScore, unsigned> ability_scores, std::map<Skill, int> skills, std::set<Skill> proficient_skills, unsigned proficiency_bonus);

		int skill_check_bonus(const Skill& skill);
		int saving_throw_bonus(const AbilityScore& ability_score);
		int modifier(const AbilityScore& ability_score);
		unsigned passive_perseption();

	private:
		std::map<AbilityScore, unsigned> ability_scores_;
		unsigned proficiency_bonus_;
		std::map<Skill, int> skills_;
		std::set<Skill> proficient_skills_;
	};

	class Character {
	public:
		Character(Race race, Class character_class, Background background, unsigned level, Stats stats, CombatAttributes combat_attributes, Description description);

		unsigned level();
		void level_up(); // Create new Stats and CombatAttributes. 

		
		const Race race;
		const Class character_class;
		const Background background;
		Stats stats;
		CombatAttributes combat_attributes;
		Description description;

	private:
		unsigned level_;
	};

	Character PC_creation();
	Character NPC_creation();
}

#endif
