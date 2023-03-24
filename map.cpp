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

#include"map.h"

namespace game_framework {

	Map::~Map()
	{
		DeleteObject(_collider);
	}
	//set function
	void Map::set_bitmap(vector<string> files)
	{
		_graph.LoadBitmapByString(files, RGB(255,255,255));
	}
	void Map::set_pos(int x, int y)
	{
		posX = x;
		posY = y;
		_graph.SetTopLeft(posX, posY);
	}
	void Map::set_pos(int x, int y, int scale)
	{
		posX = x;
		posY = y;
		_graph.SetTopLeft(posX * scale, posY * scale);
	}

	//get function
	int Map::get_posX() { return posX; }
	int Map::get_posY() { return posY; }
	//CRgn Map::get_collider() { return _collider; }

	//behavior function
	void Map::add_collider_by_point(vector<CPoint> points)
	{
		/*
		CRgn add;
		VERIFY(add.CreatePolygonRgn(&points[0], points.size(), ALTERNATE)); //ALTERNATE = 1; WINDING = 2
		VERIFY(_collider.CombineRgn(&_collider, &add, RGN_OR));
		*/
		_collider.CreateRectRgn(0,0,1024,320);
	}
	void Map::add_collider_by_point(vector<CPoint> points, int scale)
	{
		CRgn add;
		int temp = points.size();
		for(int i = 0; i < temp; i++)
			points[i].SetPoint(points[i].x * scale, points[i].y * scale);

		VERIFY(add.CreatePolygonRgn(&points[0], points.size(), ALTERNATE));	//ALTERNATE = 1; WINDING = 2
		VERIFY(_collider.CombineRgn(&_collider, &add, RGN_OR));
	}
	void Map::reset_collider()
	{
		CRgn n;
		n.CreateRectRgn(0,0,0,0);
		_collider.CopyRgn(&n);
		DeleteObject(n);
	}
	void Map::show_bitmap()
	{
		_graph.ShowBitmap();
	}
	void Map::show_bitmap(int scale)
	{
		_graph.ShowBitmap(scale);
	}

	//is function
	bool Map::is_collide(Character obj)
	{
		CRect coll;
		coll = obj.get_layer()[0].get_location()[obj.get_layer()[0].GetFrameIndexOfBitmap()];
		coll.InflateRect(1,1,1,1);		//extend collider border by 1 pixel;

		if (_collider.RectInRegion(coll) == 0)//not collide
		{
			last_collider_direction = NONE;
			obj.set_ban_move(UP, false);
			obj.set_ban_move(DOWN, false);
			obj.set_ban_move(LEFT, false);
			obj.set_ban_move(RIGHT, false);
			return false;
		}
		if (last_collider_direction == NONE)
			last_collider_direction = obj.getFace();
		else
			obj.set_ban_move(last_collider_direction, true);
		return true;
		/*
		*/
	}
	bool Map::is_collide(CMovingBitmap obj)
	{
		if (_collider.RectInRegion(obj.get_location()[obj.GetFrameIndexOfBitmap()]) == 0)
			return false;
		return true;
	}
}