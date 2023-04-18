#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

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
	if (link.isAttacking() && link.get_can_action())
	{
		
		//attack animation
		clock_t attack_t = clock() - link.get_attack_time();		//clock_t == long
		if (attack_t > link.get_attack_duration())
		{
			link.attackDone();
			link.stop();
			if (move_keys.size() != 0)
				link.movement(move_keys[move_keys.size() - 1]);
		}
		else
		{
			link.set_wapon_position(attack_t);		//input time
			if (link.getLife() == link.get_max_life() && wapon_fly == nullptr)
			{
				wapon_fly = link.make_fly_wapon();
			}
		}

		//if life == max_health => fly sword
	}
	if (wapon_fly != nullptr)
	{
		int x = 0;
		int y = 0;
		switch (link.getFace())
		{
		case UP:
			break;
		case DOWN:
			break;
		case LEFT:
			break;
		case RIGHT:
			break;
		case NONE:
			break;
		default:
			break;
		}
		/*
		for (int i = 0; i < map.monsters.size(); i++)
		{
			if (CMovingBitmap::IsOverlap(*wapon_fly, map.monsters()[i]))
			{
				//delete wapon_fly and wapon_fly = nullptr;
			}
		}
		*/
	}
	//link walk	
	link.isFrontCollide(maps.get_colliders());
	if(link.isWalk())
		link.walk();

	//if(CMovingBitmap::IsOverlap(*wapon_fly, ))

	//map triggers
	switch (maps.is_triggered(link))
	{
	case TRIGGER_MAP_U:
		maps.change_map(maps.get_posX(),maps.get_posY() - 1);
		link.set_position(link.get_posX(), 176 - 35);
		break;
	case TRIGGER_MAP_D:
		maps.change_map(maps.get_posX(),maps.get_posY() + 1);
		link.set_position(link.get_posX(), 1 + map_top_offset + 5);
		break;
	case TRIGGER_MAP_L:
		maps.change_map(maps.get_posX() - 1,maps.get_posY());
		link.set_position(255 - 16, link.get_posY());
		break;
	case TRIGGER_MAP_R:
		maps.change_map(maps.get_posX() + 1,maps.get_posY());
		link.set_position(1, link.get_posY());
		break;
	case TRIGGER_MAP_C:
		//maps.change_map(maps.get_extra_maps[0]);
		break;
	case TRIGGER_NONE:
		break;
	default:
		break;
	};


	//map and link collide detect
	/*
	*/
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//item

	//input init
	move_keys.clear();


	//set UI
	maps.set_UI_bitmap({ "resources/UI_background.bmp" });
	//set maps
	maps.reset_maps(16, 8);
	Map* adder = new Map();
	adder->set_graph({ "resources/Map/7_7.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({CRect(576,320, 1024, 636), CRect(0,0,1024,320) });
	/*
	adder->add_triggers({ CRect(1023,0,1024,1024) });	//Right
	adder->add_triggers({ CRect(0,0,1,1024) });			//Left
	adder->add_triggers({ CRect(0,320,1024,321) });		//Up
	*/
	maps.add_map(adder, 7, 7);

	adder = new Map();
	adder->set_graph({ "resources/Map/7_8.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320) });
	adder->add_triggers({ CRect(0,0,1,1024) });			//Left
	maps.add_map(adder, 7, 8);

	adder = new Map();
	adder->set_graph({ "resources/Map/7_6.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320) });
	adder->add_triggers({ CRect(1023,0,1024,1024) });	//Right
	maps.add_map(adder, 7, 6);

	adder = new Map();
	adder->set_graph({ "resources/Map/6_7.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320) });
	adder->add_triggers({ CRect(0,1023,1024,1024) });	//Down
	maps.add_map(adder, 6, 7);

	adder = new Map();
	adder->set_graph({ "resources/Map/6_8.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320) });
	adder->add_triggers({ CRect(0,0,1,1024) });			//Left
	adder->add_triggers({ CRect(0,1023,1024,1024) });	//Down
	maps.add_map(adder, 6, 8);

	//set character
	link.set_movement_animation({"resources/Link/link_run_f1.bmp", "resources/Link/link_run_f2.bmp", "resources/Link/link_run_b1.bmp", "resources/Link/link_run_b2.bmp","resources/Link/link_run_l1.bmp","resources/Link/link_run_l2.bmp","resources/Link/link_run_r1.bmp","resources/Link/link_run_r2.bmp"});
	link.set_action_animation({"resources/Link/link_act_f.bmp", "resources/Link/link_act_f.bmp","resources/Link/link_run_f2.bmp","resources/Link/link_run_f1.bmp",
		"resources/Link/link_act_b.bmp","resources/Link/link_act_b.bmp","resources/Link/link_run_b2.bmp","resources/Link/link_run_b1.bmp",
		"resources/Link/link_act_l.bmp","resources/Link/link_act_l.bmp","resources/Link/link_run_l2.bmp","resources/Link/link_run_l1.bmp",
		"resources/Link/link_act_r.bmp","resources/Link/link_act_r.bmp","resources/Link/link_run_r2.bmp","resources/Link/link_run_r1.bmp" });
	link.set_hurt_animation({ "resources/Link/link_run_f1.bmp" ,"resources/Link/link_hurt.bmp","resources/Link/link_run_b1.bmp" ,"resources/Link/link_hurt.bmp","resources/Link/link_run_l1.bmp" ,"resources/Link/link_hurt.bmp","resources/Link/link_run_r1.bmp" ,"resources/Link/link_hurt.bmp" });
	link.set_dead_animation({});
	link.set_spawn_animation({});
	link.set_wapon({"resources/items/wood_sword_f.bmp","resources/items/wood_sword_b.bmp", "resources/items/wood_sword_l.bmp", "resources/items/wood_sword_r.bmp"});
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
		move_keys.push_back(UP);
		break;
	case VK_DOWN:
		link.movement(DOWN);
		move_keys.push_back(DOWN);
		break;
	case VK_LEFT:
		link.movement(LEFT);
		move_keys.push_back(LEFT);
		break;
	case VK_RIGHT:
		link.movement(RIGHT);
		move_keys.push_back(RIGHT);
		break;
	case 0x5A:	//Z key
		link.attack();
		break;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int counter = move_keys.size();
	MOVEMENT_DIR move_key;
	switch (nChar)
	{
	case VK_UP:
		move_key = UP;
		break;
	case VK_DOWN:
		move_key = DOWN;
		break;
	case VK_LEFT:
		move_key = LEFT;
		break;
	case VK_RIGHT:
		move_key = RIGHT;
		break;
	}
	for (int i = 0; i < counter; i++)
	{
		if (move_keys[i] == move_key)
		{
			move_keys.erase(move_keys.begin() + i);
			break;
		}
	}
	if(move_keys.size() == 0)
		link.stop();
	else
		link.movement(move_keys[move_keys.size() - 1]);
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
	maps.show_maps();
	maps.show_UI();

	link.showLayers(scale_all);
	show_CRect();
}

void show_text(int posX, int posY)
{
	/*
	CDC *pDC = CDDraw::GetBackCDC();
	//CFont *fp;

	CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(0, 0, 0), 800);
	CTextDraw::Print(pDC, 237, 128, "link._posX=" + std::to_string(posX));
	CTextDraw::Print(pDC, 237, 178, "link._posX=" + std::to_string(posY));

	CDDraw::ReleaseBackCDC();
	*/
}

void CGameStateRun::show_CRect() {
	CDC *pDC = CDDraw::GetBackCDC();
	
	vector<CRect>  cur = maps.get_colliders();
	int counter = cur.size();
	for (int i = 0; i < counter; i++)
	{
		pDC->Draw3dRect(cur[i], RGB(0, 255, 0), RGB(0, 255, 0));
		//pDC->Rectangle(cur[i]);
	}
	//CRect cha = link.get_body_layer()[0].get_location()[0];
	CRect cha = CRect(link.get_body_layer()[0].GetLeft(), link.get_body_layer()[0].GetTop(), link.get_body_layer()[0].GetLeft() + link.get_body_layer()[0].GetWidth() * scale_all, link.get_body_layer()[0].GetTop() + link.get_body_layer()[0].GetHeight()* scale_all);
	pDC->Draw3dRect(cha, RGB(0, 255, 0), RGB(0, 255, 0));
	CDDraw::ReleaseBackCDC();
}