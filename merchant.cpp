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

#include "merchant.h"

namespace game_framework {
	Merchant::Merchant() : Monster()
	{
		_attacking = false;
		_max_life = 20;
		_life = _max_life;
	}
	//get
	int Merchant::get_key_cost() { return _key_cost; }

	//set
	void Merchant::set_movement_animation(vector<string> filename)
	{
		this->_movement_animation_f.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
		this->_movement_animation_b.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
		this->_movement_animation_l.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
		this->_movement_animation_r.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
	}
	void Merchant::set_dead_animation(vector<string> filename)
	{

	}
	void Merchant::set_action_animation(vector<string> filename)
	{
		this->_action_animation_f.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
		this->_action_animation_b.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
		this->_action_animation_l.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
		this->_action_animation_r.LoadBitmapByString({ filename[0] }, RGB(255, 255, 255));
	}
	void Merchant::set_hurt_animation(vector<string> filename)
	{
		this->_hurt_animation_f.LoadBitmapByString({ filename[0],filename[1] }, RGB(255, 255, 255));
		this->_hurt_animation_b.LoadBitmapByString({ filename[0],filename[1] }, RGB(255, 255, 255));
		this->_hurt_animation_l.LoadBitmapByString({ filename[0],filename[1] }, RGB(255, 255, 255));
		this->_hurt_animation_r.LoadBitmapByString({ filename[0],filename[1] }, RGB(255, 255, 255));

	}
	void Merchant::set_spawn_animation(vector<string> filename)
	{

	}
	//behavior
	void Merchant::attack()
	{

	}

	void Merchant::AI(clock_t time)
	{
		_key_cost = _key_base_cost + (_max_life - _life);
		if (_can_move)
		{
			_body_layer.push_back(_movement_animation_f);
		}
	}
}