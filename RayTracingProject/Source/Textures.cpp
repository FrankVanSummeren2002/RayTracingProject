#include "precomp.h"
#include "Textures.h"
bool Texture::grid(float x, float z)
{
   
    int Xgrid = static_cast<int> (round(x / tilesize));
    int Zgrid = static_cast<int> (round(z / tilesize));

    if ((Xgrid & 1) == (Zgrid & 1))return true;
    return false;

}