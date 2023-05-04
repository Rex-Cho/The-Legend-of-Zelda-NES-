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
	TektiteRed::TektiteRed() 
	{

	}
	//set
	void TektiteRed::set_movement_animation(vector<string> filename)
	{
		this->_movement_animation_f.LoadBitmapByString({ filename[0]}, RGB(255, 255, 255));
		this->_movement_animation_b.LoadBitmapByString({ filename[0]}, RGB(255, 255, 255));
		this->_movement_animation_l.LoadBitmapByString({ filename[0]}, RGB(255, 255, 255));
		this->_movement_animation_r.LoadBitmapByString({ filename[0]}, RGB(255, 255, 255));
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

	}
	void TektiteRed::set_spawn_animation(vector<string> filename)
	{

	}
	//behavior
	void TektiteRed::attack()
	{

	}

	void TektiteRed::AI()
	{

	}

	void TektiteRed::move(clock_t ti, clock_t jump_time, int dir)
	{
		if (ti > jump_time)
			return;
		float scale_factor = 2000 / float(jump_time);
		float t = ti * scale_factor;
		int x = int(t);
		int y = 0;
		switch (dir)
		{
		case 0:	//Right Up
			if (t > 1400)
				return;
			y = int(-10 * (t - 1) * (t - 1) + 10);
			break;
		case 1:	//Right
			y = int(-10 * (t - 1) * (t - 1) + 10);
			if (y < 0)
				return;
			break;
		case 2:	//Right Down
			y = int(-10 * (t - 0.6) * (t - 0.6) + 10);
			if (y < 0)
				return;
			break;
		case 3:	//Left Down
			x = int(-t);
			y = int(-10 * (t - 0.6) * (t - 0.6) + 10);
			if (y < 0)
				return;
			break;
		case 4:	//Left
			x = int(-t);
			y = int(-10 * (t - 1) * (t - 1) + 10);
			if (y < 0)
				return;
			break;
		case 5:	//Left Up
			x = int(-t);
			if (t > 1400)
				return;
			y = int(-10 * (t - 1) * (t - 1) + 10);
			break;
		default:
			break;
		}
		this->set_position(x * 20,y * 2);
	}

}