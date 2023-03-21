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
		RIGHT
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
		virtual bool isWalk() = 0;
		virtual int get_hurt_time() = 0;
		virtual int get_hurt_duration() = 0;
		virtual int get_posX() = 0;
		virtual int get_posY() = 0;

		//behavior function
		virtual void movement(MOVEMENT_DIR) = 0;
		virtual void walk() = 0;
		virtual void die() = 0;
		virtual void spawn() = 0;
		virtual void hurt(int) = 0;
		virtual void heal(int) = 0;
		virtual int attack() = 0;
		virtual void stop() = 0;
		virtual void showLayer(int) = 0;

		//variables
		int _posX = 0;
		int _posY = 0;
		int _hurt_duration = 200;				//ms
		int _layer_counter = 0;
		int _decision_time = 800;				//ms
		int _life = 2;
		int _damage = 1;
		int _move_duration = 100;				//ms
		int _move_speed = 1;						//pixel
		bool _can_move = true;
		bool _can_hurt = true;
		bool _can_action = true;
		bool _walking = false;
		clock_t _hurt_time = 0;
		MOVEMENT_DIR _face = DOWN;
		CMovingBitmap _movement_animation_f, _movement_animation_b, _movement_animation_l, _movement_animation_r;
		CMovingBitmap _dead_animation;
		CMovingBitmap _action_animation_f, _action_animation_b, _action_animation_l, _action_animation_r;
		CMovingBitmap _hurt_animation_f, _hurt_animation_b, _hurt_animation_l, _hurt_animation_r;
		CMovingBitmap _spawn_animation;
		vector<CMovingBitmap> _layer;
	private:

	};
}
#endif // !CREATURE_H
