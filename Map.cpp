#include "Map.h"
#include "TextureManager.h"

int lv1[20][25] =
{
    { 3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,1 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1 },
    { 3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,1 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
    { 3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
    { 3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3 },
    { 3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
};




Map::Map()
{
    dirt = TextureManager::LoadTexture("image/dirt.png");
    grass = TextureManager::LoadTexture("image/grass.png");
    stone = TextureManager::LoadTexture("image/stone.png");

    src.x = 0;
    src.y = 0;
    src.h = 32;
    src.w = 32;

    dest.x = 0;
    dest.y = 0;
    dest.h = 32;
    dest.w = 32;

    LoadMap(lv1);
}

void Map::LoadMap(int arr[20][25])
{
    for(int row = 0; row < 20; row++)
    {
        for(int column = 0; column < 25; column++)
        {
            mapping[row][column] = arr[row][column];

            tile[row][column].x = column * 32;
            tile[row][column].y = row * 32;
            tile[row][column].w = TILE_WIDTH;
            tile[row][column].h = TILE_HEIGHT;
        }
    }
}

bool Map::checkCollision( SDL_Rect a, SDL_Rect b )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    return true;
}

void Map::DrawMap(SDL_Rect Camera)
{
    int type = 0;
    for(int row = 0; row < 20; row++)
    {
        for(int column = 0; column < 25; column++)
        {
            type = mapping[row][column];

            dest.x = column * 32;
            dest.y = row * 32;
            if(checkCollision(Camera, tile[row][column]))
            {
                dest.y -= Camera.y;
                switch(type)
                {
                    case 0:
                        TextureManager::Draw(dirt, src, dest);
                        break;
                    case 1:
                        TextureManager::Draw(grass, src, dest);
                        break;
                    case 2:
                        TextureManager::Draw(stone, src, dest);
                        break;
                    case 3:
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void Map::CloseMap()
{
    SDL_DestroyTexture(dirt);
    SDL_DestroyTexture(stone);
    SDL_DestroyTexture(grass);
    dirt = NULL;
    stone = NULL;
    grass = NULL;
}
