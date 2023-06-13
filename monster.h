#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include"creature.h"

using namespace std;

namespace game_framework {
	enum MONSTER_TYPE
	{
		TEKTITE_RED,
	};
	class Monster : public Creature {
	public:
		//void AI();
		/*
		*/
		Monster();
		~Monster() = default;

		//set function
		void set_movement_animation(vector<string>);
		void set_dead_animation(vector<string>);
		void set_action_animation(vector<string>);
		void set_hurt_animation(vector<string>);
		void set_spawn_animation(vector<string>);
		void set_can_move(bool);
		void set_can_hurt(bool);
		void set_can_action(bool);
		void set_position(int x, int y);

		void set_ban_move(MOVEMENT_DIR, bool);
		void set_decision_time(int);

		void set_max_life(int);

		//get function
		MOVEMENT_DIR getFace();
		clock_t get_hurt_time();
		clock_t get_hurt_stop_time();
		clock_t get_attack_time();
		clock_t get_attack_speed();
		clock_t get_attack_duration();
		int get_posX();
		int get_posY();
		vector<CMovingBitmap> get_body_layer();
		bool get_can_action();
		bool get_can_hurt();
		bool get_can_move();
		int get_life();
		int get_max_life();
		int get_damage();

		vector<CMovingBitmap> get_wapon_layer();
		vector<CMovingBitmap> get_item_layer();

		//is function
		bool isWalk();
		bool isAttacking();

		bool isFrontCollide(vector<CRect>);

		//behavior function
		void movement(MOVEMENT_DIR);
		void walk();
		void die();
		void spawn(vector<CRect> map_collider);
		void hurt(vector<CRect> collider, vector<int> damage);
		void heal(int count);
		void attack() {};
		void attackDone();
		void stop();
		void showLayers(int);

		virtual void AI(clock_t) { _posY += 1; };

		vector<bool> detect_can_walk(vector<CRect>);

	protected:
	private:
		//variables
		CMovingBitmap _wapon_f, _wapon_b, _wapon_l, _wapon_r;
		//CMovingBitmap _wapon_fly_f, _wapon_fly_b, _wapon_fly_l, _wapon_fly_r;
		int _wapon_offsetX = 0;
		int _wapon_offsetY = 0;
		float _attack_factor = 3.5;
		
		//void drop_items(int probability);	// 1 ~ 1000, 1000 = 100% drop
		 //Item* item_set;

	};
}
#endif // !CHARACTER_H
