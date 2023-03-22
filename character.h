#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include"creature.h"

using namespace std;

namespace game_framework {
	class Character : public Creature{
	public:
		//void AI();
		/*
		*/
		Character();
		~Character() = default;

		//set function
		void set_decision_time(int);
		void set_movement_animation(vector<string>);
		void set_dead_animation(vector<string>);
		void set_action_animation(vector<string>);
		void set_hurt_animation(vector<string>);
		void set_spawn_animation(vector<string>);
		void set_can_move(bool);
		void set_can_hurt(bool);
		void set_can_action(bool);
		void set_position(int x,int y);

		//get function
		int getLife();
		int get_hurt_time();
		int get_hurt_duration();
		int get_posX();
		int get_posY();
		MOVEMENT_DIR getFace();
		vector<CMovingBitmap> get_layer();

		//is function
		bool isWalk();

		//behavior function
		void showLayer(int);
		void movement(MOVEMENT_DIR);
		void walk();
		void stop();
		void spawn();
		int attack();
		void die();
		void hurt(int damage);
		void heal(int count);
	protected:
	private:

		//void drop_items(int probability);	// 1 ~ 1000, 1000 = 100% drop

		 //Item* item_set;

	};
}
#endif // !CHARACTER_H
