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

#include"monster.h"

namespace game_framework {

	Monster::Monster() : Creature()
	{
		_move_speed = 2;
		//_body_layer.clear();
	}

	//set function
	void Monster::set_decision_time(int time)
	{
		if (time < 0 || time > 2000)
			return;
		_decision_time = time;
	}
	void Monster::set_movement_animation(vector<string> filename)
	{
		this->_movement_animation_f.LoadBitmapByString({ filename[0],filename[1] }, RGB(255, 255, 255));
		this->_movement_animation_b.LoadBitmapByString({ filename[2],filename[3] }, RGB(255, 255, 255));
		this->_movement_animation_l.LoadBitmapByString({ filename[4],filename[5] }, RGB(255, 255, 255));
		this->_movement_animation_r.LoadBitmapByString({ filename[6],filename[7] }, RGB(255, 255, 255));
	}
	void Monster::set_action_animation(vector<string> filename)
	{
		this->_action_animation_f.LoadBitmapByString({ filename[0],filename[1],filename[2],filename[3] }, RGB(255, 255, 255));
		this->_action_animation_b.LoadBitmapByString({ filename[4],filename[5],filename[6],filename[7] }, RGB(255, 255, 255));
		this->_action_animation_l.LoadBitmapByString({ filename[8],filename[9],filename[10],filename[11] }, RGB(255, 255, 255));
		this->_action_animation_r.LoadBitmapByString({ filename[12],filename[13],filename[14],filename[15] }, RGB(255, 255, 255));
	}
	void Monster::set_hurt_animation(vector<string> filename)
	{
		this->_hurt_animation_f.LoadBitmapByString({ filename[0],filename[1] }, RGB(255, 255, 255));
		this->_hurt_animation_b.LoadBitmapByString({ filename[2],filename[3] }, RGB(255, 255, 255));
		this->_hurt_animation_l.LoadBitmapByString({ filename[4],filename[5] }, RGB(255, 255, 255));
		this->_hurt_animation_r.LoadBitmapByString({ filename[6],filename[7] }, RGB(255, 255, 255));
	}
	void Monster::set_dead_animation(vector<string> filename)
	{
		this->_dead_animation.LoadBitmapByString(filename, RGB(255, 255, 255));
	}
	void Monster::set_spawn_animation(vector<string> filename)
	{
		this->_spawn_animation.LoadBitmapByString(filename);
	}
	void Monster::set_can_action(bool data)
	{
		_can_action = data;
	}
	void Monster::set_can_move(bool data)
	{
		_can_move = data;
	}
	void Monster::set_can_hurt(bool data)
	{
		_can_hurt = data;
	}
	void Monster::set_position(int x, int y)
	{
		if (x < 0 || x > 1024 || y < 0 || y > 1024)
			return;
		_posX = x;
		_posY = y;
	}
	void Monster::set_ban_move(MOVEMENT_DIR dir, bool set)
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

	//get functionW
	MOVEMENT_DIR  Monster::getFace() { return _face; }
	clock_t Monster::get_hurt_time() { return _hurt_time; }
	clock_t Monster::get_hurt_duration() { return _hurt_duration; }
	clock_t Monster::get_attack_time() { return _attack_time; }
	clock_t Monster::get_attack_speed() { return _attack_speed; }
	clock_t Monster::get_attack_duration() { return _attack_duration; }
	int Monster::get_posX() { return _posX; }
	int Monster::get_posY() { return _posY; }
	vector<CMovingBitmap> Monster::get_body_layer() { return _body_layer; }
	vector<CMovingBitmap> Monster::get_wapon_layer() { return _wapon_layer; }
	vector<CMovingBitmap> Monster::get_item_layer() { return _item_layer; }
	bool Monster::get_can_action() { return _can_action; }
	bool Monster::get_can_hurt() { return _can_hurt; }
	bool Monster::get_can_move() { return _can_move; }
	int Monster::get_life() { return _life; }
	int Monster::get_max_life() { return _max_life; }

