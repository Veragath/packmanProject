#include "klasy.h"
//konstruktor przydzielaj¹cy dane o menu
Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{

	}

	menu[0].setFont(font);
	menu[0].setFillColor(Color::Blue);
	menu[0].setString("Play");
	menu[0].setPosition(Vector2f(width / 2, height / 4 * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(Vector2f(width / 2, height / 4 * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(Vector2f(width / 2, height / 4 * 3));

	selectedItemIndex = 0;
}

void Menu::draw(RenderWindow& window, Text text[])
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(text[i]);
	}
}

void Menu::moveUp(Text text[], string color)
{
	if (selectedItemIndex - 1 >= 0)
	{
		text[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex--;
		if (color == "red")
		{
			text[selectedItemIndex].setFillColor(Color::Red);
		}
		else
		{
			text[selectedItemIndex].setFillColor(Color::Blue);
		}
	}
}

void Menu::moveDown(Text text[], string color)
{
	if (selectedItemIndex + 1 < 3)
	{
		text[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex++;
		if (color == "red")
		{
			text[selectedItemIndex].setFillColor(Color::Red);
		}
		else
		{
			text[selectedItemIndex].setFillColor(Color::Blue);
		}
	}
}


//konstruktor przydzielaj¹cy dane o opcjach
SubMenu::SubMenu(float width2, float height2)
{
	if (!font.loadFromFile("arial.ttf"))
	{

	}

	subMenu[0].setFont(font);
	subMenu[0].setFillColor(Color::Red);
	subMenu[0].setString("Instruction");
	subMenu[0].setPosition(Vector2f(width2 / 2, height2 / 4 * 1));

	subMenu[1].setFont(font);
	subMenu[1].setFillColor(Color::White);
	subMenu[1].setString("Level: easy");
	subMenu[1].setPosition(Vector2f(width2 / 2, height2 / 4 * 2));

	subMenu[2].setFont(font);
	subMenu[2].setFillColor(Color::White);
	subMenu[2].setString("Comeback");
	subMenu[2].setPosition(Vector2f(width2 / 2, height2 / 4 * 3));

	selectedItemIndex = 0;
}
//konstruktor przydzielaj¹cy dane o pacmanie
Pacman::Pacman(float t_X, float t_Y)
{
	shape.setPosition(t_X, t_Y);
	shape.setRadius(this->pacmanRadius);
	shape.setFillColor(Color::Yellow);
	shape.setOrigin(this->pacmanRadius, this->pacmanRadius);
}
//renderowanie pacmana
void Pacman::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}
// 4 funkcje zwracaj¹ce dane o najbardziej wysuniêtych punktach pacmana
float Pacman::left()
{
	return this->shape.getPosition().x - shape.getRadius();
}

float Pacman::right()
{
	return this->shape.getPosition().x + shape.getRadius();
}

float Pacman::top()
{
	return this->shape.getPosition().y - shape.getRadius();
}

float Pacman::bottom()
{
	return this->shape.getPosition().y + shape.getRadius();
}
// aktualizacja ruchu pacmana
void Pacman::update()
{
	this->shape.move(this->velocity);
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && this->left() > 0)
	{
		velocity.x = -pacmanVelocity;
		velocity.y = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->right() < 800)
	{
		velocity.x = pacmanVelocity;
		velocity.y = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Up) && this->top() > 0)
	{
		velocity.x = 0;
		velocity.y = -pacmanVelocity;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down) && this->bottom() < 600)
	{
		velocity.x = 0;
		velocity.y = pacmanVelocity;
	}
	else
	{
		velocity.x = 0;
		velocity.y = 0;
	}
}
Vector2f Pacman::getPosition()
{
	return shape.getPosition();
}
//konstruktor przydzielaj¹cy dane o duchach
Ghost::Ghost(float t_X, float t_Y, string color)
{
	shape.setPosition(t_X, t_Y);
	shape.setSize({ this->ghostWidth, this->ghostHeight });
	if (color == "red")
	{
		shape.setFillColor(Color::Red);
	}
	else if (color == "green")
	{
		shape.setFillColor(Color::Green);
	}
	else if (color == "magenta")
	{
		shape.setFillColor(Color::Magenta);
	}
	else if (color == "cyan")
	{
		shape.setFillColor(Color::Cyan);
	}
	else
	{
		shape.setFillColor(Color::White);
	}
	shape.setOrigin(ghostWidth / 2.f, ghostHeight / 2.f);
}
//renderowanie pacmana
void Ghost::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

// 4 funkcje zwracaj¹ce dane o najbardziej wysuniêtych punktach duchów
float Ghost::left()
{
	return this->shape.getPosition().x - shape.getSize().x / 2.f;
}

float Ghost::right()
{
	return this->shape.getPosition().x + shape.getSize().x / 2.f;
}

float Ghost::top()
{
	return this->shape.getPosition().y - shape.getSize().y / 2.f;
}

float Ghost::bottom()
{
	return this->shape.getPosition().y + shape.getSize().y / 2.f;
}
Vector2f Ghost::getPosition()
{
	return shape.getPosition();
}
// aktualizacja ruchu duchów
void Ghost::update(int frame)
{
	if (frame == 180)
	{
		
	}
	this->shape.move(this->velocity);
	if (this->left() < 0)
	{
		velocity.x = ghostVelocity;
	}
	else if (this->right() > 800)
	{
		velocity.x = -ghostVelocity;
	}

	if (this->top() < 0)
	{
		velocity.y = ghostVelocity;
	}
	else if (this->bottom() > 600)
	{
		velocity.y = -ghostVelocity;
	}
}

