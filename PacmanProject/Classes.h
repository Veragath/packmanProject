#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>


using namespace std;
using namespace sf;

// stale globalne
const int windowWith = 810;
const int windowHeight = 620;
const int blocksAmount = 86;

//klasa odpowiadajaca za efekty dzwiekowe
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
//deklaracja klasy, ktora bedzie potrzebna do funkcji zaprzyjaznionej collisionGhostBlock
class Ghost;
// klasy, ktore beda rysowaly cos w oknie musza dziedziczyc po Drawable
// z wielu obiektow klasy Block tworzy sie labirynt
class Block : public Drawable
{
public:
	Block(float x, float y, float blockWidth, float blockHeight);
	Block() = delete;
	~Block() = default;
	// funkcja zaprzyjazniona ktora sprawdza czy dojdzie do kolizji miedzy duszkiem a labiryntem
	friend int collisionGhostBlock(Ghost a, Block b, int direction);
	//funkcje odpowiadajace za najbardziej wychylone punkty na lewo, prawo, gore i dol, beda one potrzebne do systemu kolizji
	float left();
	float right();
	float top();
	float bottom();
private:
	//rysowanie bloczku
	void draw(RenderTarget& target, RenderStates state) const override;
	// zadaklarowanie ksztaltu bloczkow (beda one prostokatami)
	RectangleShape shape;
	float blockWidth, blockHeight;
};

// klasa, ktora pozwoli wyswietlac menu
class Menu
{
public:
	Menu(float width, float height);
	Menu() {};
	~Menu() = default;
	void draw(RenderWindow& window, Text menu[]);
	// funkcje odpowiadajace za poruszanie sie w menu
	void moveUp(Text menu[], string color);
	void moveDown(Text menu[], string color);
	int getPressedItem() { return selectedItemIndex; }
	int selectedItemIndex;
	//zmienna, ktora odpowiada za czcionke
	Font font;
	Text menu[3];
	string color = "blue";
};
// klasa, ktora wyswietla opcje po kliknieciu options w menu
class SubMenu : public Menu
{
public:
	SubMenu(float width, float height);
	Text subMenu[3];
	string color = "red";
};
// klasa, odpowiadajaca za wyswietlanie informacji
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

	// funckja odpowiadajaca za ustawianie predkosci
	void update(bool collisionPacmanMushroom, Time periodFruit);
	// ustalanie pozycji pacmana
	Vector2f getPosition();

	float left();
	float right();
	float top();
	float bottom();
	// potrzebne zmienne do wyswietlania obrazow
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
	// funkcje odpowiadajace za ruch duszkow
	friend int collisionGhostBlock(Ghost a, Block b, int direction);
	void update();
	void updateChange(int direction, Time periodFruit, bool collisionPacmanCherry, int level);
	int whichDirection();
	float left();
	float right();
	float top();
	float bottom();
	Texture texture;
	Sprite ghost;
private:
	void draw(RenderTarget& target, RenderStates state) const override;
	//zadeklarowanie stalych dla duch�w
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

// klasa, ktorej obiekty pojawiaja sie prawej czesci ekranu podczas rozgrywki
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
class Fruit : public Drawable
{
public:
	//zmienne ponizej beda potrzebne do pokazywania obrazu z odpowiedniego pliku
	Texture texture;
	Sprite fruit;
	void draw(RenderTarget& target, RenderStates state) const override;

	float left();
	float right();
	float top();
	float bottom();

	void appear();
	void disappear();
};

// jednorazowo przydziela graczowi 25 puntkow po zjedzeniu go
class Apple : public Fruit
{
public:
	Apple(float x, float y);
	Apple() = delete;
	~Apple() = default;
};

// odpowiada za podwojenie predkosci pacmana
class Orange : public Fruit
{
public:
	Orange(float x, float y);
	Orange() = delete;
	~Orange() = default;
};

// po zjedzeniu go, przez jakis czas kazdy zjadany punkt jest warty dwoch
class Banana : public Fruit
{
public:
	Banana(float x, float y);
	Banana() = delete;
	~Banana() = default;
};

// odpowiada ona za dwukrotne zmniejszane predkosci duszkow
class Cherry : public Fruit
{
public:
	Cherry(float x, float y);
	Cherry() = delete;
	~Cherry() = default;
};

// odpowiada ona za dwukrotne zmniejszane predkosci pacmana
class Mushroom : public Fruit
{
public:
	Mushroom(float x, float y);
	Mushroom() = delete;
	~Mushroom() = default;
};

// klasa, ktorej obiekt bedzie wyswietlal co sie dzieje po zakonczeniu rozgrywki
class GameOver
{
public:
	GameOver(float x, float y);
	GameOver() = delete;
	~GameOver() = default;
	Font font;
	Text text;
	// funkcje pokazujace osiagniecia gracza podczas ukonczonej rozgrywki 
	void showingTitle(RenderWindow& window, Text text, string title);
	void showingPoints(RenderWindow& window, Text text, int pointsAmount);
	void showingTime(RenderWindow& window, Text text, Time elapsed);
	void showingRecord(RenderWindow& window, Text text, int pointsAmount);
};
void setFruit(Time& periodFruit, bool& collisionPacmanApple, bool& collisionPacmanOrange, bool& collisionPacmanBanana, bool& collisionPacmanCherry, bool& collisionPacmanMushroom, Fruit& apple, Fruit& orange, Fruit& banana, Fruit& cherry, Fruit& mushroom);

string recordFile(int pointsAmount);
void drawFruit(RenderWindow& window, Texture texture, string fruit, float fromTop);