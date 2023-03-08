#pragma once
#include "cracture.h"
#include "item.h"


namespace game_framework {

	class Monster : public Creature {
	public:
		void AI();
		void show();
		void set_decision_time(int);
		/*
		void set_movement_animation(CMovingBitmap);
		void set_dead_animation(CMovingBitmap);
		void set_attack_animation(CMovingBitmap);
		void set_hurt_animation(CMovingBitmap);
		void set_spawn_animation(CMovingBitmap);
		*/
	private:
		Monster();
		~Monster() = default;
		void spawn();
		int attack();
		void die();
		void hurt(int damage);
		void movement(MOVEMENT_REF);

		void drop_items(int probability);	// 1 ~ 1000, 1000 = 100% drop

		Item* item_set;

		int decision_time = 800;
	};
}