#include <StdAfx.h>
#include "character.h"


namespace game_framework {

	Character::Character() : Creature()
	{

	}
	void Character::set_movement_animation(string filename)
	{
		this->_movement_animation.LoadBitmapByString({ filename });
		//movement_animation = anim;
	}
	void Character::set_dead_animation(string filename)
	{
		this->_dead_animation.LoadBitmapByString({ filename });
		//dead_animation.LoadBitmapByString({anim.GetImageFileName()}, anim.GetFilterColor());
		//dead_animation = anim;
	}
	void Character::set_attack_animation(string filename)
	{
		this->_attack_animation.LoadBitmapByString({ filename });
		//attack_animation.LoadBitmapByString({ anim.GetImageFileName() }, anim.GetFilterColor());
		//attack_animation = anim;
	}
	void Character::set_hurt_animation(string filename)
	{
		this->_hurt_animation.LoadBitmapByString({ filename });
		//hurt_animation.LoadBitmapByString({ anim.GetImageFileName() }, anim.GetFilterColor());
		//hurt_animation = anim;
	}
	void Character::set_spawn_animation(string filename)
	{
		this->_spawn_animation.LoadBitmapByString({ filename });
		//spawn_animation.LoadBitmapByString({ anim.GetImageFileName() }, anim.GetFilterColor());
		//spawn_animation = anim;
	}
	void Character::spawn()
	{

	}
	int Character::attack(MOVEMENT_REF direction)
	{
		_attack_animation.SetAnimation(100, true);

		//attack_item and animation

		//if hurt some one, return damage
		return 0;
	}
	void Character::die()
	{

	}
	void Character::hurt(int damage)
	{
		if (damage == 0)
			return;
	}
	void Character::movement(MOVEMENT_REF direction)
	{

	}
	void Character::show()
	{

	}
	void Character::set_decision_time(int time)
	{
		if (time < 0 || time > 2000)
			return;
		_decision_time = time;
	}
	/*
	void Character::AI()
	{

	}
	*/
	void Character::drop_items(int porbability)
	{
		int random = rand() % 1001;
		if (random < porbability)
		{
			//drop item
		}
	}
}