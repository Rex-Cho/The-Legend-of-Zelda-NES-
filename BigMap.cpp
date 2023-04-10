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
		_maps.clear();
		_maps.resize(8);
		for (int y = 0; y < 8; y++)
		{
			_maps[y].clear();
			_maps[y].resize(16);
		}
	}
	BigMap::~BigMap() {}
	
	//set function

	//get function

	//is function

	//behavior function
	void BigMap::reset_maps()
	{
		_maps.clear();
		_maps.resize(8);
		for (int y = 0; y < 8; y++)
		{
			_maps[y].clear();
			_maps[y].resize(16);
		}
	}
}