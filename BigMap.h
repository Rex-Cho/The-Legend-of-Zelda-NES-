#pragma once
#ifndef BIGMAP_H
#define BIGMAP_H

#include <list>
#include <vector>
#include <map>
#include <time.h>
#include <afxwin.h>
#include"windef.h"
#include"wingdi.h"
#include"atltypes.h"
#include"time.h"
#include"afxwin.h"
#include".\Source.\Library\gameutil.h"

#include"map.h"

using namespace std;

namespace game_framework {
	enum MAP_TRANSITION_TYPE {
		R2L,
		L2R,
		U2D,
		D2U,
		SWITCH
	};

	class BigMap {
	public:
		BigMap();
		~BigMap();

		//set function
		void set_UI_bitmap(vector<string>);

		//get function
		vector<vector<Map*>> get_maps();
		vector<Map> get_extra_maps();
		int get_posX();
		int get_posY();
		vector<CRect> get_colliders();
		vector<CRect> get_triggerss();

		//is function


		//behavior function
		void add_map(Map *data,int y,int x);
		void add_maps_row(vector<Map*>,int y);
		void add_maps_all(vector<vector<Map*>>);
		void reset_maps(int x,int y);

		void add_extra_map(Map);
		void add_extra_maps(vector<Map>);

		void change_map(int x,int y);
		void change_map(Map*);

		TRIGGER_TYPE is_triggered(Character);

		void show_maps();
		void show_UI(int max_h = 0, int heart = 0, int money = 0, int bomb = 0, CMovingBitmap itemA = CMovingBitmap(), CMovingBitmap itemB = CMovingBitmap());

		void init_heart();

		//monsters
		void add_monsters(vector<Monster>);
		void show_monsters();
		void monsters_AI(clock_t);

	protected:
		//variables
		vector<vector<Map*>> _maps;
		vector<Map> _extra_map;
		Map* _corrent_map;
		CMovingBitmap _UI;
		int _posX = 7;
		int _posY = 7;
		int _map_posX = 0;
		int _map_posY = 80;
		int _UI_posX = 0;
		int _UI_posY = 0;

	private:
		CMovingBitmap _bomb_bitmap;
		CMovingBitmap _key_bitmap;
		vector<CMovingBitmap> _heart_bitmap;
		void show_heart(int max,int current);
		void show_money(int);
		void show_bomb(int);
		void show_key(int);
	};
}
#endif // !BIGMAP_H
