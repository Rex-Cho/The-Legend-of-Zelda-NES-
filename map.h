#pragma once
#ifndef MAP_H
#define MAP_H

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

using namespace std;

namespace game_framework {
	class Map {
	public:
		Map() {};
		~Map() = default;
	
		//set function
		void set_bitmap(vector<string>);

		//get function

		//behavior function
		void add_collider_by_point(vector<CPoint>);
		void add_collider_by_point(vector<CPoint>, int scale);
		void reset_collider();

		//is function
		bool is_collide(CMovingBitmap);
	
	protected:


		//variables

		CMovingBitmap _graph;
		CRgn _collider;

	private:

	};
}
#endif // !CREATURE_H
