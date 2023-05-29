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
	//link attack
	if (link.isAttacking() && link.get_can_action())
	{
		
		//attack animation
		clock_t attack_t = clock() - link.get_attack_time();		//clock_t == long
		if (attack_t > link.get_attack_speed())
		{
			link.attackDone();
			link.stop();
			if (move_keys.size() != 0)
				link.movement(move_keys[move_keys.size() - 1]);
		}
		else
		{
			link.set_wapon_position(attack_t);		//input time
			/*
			if (link.get_life() == link.get_max_life() && wapon_fly == nullptr)
			{
				wapon_fly = link.make_fly_wapon();
			}
			*/
		}
		//if life == max_health => fly sword
	}

	//link hurt
	vector<CRect> monsters_collider = {};
	vector<int> monsters_damage = {};
	int coll_counter = maps.get_maps()[maps.get_posY()][maps.get_posX()]->get_monsters().size();
	for (int i = 0; i < coll_counter; i++)
	{
		monsters_collider.push_back(CRect(
			maps.get_maps()[maps.get_posY()][maps.get_posX()]->get_monsters()[i]->get_body_layer()[0].GetLeft(),
			maps.get_maps()[maps.get_posY()][maps.get_posX()]->get_monsters()[i]->get_body_layer()[0].GetTop(),
			maps.get_maps()[maps.get_posY()][maps.get_posX()]->get_monsters()[i]->get_body_layer()[0].GetLeft() + maps.get_maps()[maps.get_posY()][maps.get_posX()]->get_monsters()[i]->get_body_layer()[0].GetWidth() * scale_all,
			maps.get_maps()[maps.get_posY()][maps.get_posX()]->get_monsters()[i]->get_body_layer()[0].GetTop() + maps.get_maps()[maps.get_posY()][maps.get_posX()]->get_monsters()[i]->get_body_layer()[0].GetHeight() * scale_all));
		monsters_damage.push_back(maps.get_maps()[maps.get_posY()][maps.get_posX()]->get_monsters()[i]->get_damage());
	}
	link.hurt(monsters_collider, monsters_damage);

	//link walk	
	link.isFrontCollide(maps.get_colliders());
	if(link.isWalk())
		link.walk();

	//monster movement AI
	maps.get_maps()[maps.get_posY()][maps.get_posX()]->monsters_AI(clock());

	//monster hurt
	vector<CRect> wapon_area = {};
	vector<int> damage_list = {};
	int counter = link.get_wapon_layer().size();
	for (int i = 0; i < counter; i++)
	{
		wapon_area.push_back(CRect(link.get_wapon_layer()[0].GetLeft(), link.get_wapon_layer()[0].GetTop(), link.get_wapon_layer()[0].GetLeft() + link.get_wapon_layer()[0].GetWidth() *scale_all, link.get_wapon_layer()[0].GetTop() + link.get_wapon_layer()[0].GetHeight() * scale_all));
		damage_list.push_back(link.get_damage());
	}
	maps.get_maps()[maps.get_posY()][maps.get_posX()]->monsters_hurt(wapon_area, damage_list);
	//monster die
	int point = maps.get_maps()[maps.get_posY()][maps.get_posX()]->monsters_die();
	link.add_money(point);

	//key and door
	if (maps.get_maps()[maps.get_posY()][maps.get_posX()]->eat_key(link))
	{
		link.add_key(1);
	}
	if (maps.get_maps()[maps.get_posY()][maps.get_posX()]->enter_door(link))
	{
		link.add_key(-1);
		to_next_level();
	}

	//map triggers to character
	switch (maps.is_triggered(link))
	{
	case TRIGGER_MAP_U:
		maps.change_map(maps.get_posY() - 1, maps.get_posX());
		link.set_position(link.get_posX(), 176 - 35);
		break;
	case TRIGGER_MAP_D:
		maps.change_map(maps.get_posY() + 1, maps.get_posX());
		link.set_position(link.get_posX(), 3);
		break;
	case TRIGGER_MAP_L:
		maps.change_map(maps.get_posY(), maps.get_posX() - 1);
		link.set_position(255 - 23, link.get_posY());
		break;
	case TRIGGER_MAP_R:
		maps.change_map(maps.get_posY(), maps.get_posX() + 1);
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


	//character die
	if (link.get_life() == 0)
	{
		exit(1);
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//music


	//input init
	move_keys.clear();


	//set UI
	maps.init_heart();
	maps.init_bomb_money_key();

	maps.set_UI_bitmap({ "resources/UI_background.bmp" });
	//set maps
	maps.reset_maps(16, 8);
	Map* adder = new Map();
	adder->set_graph({ "resources/Map/7_7.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(576,320, 1024, 636), CRect(0,0,1024,320) ,CRect(0,320,450,450),CRect(0,450,224, 500),CRect(0,500,160,560),CRect(0,560,96,640),CRect(0,700,120,1024),CRect(120,900,900,1024),CRect(900,700,1024,1024) });
	adder->add_triggers({ CRect(998,0,1005,1024) });	//Right
	adder->add_triggers({ CRect(0,0,5,1024) });			//Left
	adder->add_triggers({ CRect(0,320,1024,335) });		//Up
	maps.add_map(adder, 7, 7);


	adder = new Map();
	adder->set_graph({ "resources/Map/7_8.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320),CRect(0,320,120,520),CRect(0,520,60,636), CRect(0,700,60,1024),CRect(60,760,120,1024),CRect(120,900,1024,1024),
						CRect(131,587,180,632),CRect(132,716,177,761),CRect(260,587,305,632),CRect(260,716,305,761),
						CRect(130,330,180,430),CRect(258,330,318,430),CRect(258,330,318,430),CRect(386,330,446,430),CRect(578,330,638,430),CRect(706,330,766,430),CRect(834,330,894,430),CRect(962,330,1024,430),
						CRect(386,520,431,565),CRect(386,648,431,693),CRect(386,776,431,821),
						CRect(578,520,638,565),CRect(578,648,638,693),CRect(578,776,638,821),
						CRect(706,520,766,565),CRect(706,648,766,693),CRect(706,776,766,821),
						CRect(834,520,894,565),CRect(834,648,894,693),CRect(834,776,894,821),
						CRect(1023,320,1050,1024)});//w45 sw128
	adder->add_triggers({ CRect(0,320,1024,335) });		//Up
	adder->add_triggers({ CRect(0,0,5,1024) });			//Left
	maps.add_map(adder, 7, 8);
	maps.get_maps()[7][8]->add_monsters({ create_Leever() ,create_Leever(),create_TektiteRed() ,create_TektiteRed() });
	//maps.add_monsters({ create_monster(TEKTITE_RED),create_monster(TEKTITE_RED) ,create_monster(TEKTITE_RED) });

	adder = new Map();
	adder->set_graph({ "resources/Map/7_6.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320),CRect(0,320,764,440),CRect(896,320,1024,560),CRect(960,560,1024,636),CRect(960,704,1024,780),CRect(896,780,1024,1024),CRect(0,896,896,1024),
						CRect(514,520,574,565),CRect(514,648,574,693),CRect(514,776,574,821),
						CRect(642,584,702,629),CRect(642,712,702,757),
						CRect(322,648,382,693),CRect(130,648,190,693)});
	adder->add_triggers({ CRect(998,0,1005,1024) });	//Right
	adder->add_triggers({ CRect(0,320,1024,335) });		//Up
	maps.add_map(adder, 7, 6);
	maps.get_maps()[7][6]->add_monsters({ create_Leever(),create_Leever() ,create_Leever() });

	adder = new Map();
	adder->set_graph({ "resources/Map/6_6.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320),
						CRect(0,320,1024,450),CRect(896,450,1024,488),CRect(960,488,1024,550),
						CRect(0,900,764,1024),CRect(896,832,1024,1024),CRect(960,768,1024,832), 
						CRect(196,520,440,568),CRect(196,648,440,696),CRect(196,776,440,824),
						CRect(516,584,696,632),CRect(516,712,696,760) });
	adder->add_triggers({ CRect(998,0,1005,1024) });	//Right
	adder->add_triggers({ CRect(0,940,1024,1024) });	//Down
	maps.add_map(adder, 6, 6);

	adder = new Map();
	adder->set_graph({ "resources/Map/6_7.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320),
						CRect(0,320,1024,450),CRect(0,450,120,500),CRect(0,500,56,550),CRect(576,450,696,510),CRect(896,450,1024,510),CRect(960,510,1024,572),
						CRect(0,900,450,1024),CRect(0,836,120,900),CRect(0,772,56,836),
						CRect(576,896,1024,1024),CRect(576,836,696,896),CRect(896,832,1024,896),CRect(964,768,1024,832),
						CRect(200,520,248,568),CRect(200,648,248,696),CRect(200,776,248,824),
						CRect(328,520,376,568),CRect(328,648,376,696),CRect(328,776,376,824),
						CRect(776,520,824,568),CRect(776,648,824,696),CRect(776,776,824,824), });//w 48
	adder->add_triggers({ CRect(998,0,1005,1024) });	//Right
	adder->add_triggers({ CRect(0,0,5,1024) });			//Left
	adder->add_triggers({ CRect(0,940,1024,1024) });	//Down
	adder->add_door(700, 700);
	adder->add_key(400, 400);
	
	maps.add_map(adder, 6, 7);

	adder = new Map();
	adder->set_graph({ "resources/Map/6_8.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320),
						CRect(131,587,180,632),CRect(132,716,177,761),
						CRect(260,520,305,565),CRect(260,648,305,693),CRect(260,776,305,821),
						CRect(130,330,180,430),CRect(258,330,318,430),CRect(258,330,318,430),CRect(386,330,446,430),CRect(578,330,638,430),CRect(706,330,766,430),CRect(834,330,894,430),CRect(962,330,1024,570),
						CRect(386,648,431,693),
						CRect(578,520,638,565),CRect(578,648,638,693),CRect(578,776,638,821),
						CRect(706,648,766,693),
						CRect(834,520,894,565),CRect(834,648,894,693),CRect(834,776,894,821),
						CRect(130,900,178,1024),CRect(258,900,318,1024),CRect(386,900,434,1024),CRect(578,900,626,1024),CRect(706,900,754,1024),CRect(834,900,882,1024),CRect(964,776,1024,1024),
						CRect(0,836,120,1024),CRect(0,772,56,836),
						CRect(0,320,120,500),CRect(0,500,56,568),
						CRect(1020,320,1050,1024),CRect(0,310,1024,330) });//w45 sw128
	adder->add_triggers({ CRect(0,0,5,1024) });			//Left
	adder->add_triggers({ CRect(0,940,1024,1024) });	//Down
	maps.add_map(adder, 6, 8);

	

	/*
	*/
	//level 2 map set
	adder = new Map();
	adder->set_graph({ "resources/Map/2_9.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320)});
	adder->add_triggers({ CRect(998,0,1005,1024) });	//Right
	adder->add_triggers({ CRect(0,940,1024,1024) });	//Down
	maps.add_map(adder, 2, 9);

	adder = new Map();
	adder->set_graph({ "resources/Map/2_10.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320) });
	adder->add_triggers({ CRect(998,0,1005,1024) });	//Right
	adder->add_triggers({ CRect(0,0,5,1024) });			//Left
	adder->add_triggers({ CRect(0,940,1024,1024) });	//Down
	maps.add_map(adder, 2, 10);

	adder = new Map();
	adder->set_graph({ "resources/Map/2_11.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320) });
	adder->add_triggers({ CRect(998,0,1005,1024) });	//Right
	adder->add_triggers({ CRect(0,0,5,1024) });			//Left
	adder->add_triggers({ CRect(0,940,1024,1024) });	//Down
	maps.add_map(adder, 2, 11);

	adder = new Map();
	adder->set_graph({ "resources/Map/2_12.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320) });
	adder->add_triggers({ CRect(0,0,5,1024) });			//Left
	maps.add_map(adder, 2, 12);

	adder = new Map();
	adder->set_graph({ "resources/Map/3_10.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320) });
	adder->add_triggers({ CRect(998,0,1005,1024) });	//Right
	adder->add_triggers({ CRect(0,320,1024,335) });		//Up
	maps.add_map(adder, 3, 10);

	adder = new Map();
	adder->set_graph({ "resources/Map/3_11.bmp" });
	adder->set_pos(0, 80, scale_all);
	adder->add_colliders({ CRect(0,0,1024,320) });
	adder->add_triggers({ CRect(0,0,5,1024) });			//Left
	adder->add_triggers({ CRect(0,320,1024,335) });		//Up
	maps.add_map(adder, 3, 11);

	maps.change_map(7, 7);

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

	//monster

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
	case 0x58:	//X key
		//link.hurt(1);
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
	maps.show_monsters();
	maps.show_UI(link.get_max_life(), link.get_life(), link.get_money(), link.get_key(), link.get_bomb());


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

//custom function
void CGameStateRun::show_CRect() {
	CDC *pDC = CDDraw::GetBackCDC();
	
	//print map collider
	vector<CRect>  cur = maps.get_colliders();
	int counter = cur.size();
	for (int i = 0; i < counter; i++)
	{
		pDC->Draw3dRect(cur[i], RGB(0, 255, 0), RGB(0, 255, 0));
		//pDC->Rectangle(cur[i]);
	}
	//print map trigger
	vector<CRect> tri = maps.get_triggerss();
	counter = tri.size();
	for (int i = 0; i < counter; i++)
	{
		pDC->Draw3dRect(tri[i], RGB(255, 0, 0), RGB(255, 0, 0));
		//pDC->Rectangle(tri[i]);
	}

	//print character trigger
	//CRect cha = CRect(link.get_body_layer()[0].GetLeft(), link.get_body_layer()[0].GetTop(), link.get_body_layer()[0].GetLeft() + link.get_body_layer()[0].GetWidth() * scale_all, link.get_body_layer()[0].GetTop() + link.get_body_layer()[0].GetHeight()* scale_all);
	int width = 5;
	int offset = 5;
	int deflacteNUM = 5;
	CRect cha;
	switch (link.getFace())
	{
	case UP:
		cha = CRect(link.get_body_layer()[0].GetLeft() + offset, link.get_body_layer()[0].GetTop() - width, link.get_body_layer()[0].GetLeft() + link.get_body_layer()[0].GetWidth() * scale_all - offset, link.get_body_layer()[0].GetTop());
		cha.DeflateRect(deflacteNUM, 0, deflacteNUM, 0);
		break;
	case DOWN:
		cha = CRect(link.get_body_layer()[0].GetLeft() + offset, link.get_body_layer()[0].GetTop() + link.get_body_layer()[0].GetHeight() * scale_all, link.get_body_layer()[0].GetLeft() + link.get_body_layer()[0].GetWidth() * scale_all - offset, link.get_body_layer()[0].GetTop() + link.get_body_layer()[0].GetHeight() * scale_all + width);
		cha.DeflateRect(deflacteNUM, 0, deflacteNUM, 0);
		break;
	case LEFT:
		cha = CRect(link.get_body_layer()[0].GetLeft() - width, link.get_body_layer()[0].GetTop() + offset, link.get_body_layer()[0].GetLeft(), link.get_body_layer()[0].GetTop() + link.get_body_layer()[0].GetHeight() * scale_all - offset);
		cha.DeflateRect(0, deflacteNUM, 0, deflacteNUM);
		break;
	case RIGHT:
		cha = CRect(link.get_body_layer()[0].GetLeft() + link.get_body_layer()[0].GetHeight() * scale_all, link.get_body_layer()[0].GetTop() + offset, link.get_body_layer()[0].GetLeft() + link.get_body_layer()[0].GetWidth() * scale_all + width, link.get_body_layer()[0].GetTop() + link.get_body_layer()[0].GetHeight() * scale_all - offset);
		cha.DeflateRect(0, deflacteNUM, 0, deflacteNUM);
		break;
	case NONE:
		break;
	default:
		break;
	}
	pDC->Draw3dRect(cha, RGB(255, 0, 0), RGB(255, 0, 0));

	//print character collider
	CRect col = CRect(link.get_body_layer()[0].GetLeft(), link.get_body_layer()[0].GetTop(), link.get_body_layer()[0].GetLeft() + link.get_body_layer()[0].GetWidth() * scale_all, link.get_body_layer()[0].GetTop() + link.get_body_layer()[0].GetHeight()* scale_all);
	col.DeflateRect(10,10,10,10);
	pDC->Draw3dRect(col, RGB(0, 255, 0), RGB(0, 255, 0));

	//print character sword collider
	counter = link.get_wapon_layer().size();
	//vector<CRect> wap = {};
	for (int i = 0; i < counter; i++)
	{
		//.push_back(CRect(link.get_wapon_layer()[0].GetLeft(), link.get_wapon_layer()[0].GetTop(), link.get_wapon_layer()[0].GetLeft() + link.get_wapon_layer()[0].GetWidth(), link.get_wapon_layer()[0].GetTop() + link.get_wapon_layer()[0].GetHeight()));
		CRect temp = CRect(link.get_wapon_layer()[0].GetLeft(), link.get_wapon_layer()[0].GetTop(), link.get_wapon_layer()[0].GetLeft() + link.get_wapon_layer()[0].GetWidth() *scale_all, link.get_wapon_layer()[0].GetTop() + link.get_wapon_layer()[0].GetHeight() * scale_all);
		pDC->Draw3dRect(temp, RGB(0, 255, 0), RGB(0, 255, 0));
	}
	/*
	*/

	CDDraw::ReleaseBackCDC();
}

void CGameStateRun::to_next_level()
{
	link.set_position(128, 48);
	link.heal(20);
	maps.change_map(2, 10);
}

Monster* CGameStateRun::create_TektiteRed()
{
	//TektiteRed mon;
	Monster* mon = new TektiteRed();
	mon->set_movement_animation({ "resources/enemies/tektite_r1.bmp", "resources/enemies/tektite_r2.bmp" });
	mon->set_action_animation({ "resources/enemies/tektite_r2.bmp" });
	mon->set_hurt_animation({ "resources/enemies/tektite_r1.bmp","resources/enemies/all_white.bmp" });
	//mon.set_dead_animation({});
	//mon.set_spawn_animation({});
	vector<CRect> temp = maps.get_maps()[maps.get_posY()][maps.get_posX()]->get_colliders();
	mon->spawn(temp);
	return mon;
}

Monster* CGameStateRun::create_Leever()
{
	//TektiteRed mon;
	Monster* mon = new Leever();
	mon->set_movement_animation({ "resources/enemies/leever2_b.bmp", "resources/enemies/leever3_b.bmp" });
	mon->set_action_animation({ "resources/enemies/leever3_b.bmp" });
	mon->set_hurt_animation({ "resources/enemies/leever1_b.bmp","resources/enemies/all_white.bmp" });
	//mon.set_dead_animation({});
	//mon.set_spawn_animation({});
	vector<CRect> temp = maps.get_maps()[maps.get_posY()][maps.get_posX()]->get_colliders();
	mon->spawn(temp);
	return mon;
}
