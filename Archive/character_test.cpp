#include "CppUnitTest.h"
#include "../Code/character.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
/*
class CombatAttributes
		CombatAttributes(unsigned armor_class, int initiative, unsigned speed, unsigned hp, unsigned temp_hp);
		

	class Stats 
		Stats(std::map<AbilityScore, unsigned> ability_scores, std::map<Skill, int> skills, std::set<Skill> proficient_skills, unsigned proficiency_bonus);

		int skill_check_bonus(const Skill& skill);
		int saving_throw_bonus(const AbilityScore& ability_score);
		int modifier(const AbilityScore& ability_score);
		unsigned passive_perseption();

	class Character 
		Character(Race race, Class character_class, Background background, unsigned level, Stats stats, CombatAttributes combat_attributes, Description description);

		unsigned level();
		void level_up(); // Create new Stats and CombatAttributes.

	Character PC_creation();
	Character NPC_creation();

*/
using namespace DnD;

namespace UnitTest
{
	TEST_CLASS(CombatAttributesTest)
	{
		TEST_METHOD(HitWithoutTempHP)
		{
			CombatAttributes ca(10, 5, 30, 20, 0);
			ca.hit(15, 10);
		}

		/*TEST_METHOD(HitWithNotEnoughTempHP)
		{

		}

		TEST_METHOD(HitWithEnoughTempHP)
		{

		}

		TEST_METHOD(HitMiss)
		{

		}*/

		
	};
}