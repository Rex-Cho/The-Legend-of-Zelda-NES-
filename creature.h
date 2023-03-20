#pragma once
#ifndef CREATURE_H
#define CREATURE_H

#include <list>
#include <vector>
#include <map>
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
		Creature();
		~Creature() = default;

		virtual void die() = 0;
		virtual void spawn() = 0;
		virtual void movement(MOVEMENT_DIR) = 0;
		virtual void hurt(int) = 0;
		virtual void heal(int) = 0;
		virtual int attack(MOVEMENT_DIR) = 0;
		virtual void set_movement_animation(string) = 0;
		virtual void set_dead_animation(string) = 0;
		virtual void set_attack_animation(string) = 0;
		virtual void set_hurt_animation(string) = 0;
		virtual void set_spawn_animation(string) = 0;
		virtual void show() = 0;
		virtual void stop() = 0;
		virtual bool isWalk() = 0;
		virtual MOVEMENT_DIR getFace() = 0;
		virtual int getLife() = 0;


		int _decision_time = 800;
		int _life = 2;
		int _damage = 1;
		int _move_duration = 100;
		bool _can_move = true;
		bool _can_hurt = true;
		bool _can_attack = true;
		bool _walking = false;
		CMovingBitmap _movement_animation;
		CMovingBitmap _dead_animation;
		CMovingBitmap _attack_animation;
		CMovingBitmap _hurt_animation;
		CMovingBitmap _spawn_animation;
	private:

	};
	Creature::Creature()
	{

	}
}
#endif // !CREATURE_H
