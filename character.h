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
		void set_wapon(vector<string>);
		void set_can_move(bool);
		void set_can_hurt(bool);
		void set_can_action(bool);
		void set_position(int x,int y);
		void set_ban_move(MOVEMENT_DIR, bool);

		void set_wapon_position(long time);

		//get function
		int getLife();
		clock_t get_hurt_time();
		clock_t get_hurt_duration();
		clock_t get_attack_time();
		clock_t get_attack_duration();
		int get_posX();
		int get_posY();
		MOVEMENT_DIR getFace();
		vector<CMovingBitmap> get_body_layer();
		vector<CMovingBitmap> get_wapon_layer();
		vector<CMovingBitmap> get_item_layer();

		//is function
		bool isWalk();
		bool isAttacking();
		bool isFrontCollide(vector<CRect>);

		//behavior function
		void showLayers(int);
		void movement(MOVEMENT_DIR);
		void walk();
		void stop();
		void spawn();
		void attack();
		void attackDone();
		void die();
		void hurt(int damage);
		void heal(int count);
	protected:
	private:
		//variables
		CMovingBitmap _wapon_f, _wapon_b, _wapon_l, _wapon_r;
		int _wapon_offsetX = 0;
		int _wapon_offsetY = 0;
		float _attack_factor = 3.5;

		//void drop_items(int probability);	// 1 ~ 1000, 1000 = 100% drop
		 //Item* item_set;

	};
}
#endif // !CHARACTER_H