	//is function
	bool Monster::isWalk() { return _walking; }
	bool Monster::isAttacking() { return _attacking; };
	bool Monster::isFrontCollide(vector<CRect> data)
	{
		int width = 5;
		int offset = 5;
		CRect coll;
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
	void Monster::showLayers(int scale)
	{
		//show body
		int temp = _body_layer.size();
		for (int i = 0; i < temp; i++)
		{
			_body_layer[i].SetTopLeft(_posX * scale_all, _posY * scale_all + map_top_offset * scale_all);
			_body_layer[i].ShowBitmap(scale);
		}
	}
	void Monster::movement(MOVEMENT_DIR direction)
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
	void Monster::walk()
	{
		switch (_face)
		{
		case UP:
			if (!ban_move_up)
				_posY -= _move_speed;
			break;
		case DOWN:
			if (!ban_move_down)
				_posY += _move_speed;
			break;
		case LEFT:
			if (!ban_move_left)
				_posX -= _move_speed;
			break;
		case RIGHT:
			if (!ban_move_right)
				_posX += _move_speed;
			break;
		}
		/*
		int temp = _layer.size();
		for(int i = 0; i < temp; i++)
			_layer[i].SetTopLeft(_posX * scale_all, _posY * scale_all + map_top_offset * scale_all);
		*/
	}
	void Monster::stop()
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
	void Monster::spawn()
	{

	}
	void Monster::attackDone()
	{
		_attacking = false;
		_walking = true;
		_can_move = true;
		_wapon_layer.clear();
	}
	void Monster::die()
	{

	}
	void Monster::hurt(int damage)
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
	void Monster::heal(int count)
	{
		if (count == 0)
			return;

	}
	vector<bool> Monster::detect_can_walk(vector<CRect> data)
	{
		int width = 5;
		int offset = 5;
		CRect coll_UP;
		coll_UP = CRect(_body_layer[0].GetLeft() + offset, _body_layer[0].GetTop() - width, _body_layer[0].GetLeft() + _body_layer[0].GetWidth() * scale_all - offset, _body_layer[0].GetTop());
		coll_UP.InflateRect(0, _body_layer[0].GetHeight() * scale_all, 0, 0);
		CRect coll_DOWN;
		coll_DOWN = CRect(_body_layer[0].GetLeft() + offset, _body_layer[0].GetTop() + _body_layer[0].GetHeight() * scale_all, _body_layer[0].GetLeft() + _body_layer[0].GetWidth() * scale_all - offset, _body_layer[0].GetTop() + _body_layer[0].GetHeight() * scale_all + width);
		coll_DOWN.InflateRect(0, 0, 0, _body_layer[0].GetHeight() * scale_all);
		CRect coll_LEFT;
		coll_LEFT = CRect(_body_layer[0].GetLeft() - width, _body_layer[0].GetTop() + offset, _body_layer[0].GetLeft(), _body_layer[0].GetTop() + _body_layer[0].GetHeight() * scale_all - offset);
		coll_LEFT.InflateRect(_body_layer[0].GetWidth() * scale_all, 0, 0, 0);
		CRect coll_RIGHT;
		coll_RIGHT = CRect(_body_layer[0].GetLeft() + _body_layer[0].GetHeight() * scale_all, _body_layer[0].GetTop() + offset, _body_layer[0].GetLeft() + _body_layer[0].GetWidth() * scale_all + width, _body_layer[0].GetTop() + _body_layer[0].GetHeight() * scale_all - offset);
		coll_RIGHT.InflateRect(0, 0, _body_layer[0].GetWidth() * scale_all, 0);
		CRect tester;
		vector<bool> re = { true,true, true, true };	//left up right bottom
		int counter = data.size();
		for (int i = 0; i < counter; i++)
		{
			if (re[0] == true && tester.IntersectRect(coll_LEFT, data[i]) != 0)	//collide something
				re[0] = false;
			if (re[1] == true && tester.IntersectRect(coll_UP, data[i]) != 0)	//collide something
				re[1] = false;
			if (re[2] == true && tester.IntersectRect(coll_RIGHT, data[i]) != 0)	//collide something
				re[2] = false;
			if (re[3] == true && tester.IntersectRect(coll_DOWN, data[i]) != 0)	//collide something
				re[3] = false;
		}
		return re;
	}
	
}