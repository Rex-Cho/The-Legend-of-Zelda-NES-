#include <StdAfx.h>
#include "map.h"
/*
#include "../Library/gamecore.h"
#include "../Library/gameutil.h"
*/


namespace game_framework {
	Map::Map()
	{
		_map_area = new short*[176];
		for (int a = 0; a < 176; a++)
		{
			_map_area[a] = new short[256];
		}
	}
	short** Map::get_collision()
	{
		return _map_area;
	}
	void Map::set_map(string filename)
	{
		this->_map.LoadBitmapByString({ filename });
		//this->_map.SetTopLeft(CGameState::scale, ( + CGameState::map_top_offset) * CGameState::scale);
		this->_map.SetTopLeft(0, 80*4);
	}
	CMovingBitmap Map::get_map()
	{
		return _map;
	}
}