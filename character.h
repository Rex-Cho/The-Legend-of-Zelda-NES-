#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <list>
#include <vector>
#include <map>
#include"windef.h"
#include"wingdi.h"
#include"atltypes.h"
#include"time.h"
#include"afxwin.h"
#include".\Source.\Library\gameutil.h"

#include"creature.h"

using namespace std;

namespace game_framework {
	class Character : public Creature{
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
#endif // !CHARACTER_H
