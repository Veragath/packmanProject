#pragma once
#include <iostream>
#include <random>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

class Menu
{
public:
	Menu(float width, float height); //SPRÓBOWAÆ USTAWIÆ TO W DOMYŒLNYM 
	Menu() {};
	~Menu() = default;

	void draw(RenderWindow& window, Text menu[]);
	void moveUp(Text menu[], string color);
	void moveDown(Text menu[], string color);
	int getPressedItem() { return selectedItemIndex; }
	int selectedItemIndex;
	Font font;
	Text menu[3];
	string color = "blue";
};

class SubMenu : public Menu 
{
public:
	SubMenu(float width2, float height2);
	//SubMenu() = delete;
	//~SubMenu() = default;
	Text subMenu[3];
	string color = "red";
};

class Pacman : public Drawable
{
public:
	Pacman(float t_X, float t_Y);
	Pacman() = delete;
	~Pacman() = default;

	void update();
	Vector2f getPosition();

	float left();
	float right();
	float top();
	float bottom();
private:
	// zadeklarowanie kszta³tu pacmana
	CircleShape shape;
	//zadeklarowanie sta³ych dla pacmana
	const float pacmanRadius{ 10.0f };
	const float pacmanVelocity{ 3.0f };
	Vector2f velocity{ 0.f, 0.f };
	void draw(RenderTarget& target, RenderStates state) const override;

};

class Ghost : public Drawable
{
public:
	Ghost(float t_X, float t_Y, string color);
	Ghost() = delete;
	~Ghost() = default;

	void update(int frame);
	Vector2f getPosition();

	float left();
	float right();
	float top();
	float bottom();
private:
	// zadeklarowanie kszta³tu duchów
	RectangleShape shape;
	void draw(RenderTarget& target, RenderStates state) const override;
	//zadeklarowanie sta³ych dla duchów
	const float ghostWidth{ 20.0f };
	const float ghostHeight{ 20.0f };
	const float ghostVelocity{ 3.1f };
	Vector2f velocity{ 0.f, ghostVelocity };
};

class Point : public Drawable
{
public:
	Point(float t_X, float t_Y);
	Point() = delete;
	~Point() = default;
};

class Wall : public Drawable
{
public:
	Wall(float t_X, float t_Y);
	Wall() = delete;
	~Wall() = default;

	float left();
	float right();
	float top();
	float bottom();
private:
	// zadeklarowanie kszta³tu œciany
	RectangleShape shape;
	void draw(RenderTarget& target, RenderStates state) const override;
	//zadeklarowanie sta³ych dla duchów
	const float wallWidth{ 20.0f };
	const float walltHeight{ 5.0f };
};