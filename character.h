#pragma once
#include"creature.h"
//#include "item.h"


namespace game_framework {

	class Character : public Creature {
	public:
		//void AI();
		void show();
		void set_decision_time(int);
		void set_movement_animation(string);
		void set_dead_animation(string);
		void set_attack_animation(string);
		void set_hurt_animation(string);
		void set_spawn_animation(string);
		/*
		*/
	private:
		Character();
		~Character() = default;
		/*
		*/
		void spawn();
		int attack(MOVEMENT_REF);
		void die();
		void hurt(int damage);
		void movement(MOVEMENT_REF);

		void drop_items(int probability);	// 1 ~ 1000, 1000 = 100% drop

		//Item* item_set;

		int _decision_time = 800;
	};
}