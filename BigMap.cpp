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

	//is function

	//behavior function
	void BigMap::reset_maps(int x, int y)
	{
		/*
		for (int i = 0; i < _maps.size(); i++)
			for (int j = 0; j < _maps[0].size(); j++)
				delete _maps[i][j];
		*/
		_maps.resize(y, vector<Map*>(x));
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				_maps[i][j] = new Map();
			}
		}
	}

	void BigMap::add_map(Map *data, int x, int y)
	{
		
		/*
		_maps[y][x].set_bitmap(data.get_graph().GetImageFilesName());
		_maps[y][x].set_pos(data.get_posX(), data.get_posY());
		_maps[y][x].add_colliders(data.get_colliders());
		_maps[y][x].add_triggers(data.get_triggers());
		_maps[y][x].add_monsters(data.get_monsters());
		*/
		//_maps[y][x] = data;
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

	void BigMap::jump_map(Map next, MAP_TRANSITION_TYPE)
	{

	}
	void BigMap::move_map(MAP_TRANSITION_TYPE)
	{

	}

	void BigMap::show_maps()
	{
		_corrent_map.show_bitmap(scale_all);
	}
	void BigMap::show_UI(int heart, int money, int bomb, CMovingBitmap itemA, CMovingBitmap itemB)
	{
		_UI.ShowBitmap(scale_all);
	}

	TRIGGER_TYPE BigMap::is_triggered(Character obj)
	{
		return _corrent_map.is_triggered(obj);
	}
}