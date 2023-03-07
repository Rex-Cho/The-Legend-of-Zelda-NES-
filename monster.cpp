#include <StdAfx.h>
#include "cracture.h"


namespace game_framework {

	class Monster : public Creature {
	public:
		void AI();
		void show();
	private:
		Monster();
		~Monster() = default;
		void spawn();
		void attack();
		void die();
		void hurt();
		void movement(MOVEMENT_REF);
		void set_movement_animation(CMovingBitmap);
		void set_dead_animation(CMovingBitmap);
		void set_attack_animation(CMovingBitmap);
		void set_hurt_animation(CMovingBitmap);
		void set_spawn_animation(CMovingBitmap);
		
		void set_decision_time(int);

		int decision_time = 800;
	};
	Monster::Monster() : Creature() 
	{

	}
	void Monster::set_decision_time(int time)
	{
		if (time < 0 || time > 2000)
			return;
		decision_time = time;
	}
	void Monster::set_movement_animation(CMovingBitmap anim)
	{
		movement_animation = anim;
	}
	void Monster::set_dead_animation(CMovingBitmap anim)
	{
		dead_animation = anim;
	}
	void Monster::set_attack_animation(CMovingBitmap anim)
	{
		attack_animation = anim;
	}
	void Monster::set_hurt_animation(CMovingBitmap anim)
	{
		hurt_animation = anim;
	}
	void Monster::set_spawn_animation(CMovingBitmap anim)
	{
		spawn_animation = anim;
	}
	void Monster::spawn()
	{

	}
	void Monster::attack()
	{
		attack_animation.SetAnimation(100, true);
		
		//attack_item and animation
	}
	void Monster::die()
	{

	}
	void Monster::hurt()
	{

	}
	void Monster::movement(MOVEMENT_REF direction)
	{

	}
	void Monster::AI()
	{
		
	}
	void Monster::show()
	{

	}
}