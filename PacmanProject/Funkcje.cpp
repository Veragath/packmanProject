#include "klasy.h"

SoundPlayer::SoundPlayer(string filename)
{
	if (!buffer.loadFromFile(filename))
	{
		cout << "Nie załadowano dzwieku" << endl;
	}
	sound.setBuffer(buffer);
}

void SoundPlayer::play()
{
	sound.play();
}

// konstruktor parametryczny, ktory przydziela informacje o bloczku 
Block::Block(float x, float y, float blockWidth, float blockHeight)
{
	this->blockWidth = blockWidth;
	this->blockHeight = blockHeight;
	shape.setPosition(x, y);
	shape.setSize({ this->blockWidth,this->blockHeight });
	shape.setFillColor(Color{ 60,105,180 });
}

// funkcje, ktore zwracaja najbardziej wychylone punkty na lewo, prawo, gora i dol (funkcje te przydadza sie do kolizji)
float Block::left()
{
	return this->shape.getPosition().x;
}
float Block::right()
{
	return this->shape.getPosition().x + blockWidth;
}
float Block::top()
{
	return this->shape.getPosition().y;
}
float Block::bottom()
{
	return this->shape.getPosition().y + blockHeight;
}
// rysowanie obiektu
void Block::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

//konstruktor przydzielajacy dane o menu
Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("fonts/deltha.ttf"))
	{
		//TU TRZEBA CO� WPISA�
	}

	menu[0].setFont(font);
	menu[0].setFillColor(Color{ 60,105,180 });
	menu[0].setString("Play");
	menu[0].setPosition(Vector2f(width / 2, height / 4 * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("More");
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

// funkcje odpowiadajaca za wyglad menu
void Menu::moveUp(Text text[], string color)
{
	if (selectedItemIndex - 1 >= 0)
	{
		text[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex--;
		if (color == "red")
		{
			text[selectedItemIndex].setFillColor(Color{ 195,85,85 });
		}
		else
		{
			text[selectedItemIndex].setFillColor(Color{ 60,105,180 });
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
			text[selectedItemIndex].setFillColor(Color{ 195,85,85 });
		}
		else
		{
			text[selectedItemIndex].setFillColor(Color{ 60,105,180 });
		}
	}
}


//konstruktor przydzielajacy dane o opcjach
SubMenu::SubMenu(float width2, float height2)
{
	if (!font.loadFromFile("fonts/deltha.ttf"))
	{
		cout << "Niezaladowano czcionki";
	}

	subMenu[0].setFont(font);
	subMenu[0].setFillColor(Color{ 195,85,85 });
	subMenu[0].setString("Instruction");
	subMenu[0].setPosition(Vector2f(width2 / 2, height2 / 4 * 1));

	subMenu[1].setFont(font);
	subMenu[1].setFillColor(Color::White);
	subMenu[1].setString("About us");
	subMenu[1].setPosition(Vector2f(width2 / 2, height2 / 4 * 2));

	subMenu[2].setFont(font);
	subMenu[2].setFillColor(Color::White);
	subMenu[2].setString("Comeback");
	subMenu[2].setPosition(Vector2f(width2 / 2, height2 / 4 * 3));

	selectedItemIndex = 0;
}

// przydzialanie informacji o instrukcji
Information::Information(float width, float height)
{
	//sprawdzenie czy mamy w pliku dana czcionke
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		cout << "Niezaladowano czcionki";
	}

	text.setFont(font);
	text.setCharacterSize(16);
	text.setFillColor(Color::White);
	text.setString("");
}

// pokazywanie instrukcji
void Information::informationShowing(RenderWindow& window, Text text, string filename)
{
	ifstream file(filename);
	string line;
	float fromTop = 6.0;
	if (file.good())
	{
		while (!file.eof())
		{
			getline(file, line);
			text.setString(line);
			text.setPosition(Vector2f(9.0f, fromTop));
			window.draw(text);
			fromTop += 23.0;
		}
		file.close();
	}
	else
	{
		cout << "nie dziala";
	}
	// pokazywanie ponizej instrukcji co nalezy zrobic aby wrocic
	fromTop += 40.0;
	text.setString("Nacisnij 'Esc', aby wrocic");
	text.setStyle(Text::Italic);
	text.setPosition(Vector2f(9.0f, fromTop));
	window.draw(text);
}


//konstruktor przydzielajacy dane o pacmanie
Pacman::Pacman(float x, float y)
{
	if (!texture.loadFromFile("images/pacman.png"))
	{
		cout << "Niezaladowano obrazu";
	}
	pacman.setTexture(texture);
	pacman.setPosition(x, y);
	pacman.setOrigin(this->texture.getSize().x / 2.f, this->texture.getSize().x / 2.f);
}
//renderowanie pacmana
void Pacman::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->pacman, state);
}
// 4 funkcje zwracajace dane o najbardziej wysunetych punktach pacmana
float Pacman::left()
{
	return this->pacman.getPosition().x - texture.getSize().x / 2.f;
}

