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
		void AI();
	private:
		void move(clock_t, int dir);	//0 Right Up, 1 Right, 2 Right Down, 3 Left down, 4 Left, 5 Left Up

		int _move_times = 1;
		int _max_move_times = 3;
		int _attack_times = 1;
		int _max_attack_times = 2;
		clock_t stop_time = 700;	//ms
		clock_t jump_time = 700;	//ms
		int jump_height = 25;	//pixel
	};

}

#endif // !TEKTITERED
