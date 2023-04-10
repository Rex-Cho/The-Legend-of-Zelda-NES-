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
		//DeleteObject(_collider);
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
	vector<CRect> Map::get_colliders() { return _colliders; };
	vector<Trigger_s> Map::get_triggers() { return _triggers; };
	//CRgn Map::get_collider() { return _collider; }

	//behavior function
	/*
	void Map::add_collider_by_point(vector<CPoint> points)
	{
		//CRgn add;
		//VERIFY(add.CreatePolygonRgn(&points[0], points.size(), ALTERNATE)); //ALTERNATE = 1; WINDING = 2
		//VERIFY(_collider.CombineRgn(&_collider, &add, RGN_OR));
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
	*/
	void Map::add_colliders(vector<CRect> data)
	{
		int counter = data.size();
		for (int i = 0; i < counter; i++)
			_colliders.push_back(data[i]);
	}
	void Map::clear_collider()
	{
		/*
		CRgn n;
		n.CreateRectRgn(0,0,0,0);
		_collider.CopyRgn(&n);
		DeleteObject(n);
		*/
		_colliders.clear();
	}

	void Map::add_triggers(vector<Trigger_s> data)
	{
		int counter = data.size();
		for (int i = 0; i < counter; i++)
			_triggers.push_back(data[i]);
	}
	void Map::clear_triggers()
	{
		_triggers.clear();
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
		coll = obj.get_body_layer()[0].get_location()[obj.get_body_layer()[0].GetFrameIndexOfBitmap()];
		coll.InflateRect(1,1,1,1);		//extend collider border by 1 pixel;
		CRect tester;
		int counter = _colliders.size();
		for (int i = 0; i < counter; i++)
		{
			if (tester.IntersectRect(coll, _colliders[i]) != 0)
				return true;
		}
		return false;
	}
	bool Map::is_collide(CMovingBitmap obj)
	{
		CRect tester;
		int counter = _colliders.size();
		for (int i = 0; i < counter; i++)
		{
			if (tester.IntersectRect(obj.get_location()[obj.GetFrameIndexOfBitmap()], _colliders[i]) != 0)
				return true;
		}
		return false;
	}

	Map Map::is_trigger(Character obj)
	{
		/*
		CRect coll;
		coll = obj.get_body_layer()[0].get_location()[obj.get_body_layer()[0].GetFrameIndexOfBitmap()];
		coll.InflateRect(1, 1, 1, 1);		//extend collider border by 1 pixel;
		CRect tester;
		int counter = _triggers.size();
		for (int i = 0; i < counter; i++)
		{
			if (tester.IntersectRect(coll, _triggers[i].trigger_area) != 0)
				return _triggers[i].link_map;
		}
		*/
		return Map();
	}
	Map Map::is_trigger(CMovingBitmap obj)
	{
		/*
		CRect tester;
		int counter = _triggers.size();
		for (int i = 0; i < counter; i++)
		{
			if (tester.IntersectRect(obj.get_location()[obj.GetFrameIndexOfBitmap()], _triggers[i].trigger_area) != 0)
			{
				return _triggers[i].link_map;
			}
		}
		*/
		return Map();
	}
}