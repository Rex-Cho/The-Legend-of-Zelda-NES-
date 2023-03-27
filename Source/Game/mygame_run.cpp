#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

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
	//Timer
	/*
	//hurt
	if (clock() - link.get_hurt_time() > link.get_hurt_duration())
		link.set_can_move(true);
	//attack
	
	*/
	if (link.isAttacking())
	{
		//attack animation
		//if life == max_health => fly sword
		if (clock() - link.get_attack_time() > link.get_attack_duration())
		{
			link.attackDone();
		}
	}

	link.isFrontCollide(m_map.get_colliders());
	if(link.isWalk())
		link.walk();

	//map and link collide detect
	/*
	*/
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//item

	//set map
	m_map.set_bitmap({ "resources/Map/7_7.bmp" });
	m_map.set_pos(0, 80, scale_all);
	m_map.add_colliders({ CRect(0,0,1024,320) });
	//m_map.add_collider_by_point({ CPoint(144,0),CPoint(144,75) ,CPoint(157,75),CPoint(157,80),CPoint(256,0) }, scale_all);
	
	/*
	CDC *pDC = CDDraw::GetBackCDC();
	pDC->FillRgn(&m_map._collider, &CBrush(0xFF00));
	mmap.LoadBitmapByString({ "resources/Map/7_7.bmp" }, RGB(255, 255, 255));
	mmap.SetTopLeft(scale_all, scale_all + map_top_offset * scale_all);
	*/
	ui_bg.LoadBitmapByString({ "resources/UI_background.bmp" });
	ui_bg.SetTopLeft(0, 0);

	//set character
	link.set_movement_animation({"resources/Link/link_run_f1.bmp", "resources/Link/link_run_f2.bmp", "resources/Link/link_run_b1.bmp", "resources/Link/link_run_b2.bmp","resources/Link/link_run_l1.bmp","resources/Link/link_run_l2.bmp","resources/Link/link_run_r1.bmp","resources/Link/link_run_r2.bmp"});
	link.set_action_animation({"resources/Link/link_act_f.bmp", "resources/Link/link_act_b.bmp", "resources/Link/link_act_l.bmp","resources/Link/link_act_r.bmp" });
	link.set_hurt_animation({ "resources/Link/link_run_f1.bmp" ,"resources/Link/link_hurt.bmp","resources/Link/link_run_b1.bmp" ,"resources/Link/link_hurt.bmp","resources/Link/link_run_l1.bmp" ,"resources/Link/link_hurt.bmp","resources/Link/link_run_r1.bmp" ,"resources/Link/link_hurt.bmp" });
	link.set_dead_animation({});
	link.set_spawn_animation({});
	link.set_position(128,48);
	link.stop();

	Sleep(200);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_UP:
		link.movement(UP);
		key_down_count += 1;
		break;
	case VK_DOWN:
		link.movement(DOWN);
		key_down_count += 1;
		break;
	case VK_LEFT:
		link.movement(LEFT);
		key_down_count += 1;
		break;
	case VK_RIGHT:
		link.movement(RIGHT);
		key_down_count += 1;
		break;
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
		key_down_count -= 1;
		if(key_down_count == 0)
			link.stop();
		break;
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
	//mmap.ShowBitmap(scale_all);
	m_map.show_bitmap(scale_all);
	ui_bg.ShowBitmap(scale_all);
	link.showLayers(scale_all);
}
