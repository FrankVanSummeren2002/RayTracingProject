#pragma once
#include "precomp.h"
#ifndef SCREEN
#define SCREEN

class Screen
{
	void CalcCentre();
	sf::Image image;
	sf::Texture texture;
	sf::Sprite Photo;

	int dist_Eye_Screen = 1;
	float currentRotation = 0;
	vec3 ScreenCentre;
	vec3 eye;
	//the viewDirection is basicly the zaxis
	vec3 viewDirection;
	vec3 Yaxis = vec3(0,1,0);
	vec3 Xaxis = vec3(1, 0, 0);
	
	//the corners of the screen
	vec3 TLC;
	vec3 TRC;
	vec3 BLC;
	// these are the offsets of the screen corner ro the screen centre
	vec3 C1;
	vec3 C2;
	vec3 C3;

	vec3 F1;
	vec3 F2;
	float division;
public:
	void rotateScreen(float DegreesX,float DegreesY,float DegreesZ);
	vec3 getScreenDir();
	sf::Sprite getImage();
	void draw(int x, int y, float red, float green, float blue);
	void AA(int x, int y);
	void SetScreen();
	void ScreenCopyY(int x, int y);
	void ScreenCopyX(int x, int y);
	vec3 CurrcentScreenPos(int x, int y,int&seed);
	vec3 getEye();
	void setEye(vec3 eyePos);
	void SetViewDir(vec3 view);
	void SetDistance(int x);
	vec3 getXaxis();
	Screen();
	
};
#endif // !SCREEN


