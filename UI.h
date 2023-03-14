#pragma once

namespace game_framework{
    class UI{
    private:
        CMovingBitmap bumb;
        CMovingBitmap key;
    public:
        void show_money(int count);
        void show_bomb(int count);
        void show_key(int count);
        void show_minimap(int x,int y);
        void show_life(int max_heart, int heart);
        void show_waponA(CmovingBitmap ref);
        void show_waponB(CMovingBitmap ref);
        void show_SetUI();
    };
}