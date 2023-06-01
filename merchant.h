#pragma once
#ifndef MERCHANT
#define MERCHANT
#include "monster.h"


namespace game_framework {

	class Merchant : public Monster
	{
	public:
		Merchant();
		~Merchant() = default;

		void attack() override;
		void set_movement_animation(vector<string>) override;
		void set_dead_animation(vector<string>) override;
		void set_action_animation(vector<string>) override;
		void set_hurt_animation(vector<string>) override;
		void set_spawn_animation(vector<string>) override;
		void AI(clock_t) override;

		int get_key_cost();
	private:
		int _key_base_cost = 20;
		int _key_cost = _key_base_cost;
	};

}

#endif // !MERCHANT
