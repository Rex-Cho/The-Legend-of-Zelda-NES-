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

#include"monster.h"

using namespace std;

namespace game_framework {
	class Map {
	public:
		//Map() { _collider.CreateRectRgn(0, 0, 0, 0); };
		Map() {};
		~Map();
	
		//set function
		void set_bitmap(vector<string>);
		void set_pos(int x, int y);
		void set_pos(int x, int y, int scale);

		//get function
		int get_posX();
		int get_posY();
		//CRgn get_collider();
		vector<CRect> get_colliders();

		//is function
		bool is_collide(Character);
		bool is_collide(CMovingBitmap);

		//behavior function
		//void add_collider_by_point(vector<CPoint>);
		//void add_collider_by_point(vector<CPoint>, int scale);
		void clear_collider();
		void show_bitmap();
		void show_bitmap(int);
		void add_colliders(vector<CRect>);
		void add_collider(CRect);

		void add_

	protected:


		//variables
		CMovingBitmap _graph;
		vector<CRect> _colliders;
		vector<Monster> _monsters;

	private:
		int posX = 0;
		int posY = 80;
	};
}
#endif // !CREATURE_H
