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
		//_bomb_bitmap.LoadBitmapByString({});
		//_key_bitmap.LoadBitmapByString({});
	}
	BigMap::~BigMap() 
	{
		int counterY = _maps.size();
		int counterX = _maps[0].size();
		for (int i = 0; i < counterY; i++)
			for(int j = 0; j < counterX; j++)
				delete _maps[i][j];
	}

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
		for (int i = 0; i < counter; i++)
			_extra_map.push_back(data[i]);
	}

	void BigMap::change_map(int y, int x)
	{
		int counterY = _maps.size();
		if (counterY == 0)
			return;
		int counterX = _maps[0].size();
		if (y > counterY || y < 0 || x > counterX || x < 0)
			return;
		if (_maps[y][x]->get_colliders().size() == 0)
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
	void BigMap::show_UI(int max_h, int heart, int money, int bomb, CMovingBitmap itemA, CMovingBitmap itemB)
	{
		_UI.ShowBitmap(scale_all);
		show_heart(max_h, heart);
	}
	void BigMap::show_heart(int m, int now)
	{
		if (now < 0)
			now = 0;
		int full = now / 2;
		int max = m / 2;
		int counter = _heart_bitmap.size();
		for (int i = 0; i < counter; i++)
		{
			if (i < full)
			{
				_heart_bitmap[i].SetFrameIndexOfBitmap(0);
				_heart_bitmap[i].ShowBitmap(scale_all);
			}
			else if (i == full && now % 2 == 1)
			{
				_heart_bitmap[i].SetFrameIndexOfBitmap(1);
				_heart_bitmap[i].ShowBitmap(scale_all);
			}
			else if (i < max)
			{
				_heart_bitmap[i].SetFrameIndexOfBitmap(2);
				_heart_bitmap[i].ShowBitmap(scale_all);
			}
			else
			{
				_heart_bitmap[i].SetFrameIndexOfBitmap(3);
				_heart_bitmap[i].ShowBitmap(scale_all);
			}
		}
	}
	void BigMap::init_heart()
	{
		int max_heart = 16;
		int left = 176;
		int top = 44;
		int width = 8;
		int height = 8;
		_heart_bitmap.clear();
		for (int i = 0; i < max_heart; i++)
		{
			int offsetX = (i % (max_heart / 2)) * width;
			int offsetY = height;
			if (i > 7)
				offsetY = 0;
			CMovingBitmap adder;
			adder.LoadBitmapByString({ "resources/items/heart_full.bmp","resources/items/heart_half.bmp" ,"resources/items/heart_none.bmp","resources/items/8x8_none.bmp" }, RGB(255, 255, 255));
			adder.SetTopLeft((left + offsetX)*scale_all, (top + offsetY)*scale_all);
			_heart_bitmap.push_back(adder);
		}
	}

	TRIGGER_TYPE BigMap::is_triggered(Character obj)
	{
		_corrent_map = _maps[_posY][_posX];
		return _corrent_map->is_triggered(obj);
	}

	//monsters
	void BigMap::add_monsters(vector<Monster*> monsters)
	{
		_corrent_map->add_monsters(monsters);
	}
	void BigMap::show_monsters()
	{
		_corrent_map->show_monsters();
	}
	void BigMap::monsters_AI(clock_t t)
	{
		_corrent_map->monsters_AI(t);
	}
}