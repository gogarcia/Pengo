#include <Pengo.h>
#include <Console.h>
#include <Map.h>
#include <Render.h>

const float VELOCITY = .3f;
const float TIMEHITTED = .2f;

Pengo::Pengo(int x, int y) : GameObject(x, y)
{
    anim_SD = Render::getInstance()->createAnimation(15);
    Render::getInstance()->addFrameToAnimation(anim_SD, Render::getInstance()->createSprite("res/T3.png",Rrect(0,0,16,16)));
    anim_SU = Render::getInstance()->createAnimation(15);
    Render::getInstance()->addFrameToAnimation(anim_SU, Render::getInstance()->createSprite("res/T3.png",Rrect(80,17,16,16)));
    anim_SL = Render::getInstance()->createAnimation(15);
    Render::getInstance()->addFrameToAnimation(anim_SL, Render::getInstance()->createSprite("res/T3.png",Rrect(48,0,16,16)));
    anim_SR = Render::getInstance()->createAnimation(15);
    Render::getInstance()->addFrameToAnimation(anim_SR, Render::getInstance()->createSprite("res/T3.png",Rrect(112,0,16,16)));
    anim_WD = Render::getInstance()->createAnimation(15);
    Render::getInstance()->addFrameToAnimation(anim_WD, Render::getInstance()->createSprite("res/T3.png",Rrect(0,0,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_WD, Render::getInstance()->createSprite("res/T3.png",Rrect(16,0,16,16)));
    anim_WU = Render::getInstance()->createAnimation(15);
    Render::getInstance()->addFrameToAnimation(anim_WU, Render::getInstance()->createSprite("res/T3.png",Rrect(64,0,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_WU, Render::getInstance()->createSprite("res/T3.png",Rrect(80,0,16,16)));
    anim_WL = Render::getInstance()->createAnimation(15);
    Render::getInstance()->addFrameToAnimation(anim_WL, Render::getInstance()->createSprite("res/T3.png",Rrect(32,0,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_WL, Render::getInstance()->createSprite("res/T3.png",Rrect(48,0,16,16)));
    anim_WR = Render::getInstance()->createAnimation(15);
    Render::getInstance()->addFrameToAnimation(anim_WR, Render::getInstance()->createSprite("res/T3.png",Rrect(96,0,16, 16)));
    Render::getInstance()->addFrameToAnimation(anim_WR, Render::getInstance()->createSprite("res/T3.png",Rrect(112,0,16,16)));
    anim_HU = Render::getInstance()->createAnimation(15);
    Render::getInstance()->addFrameToAnimation(anim_HU, Render::getInstance()->createSprite("res/T3.png",Rrect(5*16,0*16,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_HU, Render::getInstance()->createSprite("res/T3.png",Rrect(5*16,1*16,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_HU, Render::getInstance()->createSprite("res/T3.png",Rrect(4*16,1*16,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_HU, Render::getInstance()->createSprite("res/T3.png",Rrect(5*16,1*16,16,16)));
    anim_HD = Render::getInstance()->createAnimation(15);   
    Render::getInstance()->addFrameToAnimation(anim_HD, Render::getInstance()->createSprite("res/T3.png",Rrect(1*16,0*16,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_HD, Render::getInstance()->createSprite("res/T3.png",Rrect(1*16,1*16,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_HD, Render::getInstance()->createSprite("res/T3.png",Rrect(0*16,1*16,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_HD, Render::getInstance()->createSprite("res/T3.png",Rrect(1*16,1*16,16,16)));
    anim_HL = Render::getInstance()->createAnimation(15);
    Render::getInstance()->addFrameToAnimation(anim_HL, Render::getInstance()->createSprite("res/T3.png",Rrect(3*16,0*16,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_HL, Render::getInstance()->createSprite("res/T3.png",Rrect(3*16,1*16,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_HL, Render::getInstance()->createSprite("res/T3.png",Rrect(2*16,1*16,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_HL, Render::getInstance()->createSprite("res/T3.png",Rrect(3*16,1*16,16,16)));
    anim_HR = Render::getInstance()->createAnimation(15);
    Render::getInstance()->addFrameToAnimation(anim_HR, Render::getInstance()->createSprite("res/T3.png",Rrect(7*16,0*16,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_HR, Render::getInstance()->createSprite("res/T3.png",Rrect(7*16,1*16,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_HR, Render::getInstance()->createSprite("res/T3.png",Rrect(6*16,1*16,16,16)));
    Render::getInstance()->addFrameToAnimation(anim_HR, Render::getInstance()->createSprite("res/T3.png",Rrect(7*16,1*16,16,16)));


    state= S_D;
}

Pengo::~Pengo(){
    Render* r = Render::getInstance();
    r->deleteAnimation(anim_SU);
    r->deleteAnimation(anim_SD);
    r->deleteAnimation(anim_SR);
    r->deleteAnimation(anim_SL);
    r->deleteAnimation(anim_WU);
    r->deleteAnimation(anim_WD);
    r->deleteAnimation(anim_WL);
    r->deleteAnimation(anim_WR);
    r->deleteAnimation(anim_HU);
    r->deleteAnimation(anim_HD);
    r->deleteAnimation(anim_HL);
    r->deleteAnimation(anim_HR);
}

void Pengo::update(float dt)
{
    if(this->wasUpdate)
        return;

    this->wasUpdate = true;
    if(state == H_U || state == H_D || state == H_L || state == H_R)
    {
        hit_Time += dt;
        if(hit_Time>TIMEHITTED)
        {
            switch (state)
            {
            case H_U:
                state = S_U;
                break;
            case H_D:
                state = S_D;
                break;
            case H_L:
                state = S_L;
                break;
            case H_R:
                state = S_R;
                break;
            default:
                break;
            }
        }
        return;   
    }
    if(state == S_D || state == S_U || state == S_L ||state == S_R)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            switch (state)
            {
            case S_D:
                Map::getInstance()->pengoHits(x, y+1, 2);
                state = H_D;
                hit_Time = 0.f;
                break;
            case S_U:
                Map::getInstance()->pengoHits(x, y-1, 0);
                state = H_U;                
                hit_Time = 0.f;
                break;
            case S_L:
                Map::getInstance()->pengoHits(x-1, y, 3);
                state = H_L;
                hit_Time = 0.f;
                break;
            case S_R:
                Map::getInstance()->pengoHits(x+1, y, 1);
                state = H_R;
                hit_Time = 0.f;
                break;
            
            default:
                break;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(Map::getInstance()->pengoMoving(this, 0))
            {
                state = W_U;
                walking_Time = 0.f;
                y--;
            }
            else
            {
                state = S_U;
            }
            

        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(Map::getInstance()->pengoMoving(this, 2))
            {
                state = W_D;
                walking_Time = 0.f;
                y++;
            }
            else
            {
                state = S_D;
            }

        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(Map::getInstance()->pengoMoving(this, 3))
            {
                state = W_L;
                walking_Time = 0.f;
                x--;
            }            
            else
            {
                state = S_L;
            }

        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {

            if(Map::getInstance()->pengoMoving(this, 1))
            {
                state = W_R;
                walking_Time = 0.f;
                x++;
            }
            else
            {
                state = S_R;
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

void Pengo::draw()
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
    case H_D:
        Render::getInstance()->drawAnimation(anim_HD, Rvect(x*16+8, y*16+48), 0.f, 1.f, false);
        break;
    case H_U:
        Render::getInstance()->drawAnimation(anim_HU, Rvect(x*16+8, y*16+48), 0.f, 1.f, false);
        break;
    case H_L:
        Render::getInstance()->drawAnimation(anim_HL, Rvect(x*16+8, y*16+48), 0.f, 1.f, false);
        break;
    case H_R:
        Render::getInstance()->drawAnimation(anim_HR, Rvect(x*16+8, y*16+48), 0.f, 1.f, false);
        break;
    default:
        break;
    }
}


int Pengo::getLifes()
{
    return lifes;
}

bool Pengo::hit()
{
    lifes--;

    if(lifes<0)
        return false;
    
    return true;
}

void Pengo::setLifes(int l)
{
    lifes = l;
}