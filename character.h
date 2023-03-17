#pragma once
#include"creature.h"
//#include "item.h"


namespace game_framework {

	class Character : public Creature, public CGameState{
	public:
		//void AI();
		/*
		*/
		void show();
		void set_decision_time(int);
		void set_movement_animation(string);
		void set_dead_animation(string);
		void set_attack_animation(string);
		void set_hurt_animation(string);
		void set_spawn_animation(string);
		bool isWalk();
		MOVEMENT_DIR getFace();
	protected:
	private:
		Character();
		Character(CGame *g);
		~Character() = default;
		/*
		*/
		MOVEMENT_DIR _face = DOWN;
		void spawn();
		int attack();
		void die();
		void hurt(int damage);
		void heal(int count);
		void movement(MOVEMENT_DIR);
		void stop();
		/*
		void drop_items(int probability);	// 1 ~ 1000, 1000 = 100% drop
		 */

		//Item* item_set;

		
	};
}