#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

//#include "../../Source/Library/gameutil.h"


using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	/*
	if(character.isWalk())
	{
		switch(character.getFace())
		{
		case UP:
		case DOWN:
		case LEFT:
		case RIGHT:
		default:
		}
	}
	*/
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//collision area read
	//fopen("../../resources/collision_area.bmp", "r");

	/*
	*/
	mmap.LoadBitmapByString({ "resources/Map/7_7.bmp" }, RGB(255, 255, 255));
	mmap.SetTopLeft(scale_all,scale_all + map_top_offset * scale_all);
	ui_bg.LoadBitmapByString({ "resources/UI_background.bmp" });
	ui_bg.SetTopLeft(0,0);
	Sleep(200);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_UP:
		//character.movement(UP);
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
	default:

	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
		//character.stop();
	default:

	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	//smap.get_map().ShowBitmap();
	mmap.ShowBitmap(scale_all);
	ui_bg.ShowBitmap(scale_all);
}
