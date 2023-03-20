#include "stdafx.h"
#include "../Core/game.h"
#include "../Core/MainFrm.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <direct.h>
#include <string.h>
#include ".\Source.\Library\audio.h"
#include ".\Source.\Library\gameutil.h"
#include ".\Source.\Library\gamecore.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>
#include"windef.h"
#include"wingdi.h"
#include"atltypes.h"
#include"time.h"
#include"afxwin.h"

#include"character.h"

namespace game_framework {

	Character::Character() : Creature()
	{

	}

	//set function
	void Character::set_decision_time(int time)
	{
		if (time < 0 || time > 2000)
			return;
		_decision_time = time;
	}
	void Character::set_movement_animation(vector<string> filename)
	{
		this->_movement_animation_f.LoadBitmapByString({ filename[0],filename[1] },RGB(255,255,255));
		this->_movement_animation_b.LoadBitmapByString({ filename[2],filename[3] }, RGB(255, 255, 255));
		this->_movement_animation_l.LoadBitmapByString({ filename[4],filename[5] }, RGB(255, 255, 255));
		this->_movement_animation_r.LoadBitmapByString({ filename[6],filename[7] }, RGB(255, 255, 255));
	}
	void Character::set_action_animation(vector<string> filename)
	{
		this->_action_animation_f.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
		this->_action_animation_b.LoadBitmapByString({ filename[1] }, RGB(255, 255, 255));
		this->_action_animation_l.LoadBitmapByString({ filename[2] }, RGB(255, 255, 255));
		this->_action_animation_r.LoadBitmapByString({ filename[3] }, RGB(255, 255, 255));
	}
	void Character::set_hurt_animation(vector<string> filename)
	{
		this->_hurt_animation_f.LoadBitmapByString({ filename[0],filename[1] }, RGB(255, 255, 255));
		this->_hurt_animation_b.LoadBitmapByString({ filename[2],filename[3] }, RGB(255, 255, 255));
		this->_hurt_animation_l.LoadBitmapByString({ filename[4],filename[5] }, RGB(255, 255, 255));
		this->_hurt_animation_r.LoadBitmapByString({ filename[6],filename[7] }, RGB(255, 255, 255));
	}
	void Character::set_dead_animation(vector<string> filename)
	{
		this->_dead_animation.LoadBitmapByString(filename, RGB(255, 255, 255));
	}
	void Character::set_spawn_animation(vector<string> filename)
	{
		this->_spawn_animation.LoadBitmapByString(filename);
	}
	void Character::set_can_action(bool data)
	{
		_can_action = data;
	}
	void Character::set_can_move(bool data)
	{
		_can_move = data;
	}
	void Character::set_can_hurt(bool data)
	{
		_can_hurt = data;
	}
	//get function
	int Character::getLife()
	{
		return 0;
	}
	bool Character::isWalk()
	{
		return _walking;
	}
	MOVEMENT_DIR  Character::getFace()
	{
		return _face;
	}
	int Character::get_hurt_time()
	{
		return _hurt_time;
	}
	int Character::get_hurt_duration()
	{
		return _hurt_duration;
	}

	//behavior function
	void Character::showLayer()
	{

	}
	void Character::spawn()
	{

	}
	int Character::attack()
	{
		_walking = false;
		//attack_item and animation
		//_attack_animation.SetAnimation(100, true);
		_walking = true;

		//if hurt some one, return damage
		return 0;
	}
	void Character::die()
	{

	}
	void Character::hurt(int damage)
	{
		_hurt_duration = clock();
		_can_move = false;
		if (damage == 0)
			return;


		if (_life == 0)
		{
			//dead animation
			//reset the game
		}
	}
	void Character::heal(int count)
	{
		if (count == 0)
			return;

	}
	void Character::movement(MOVEMENT_DIR direction)
	{
		if (_can_move == false)
			return;

		_face = direction;
		_layer.clear();
		_walking = true;
		switch (_face)
		{
		case UP:
			_layer.push_back(_movement_animation_b);
		case DOWN:
			_layer.push_back(_movement_animation_f);
		case LEFT:
			_layer.push_back(_movement_animation_l);
		case RIGHT:
			_layer.push_back(_movement_animation_r);
		}
		//_movement_animation.SetAnimation(20, true);
	}
	void Character::stop()
	{
		_walking = false;
		//_movement_animation.SetAnimation(20, false);
	}

	/*
	void Character::AI()
	{

	}
	void Character::drop_items(int porbability)
	{
		int random = rand() % 1001;
		if (random < porbability)
		{
			//drop item
		}
	}
	*/
}