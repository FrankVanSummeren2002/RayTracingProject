#include"precomp.h"
#include "Rendering/Screen.h"
Screen::Screen()
{
    //i calculate the division once because they are the awnser is the same every time
    division = 1.f / SCRWIDTH;
    eye = { 0,0,0 };
    viewDirection = {0,0,-1};
    dist_Eye_Screen = 1;
    CalcCentre();
    //these would be the corners directly against the axis
    C1 = vec3(-0.5, -0.5, 0);
    C2 = vec3(0.5, -0.5, 0);
    C3 = vec3(-0.5, 0.5, 0);
    //these are the actual screen corners
    TLC = ScreenCentre + C1;
    TRC = ScreenCentre + C2;
    BLC = ScreenCentre + C3;

    F1 = TRC - TLC;
    F2 = BLC - TLC;
    image.loadFromFile("assets/background.jpg");
    //image.create(static_cast<unsigned int>(SCRWIDTH), static_cast<unsigned int>(SCRHEIGHT), sf::Color(255, 0, 0));
}

 vec3 Screen::CurrcentScreenPos(int x, int y,int& seed)
{
     float DisX = (x + math::RANDF_MIN_MAX(seed,1,0)) * division;
     float DisY = (y + math::RANDF_MIN_MAX(seed, 1, 0)) * division;
     return TLC + F1 * static_cast<float>(DisX) + F2 * static_cast<float>(DisY);
}

 void Screen::CalcCentre()
{
    ScreenCentre = eye + viewDirection * dist_Eye_Screen;
}

vec3 Screen::getEye()
{
    return eye;
}
void Screen::setEye(vec3 eyePos)
{
    eye = eyePos;
    CalcCentre();
    TLC = ScreenCentre + C1;
    TRC = ScreenCentre + C2;
    BLC = ScreenCentre + C3;
   
}

void Screen::SetViewDir(vec3 view)
{
    viewDirection = view;
}

void Screen::SetDistance(int x)
{
    dist_Eye_Screen = x;
}
vec3 Screen::getXaxis()
{
    return Xaxis;
}
void Screen::rotateScreen(float degreesX,float degreesY,float degreesZ)
{
    Matrix mat(Matrix::MatSizes::THREE_THREE);
    if (degreesX != 0)
    {
       
        mat.rotationMatrix(Xaxis,degreesX);
        mat.rotateAxis(Yaxis);
        mat.rotateAxis(viewDirection);
        Yaxis.normalize();
        viewDirection.normalize();
        mat.rotateAxis(C1);
        mat.rotateAxis(C2);
        mat.rotateAxis(C3);
       
        CalcCentre();
        TLC = ScreenCentre + C1;
        TRC = ScreenCentre + C2;
        BLC = ScreenCentre + C3;
  
        
        F1 = TRC - TLC;
        F2 = BLC - TLC;
       
    }
    if (degreesY != 0)
    {
       
        mat.rotationMatrix(Yaxis, degreesY);
        mat.rotateAxis(viewDirection);
        mat.rotateAxis(Xaxis);
        Xaxis.normalize();
        viewDirection.normalize();
      mat.rotateAxis(C1);
      mat.rotateAxis(C2);
      mat.rotateAxis(C3);

     
        CalcCentre();
        TLC = ScreenCentre + C1;
        TRC = ScreenCentre + C2;
        BLC = ScreenCentre + C3;
       
        F1 = TRC - TLC;
        F2 = BLC - TLC;
    }
    if (degreesZ != 0)
    {
       
      mat.rotationMatrix(viewDirection, degreesZ);
      mat.rotateAxis(Yaxis);
      mat.rotateAxis(Xaxis);
      Xaxis.normalize();
      Yaxis.normalize();
      mat.rotateAxis(C1);
      mat.rotateAxis(C2);
      mat.rotateAxis(C3);
           
        CalcCentre();

        TLC = ScreenCentre + C1;
        TRC = ScreenCentre + C2;
        BLC = ScreenCentre + C3;

        F1 = TRC - TLC;
        F2 = BLC - TLC;
    }

}

vec3 Screen::getScreenDir()
{
    return viewDirection;
}

sf::Sprite Screen::getImage()
{
    return Photo;
}

void Screen::draw(int x, int y, float red, float green, float blue)
{
    int R = math::clampI(static_cast<int>(red * 255), 0, 255);
    int G = math::clampI(static_cast<int>(green * 255), 0, 255);
    int B = math::clampI(static_cast<int>(blue * 255), 0, 255);
    image.setPixel(x, y,sf::Color(static_cast<sf::Uint8>(R),static_cast<sf::Uint8>(G),static_cast<sf::Uint8>(B)));
 //   if (x != 0 && y != 0)
 //  {
 //       AA(x, y);
 //   }
}

void Screen::AA(int x,int y)
{
    float r, g, b;
    sf::Color c;

            c = image.getPixel(x, y);
            r = c.r;
            g = c.g;
            b = c.b;

            c = image.getPixel(x-1, y);
            r += c.r;
            g += c.g;
            b += c.b;

            c = image.getPixel(x, y - 1);
            r += c.r;
            g += c.g;
            b += c.b;

            c = image.getPixel(x - 1, y-1);
            r += c.r;
            g += c.g;
            b += c.b;

            r = r / 4;
            g = g / 4;
            b = b / 4;
            image.setPixel(x, y,sf::Color(static_cast<sf::Uint8>(r),static_cast<sf::Uint8>(g), static_cast<sf::Uint8>(b)));
}
void Screen::SetScreen()
{
    texture.loadFromImage(image);
    Photo.setTexture(texture);
}

void Screen::ScreenCopyY(int x, int y)
{
    image.setPixel(x, y, image.getPixel(x, y - 1));
}
void Screen::ScreenCopyX(int x, int y)
{
    image.setPixel(x, y, image.getPixel(x - 1, y));
}
