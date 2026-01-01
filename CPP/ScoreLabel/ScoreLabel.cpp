#include "ScoreLabel.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <string>

using namespace godot;

ScoreLabel::ScoreLabel() {
	// Initialize any variables here.
	score = 1;
}

ScoreLabel::~ScoreLabel() {
	// Add your cleanup here.
}

void ScoreLabel::_bind_methods() {
	ClassDB::bind_method(D_METHOD("score_inc"), &ScoreLabel::score_inc);
}

void ScoreLabel::score_inc(void) {
	String temp = std::to_string(score).c_str();
	String temp2 = temp.indent("Score: ");

	score += 1;
	set_text(temp2);
}
