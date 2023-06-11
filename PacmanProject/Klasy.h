#pragma once
// pobranie odpowiednich bibliotek
#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>


using namespace std;
using namespace sf;

// stale globalne
const int windowWith = 810;
const int windowHeight = 620;
const int blocksAmount = 86;

class SoundPlayer
{
public:
	SoundPlayer(string filename);
	SoundPlayer() = delete;
	~SoundPlayer() = default;
	void play();
private:
	SoundBuffer buffer;
	Sound sound;
};
// klasy, ktore beda rysowaly cos w oknie musza dziedziczyc po Drawable
class Ghost;
// z wielu obiektow klasy Block tworzy sie labirynt
class Block : public Drawable
{
public:
	Block(float x, float y, float blockWidth, float blockHeight);
	Block() = delete;
	~Block() = default;
	// funkcja zaprzyjazniona ktora sprawdza czy dojdzie do kolizji miedzy duszkiem a labiryntem
	friend int collisionGhostBlock(Ghost a, Block b, int direction);
	float left();
	float right();
	float top();
	float bottom();
private:
	//rysowanie bloczku
	void draw(RenderTarget& target, RenderStates state) const override;
	RectangleShape shape;
	float blockWidth, blockHeight;
};

// klasa, kotra pozwoli wyswietlac nam menu
class Menu
{
public:
	Menu(float width, float height);
	Menu() {};
	~Menu() = default;

	void draw(RenderWindow& window, Text menu[]);
	void moveUp(Text menu[], string color);
	void moveDown(Text menu[], string color);
	int getPressedItem() { return selectedItemIndex; }
	int selectedItemIndex;
	//zmienna, ktora odpowiada za czcionke
	Font font;
	Text menu[3];
	string color = "blue";
};

class SubMenu : public Menu
{
public:
	SubMenu(float width2, float height2);
	Text subMenu[3];
	string color = "red";
};

class Information
{
public:
	Information(float width, float height);
	//zmienna, ktora odpowiada za czcionke
	Font font;
	Text text;
	void informationShowing(RenderWindow& window, Text text, string filename);
};

class Pacman : public Drawable
{
public:
	Pacman(float x, float y);
	Pacman() = delete;
	~Pacman() = default;

	void update(bool collisionPacmanMushroom, Time periodFruit);
	Vector2f getPosition();

	float left();
	float right();
	float top();
	float bottom();
	Texture texture;
	Sprite pacman;
private:
	//zadeklarowanie stalych dla pacmana
	const float pacmanVelocity{ 2.4f };
	Vector2f velocity{ 0.f, 0.f };
	void draw(RenderTarget& target, RenderStates state) const override;

};

class Ghost : public Drawable
{
public:
	Ghost(float x, float y, string color);
	Ghost() = delete;
	~Ghost() = default;
	friend int collisionGhostBlock(Ghost a, Block b, int direction);
	void update();
	void updateChange(int direction, Time periodFruit, bool collisionPacmanCherry, int level);
	int whichDirection();
	//Vector2f getPosition();
	float left();
	float right();
	float top();
	float bottom();
	Texture texture;
	Sprite ghost;
private:
	void draw(RenderTarget& target, RenderStates state) const override;
	//zadeklarowanie sta�ych dla duch�w
	const float ghostWidth{ 18.6f };
	const float ghostHeight{ 18.6f };
	const float ghostVelocity{ 2.5f };
	Vector2f velocity{ 0.f, ghostVelocity };
};

class Point :public Drawable
{
public:
	Point();
	~Point() = default;
	float left();
	float right();
	float top();
	float bottom();
	void changeColor();
	// zadeklarowanie ksztaltu punktow (kolo)
	CircleShape shape;
private:
	// funkcja odpowiadajaca za rysowanie
	void draw(RenderTarget& target, RenderStates state) const override;
	const float pointRadius = 3.0f;
};

class Panel
{
public:
	Panel(float x, float y);
	Panel() = delete;
	~Panel() = default;
	Font font;
	Text text;
	void showingPoints(RenderWindow& window, Text text, int pointsAmount);
	void showingTime(RenderWindow& window, Text text, Time elapsed);
	void showingLife(RenderWindow& window, Text text);
	void showingPower(RenderWindow& window, Text text);
	void showingLevel(RenderWindow& window, Text text, int level);
	void showingRecord(RenderWindow& window, Text text, int pointsAmount);
};

// klasa bazowa, po ktorej beda dziedziczyc owoce
class Fruit :public Drawable
{
public:
	//zmienne ponizej beda potrzebne do pokazywania obrazu z odpowiedniego pliku
	Texture texture;
	Sprite fruit;
	void draw(RenderTarget& target, RenderStates state) const override;

	//Vector2f getPosition();

	float left();
	float right();
	float top();
	float bottom();

	void appear();
	void disappear();
};

class Apple : public Fruit
{
public:
	Apple(float x, float y);
	Apple() = delete;
	~Apple() = default;
};

class Orange : public Fruit
{
public:
	Orange(float x, float y);
	Orange() = delete;
	~Orange() = default;
};

class Banana : public Fruit
{
public:
	Banana(float x, float y);
	Banana() = delete;
	~Banana() = default;
};

class Cherry : public Fruit
{
public:
	Cherry(float x, float y);
	Cherry() = delete;
	~Cherry() = default;
};

class Mushroom : public Fruit
{
public:
	Mushroom(float x, float y);
	Mushroom() = delete;
	~Mushroom() = default;
};

class GameOver
{
public:
	GameOver(float x, float y);
	GameOver() = delete;
	~GameOver() = default;
	Font font;
	Text text;
	void showingTitle(RenderWindow& window, Text text, string title);
	void showingPoints(RenderWindow& window, Text text, int pointsAmount);
	void showingTime(RenderWindow& window, Text text, Time elapsed);
	void showingRecord(RenderWindow& window, Text text, int pointsAmount);
};
void setFruit(Time& periodFruit, bool& collisionPacmanApple, bool& collisionPacmanOrange, bool& collisionPacmanBanana, bool& collisionPacmanCherry, bool& collisionPacmanMushroom, Fruit& apple, Fruit& orange, Fruit& banana, Fruit& cherry, Fruit& mushroom);

string recordFile(int pointsAmount);
