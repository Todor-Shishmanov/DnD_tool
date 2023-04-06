#ifndef QUEST_TRACKER_HEADER
#define QUEST_TRACKER_HEADER

#include <string>

namespace Quest {

class Phase {
public:
	enum class State {
		Completed = 0,
		Future = 1,
		Derailed = 2
	};

	inline Phase(std::string name, std::string description, State state) :
		name_(name),
		description_(description),
		state_(state)
	{}

	inline std::string name() const { return name_; }
	inline std::string description() const { return description_; }
	inline State state() const { return state_; }

	inline void setName(const std::string& name) { name_ = name; }
	inline void setDescription(const std::string& description) { description_ = description; }
	inline void setState(const State& state) { state_ = state; }
private:
	std::string name_;
	std::string description_;
	State state_;
};

class QuestTracker {
private:
	struct QuestNode {
		Phase phase_;
		Phase* next;
		Phase* derailed_next; // Used to denote the derailed quest.
	};
};

} // namespace Quest
#endif //QUEST_TRACKER_HEADER