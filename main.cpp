#include "include/raylib.h"
#include <random>
#include <vector>
#include <math.h>


float randrange(int min, int max) {
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(min, max); 
    return distr(gen); 
}


class partical
{
    public:
        Vector2 center {0,0};
        Vector2 velocity {0,0};
        partical(float x = 0, float y = 0 ,float v=0);
        void update();

    private:
        int radius{5};
        void draw();
};

void partical::update()
{
    if(center.x+radius >= GetScreenWidth() || center.x-radius <= 0)
    {
        velocity.x = -(velocity.x);
    }
    else if (center.y-radius <= 0 || center.y+radius >= GetScreenHeight())
    {
        velocity.y = -(velocity.y);
    }
    center.x += velocity.x;
    center.y += velocity.y;
    this->draw();
}

partical::partical(float x,float y ,float v)
:center{x,y},velocity{v,v} {}

void partical::draw()
{
    DrawCircle(center.x,center.y,radius,WHITE);
}


int main(void)
{
    const int screenhight {750};
    const int screenwidth {1050};

    int population {200};

    InitWindow(screenwidth,screenhight,"Game");
    SetTargetFPS(60);

    std::vector <partical> all;

    for(int i{0}; i<population; i++)
    {
        partical temp {randrange(0,screenwidth),randrange(0,screenhight),randrange(1,5)};
        all.push_back(temp);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(BLACK);

            for(int i{0}; i<all.size();i++)
            {
                for(int j{0};j<all.size();j++)
                {
                    int distance {0};
                    int ix = all.at(i).center.x , iy = all.at(i).center.y , jx = all.at(j).center.x,jy = all.at(j).center.y;
                    int dx {jx-ix};
                    int dy {jy-iy};
                    distance = std::sqrt((dx*dx)+(dy*dy));
                    if(distance <= 100){
                        DrawLine(ix,iy,jx,jy,WHITE);
                    }
                    if(distance == 10){
                        all.at(i).velocity = {-(all.at(i).velocity.x),-(all.at(i).velocity.y)};
                        all.at(j).velocity = {-(all.at(j).velocity.x),-(all.at(j).velocity.y)};
                    }
                }
                all.at(i).update();
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}