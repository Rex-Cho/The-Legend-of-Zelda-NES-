#pragma once
#include "../Library/gameutil.h"

using namespace std;

namespace game_framework {
	class Creature {
	public:

	protected:
		enum MOVEMENT_REF {
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		Creature();
		~Creature() = default;

		virtual void die() = 0;
		virtual void spawn() = 0;
		virtual void movement(MOVEMENT_REF) = 0;
		virtual void hurt(int) = 0;
		virtual int attack(MOVEMENT_REF) = 0;
		virtual void set_movement_animation(string) = 0;
		virtual void set_dead_animation(string) = 0;
		virtual void set_attack_animation(string) = 0;
		virtual void set_hurt_animation(string) = 0;
		virtual void set_spawn_animation(string) = 0;
		virtual void show() = 0;

		int _life = 2;
		int _damage = 1;
		int _move_duration = 100;
		bool _can_move = true;
		bool _can_hurt = true;
		bool _can_attack = true;
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