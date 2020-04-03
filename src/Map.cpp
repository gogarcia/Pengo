#include "Map.h"

#include "GameObject.h"
#include "Pengo.h"
#include "SnoBee.h"
#include "Ice.h"
#include "Render.h"
#include <iostream>

/*
Initialize all the values
*/
Map::Map()
{

}


/*
Calls clear()
*/
Map::~Map()
{
    clear();
}

/*
Calls the destructor of all the GameObjects in the map
*/
void Map::clear()
{
    for(int x = 0; x<MAP_W; x++)
    {
        for(int y = 0; y<MAP_H; y++)
        {
            if(map[x]!=nullptr && map[y]!=nullptr)
                delete map[x][y];
        }
    }
}

/*
Returns the Game Object located in the position xy. Returns null if it is empty
*/
GameObject* Map::getGameobject(int x, int y)
{
    GameObject* r = nullptr;

    if(map[x]!=nullptr && map[x][y]!=nullptr)
        r = map[x][y];

    return r;
}

/*
Returns the Pengo iten in the map or null if there is no Pengo
*/
Pengo* Map::getPengo()
{
    return pengo;
}

/*
Calls the draw() function of all the Game Objects in the map
*/
void Map::draw()
{
    Render::getInstance()->drawSprite(spriteBack, Rvect(0,0), 0.f, 1.f, false);
    for(int x=0; x<MAP_W; x++)
    {
        for(int y=0; y<MAP_H; y++)
        {
            if(map[x][y]!=nullptr)
            {
                map[x][y]->draw();
            }
        }
    }
}

/*
Allocate gameObject at the xy position, returns true if xy was empty and false if has a Game Object
*/
bool Map::put(GameObject* gameObject, int x, int y)
{
    if(map[x] !=nullptr && map[x][y] == nullptr)
    {
        map[x][y] = gameObject;
        return true;
    }

    return false;
}

/*
Removes the Game Object located in the position xy
*/
bool Map::push(int x, int y)
{
    if(map[x] !=nullptr && map[x][y] != nullptr)
    {
        delete map[x][y];
        map[x][y] = nullptr;
        return true;
    }

    return false;
}

/*
If the gameObject is in the map returns true and the xy position, else returns false
*/
bool Map::getPosition(GameObject* gameObject, int &x, int &y)
{
    if(gameObject==nullptr)
        return false;

    for(int i = 0; i<MAP_W; i++)
    {
        for(int j = 0; j<MAP_H; j++)
        {
            if(map[i]!=nullptr && map[j]!=nullptr && map[i][j] == gameObject)
            {
                x = i;
                y = j;
                return true;
            }
            
        }
    }
    return false;
}

/*
Creates a Pengo in the xy position, then returns the pengo. Returns null if there is something in xy
*/
Pengo* Map::createPengo(int x,int y)
{
    if(map[x] !=nullptr && map[x][y] == nullptr)
    {

        map[x][y] = new Pengo(x, y);
        pengo = (Pengo*)map[x][y];
        return pengo;
    }
    return nullptr;
}

/*
Creates an ice in the xy position, then returns the pengo. Returns null if there is something in xy
*/
Ice* Map::createIce(int x,int y)
{
    if(map[x] !=nullptr && map[x][y] == nullptr)
    {
        
        map[x][y] = new Ice(x, y);
        return (Ice*)map[x][y];
    }
    return nullptr;
}

/*
Creates a Sno-Bee in the xy position, then returns the pengo. Returns null if there is something in xy
*/
SnoBee* Map::createSnobee(int x,int y)
{
    if(map[x] !=nullptr && map[x][y] == nullptr)
    {
        
        map[x][y] = new SnoBee(x, y);
        return (SnoBee*)map[x][y];
    }
    return nullptr;
}

/*
Calls the update(float dt) function of all the Game Objects in the map
*/
void Map::update(float dt)
{
    int s = sizeof(map)/sizeof(map[0]);
    
    for(int x = 0; x<MAP_W; x++)
        for(int y = 0; y<MAP_H; y++)
            if(map[x]!=nullptr && map[x][y]!=nullptr)
                map[x][y]->noUpdate();
    

    
    for(int x = 0; x<MAP_W; x++)
        for(int y = 0; y<MAP_H; y++)
            if(map[x]!=nullptr && map[x][y]!=nullptr)
                map[x][y]->update(dt);
    
}

