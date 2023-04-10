#pragma once
#ifndef TRIGGER_H
#define TRIGGER_H

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
#include"character.h"

using namespace std;

namespace game_framework {
	class Trigger {
	public:
		Trigger();
		Trigger(CRect,Map);
		~Trigger();

		//set function
		void set_trigger(CRect);
		void set_link_map(Map);
		//get function
		CRect get_trigger();
		Map get_link_map();

		//is function
		bool is_triggered(Character);

		//behavior function

	protected:
		//variables
		CRect _area;
		Map _link_map;

	private:
	};
}
#endif // !TRIGGER_H
