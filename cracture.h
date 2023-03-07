#pragma once
#include "Source/Library/gameutil.h"

using namespace std;

namespace game_framework {
	class Creature {
	public:

	protected:
		enum MOVEMENT_REF{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		Creature();
		~Creature() = default;
		virtual void die() = 0;
		virtual void spawn() = 0;
		virtual void movement() = 0;
		virtual void hurt() = 0;
		virtual void attack() = 0;
		virtual void set_movement_animation(CMovingBitmap) = 0;
		virtual void set_dead_animation(CMovingBitmap) = 0;
		virtual void set_attack_animation(CMovingBitmap) = 0;
		virtual void set_hurt_animation(CMovingBitmap) = 0;
		virtual void set_spawn_animation(CMovingBitmap) = 0;
		virtual void show(MOVEMENT_REF) = 0;
		int life;
		CMovingBitmap movement_animation;
		CMovingBitmap dead_animation;
		CMovingBitmap attack_animation;
		CMovingBitmap hurt_animation;
		CMovingBitmap spawn_animation;
	private:

	};
	Creature::Creature()
	{

	}
}