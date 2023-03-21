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

	//set function
	void Map::set_bitmap(vector<string> files)
	{
		_graph.LoadBitmapByString(files, RGB(255,255,255));
	}

	//get function

	//behavior function
	void Map::add_collider_by_point(vector<CPoint> points)
	{
		CRgn add;
		add.CreatePolygonRgn(&points[0], points.size(), ALTERNATE);	//ALTERNATE = 1; WINDING = 2
		_collider.CombineRgn(&_collider, &add, RGN_OR);
	}
	void Map::add_collider_by_point(vector<CPoint> points, int scale)
	{
		CRgn add;
		for(int i = 0; i < points.size(); i++)
			points[i].SetPoint(points[i].x * scale, points[i].y * scale);

		add.CreatePolygonRgn(&points[0], points.size(), ALTERNATE);	//ALTERNATE = 1; WINDING = 2
		_collider.CombineRgn(&_collider, &add, RGN_OR);
	}

	void Map::reset_collider()
	{
		_collider.CopyRgn(new CRgn);
	}

	//is function
	bool Map::is_collide(CMovingBitmap obj)
	{
		return _collider.RectInRegion(obj.get_location()[obj.GetFrameIndexOfBitmap()]);
	}
}