float Pacman::right()
{
	return this->pacman.getPosition().x + texture.getSize().x / 2.f;
}

float Pacman::top()
{
	return this->pacman.getPosition().y - texture.getSize().y / 2.f;
}

float Pacman::bottom()
{
	return this->pacman.getPosition().y + texture.getSize().y / 2.f;
}
// aktualizacja ruchu pacmana
void Pacman::update(bool collisionPacmanMushroom, Time periodFruit)
{
	this->pacman.move(this->velocity);
	float changeVelocity;
	if (collisionPacmanMushroom == true && periodFruit >= seconds(65)
		&& periodFruit < seconds(80))
	{
		changeVelocity = pacmanVelocity / 2;
	}
	else
	{
		changeVelocity = pacmanVelocity;
	}
	// uzaleznienie kierunku ruchu pacmana od tego co uzytkownik wybierze
	if (Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		velocity.x = -changeVelocity;
		velocity.y = 0;
		pacman.setRotation(180);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		velocity.x = changeVelocity;
		velocity.y = 0;
		pacman.setRotation(0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		velocity.x = 0;
		velocity.y = -changeVelocity;
		pacman.setRotation(270);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
	{
		velocity.x = 0;
		velocity.y = changeVelocity;
		pacman.setRotation(90);
	}
	else
	{
		velocity.x = 0;
		velocity.y = 0;
	}
}
// zwracanie pozycji pacmana
Vector2f Pacman::getPosition()
{
	return pacman.getPosition();
}
//konstruktor przydzielajacy dane o duchach
Ghost::Ghost(float x, float y, string color)
{
	if (color == "red")
	{
		if (!texture.loadFromFile("images/ghostRed.png"))
		{
			cout << "Niezaladowano obrazu";
		}
	}
	else if (color == "green")
	{
		if (!texture.loadFromFile("images/ghostGreen.png"))
		{
			cout << "Niezaladowano obrazu";
		}
	}
	else if (color == "magenta")
	{
		if (!texture.loadFromFile("images/ghostMagenta.png"))
		{
			cout << "Niezaladowano obrazu";
		}
	}
	else if (color == "cyan")
	{
		if (!texture.loadFromFile("images/ghostCyan.png"))
		{
			cout << "Niezaladowano obrazu";
		}
	}/*
	else
	{
		if (!texture.loadFromFile("ghostRed.png"))
		{
			cout << "Niezaladowano obrazu";
		}
	}	*/
	ghost.setTexture(texture);
	ghost.setPosition(x, y);
	ghost.setOrigin(this->texture.getSize().x / 2.f, this->texture.getSize().x / 2.f);
}
//renderowanie duszka
void Ghost::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->ghost, state);
}

// 4 funkcje zwracajace dane o najbardziej wysunietych punktach duchow
float Ghost::left()
{
	return this->ghost.getPosition().x - texture.getSize().x / 2.f;
}

float Ghost::right()
{
	return this->ghost.getPosition().x + texture.getSize().x / 2.f;
}

