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

#include"trigger.h"

namespace game_framework {
	Trigger::Trigger() {}
	Trigger::Trigger(CRect d, Map m)
	{
		_area = d;
		_link_map = m;
	}
	Trigger::~Trigger(){}

	//set function
	void Trigger::set_trigger(CRect data)
	{
		_area = data;
	}
	void Trigger::set_link_map(Map data)
	{
		_link_map = data;
	}
	//get function
	CRect Trigger::get_trigger() { return _area; }
	Map Trigger::get_link_map() { return _link_map; }

	//is function
	bool Trigger::is_triggered(Character obj)
	{
		CRect coll;
		coll = obj.get_body_layer()[0].get_location()[obj.get_body_layer()[0].GetFrameIndexOfBitmap()];
		coll.InflateRect(1, 1, 1, 1);		//extend collider border by 1 pixel;
		CRect tester;
		return tester.IntersectRect(coll, _area) != 0;
	}
}