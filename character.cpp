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
		_layer.clear();
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
	void Character::set_position(int x, int y)
	{
		if (x < 0 || x > 1024 || y < 0 || y > 1024)
			return;
		_posX = x;
		_posY = y;
	}
	void Character::set_ban_move(MOVEMENT_DIR dir, bool set)
	{
		switch (dir)
		{
		case UP:
			ban_move_up = set;
			break;
		case DOWN:
			ban_move_down = set;
			break;
		case LEFT:
			ban_move_left = set;
			break;
		case RIGHT:
			ban_move_right = set;
			break;
		}
	}

	//get function
	int Character::getLife(){ return 0; }
	bool Character::isWalk(){ return _walking; }
	MOVEMENT_DIR  Character::getFace(){ return _face; }
	int Character::get_hurt_time(){ return _hurt_time; }
	int Character::get_hurt_duration(){ return _hurt_duration; }
	int Character::get_posX() { return _posX; }
	int Character::get_posY() { return _posY; }
	vector<CMovingBitmap> Character::get_layer() { return _layer; }

	//behavior function
	void Character::showLayer(int scale)
	{
		/*
		*/
		int temp = _layer.size();
		for (int i = 0; i < temp; i++)
		{
			_layer[i].SetTopLeft(_posX * scale_all, _posY * scale_all + map_top_offset * scale_all);
			_layer[i].ShowBitmap(scale);
		}

	}
	void Character::movement(MOVEMENT_DIR direction)
	{
		if (_can_move == false)
			return;

		_walking = true;
		_face = direction;
		_layer.clear();
		switch (_face)
		{
		case UP:
			_movement_animation_b.SetAnimation(_move_duration, false);
			_layer.push_back(_movement_animation_b);
			break;
		case DOWN:
			_movement_animation_f.SetAnimation(_move_duration, false);
			_layer.push_back(_movement_animation_f);
			break;
		case LEFT:
			_movement_animation_l.SetAnimation(_move_duration, false);
			_layer.push_back(_movement_animation_l);
			break;
		case RIGHT:
			_movement_animation_r.SetAnimation(_move_duration, false);
			_layer.push_back(_movement_animation_r);
			break;
		}
		//_movement_animation.SetAnimation(20, true);
	}
	void Character::walk()
	{
		if (_walking == false)
			return;
		switch (_face)
		{
		case UP:
			if(!ban_move_up)
				_posY -= _move_speed;
			break;
		case DOWN:
			if(!ban_move_down)
				_posY += _move_speed;
			break;
		case LEFT:
			if(!ban_move_left)
				_posX -= _move_speed;
			break;
		case RIGHT:
			if(!ban_move_right)
				_posX += _move_speed;
			break;
		}
		/*
		int temp = _layer.size();
		for(int i = 0; i < temp; i++)
			_layer[i].SetTopLeft(_posX * scale_all, _posY * scale_all + map_top_offset * scale_all);
		*/
	}
	void Character::stop()
	{
		_walking = false;
		_layer.clear();
		switch (_face)
		{
		case UP:
			_movement_animation_b.StopAnimation();
			_layer.push_back(_movement_animation_b);
			break;
		case DOWN:
			_movement_animation_f.StopAnimation();
			_layer.push_back(_movement_animation_f);
			break;
		case LEFT:
			_movement_animation_l.StopAnimation();
			_layer.push_back(_movement_animation_l);
			break;
		case RIGHT:
			_movement_animation_r.StopAnimation();
			_layer.push_back(_movement_animation_r);
			break;
		}
		/*
		int temp = _layer.size();
		for (int i = 0; i < temp; i++)
			_layer[i].SetTopLeft(_posX * scale_all, _posY * scale_all + map_top_offset * scale_all);
		*/
	}
	void Character::spawn()
	{

	}
	int Character::attack()
	{
		_walking = false;
		//attack_item and animation
		//_attack_animation.ToggleAnimation();
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