float Ghost::top()
{
	return this->ghost.getPosition().y - texture.getSize().y / 2.f;
}

float Ghost::bottom()
{
	return this->ghost.getPosition().y + texture.getSize().y / 2.f;
}
/*
Vector2f Ghost::getPosition()
{
	return shape.getPosition();
}*/

//tego chyba nie uzywamy
// aktualizacja ruchu duchow tak aby nie wychodzily poza okno
void Ghost::update()
{

	this->ghost.move(this->velocity);
}

// funckja, ktora zwraca kierunek duszka
int Ghost::whichDirection() // 1 - lewo; 2 - prawo; 3 - gora; 4 - dol
{
	return rand() % 4 + 1;
}

// ustalanie kierunku predkosci pacmana
void Ghost::updateChange(int direction, Time periodFruit, bool collisionPacmanCherry, int level)
{
	this->ghost.move(this->velocity);
	float difference = 0.2 * (level - 1);
	float changeVelocity;
	if (collisionPacmanCherry == true && periodFruit >= seconds(20)
		&& periodFruit < seconds(25))
	{
		changeVelocity = (ghostVelocity / 2) + difference;
	}
	else
	{
		changeVelocity = ghostVelocity + difference;
	}
	if (direction == 1)
	{
		velocity.x = -changeVelocity;
		velocity.y = 0;
	}
	else if (direction == 2)
	{
		velocity.x = changeVelocity;
		velocity.y = 0;
	}

	else if (direction == 3)
	{
		velocity.x = 0;
		velocity.y = -changeVelocity;
	}
	else if (direction == 4)
	{
		velocity.x = 0;
		velocity.y = changeVelocity;
	}
	else
	{
		velocity.x = 0;
		velocity.y = 0;
	}
}

// funkcja sprawdzajaca kolizje miedzy duszkiem a labiryntem
int collisionGhostBlock(Ghost a, Block b, int direction)
{
	if (direction == 1 && a.right() - 7 >= b.left() && a.left() - 7 <= b.right()
		&& a.bottom() >= b.top() && a.top() <= b.bottom())
	{
		return collisionGhostBlock(a, b, rand() % 2 + 3);
	}
	else if (direction == 2 && a.right() + 7 >= b.left() && a.left() + 7 <= b.right()
		&& a.bottom() >= b.top() && a.top() <= b.bottom())
	{
		return collisionGhostBlock(a, b, rand() % 2 + 3);
	}
	else if (direction == 3 && a.right() >= b.left() && a.left() <= b.right()
		&& a.bottom() - 7 >= b.top() && a.top() - 7 <= b.bottom())
	{
		return collisionGhostBlock(a, b, rand() % 2 + 1);
	}
	else if (direction == 4 && a.right() >= b.left() && a.left() <= b.right()
		&& a.bottom() + 7 >= b.top() && a.top() + 7 <= b.bottom())
	{
		return collisionGhostBlock(a, b, rand() % 2 + 1);
	}
	else
	{
		return direction;
	}
}

// konstruktor odpowiadajacy za ustawienie parametrow punktu
Point::Point()
{
	shape.setPosition(22, 22);
	shape.setRadius(this->pointRadius);
	shape.setFillColor(Color::White);
	shape.setOrigin(3.0f, 3.0f);
}

// rysowanie punktu
void Point::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

float Point::left()
{
	return this->shape.getPosition().x - shape.getRadius();
}

float Point::right()
{
	return this->shape.getPosition().x + shape.getRadius();
}

float Point::top()
{
	return this->shape.getPosition().y - shape.getRadius();
}

float Point::bottom()
{
	return this->shape.getPosition().y + shape.getRadius();
}

void Point::changeColor()
{
	shape.setFillColor(Color::Transparent);
}

