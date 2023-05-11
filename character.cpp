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
		_move_speed = 2;
		_max_life = 6;
		_life = _max_life;
		_attack_speed = 200;
		_attack_duration = 300;
		_attack_time = 0;
		_invincible_time = 700;
		//_body_layer.clear();
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
		this->_action_animation_f.LoadBitmapByString({ filename[0],filename[1],filename[2],filename[3] }, RGB(255, 255, 255));
		this->_action_animation_b.LoadBitmapByString({ filename[4],filename[5],filename[6],filename[7] }, RGB(255, 255, 255));
		this->_action_animation_l.LoadBitmapByString({ filename[8],filename[9],filename[10],filename[11] }, RGB(255, 255, 255));
		this->_action_animation_r.LoadBitmapByString({ filename[12],filename[13],filename[14],filename[15] }, RGB(255, 255, 255));
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
	void Character::set_wapon(vector<string> filename)
	{
		_wapon_f.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
		_wapon_b.LoadBitmapByString({ filename[1] }, RGB(255, 255, 255));
		_wapon_l.LoadBitmapByString({ filename[2] }, RGB(255, 255, 255));
		_wapon_r.LoadBitmapByString({ filename[3] }, RGB(255, 255, 255));
		_wapon_fly_f.LoadBitmapByString({ "resources/items/sword_fly_f1.bmp","resources/items/sword_fly_f2.bmp" ,"resources/items/sword_fly_f3.bmp" }, RGB(255, 255, 255));
		_wapon_fly_b.LoadBitmapByString({ "resources/items/sword_fly_b1.bmp","resources/items/sword_fly_b2.bmp" ,"resources/items/sword_fly_b3.bmp" }, RGB(255, 255, 255));
		_wapon_fly_l.LoadBitmapByString({ "resources/items/sword_fly_l1.bmp","resources/items/sword_fly_l2.bmp" ,"resources/items/sword_fly_l3.bmp" }, RGB(255, 255, 255));
		_wapon_fly_r.LoadBitmapByString({ "resources/items/sword_fly_r1.bmp","resources/items/sword_fly_r2.bmp" ,"resources/items/sword_fly_r3.bmp" }, RGB(255, 255, 255));
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
	void Character::set_wapon_position(long t)
	{
		float n = (float)(int)(t * 4 / _attack_speed);		//n = t per 1/4 attack duration
		float s = -2 * (n - 2) * (n - 2) + 12;
		int x = 0;
		int y = 0;
		switch (_face)
		{
		case UP:
			y = (int)-s;
			break;
		case DOWN:
			y = (int)s;
			break;
		case LEFT:
			x = (int)-s;
			break;
		case RIGHT:
			x = (int)s;
			break;
		case NONE:
			break;
		default:
			break;
		}
		int counter = _wapon_layer.size();
		for (int i = 0; i < counter; i++)
		{
			_wapon_layer[i].SetTopLeft((_posX + _wapon_offsetX + x)*scale_all, (_posY + _wapon_offsetY + map_top_offset + y)*scale_all);
		}
	}

	//get function
	MOVEMENT_DIR  Character::getFace(){ return _face; }
	clock_t Character::get_hurt_time(){ return _hurt_time; }
	clock_t Character::get_hurt_stop_time(){ return _hurt_stop_time; }
	clock_t Character::get_attack_time(){ return _attack_time; }
	clock_t Character::get_attack_speed(){ return _attack_speed; }
	clock_t Character::get_attack_duration(){ return _attack_duration; }
	int Character::get_posX() { return _posX; }
	int Character::get_posY() { return _posY; }
	vector<CMovingBitmap> Character::get_body_layer() { return _body_layer; }
	vector<CMovingBitmap> Character::get_wapon_layer() { return _wapon_layer; }
	vector<CMovingBitmap> Character::get_item_layer() { return _item_layer; }
	bool Character::get_can_action() { return _can_action; }
	bool Character::get_can_hurt() { return _can_hurt; }
	bool Character::get_can_move() { return _can_move; }
	int Character::get_life() { return _life; }
	int Character::get_max_life() { return _max_life; }
	int Character::get_damage() { return _damage; }
	int Character::get_key() { return _key; }
	int Character::get_bomb() { return _bomb; }

	//is function
	bool Character::isWalk(){ return _walking; }
	bool Character::isAttacking() { return _attacking; };
	bool Character::isFrontCollide(vector<CRect> data)
	{
		int width = 5;
		int offset = 5;
		CRect coll;
		//coll = CRect(_body_layer[0].GetLeft(), _body_layer[0].GetTop(), _body_layer[0].GetLeft() + _body_layer[0].GetWidth() * scale_all, _body_layer[0].GetTop() + _body_layer[0].GetHeight() * scale_all);
		switch (_face)
		{
		case UP:
			//coll.InflateRect(0, 2, 0, 0);	//left top right bottom
			coll = CRect(_body_layer[0].GetLeft() + offset, _body_layer[0].GetTop() - width, _body_layer[0].GetLeft() + _body_layer[0].GetWidth() * scale_all - offset, _body_layer[0].GetTop());
			break;
		case DOWN:
			coll = CRect(_body_layer[0].GetLeft() + offset, _body_layer[0].GetTop() + _body_layer[0].GetHeight() * scale_all, _body_layer[0].GetLeft() + _body_layer[0].GetWidth() * scale_all - offset, _body_layer[0].GetTop() + _body_layer[0].GetHeight() * scale_all + width);
			break;
		case LEFT:
			coll = CRect(_body_layer[0].GetLeft() - width, _body_layer[0].GetTop() + offset, _body_layer[0].GetLeft(), _body_layer[0].GetTop() + _body_layer[0].GetHeight() * scale_all - offset);
			break;
		case RIGHT:
			coll = CRect(_body_layer[0].GetLeft() + _body_layer[0].GetHeight() * scale_all, _body_layer[0].GetTop() + offset, _body_layer[0].GetLeft() + _body_layer[0].GetWidth() * scale_all + width, _body_layer[0].GetTop() + _body_layer[0].GetHeight() * scale_all - offset);
			break;
		case NONE:
			break;
		default:
			break;
		}
		CRect tester;
		int counter = data.size();
		for (int i = 0; i < counter; i++)
		{
			if (tester.IntersectRect(coll, data[i]) != 0)	//collide something
			{
				set_ban_move(_face, true);
				return true;
			}
		}
		set_ban_move(UP, false);
		set_ban_move(DOWN, false);
		set_ban_move(LEFT, false);
		set_ban_move(RIGHT, false);
		return false;
	}
	//behavior function
	void Character::showLayers(int scale)
	{
		int temp = _wapon_layer.size();
		//show wapon
		for (int i = 0; i < temp; i++)
		{
			//_wapon_layer[i].SetTopLeft(_posX * scale_all, _posY * scale_all + map_top_offset * scale_all);
			_wapon_layer[i].ShowBitmap(scale);
		}
		//show body
		temp = _body_layer.size();
		for (int i = 0; i < temp; i++)
		{
			_body_layer[i].SetTopLeft(_posX * scale_all, _posY * scale_all + map_top_offset * scale_all);
			_body_layer[i].ShowBitmap(scale);
		}
		//show item
		temp = _item_layer.size();
		for (int i = 0; i < temp; i++)
		{
			_item_layer[i].SetTopLeft(_posX * scale_all, _posY * scale_all + map_top_offset * scale_all);
			_item_layer[i].ShowBitmap(scale);
		}
	}
	void Character::movement(MOVEMENT_DIR direction)
	{
		if (_can_move == false)
			return;

		_walking = true;
		_face = direction;
		_body_layer.clear();
		switch (_face)
		{
		case UP:
			_movement_animation_b.SetAnimation(_move_duration, false);
			_body_layer.push_back(_movement_animation_b);
			break;
		case DOWN:
			_movement_animation_f.SetAnimation(_move_duration, false);
			_body_layer.push_back(_movement_animation_f);
			break;
		case LEFT:
			_movement_animation_l.SetAnimation(_move_duration, false);
			_body_layer.push_back(_movement_animation_l);
			break;
		case RIGHT:
			_movement_animation_r.SetAnimation(_move_duration, false);
			_body_layer.push_back(_movement_animation_r);
			break;
		}
		//_movement_animation.SetAnimation(20, true);
	}
	void Character::walk()
	{
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
		_body_layer.clear();
		switch (_face)
		{
		case UP:
			_movement_animation_b.StopAnimation();
			_body_layer.push_back(_movement_animation_b);
			break;
		case DOWN:
			_movement_animation_f.StopAnimation();
			_body_layer.push_back(_movement_animation_f);
			break;
		case LEFT:
			_movement_animation_l.StopAnimation();
			_body_layer.push_back(_movement_animation_l);
			break;
		case RIGHT:
			_movement_animation_r.StopAnimation();
			_body_layer.push_back(_movement_animation_r);
			break;
		}
		/*
		int temp = _layer.size();
		for (int i = 0; i < temp; i++)
			_layer[i].SetTopLeft(_posX * scale_all, _posY * scale_all + map_top_offset * scale_all);
		*/
	}
	void Character::spawn(vector<CRect>)
	{

	}
	void Character::attack()
	{
		if (clock() - _attack_time < _attack_duration)
			return;
		_attacking = true;
		_walking = false;
		_can_move = false;
		_attack_time = clock();
		_wapon_layer.clear();
		_body_layer.clear();

		switch (_face)
		{
		case UP:
			_wapon_offsetX = 5;
			_wapon_offsetY = -3;
			//_wapon_b.SetTopLeft((_posX + _wapon_offsetX)*scale_all, (_posY + _wapon_offsetY)*scale_all);
			_wapon_layer.push_back(_wapon_b);
			_action_animation_b.SetTopLeft(_posX * scale_all, _posY * scale_all);
			_action_animation_b.SetAnimation(_attack_duration / 4, true);
			_action_animation_b.ToggleAnimation();
			_body_layer.push_back(_action_animation_b);
			break;
		case DOWN:
			_wapon_offsetX = 5;
			_wapon_offsetY = 3;
			//_wapon_f.SetTopLeft((_posX + _wapon_offsetX)*scale_all, (_posY + _wapon_offsetY)*scale_all);
			_wapon_layer.push_back(_wapon_f);
			_action_animation_f.SetTopLeft(_posX * scale_all, _posY * scale_all);
			_action_animation_f.SetAnimation(_attack_duration / 4, true);
			_action_animation_f.ToggleAnimation();
			_body_layer.push_back(_action_animation_f);
			break;
		case LEFT:
			_wapon_offsetX = -3;
			_wapon_offsetY = 5;
			//_wapon_l.SetTopLeft((_posX + _wapon_offsetX)*scale_all, (_posY + _wapon_offsetY)*scale_all);
			_wapon_layer.push_back(_wapon_l);
			_action_animation_l.SetTopLeft(_posX * scale_all, _posY * scale_all);
			_action_animation_l.SetAnimation(_attack_duration / 4, true);
			_action_animation_l.ToggleAnimation();
			_body_layer.push_back(_action_animation_l);
			break;
		case RIGHT:
			_wapon_offsetX = 3;
			_wapon_offsetY = 5;
			//_wapon_r.SetTopLeft((_posX + _wapon_offsetX)*scale_all, (_posY + _wapon_offsetY)*scale_all);
			_wapon_layer.push_back(_wapon_r);
			_action_animation_r.SetTopLeft(_posX * scale_all, _posY * scale_all);
			_action_animation_r.SetAnimation(_attack_duration / 4, true);
			_action_animation_r.ToggleAnimation();
			_body_layer.push_back(_action_animation_r);
			break;
		case NONE:
			break;
		default:
			break;
		}
	}
	void Character::attackDone()
	{
		_attacking = false;
		_walking = true;
		_can_move = true;
		_wapon_layer.clear();
	}
	CMovingBitmap* Character::make_fly_wapon()
	{
		CMovingBitmap* data = new CMovingBitmap();
		switch (_face)
		{
		case UP:
			data->LoadBitmapByString(_wapon_fly_b.GetImageFilesName(),RGB(255,255,255));
			break;
		case DOWN:
			data->LoadBitmapByString(_wapon_fly_f.GetImageFilesName(), RGB(255, 255, 255));
			break;
		case LEFT:
			data->LoadBitmapByString(_wapon_fly_l.GetImageFilesName(), RGB(255, 255, 255));
			break;
		case RIGHT:
			data->LoadBitmapByString(_wapon_fly_r.GetImageFilesName(), RGB(255, 255, 255));
			break;
		case NONE:
			break;
		default:
			break;
		}
		data->SetTopLeft((_posX + _wapon_offsetX)*scale_all, (_posY + _wapon_offsetY)*scale_all);
		data->SetAnimation(100, false);
		return data;
	}
	void Character::die()
	{

	}
	/*
	void Character::hurt(vector<Monster*> monsters)
	{
		clock_t time = clock();
		if (time < _hurt_time + _hurt_stop_time)
		{
			_can_move = false;
			//play hurt animation
			_body_layer.clear();
			switch (_face)
			{
			case game_framework::UP:
				_body_layer.push_back(_hurt_animation_b);
				break;
			case game_framework::DOWN:
				_body_layer.push_back(_hurt_animation_f);
				break;
			case game_framework::LEFT:
				_body_layer.push_back(_hurt_animation_l);
				break;
			case game_framework::RIGHT:
				_body_layer.push_back(_hurt_animation_r);
				break;
			case game_framework::NONE:
				break;
			default:
				break;
			}
			_body_layer[0].SetAnimation(_hurt_stop_time / 2, false);
			return;
		}
		else if (time < _hurt_time + _invincible_time)
		{
			_can_move = true;
			return;
		}


		_hurt_time = time;
		CRect self = CRect(_body_layer[0].GetLeft(), _body_layer[0].GetTop(), _body_layer[0].GetLeft() + _body_layer[0].GetWidth() * scale_all, _body_layer[0].GetTop() + _body_layer[0].GetHeight() * scale_all);
		CRect tester;
		int counter = monsters.size();
		for (int i = 0; i < counter; i++)
		{
			CRect monsters_coll = CRect(monsters[i]->get_body_layer()[i].GetLeft(), monsters[i]->get_body_layer()[i].GetTop(), monsters[i]->get_body_layer()[i].GetLeft() + monsters[i]->get_body_layer()[i].GetWidth() * scale_all, monsters[i]->get_body_layer()[i].GetTop() + monsters[i]->get_body_layer()[i].GetHeight() * scale_all);
			if (tester.IntersectRect(self, monsters_coll) != 0)
			{
				_life -= monsters[i]->get_damage();
				if (_life < 0)
					_life = 0;
				break;
			}
		}
		//_hurt_time = clock();


		if (_life == 0)
		{
			//dead animation
			//reset the game
		}
	}
	*/
	void Character::hurt(vector<CRect> collider, vector<int> damage)
	{
		clock_t time = clock();
		if (time < _hurt_time + _hurt_stop_time)
		{
			_can_move = false;
			//play hurt animation
			_body_layer.clear();
			switch (_face)
			{
			case game_framework::UP:
				_body_layer.push_back(_hurt_animation_b);
				break;
			case game_framework::DOWN:
				_body_layer.push_back(_hurt_animation_f);
				break;
			case game_framework::LEFT:
				_body_layer.push_back(_hurt_animation_l);
				break;
			case game_framework::RIGHT:
				_body_layer.push_back(_hurt_animation_r);
				break;
			case game_framework::NONE:
				break;
			default:
				break;
			}
			_body_layer[0].SetAnimation(_hurt_stop_time / 4, false);
			return;
		}
		else if (time < _hurt_time + _invincible_time)
		{
			_can_move = true;
			return;
		}

		CRect self = CRect(_body_layer[0].GetLeft(), _body_layer[0].GetTop(), _body_layer[0].GetLeft() + _body_layer[0].GetWidth() * scale_all, _body_layer[0].GetTop() + _body_layer[0].GetHeight() * scale_all);
		self.DeflateRect(10,10,10,10);
		CRect tester;
		int counter = collider.size();
		for (int i = 0; i < counter; i++)
		{
			if (tester.IntersectRect(self, collider[i]) != 0)
			{
				_hurt_time = time;
				_life -= damage[i];
				if (_life < 0)
					_life = 0;
			}
		}
		//_hurt_time = clock();


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
	
}