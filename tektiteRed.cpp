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

	void TektiteRed::attack()
	{

	}

	void TektiteRed::AI()
	{

	}

	void TektiteRed::move(clock_t ti, int dir)
	{
		switch (dir)
		{
		case 0:	//Right Up
			//y = -10(x - 1)^2 + 10

			break;
		case 1:	//Right
			break;
		case 2:	//Right Down
			break;
		case 3:	//Left Down
			break;
		case 4:	//Left
			break;
		case 5:	//Left Up
			break;
		default:
			break;
		}
	}

}