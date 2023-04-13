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

#include "BigMap.h"

namespace game_framework {
	BigMap::BigMap()
	{

	}
	BigMap::~BigMap() {}
	
	//set function
	void BigMap::set_UI_bitmap(vector<string> data)
	{
		_UI.LoadBitmapByString(data);
		_UI.SetTopLeft(_UI_posX, _UI_posY);
	}

	//get function
	vector<vector<Map*>> BigMap::get_maps() { return _maps; }
	vector<Map> BigMap::get_extra_maps() { return _extra_map; }
	int BigMap::get_posX() { return _posX; }
	int BigMap::get_posY() { return _posY; }
	vector<CRect> BigMap::get_colliders() { return _corrent_map->get_colliders(); }
	vector<CRect> BigMap::get_triggerss() { return _corrent_map->get_triggers(); }

	//is function

	//behavior function
	void BigMap::reset_maps(int x, int y)
	{
		/*
		*/
		int counterY = _maps.size();
		if (counterY != 0)
		{
			int counterX = _maps[0].size();
			for (int i = 0; i < counterY; i++)
				for (int j = 0; j < counterX; j++)
					delete _maps[i][j];
		}
		_maps.resize(y, vector<Map*>(x));
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				_maps[i][j] = new Map();
			}
		}
	}

	void BigMap::add_map(Map *data, int y, int x)
	{
		_maps[y][x] = data;
	}
	void BigMap::add_maps_row(vector<Map*> data, int y)
	{
		_maps[y] = data;
	}
	void BigMap::add_maps_all(vector<vector<Map*>> data)
	{
		_maps = data;
	}

	void BigMap::add_extra_map(Map data)
	{
		_extra_map.push_back(data);
	}
	void BigMap::add_extra_maps(vector<Map> data)
	{
		int counter = data.size();
		for(int i= 0 ; i < counter; i++)
			_extra_map.push_back(data[i]);
	}

	void BigMap::change_map(int x,int y)
	{
		int counterY = _maps.size();
		if (counterY == 0)
			return;
		int counterX = _maps[0].size();
		if (y > counterY || y < 0 || x > counterX || x < 0)
			return;
		_posX = x;
		_posY = y;
		_corrent_map = _maps[_posY][_posX];
	}
	void BigMap::change_map(Map*)
	{

	}

	void BigMap::show_maps()
	{
		_corrent_map = _maps[_posY][_posX];
		_corrent_map->show_bitmap(scale_all);
	}
	void BigMap::show_UI(int heart, int money, int bomb, CMovingBitmap itemA, CMovingBitmap itemB)
	{
		_UI.ShowBitmap(scale_all);
	}

	TRIGGER_TYPE BigMap::is_triggered(Character obj)
	{
		_corrent_map = _maps[_posY][_posX];
		return _corrent_map->is_triggered(obj);
	}
}