void Map::init()
{
    spriteBack = Render::getInstance()->createSprite("res/T2.png", Rrect(0, 0, 223, 255) );

    createPengo(0, 0);
    createIce(1,0);
    createIce(1,1);
    createIce(1,2);
    createIce(1,3);
    createIce(1,4);
    createIce(1,6);
    createIce(1,7);
    createIce(1,8);
    createIce(1,9);
    createIce(1,11);
    createIce(1,12);
    createIce(1,13);
    createIce(1,14);
    createIce(2,3);
    createIce(2,7);
    createIce(3,1);
    createIce(3,7);
    createIce(3,8);
    createIce(3,9);
    createIce(3,10);
    createIce(3,11);
    createIce(3,12);
    createIce(3,13);
    createIce(4,1);
    createIce(4,3);
    createIce(4,5);
    createIce(4,11);
    createIce(5,0);
    createIce(5,1);
    createIce(5,3);
    createIce(5,5);
    createIce(5,7);
    createIce(5,8);
    createIce(5,9);
    createIce(5,11);
    createIce(5,13);
    createIce(6,3);
    createIce(6,5);
    createIce(7,1);
    createIce(7,2);
    createIce(7,3);
    createIce(7,5);
    createIce(7,7);
    createIce(7,9);
    createIce(7,10);
    createIce(7,11);
    createIce(7,12);
    createIce(7,13);
    createIce(8,1);
    createIce(8,5);
    createIce(8,9);
    createIce(8,13);
    createIce(9,1);
    createIce(9,3);
    createIce(9,4);
    createIce(9,6);
    createIce(9,7);
    createIce(9,8);
    createIce(9,9);
    createIce(9,11);
    createIce(9,13);
    createIce(10,3);
    createIce(10,11);
    createIce(11,0);
    createIce(11,1);
    createIce(11,2);
    createIce(11,3);
    createIce(11,4);
    createIce(11,5);
    createIce(11,6);
    createIce(11,7);
    createIce(11,9);
    createIce(11,10);
    createIce(11,11);
    createIce(11,12);
    createIce(11,13);
    createIce(11,14);

}

bool Map::moveUp(GameObject* gameobject)
{   
    if(gameobject==nullptr)
        return false;
    
    int x = -1;
    int y = -1;
    for(int i = 0; i<MAP_W; i++)
    {
        for(int j = 0 ; j<MAP_H; j++)
        {
            if(map[i]!=nullptr && map[j]!=nullptr && map[i][j] == gameobject)
            {
                x = i;
                y = j;
            }
        }
    }

    if(x>=0 && x<MAP_W && (y-1)>=0 && (y-1)<MAP_H && map[x][y-1]==nullptr)
    {
        map[x][y-1] = map[x][y];
        map[x][y] = nullptr;
        return true;
    }
    return false;
}
bool Map::moveDown(GameObject* gameobject)
{

    if(gameobject==nullptr)
        return false;
    
    int x = -1;
    int y = -1;
    for(int i = 0; i<MAP_W; i++)
    {
        for(int j = 0; j<MAP_H; j++)
        {
            if(map[i]!=nullptr && map[j]!=nullptr && map[i][j] == gameobject)
            {
                x = i;
                y = j;
            }
        }
    }
    if(x>=0 && x<MAP_W && (y+1)>=0 && (y+1)<MAP_H && map[x][y+1]==nullptr)
    {
        map[x][y+1] = map[x][y];
        map[x][y] = nullptr;
        return true;
    }
    return false;
}

bool Map::moveLeft(GameObject* gameobject)
{
    if(gameobject==nullptr)
        return false;
    
    int x = -1;
    int y = -1;
    for(int i = 0; i<MAP_W; i++)
    {
        for(int j = 0; j<MAP_H; j++)
        {
            if(map[i]!=nullptr && map[j]!=nullptr && map[i][j] == gameobject)
            {
                x = i;
                y = j;
            }
        }
    }

    if((x-1)>=0 && (x-1)<MAP_W && y>=0 && y<MAP_H && map[x-1][y]==nullptr)
    {
        map[x-1][y] = map[x][y];
        map[x][y] = nullptr;
        return true;
    }
    return false;
}

bool Map::moveRight(GameObject* gameobject)
{
    if(gameobject==nullptr)
        return false;
    
    int x = -1;
    int y = -1;
    for(int i = 0; i<MAP_W; i++)
    {
        for(int j = 0; j<MAP_H; j++)
        {
            if(map[i]!=nullptr && map[j]!=nullptr && map[i][j] == gameobject)
            {
                x = i;
                y = j;
            }
        }
    }

    if((x+1)>=0 && (x+1)<MAP_W && y>=0 && y<MAP_H && map[x+1][y]==nullptr)
    {
        map[x+1][y] = map[x][y];
        map[x][y] = nullptr;
        return true;
    }
    return false;
}

