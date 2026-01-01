#pragma once

#include <godot_cpp/classes/label.hpp>

namespace godot {
	class ScoreLabel : public Label {
		GDCLASS(ScoreLabel, Label)

	protected:
		static void _bind_methods(void);

	private:
		uint16_t score;

	public:
		ScoreLabel(void);
		~ScoreLabel(void) override;

		void score_inc(void);
	};
}
