#include <StdAfx.h>
#include "monster.h"


namespace game_framework {

	Monster::Monster() : Creature() 
	{

	}
	void Monster::set_movement_animation(string filename) override
	{
		this->_movement_animation.LoadBitmapByString({ filename });
		//movement_animation = anim;
	}
	void Monster::set_dead_animation(string filename) override
	{
		this->dead_animation.LoadBitmapByString({ filename });
		//dead_animation.LoadBitmapByString({anim.GetImageFileName()}, anim.GetFilterColor());
		//dead_animation = anim;
	}
	void Monster::set_attack_animation(string filename) override
	{
		this->attack_animation.LoadBitmapByString({ filename });
		//attack_animation.LoadBitmapByString({ anim.GetImageFileName() }, anim.GetFilterColor());
		//attack_animation = anim;
	}
	void Monster::set_hurt_animation(string filename) override
	{
		this->hurt_animation.LoadBitmapByString({ filename });
		//hurt_animation.LoadBitmapByString({ anim.GetImageFileName() }, anim.GetFilterColor());
		//hurt_animation = anim;
	}
	void Monster::set_spawn_animation(string filename) override
	{
		this->spawn_animation.LoadBitmapByString({ filename });
		//spawn_animation.LoadBitmapByString({ anim.GetImageFileName() }, anim.GetFilterColor());
		//spawn_animation = anim;
	}
	void Monster::spawn() override
	{

	}
	int Monster::attack() override
	{
		attack_animation.SetAnimation(100, true);
		
		//attack_item and animation

		//if hurt some one, return damage
	}
	void Monster::die() override
	{

	}
	void Monster::hurt(int damage) override
	{
		if (damage == 0)
			return;
	}
	void Monster::movement(MOVEMENT_REF direction) override
	{

	}
	void Monster::show() override
	{

	}
	void Monster::set_decision_time(int time)
	{
		if (time < 0 || time > 2000)
			return;
		decision_time = time;
	}
	void Monster::AI()
	{
		
	}
	void Monster::drop_items(int porbability)
	{
		int random = rand() % 1001;
		if (random < porbability)
		{
			//drop item
		}
	}
}