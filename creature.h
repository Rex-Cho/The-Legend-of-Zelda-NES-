#pragma once
#ifndef CREATURE_H
#define CREATURE_H

#include <list>
#include <vector>
#include <map>
#include <time.h>
#include"windef.h"
#include"wingdi.h"
#include"atltypes.h"
#include"time.h"
#include"afxwin.h"
#include".\Source.\Library\gameutil.h"

using namespace std;

namespace game_framework {
	enum MOVEMENT_DIR {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};
	class Creature {
	public:
	protected:
		Creature() {};
		~Creature() = default;

		//set function
		virtual void set_movement_animation(vector<string>) = 0;
		virtual void set_dead_animation(vector<string>) = 0;
		virtual void set_action_animation(vector<string>) = 0;
		virtual void set_hurt_animation(vector<string>) = 0;
		virtual void set_spawn_animation(vector<string>) = 0;
		virtual void set_can_move(bool) = 0;
		virtual void set_can_hurt(bool) = 0;
		virtual void set_can_action(bool) = 0;
		virtual void set_position(int x, int y) = 0;

		//get function
		virtual MOVEMENT_DIR getFace() = 0;
		virtual int getLife() = 0;
		virtual clock_t get_hurt_time() = 0;
		virtual clock_t get_hurt_duration() = 0;
		virtual clock_t get_attack_time() = 0;
		virtual clock_t get_attack_duration() = 0;
		virtual int get_posX() = 0;
		virtual int get_posY() = 0;
		virtual vector<CMovingBitmap> get_body_layer() = 0;
		virtual vector<CMovingBitmap> get_wapon_layer() = 0;
		virtual vector<CMovingBitmap> get_item_layer() = 0;
		virtual bool isWalk() = 0;
		virtual bool isAttacking() = 0;
		virtual bool get_can_action() = 0;
		virtual bool get_can_hurt() = 0;
		virtual bool get_can_move() = 0;
		virtual int get_life() = 0;
		virtual int get_max_life() = 0;

		//behavior function
		virtual void movement(MOVEMENT_DIR) = 0;
		virtual void walk() = 0;
		virtual void die() = 0;
		virtual void spawn() = 0;
		virtual void hurt(int) = 0;
		virtual void heal(int) = 0;
		virtual void attack() = 0;
		virtual void attackDone() = 0;
		virtual void stop() = 0;
		virtual void showLayers(int) = 0;

		//variables
		int _posX;
		int _posY;
		int _layer_counter = 0;
		int _decision_time = 800;				//ms
		int _life = 3;
		int _max_life = _life;
		int _damage = 1;
		int _move_duration = 100;				//ms
		int _move_speed = 1;						//pixel
		bool _can_move = true;
		bool _can_hurt = true;
		bool _can_action = true;
		bool _walking = false;
		bool _attacking = false;

		bool ban_move_up = false;
		bool ban_move_down = false;
		bool ban_move_left = false;
		bool ban_move_right = false;

		clock_t _hurt_time = 0;
		clock_t _hurt_duration = 200;				//ms, get hurt can't controling time
		clock_t _attack_time = 0;
		clock_t _attack_duration = 200;				//ms, attack speed
		MOVEMENT_DIR _face = DOWN;
		CMovingBitmap _movement_animation_f, _movement_animation_b, _movement_animation_l, _movement_animation_r;
		CMovingBitmap _action_animation_f, _action_animation_b, _action_animation_l, _action_animation_r;
		CMovingBitmap _hurt_animation_f, _hurt_animation_b, _hurt_animation_l, _hurt_animation_r;
		CMovingBitmap _spawn_animation;
		CMovingBitmap _dead_animation;
		vector<CMovingBitmap> _body_layer;	
		vector<CMovingBitmap> _wapon_layer;	
		vector<CMovingBitmap> _item_layer;	
	private:

	};
}
#endif // !CREATURE_H
