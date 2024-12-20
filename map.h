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
#include"merchant.h"

using namespace std;

namespace game_framework {
	enum TRIGGER_TYPE {
		TRIGGER_MAP_R,
		TRIGGER_MAP_L,
		TRIGGER_MAP_U,
		TRIGGER_MAP_D,
		TRIGGER_MAP_C,
		TRIGGER_NONE,
	};
	enum ITEM_TYPE {
		FIRE,
		BOMB
	};
	struct Secrets_s {
		CMovingBitmap ori;
		CMovingBitmap trans;
		ITEM_TYPE trigger;
	};

	class Map {
	public:
		//Map() { _collider.CreateRectRgn(0, 0, 0, 0); };
		Map();
		~Map();
	
		//set function
		void set_graph(vector<string>);
		void set_pos(int x, int y);
		void set_pos(int x, int y, int scale);

		//get function
		int get_posX();
		int get_posY();
		//CRgn get_collider();
		vector<CRect> get_colliders();
		vector<CRect> get_triggers();
		vector<Monster*> get_monsters();

		//is function
		bool is_collide(Character);
		bool is_collide(CMovingBitmap);

		TRIGGER_TYPE is_triggered(Character);
		TRIGGER_TYPE is_triggered(CMovingBitmap);
		//TRIGGER_TYPE is_triggered(Item);

		//behavior function
		void show_bitmap();
		void show_bitmap(int);
		
		void add_colliders(vector<CRect>);
		void clear_collider();

		void add_triggers(vector<CRect>);
		void clear_triggers();

		//monsters
		void add_monsters(vector<Monster*>);
		void show_monsters();
		void monsters_AI(clock_t t);
		void monsters_hurt(vector<CRect>, vector<int>);
		int monsters_die();

		//merchants keys and door
		void add_merchant(int posY, int posX);
		void show_merchants();
		void merchants_hurt(vector<CRect>, vector<int>);
		void merchants_AI(clock_t t);
		int merchants_die();
		void add_key(int posY, int posX);
		void add_door(int posY, int posX);
		void show_key_and_door();
		bool eat_key(Character link);
		bool enter_door(Character link);
		bool buy_key(Character *link);

		//operator overloading
		/*
		*/
		Map& operator=(Map& map);

	protected:
		//variables
		CMovingBitmap _graph;
		vector<CRect> _colliders;
		vector<CRect> _triggers;
		vector<Monster*> _monsters;
		vector<Merchant> _merchants;
		int _posX = 0;
		int _posY = 80;
		vector<CMovingBitmap> _keys;
		vector<CMovingBitmap> _doors;

	private:
	};
}
#endif // !CREATURE_H
