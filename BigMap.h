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
		/*
		BigMap() {
			_maps.clear();
			_maps.resize(8);
			for (int y = 0; y < 8; y++)
			{
				_maps[y].clear();
				_maps[y].resize(16);
			}
		};
		*/
		BigMap();
		~BigMap();

		//set function
		void set_UI_bitmap(vector<string>);

		//get function
		vector<vector<Map>> get_maps();
		vector<Map> get_extra_maps();
		int get_posX();
		int get_posY();

		//is function


		//behavior function
		void add_map(Map data,int x,int y);
		void add_maps_row(vector<Map>,int y);
		void add_maps_all(vector<vector<Map>>);
		void reset_maps();

		void add_extra_map(Map);
		void add_extra_maps(vector<Map>);

		void jump_map(Map next, MAP_TRANSITION_TYPE = SWITCH);
		void move_map(MAP_TRANSITION_TYPE);

		void show_maps();
		void show_UI(int heart,int money,int bomb, CMovingBitmap itemA, CMovingBitmap itemB);

	protected:
		//variables
		vector<vector<Map>> _maps;
		vector<Map> _extra_map;
		Map _corrent_map;
		CMovingBitmap _UI;
		int posX = 7;
		int posY = 7;
		int map_posX = 0;
		int map_posY = 80;
		int UI_posX = 0;
		int UI_posY = 0;

	private:
	};
}
#endif // !BIGMAP_H