Panel::Panel(float x, float y)
{
	if (!font.loadFromFile("fonts/deltha.ttf"))
	{
		cout << "Nie zaladowano czcionki";
	}
	text.setFont(font);
	text.setCharacterSize(16);
	text.setLineSpacing(1.5f);
	text.setFillColor(Color::White);
	text.setString("");
	text.setPosition(x, y);
	text.setStyle(Text::Italic);
}

void Panel::showingPoints(RenderWindow& window, Text text, int pointsAmount)
{
	text.setString("Punkty: \n" + to_string(pointsAmount));
	window.draw(text);
}

void Panel::showingTime(RenderWindow& window, Text text, Time elapsed)
{
	int totalSeconds = elapsed.asSeconds();
	int minutes = totalSeconds / 60;
	int seconds = totalSeconds % 60;
	if (seconds >= 0 && seconds < 10)
	{
		text.setString("Czas: \n" + to_string(minutes) + ":0" + to_string(seconds));

	}
	else
	{
		text.setString("Czas: \n" + to_string(minutes) + ":" + to_string(seconds));
	}
	window.draw(text);
}

void Panel::showingLife(RenderWindow& window, Text text)
{
	text.setString("Zycia:");
	window.draw(text);
}

void Panel::showingPower(RenderWindow& window, Text text)
{
	text.setString("Moce:");
	window.draw(text);
}

void Panel::showingLevel(RenderWindow& window, Text text, int level)
{
	text.setString("Poziom: \n" + to_string(level));
	window.draw(text);
}

void Panel::showingRecord(RenderWindow& window, Text text, int pointsAmount)
{
	string record = recordFile(pointsAmount);
	text.setString("Rekord: \n" + record);
	window.draw(text);
}

// za pomoca spritow wyswietlamy pobrany obraz w odpowiednim miejscu
Apple::Apple(float x, float y)
{
	if (!texture.loadFromFile("images/apple.png"))
	{
		cout << "Niezaladowano obrazu";
	}
	fruit.setTexture(texture);
	fruit.setPosition(x, y);
}

Orange::Orange(float x, float y)
{
	if (!texture.loadFromFile("images/orange.png"))
	{
		cout << "Niezaladowano obrazu";
	}
	fruit.setTexture(texture);
	fruit.setPosition(x, y);
}

Banana::Banana(float x, float y)
{
	if (!texture.loadFromFile("images/banana.png"))
	{
		cout << "Niezaladowano obrazu";
	}
	fruit.setTexture(texture);
	fruit.setPosition(x, y);
}

Cherry::Cherry(float x, float y)
{
	if (!texture.loadFromFile("images/cherry.png"))
	{
		cout << "Niezaladowano obrazu";
	}
	fruit.setTexture(texture);
	fruit.setPosition(x, y);
}

Mushroom::Mushroom(float x, float y)
{
	if (!texture.loadFromFile("images/mushroom.png"))
	{
		cout << "Niezaladowano obrazu";
	}
	fruit.setTexture(texture);
	fruit.setPosition(x, y);
}

// funkcja z klasy bazowej, ktora pokazuje poszczegolny owoc
void Fruit::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->fruit, state);
}

float Fruit::left()
{
	return this->fruit.getPosition().x - texture.getSize().x / 2.f;
}

float Fruit::right()
{
	return this->fruit.getPosition().x + texture.getSize().x / 2.f;
}

float Fruit::top()
{
	return this->fruit.getPosition().y - texture.getSize().y / 2.f;
}

float Fruit::bottom()
{
	return this->fruit.getPosition().y + texture.getSize().y / 2.f;
}



/*
Vector2f Fruit::getPosition()
{
	return fruit.getPosition();
}*/


