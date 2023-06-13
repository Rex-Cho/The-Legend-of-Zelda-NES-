#pragma once
#ifndef TEKTITERED
#define TEKTITERED
#include "monster.h"


namespace game_framework {

	class TektiteRed : public Monster
	{
	public:
		TektiteRed();
		~TektiteRed() = default;

		void attack() override;
		void set_movement_animation(vector<string>) override;
		void set_dead_animation(vector<string>) override;
		void set_action_animation(vector<string>) override;
		void set_hurt_animation(vector<string>) override;
		void set_spawn_animation(vector<string>) override;
		void AI(clock_t) override;

		void set_max_life(int);
	private:
		void move(clock_t t, clock_t jump_time, int dir);

		int _move_times = 1;
		int _max_move_times = 3;
		int _attack_times = 1;
		int _max_attack_times = 2;
		clock_t _stop_time = 1500;	//ms
		clock_t _start_stop_time = 0;
		clock_t _jump_time = 500;	//ms
		clock_t _start_jump_time = 0;
		int _jump_dir = 0;
	};

}

#endif // !TEKTITERED
