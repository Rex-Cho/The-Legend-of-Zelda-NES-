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

#include "tektiteRed.h"

namespace game_framework {
	TektiteRed::TektiteRed() : Monster()
	{
		_attacking = false;
	}
	//set
	void TektiteRed::set_movement_animation(vector<string> filename)
	{
		this->_movement_animation_f.LoadBitmapByString({ filename[0], filename[1] }, RGB(255, 255, 255));
		this->_movement_animation_f.SetAnimation(300, false);
		this->_movement_animation_b.LoadBitmapByString({ filename[0], filename[1] }, RGB(255, 255, 255));
		this->_movement_animation_b.SetAnimation(300, false);
		this->_movement_animation_l.LoadBitmapByString({ filename[0], filename[1] }, RGB(255, 255, 255));
		this->_movement_animation_l.SetAnimation(300, false);
		this->_movement_animation_r.LoadBitmapByString({ filename[0], filename[1] }, RGB(255, 255, 255));
		this->_movement_animation_r.SetAnimation(300, false);
	}
	void TektiteRed::set_dead_animation(vector<string> filename)
	{

	}
	void TektiteRed::set_action_animation(vector<string> filename)
	{
		this->_action_animation_f.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
		this->_action_animation_b.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
		this->_action_animation_l.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
		this->_action_animation_r.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
	}
	void TektiteRed::set_hurt_animation(vector<string> filename)
	{
		this->_hurt_animation_f.LoadBitmapByString({ filename[0],filename[1] }, RGB(255, 255, 255));
		this->_hurt_animation_b.LoadBitmapByString({ filename[0],filename[1] }, RGB(255, 255, 255));
		this->_hurt_animation_l.LoadBitmapByString({ filename[0],filename[1] }, RGB(255, 255, 255));
		this->_hurt_animation_r.LoadBitmapByString({ filename[0],filename[1] }, RGB(255, 255, 255));

	}
	void TektiteRed::set_spawn_animation(vector<string> filename)
	{

	}
	//behavior
	void TektiteRed::attack()
	{

	}

	void TektiteRed::AI(clock_t time)
	{
		if (_attacking)		//move
		{
			move(time, _start_jump_time, _jump_dir);
			_start_stop_time = time;
			if (time > _start_jump_time + _jump_time)
			{
				_body_layer.clear();
				_body_layer.push_back(_movement_animation_f);
				_attacking = false;
			}
		}
		else				//stop
		{
			_start_jump_time = time;
			if (time > _start_stop_time + _stop_time)
			{
				_body_layer.clear();
				_body_layer.push_back(_action_animation_f);
				_attacking = true;
				_jump_dir = rand() % 6;		//0 Right Up, 1 Right, 2 Right Down, 3 Left down, 4 Left, 5 Left Up
			}
		}
	}

	void TektiteRed::move(clock_t t, clock_t start_jump_time, int dir)
	{
		if (_can_move == false)
			return;
		clock_t time = t - start_jump_time;
		if (time > _jump_time)
			return;
		int step = 2;
		int x = step;
		int y = step;
		switch (dir)
		{
		case 0:	//Right Up
			if (time > _jump_time)
				return;
			else if (time > _jump_time * 4 / 5)
			{
				x = step;
				y = step;
			}
			else
			{
				x = step;
				y = -step;
			}
			break;
		case 1:	//Right
			if (time > _jump_time)
				return;
			else if (time > _jump_time / 2)
			{
				x = step;
				y = step;
			}
			else
			{
				x = step;
				y = -step;
			}
			break;
		case 2:	//Right Down
			if (time > _jump_time)
				return;
			else if (time > _jump_time * 1 / 5)
			{
				x = step;
				y = step;
			}
			else
			{
				x = step;
				y = -step;
			}
			break;
		case 3:	//Left Down
			if (time > _jump_time)
				return;
			else if (time > _jump_time * 1 / 5)
			{
				x = -step;
				y = step;
			}
			else
			{
				x = -step;
				y = -step;
			}
			break;
		case 4:	//Left
			if (t > _jump_time)
				return;
			else if (t > _jump_time / 2)
			{
				x = -step;
				y = step;
			}
			else
			{
				x = -step;
				y = -step;
			}
			break;
		case 5:	//Left Up
			if (t > _jump_time)
				return;
			else if (t > _jump_time * 4 / 5)
			{
				x = -step;
				y = step;
			}
			else
			{
				x = -step;
				y = -step;
			}
			break;
		default:
			break;
		}
		int fx = _posX + x;
		int fy = _posY + y;
		if (fx > 255 - _body_layer[0].GetWidth() || fx < 1 || fy > 175 - _body_layer[0].GetHeight() || fy < 1)
			return;
		this->set_position(fx, fy);
	}

}