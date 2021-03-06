#include <SnoBee.h>
#include <Render.h>
#include <Map.h>

const float VELOCITY = .3f;
const float TIMESTUNNED = 5.f;

SnoBee::SnoBee(int x, int y) : GameObject(x, y)
{
    anim_SD = Render::getInstance()->createAnimation(10);
    Render::getInstance()->addFrameToAnimation(anim_SD, Render::getInstance()->createSprite("res/T3.png",Rrect(16,144,16,16)));
    anim_SU = Render::getInstance()->createAnimation(10);
    Render::getInstance()->addFrameToAnimation(anim_SU, Render::getInstance()->createSprite("res/T3.png",Rrect(5*16,144,16,16)));
    anim_SL = Render::getInstance()->createAnimation(10);
    Render::getInstance()->addFrameToAnimation(anim_SL, Render::getInstance()->createSprite("res/T3.png",Rrect(3*16,144,16,16)));
    anim_SR = Render::getInstance()->createAnimation(10);
    Render::getInstance()->addFrameToAnimation(anim_SR, Render::getInstance()->createSprite("res/T3.png",Rrect(7*16,144,16,16)));
    anim_WD = Render::getInstance()->createAnimation(10);
    Render::getInstance()->addFrameToAnimation(anim_WD, Render::getInstance()->createSprite("res/T3.png",Rrect(0,144,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_WD, Render::getInstance()->createSprite("res/T3.png",Rrect(16,144,16,16)));
    anim_WU = Render::getInstance()->createAnimation(10);
    Render::getInstance()->addFrameToAnimation(anim_WU, Render::getInstance()->createSprite("res/T3.png",Rrect(4*16,144,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_WU, Render::getInstance()->createSprite("res/T3.png",Rrect(5*16,144,16,16)));
    anim_WL = Render::getInstance()->createAnimation(10);
    Render::getInstance()->addFrameToAnimation(anim_WL, Render::getInstance()->createSprite("res/T3.png",Rrect(2*16,144,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_WL, Render::getInstance()->createSprite("res/T3.png",Rrect(3*16,144,16,16)));
    anim_WR = Render::getInstance()->createAnimation(10);
    Render::getInstance()->addFrameToAnimation(anim_WR, Render::getInstance()->createSprite("res/T3.png",Rrect(6*16,144,16, 16)));
    Render::getInstance()->addFrameToAnimation(anim_WR, Render::getInstance()->createSprite("res/T3.png",Rrect(7*16,144,16,16)));
    anim_Stunned = Render::getInstance()->createAnimation(5);
    Render::getInstance()->addFrameToAnimation(anim_Stunned, Render::getInstance()->createSprite("res/T3.png",Rrect(6*16,16*8,16, 16)));
    Render::getInstance()->addFrameToAnimation(anim_Stunned, Render::getInstance()->createSprite("res/T3.png",Rrect(7*16,16*8,16, 16)));

    state= S_D;
}

SnoBee::~SnoBee()
{
    Render* r = Render::getInstance();
    r->deleteAnimation(anim_SU);
    r->deleteAnimation(anim_SD);
    r->deleteAnimation(anim_SR);
    r->deleteAnimation(anim_SL);
    r->deleteAnimation(anim_WU);
    r->deleteAnimation(anim_WD);
    r->deleteAnimation(anim_WL);
    r->deleteAnimation(anim_WR);
    r->deleteAnimation(anim_Stunned);
}

void SnoBee::update(float dt)
{
    if(this->wasUpdate)
        return;

    this->wasUpdate = true;

    if(state == STUNNED)
    {
        stunned_Time += dt;
        if(stunned_Time>TIMESTUNNED)
        {
            state=S_D;
            stunned_Time = 0.f;
        }

        return;
    }

    if(state == S_D || state == S_U || state == S_L ||state == S_R)
    {
        //Time to move
        bool hasContinue = false;
        switch (state)
        {
            case S_D:
                if(Map::getInstance()->snobeeMoving(this, 2))
                {
                    y++;
                    state = W_D;
                    walking_Time = 0.f;
                    hasContinue = true;
                }
                break;
            case S_U:
                if(Map::getInstance()->snobeeMoving(this, 0))
                {
                    y--;
                    state = W_U;
                    walking_Time = 0.f;
                    hasContinue = true;
                }
                break;        
            case S_L:
                if(Map::getInstance()->snobeeMoving(this, 3))
                {
                    x--;
                    state = W_L;
                    walking_Time = 0.f;
                    hasContinue = true;
                }
                break;
            case S_R:
                if(Map::getInstance()->snobeeMoving(this, 1))
                {
                    x++;
                    state = W_R;
                    walking_Time = 0.f;
                    hasContinue = true;
                }
                break;
            default:
                break;
        }
        if(!hasContinue)
        {
            int dir;
            if((Map::getInstance()->getGameobject(x-1, y) != nullptr || (x-1)<0) &&
                (Map::getInstance()->getGameobject(x+1, y) != nullptr || (x+1)>=MAP_W) &&
                (Map::getInstance()->getGameobject(x, y-1) != nullptr || (y-1)<0) &&
                (Map::getInstance()->getGameobject(x, y+1) != nullptr || (y+1)>=MAP_H))
            {
                //NO SE PUEDE MOVER
            }else{
                do
                {
                    dir = rand()%4;
                } while (!Map::getInstance()->snobeeMoving(this, dir));
                switch (dir)
                {
                    case 2:
                        y++;
                        state = W_D;
                        walking_Time = 0.f;
                        break;
                    case 0:
                        y--;
                        state = W_U;
                        walking_Time = 0.f;
                        break;        
                    case 3:
                        x--;
                        state = W_L;
                        walking_Time = 0.f;
                        break;
                    case 1:
                        x++;
                        state = W_R;
                        walking_Time = 0.f;
                        break;
                }

            }
            
        }
    }else
    {
        walking_Time += dt;
        if(walking_Time>VELOCITY)
        {
            if(state==W_U)
                state = S_U;
            else if(state == W_D)
                state = S_D;
            else if(state == W_L)
                state = S_L;
            else if(state == W_R)
                state = S_R;
        }
    }
}


void SnoBee::draw()
{
    int delay = (1-(walking_Time/VELOCITY))*16;
    switch (state)
    {
        case S_D:
            Render::getInstance()->drawAnimation(anim_SD, Rvect(x*16+8, y*16+48), 0.f, 1.f, false);
            break;
        case S_U:
            Render::getInstance()->drawAnimation(anim_SU, Rvect(x*16+8, y*16+48), 0.f, 1.f, false);
            break;
        case S_L:
            Render::getInstance()->drawAnimation(anim_SL, Rvect(x*16+8, y*16+48), 0.f, 1.f, false);
            break;
        case S_R:
            Render::getInstance()->drawAnimation(anim_SR, Rvect(x*16+8, y*16+48), 0.f, 1.f, false);
            break;
        case W_D:
            Render::getInstance()->drawAnimation(anim_WD, Rvect(x*16+8, (y*16+48)-delay), 0.f, 1.f, false);
            break;
        case W_U:
            Render::getInstance()->drawAnimation(anim_WU, Rvect(x*16+8, (y*16+48)+delay), 0.f, 1.f, false);
            break;
        case W_L:
            Render::getInstance()->drawAnimation(anim_WL, Rvect((x*16+8)+ delay, y*16+48), 0.f, 1.f, false);
            break;
        case W_R:
            Render::getInstance()->drawAnimation(anim_WR, Rvect((x*16+8) - delay, y*16+48), 0.f, 1.f, false);
            break;
        case STUNNED:
            Render::getInstance()->drawAnimation(anim_Stunned, Rvect(x*16+8, y*16+48), 0.f, 1.f, false);
            break;
        
        default:
            break;
    }
}


void SnoBee::stun()
{
    state = STUNNED;
    stunned_Time = 0.f;
}