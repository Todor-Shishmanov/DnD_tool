#include "character.h"
#include <assert.h>

namespace DnD {
	Description::Description(std::string name, unsigned age, unsigned height, unsigned weight, Color eyes_color, Color hair_color, Color skin):
		name(name),
		age(age),
		height(height),
		weight(weight),
		eyes_color(eyes_color),
		hair_color(hair_color),
		skin(skin)
	{
		assert(!name.empty() && age != 0 && height != 0 && weight != 0);
	}

	CombatAttributes::CombatAttributes(unsigned armor_class, int initiative, unsigned speed, unsigned hp, unsigned temp_hp):
		armor_class_(armor_class),
		initiative_(initiative),
		speed_(speed),
		HP_(hp),
		temporary_HP_(temp_hp)
	{
		assert(armor_class_ != 0 && speed_ != 0 && HP_ != 0);
	}

	bool CombatAttributes::hit(unsigned attack_roll, unsigned damage){
		assert(attack_roll != 0 && damage != 0);

		if (armor_class_ > attack_roll)
			return false;
		
		if (temporary_HP_ == 0) {
			if (HP_ < damage)
				HP_ = 0;
			else
				HP_ -= damage;
		}
		else if (temporary_HP_ < damage) {
			damage -= temporary_HP_;
			HP_ -= damage;
			temporary_HP_ = 0;
		}
		else
			temporary_HP_ -= damage;

		return true;
	}

	Stats::Stats(std::map<AbilityScore, unsigned> ability_scores, std::map<Skill, int> skills, std::set<Skill> proficient_skills, unsigned proficiency_bonus):
		ability_scores_(ability_scores),
		skills_(skills),
		proficient_skills_(proficient_skills),
		proficiency_bonus_(proficiency_bonus)
	{
		assert(ability_scores_.size() == 6 && skills.size() == 18 && proficiency_bonus_ != 0);
	}

	int Stats::skill_check_bonus(const Skill& skill){
		return 0;
	}
	
	int Stats::saving_throw_bonus(const AbilityScore& ability_score){
		return 0;
	}
	
	int Stats::modifier(const AbilityScore& ability_score){
		return 0;
	}
	
	unsigned Stats::passive_perseption(){
		return 0;
	}
	
	Character::Character(Race race, Class character_class, Background background, unsigned level, Stats stats, CombatAttributes combat_attributes, Description description):
		race(race), 
		character_class(character_class), 
		background(background),
		level_(level),
		stats(stats),
		combat_attributes(combat_attributes),
		description(description)
	{}
	
	unsigned Character::level(){
		return 0;
	}

	void Character::level_up(){
		return;
	}
	
	Character PC_creation(){
		std::map<AbilityScore, unsigned> ability_scores;
		ability_scores[AbilityScore::Charisma] = 10;
		ability_scores[AbilityScore::Strength] = 10;
		ability_scores[AbilityScore::Dexterity] = 10;
		ability_scores[AbilityScore::Constitution] = 10;
		ability_scores[AbilityScore::Wisdom] = 10;
		ability_scores[AbilityScore::Intelligence] = 10;

		std::map<Skill, int> skills;
		skills[Skill::Acrobatics] = 10;
		skills[Skill::AnimalHandling] = 10;
		skills[Skill::Arcana] = 10;
		skills[Skill::Athletics] = 10;
		skills[Skill::Deception] = 10;
		skills[Skill::History] = 10;
		skills[Skill::Insight] = 10;
		skills[Skill::Intimidation] = 10;
		skills[Skill::Investigation ] = 10;
		skills[Skill::Medicine] = 10;
		skills[Skill::Nature] = 10;
		skills[Skill::Perception] = 10;
		skills[Skill::Performance] = 10;
		skills[Skill::Persuasion] = 10;
		skills[Skill::Religion] = 10;
		skills[Skill::SleightOfHand] = 10;
		skills[Skill::Stealth] = 10;
		skills[Skill::Survival] = 10;

		std::set<Skill> proficient_skills;
		proficient_skills.insert(Skill::Acrobatics);

		Stats s(ability_scores, skills, proficient_skills, 2);
		CombatAttributes c(10, 5, 30, 20, 0);
		Description d("Testy", 25, 5, 75, Color::Blue, Color::Brown, Color::White);
		return Character(Race::Human, Class::Barbarian, Background::Acolyte, 1, s, c, d);
	}
	
	Character NPC_creation(){
		std::map<AbilityScore, unsigned> ability_scores;
		ability_scores[AbilityScore::Charisma] = 10;
		ability_scores[AbilityScore::Strength] = 10;
		ability_scores[AbilityScore::Dexterity] = 10;
		ability_scores[AbilityScore::Constitution] = 10;
		ability_scores[AbilityScore::Wisdom] = 10;
		ability_scores[AbilityScore::Intelligence] = 10;

		std::map<Skill, int> skills;
		skills[Skill::Acrobatics] = 10;
		skills[Skill::AnimalHandling] = 10;
		skills[Skill::Arcana] = 10;
		skills[Skill::Athletics] = 10;
		skills[Skill::Deception] = 10;
		skills[Skill::History] = 10;
		skills[Skill::Insight] = 10;
		skills[Skill::Intimidation] = 10;
		skills[Skill::Investigation] = 10;
		skills[Skill::Medicine] = 10;
		skills[Skill::Nature] = 10;
		skills[Skill::Perception] = 10;
		skills[Skill::Performance] = 10;
		skills[Skill::Persuasion] = 10;
		skills[Skill::Religion] = 10;
		skills[Skill::SleightOfHand] = 10;
		skills[Skill::Stealth] = 10;
		skills[Skill::Survival] = 10;

		std::set<Skill> proficient_skills;
		proficient_skills.insert(Skill::Acrobatics);

		Stats s(ability_scores, skills, proficient_skills, 2);
		CombatAttributes c(10, 5, 30, 20, 0);
		Description d("TestyNPC", 25, 5, 75, Color::Blue, Color::Brown, Color::White);
		return Character(Race::Human, Class::Barbarian, Background::Acolyte, 1, s, c, d);
	}
}