void setFruit(Time& periodFruit, bool& collisionPacmanApple, bool& collisionPacmanOrange, bool& collisionPacmanBanana, bool& collisionPacmanCherry, bool& collisionPacmanMushroom, Fruit& apple, Fruit& orange, Fruit& banana, Fruit& cherry, Fruit& mushroom)
{
	if (periodFruit >= seconds(5) && periodFruit < seconds(17))
	{
		if (collisionPacmanApple == true)
		{
			apple.disappear();
		}
		else
		{
			apple.appear();

		}
		orange.disappear();
		banana.disappear();
		cherry.disappear();
		mushroom.disappear();
	}
	else if (periodFruit >= seconds(20) && periodFruit < seconds(32))
	{
		apple.disappear();
		if (collisionPacmanOrange == true)
		{
			orange.disappear();
		}
		else
		{
			orange.appear();
		}
		banana.disappear();
		cherry.disappear();
		mushroom.disappear();
	}
	else if (periodFruit >= seconds(35) && periodFruit < seconds(48))
	{
		apple.disappear();
		orange.disappear();
		if (collisionPacmanBanana == true)
		{
			banana.disappear();
		}
		else
		{
			banana.appear();
		}
		cherry.disappear();
		mushroom.disappear();
	}
	else if (periodFruit >= seconds(50) && periodFruit < seconds(62))
	{
		apple.disappear();
		orange.disappear();
		banana.disappear();
		mushroom.disappear();
		if (collisionPacmanCherry == true)
		{
			cherry.disappear();
		}
		else
		{
			cherry.appear();
		}
	}
	else if (periodFruit >= seconds(65) && periodFruit < seconds(77))
	{
		apple.disappear();
		orange.disappear();
		banana.disappear();
		cherry.disappear();
		if (collisionPacmanMushroom == true)
		{
			mushroom.disappear();
		}
		else
		{
			mushroom.appear();
		}
	}
	else if (periodFruit >= seconds(80))
	{
		periodFruit = seconds(0);
		collisionPacmanApple = false;
		collisionPacmanOrange = false;
		collisionPacmanBanana = false;
		collisionPacmanCherry = false;
		collisionPacmanMushroom = false;
	}
	else
	{
		apple.disappear();
		orange.disappear();
		banana.disappear();
		cherry.disappear();
		mushroom.disappear();
	}
}
void Fruit::appear()
{
	fruit.setColor(Color::White);
}

void Fruit::disappear()
{
	fruit.setColor(Color::Transparent);
}

GameOver::GameOver(float x, float y)
{
	if (!font.loadFromFile("fonts/deltha.ttf"))
	{
		cout << "Nie zaladowano czcionki";
	}
	text.setFont(font);
	text.setCharacterSize(30);
	text.setLineSpacing(1.2f);
	text.setFillColor(Color::White);
	text.setString("");
	text.setPosition(x, y);
}

void GameOver::showingTitle(RenderWindow& window, Text text, string title)
{
	text.setString(title);
	text.setCharacterSize(50);
	window.draw(text);
}

void GameOver::showingTime(RenderWindow& window, Text text, Time elapsed)
{
	int totalSeconds = elapsed.asSeconds();
	int minutes = totalSeconds / 60;
	int seconds = totalSeconds % 60;
	if (seconds >= 0 && seconds < 10)
	{
		text.setString("Czas Gry: \n" + to_string(minutes) + ":0" + to_string(seconds));

	}
	else
	{
		text.setString("Czas gry: \n" + to_string(minutes) + ":" + to_string(seconds));
	}
	window.draw(text);
}

void GameOver::showingPoints(RenderWindow& window, Text text, int pointsAmount)
{
	text.setString("Punkty: \n" + to_string(pointsAmount));
	window.draw(text);
}

void GameOver::showingRecord(RenderWindow& window, Text text, int pointsAmount)
{
	string record = recordFile(pointsAmount);
	text.setString("Rekord: \n" + record);
	window.draw(text);
}

string recordFile(int pointsAmount)
{
	ifstream fileIn("txt/record.txt");
	int currentRecord;
	if (fileIn.good())
	{
		fileIn >> currentRecord;
		fileIn.close();

		if (currentRecord < pointsAmount)
		{
			ofstream fileOut("txt/record.txt");

			fileOut << pointsAmount;
			currentRecord = pointsAmount;

			fileOut.close();
		}
		return to_string(currentRecord);
	}
	else
	{
		return "blad";
	}
}


