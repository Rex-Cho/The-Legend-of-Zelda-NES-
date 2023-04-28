#pragma once
#ifndef TEKTITERED
#define TEKTITERED
#include "monster.h"


namespace game_framework {

	class TektiteRed : public Monster
	{
	public:
		TektiteRed();
		~TektiteRed() = default;

		void attack() override;
		void AI();
	private:

	};

}

#endif // !TEKTITERED
