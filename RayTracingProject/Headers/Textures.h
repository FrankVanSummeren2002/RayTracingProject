#pragma once
class Texture
{
    int tilesize = 10;
    struct textures
    {
        enum
        {
            checkerboard
        };
    };
public:
    bool grid(float x, float z);
};