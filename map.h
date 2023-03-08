#pragma once
using namespace std;
/*
#include "../Library/gamecore.h"
*/
#include "../Library/gameutil.h"


namespace game_framework {
	class Map {
	public:
		Map();
		short** get_collision();
		void set_map(string);
		CMovingBitmap get_map();
	protected:
	private:
		//short _map_area[176][256] = {0}; // 0 -> walkable ; 1 -> can't walk ; 2 -> entry area ; 3 -> special
		short** _map_area;
		CMovingBitmap _map;
		//int position_x, position_y;
	};

}