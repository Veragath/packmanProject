#include "Classes.h"

SoundPlayer::SoundPlayer(string filename)
{
	// pobranie dzwieku
	if (!buffer.loadFromFile(filename))
	{
		cout << "Nie załadowano dzwieku" << endl;
	}
	sound.setBuffer(buffer);
}
// funkcja odpowiadajaca za odtwarzanie
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
		// w przypadku gdy nie uda sie pobrac czcionki wyswietli sie w konsoli domyslny tekst
	}
	// podzielenie naszego menu na 3 czesci
	menu[0].setFont(font);
	menu[0].setFillColor(Color{ 60,105,180 });
	menu[0].setString("Graj");
	menu[0].setPosition(Vector2f(width / 2, height / 4 * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("Wiecej");
	menu[1].setPosition(Vector2f(width / 2, height / 4 * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Wyjscie");
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
		// w zaleznosci od tego gdzie jest uzytkownik to dana opcja podswietla sie
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
// analogiczny konstruktor parametryczny jak dla klasy menu
SubMenu::SubMenu(float width, float height)
{
	if (!font.loadFromFile("fonts/deltha.ttf"))
	{
		// w przypadku gdy nie uda sie pobrac czcionki wyswietli sie w konsoli domyslny tekst
	}

	subMenu[0].setFont(font);
	subMenu[0].setFillColor(Color{ 195,85,85 });
	subMenu[0].setString("Instrukcja");
	subMenu[0].setPosition(Vector2f(width / 2, height / 4 * 1));

	subMenu[1].setFont(font);
	subMenu[1].setFillColor(Color::White);
	subMenu[1].setString("O nas");
	subMenu[1].setPosition(Vector2f(width / 2, height / 4 * 2));

	subMenu[2].setFont(font);
	subMenu[2].setFillColor(Color::White);
	subMenu[2].setString("Powrot");
	subMenu[2].setPosition(Vector2f(width / 2, height / 4 * 3));

	selectedItemIndex = 0;
}

// przydzialanie informacji o instrukcji
Information::Information(float width, float height)
{
	//sprawdzenie czy mamy w pliku dana czcionke
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		// w przypadku gdy nie uda sie pobrac czcionki wyswietli sie w konsoli domyslny tekst
	}

	text.setFont(font);
	text.setCharacterSize(16);
	text.setFillColor(Color::White);
	text.setString("");
}
// wyswietlanie owocow w instrukcji 
void drawFruit(RenderWindow& window, Texture texture, string fruit, float fromTop)
{
	if (!texture.loadFromFile("images/" + fruit + ".png"))
	{
		// w przypadku gdy nie uda sie pobrac obrazu wyswietli sie w konsoli domyslny tekst informujacy o bledzie
	}
	Sprite sprite(texture);
	sprite.setPosition(Vector2f(21.0f, fromTop));
	window.draw(sprite);
}

// pokazywanie instrukcji
void Information::informationShowing(RenderWindow& window, Text text, string filename)
{
	// pokazywanie instrukcji za pomoca odczytu z plikow
	ifstream file(filename);
	string line;
	Texture texture;
	// okreslanie dodatkowej odleglosci od lewej czesci ekranu
	float fromLeftPlus = 0.0;
	float fromTop = 12.0;
	if (file.good())
	{
		while (!file.eof())
		{
			getline(file, line);
			if (line == "jablko")
			{
				drawFruit(window, texture, "apple", fromTop);
				fromLeftPlus = 41.0;
			}
			else if (line == "pomarancza")
			{
				drawFruit(window, texture, "orange", fromTop);
				fromLeftPlus = 41.0;
			}
			else if (line == "banan")
			{
				drawFruit(window, texture, "banana", fromTop);
				fromLeftPlus = 41.0;
			}
			else if (line == "wisnia")
			{
				drawFruit(window, texture, "cherry", fromTop);
				fromLeftPlus = 41.0;
			}
			else if (line == "grzyb")
			{
				drawFruit(window, texture, "mushroom", fromTop);
				fromLeftPlus = 41.0;
			}
			else
			{
				text.setString(line);
				text.setPosition(Vector2f(15.0f + fromLeftPlus, fromTop));
				window.draw(text);
				fromTop += 25.0;
				fromLeftPlus = 0;
			}
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
	// ustawienie czcionki
	text.setStyle(Text::Italic);
	text.setPosition(Vector2f(15.0f, fromTop));
	window.draw(text);
}


//konstruktor przydzielajacy dane o pacmanie
Pacman::Pacman(float x, float y)
{
	if (!texture.loadFromFile("images/pacman.png"))
	{
		
	}
	pacman.setTexture(texture);
	pacman.setPosition(x, y);
	// zmiana punktu odniesienia
	pacman.setOrigin(this->texture.getSize().x / 2.f, this->texture.getSize().x / 2.f);
}
//renderowanie pacmana
void Pacman::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->pacman, state);
}
// 4 funkcje zwracajace dane o najbardziej wysunetych punktach pacmana, pamietajac o tym w lewym gornym rogu znajduje sie punkt (0,0)
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
	//jesli pacman zje grzybka to jego predkosc zmniejsza sie dwukrotnie
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
		// rotacja pacmana aby mial skierowany dziobek w kierunku ruchu
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

		}
	}
	else if (color == "green")
	{
		if (!texture.loadFromFile("images/ghostGreen.png"))
		{

		}
	}
	else if (color == "magenta")
	{
		if (!texture.loadFromFile("images/ghostMagenta.png"))
		{

		}
	}
	else if (color == "cyan")
	{
		if (!texture.loadFromFile("images/ghostCyan.png"))
		{
			
		}
	}
	ghost.setTexture(texture);
	ghost.setPosition(x, y);
	ghost.setOrigin(this->texture.getSize().x / 2.f, this->texture.getSize().x / 2.f);
}
//renderowanie duszka
void Ghost::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->ghost, state);
}

// 4 funkcje zwracajace dane o najbardziej wysunietych punktach duchow, pamietajac o tym w lewym gornym rogu znajduje sie punkt (0,0)
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

// aktualizacja ruchu duchow
void Ghost::update()
{
	this->ghost.move(this->velocity);
}

// funckja, ktora zwraca kierunek duszka
int Ghost::whichDirection() // 1 - lewo; 2 - prawo; 3 - gora; 4 - dol
{
	return rand() % 4 + 1;
}

// ustalanie kierunku predkosci duszka
void Ghost::updateChange(int direction, Time periodFruit, bool collisionPacmanCherry, int level)
{
	this->ghost.move(this->velocity);
	// roznica w predkosci miedzy kolejnymi poziomami
	float difference = 0.2 * (level - 1);
	float changeVelocity;
	// gdy pacman zje wisnie to duszek zmniejsza predkosc dwukrotnie
	if (collisionPacmanCherry == true && periodFruit >= seconds(50)
		&& periodFruit < seconds(62))
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

// funkcja sprawdzajaca potencjalne kolizje miedzy duszkiem a labiryntem
int collisionGhostBlock(Ghost a, Block b, int direction)
{
	if (direction == 1 && a.right() - 7 >= b.left() && a.left() - 7 <= b.right()
		&& a.bottom() >= b.top() && a.top() <= b.bottom())
	{
		// gdy dojdze do potencjalnej kolizji to wtedy zmieniami kierunek predkosci duszka
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
	shape.setRadius(this->pointRadius);
	shape.setFillColor(Color::White);
	shape.setOrigin(3.0f, 3.0f);
}

// rysowanie punktu
void Point::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}
// funkcje zwracajace punkty najbardziej wychylone lewo, prawo, gora i dol, pamietajac o tym w lewym gornym rogu znajduje sie punkt (0,0)
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

// funkcja, ktora zmienia kolor duszku na przezroczysty (przyda sie ona do systemu kolizji)
void Point::changeColor()
{
	shape.setFillColor(Color::Transparent);
}

// przydzielanie informacji o panelu
Panel::Panel(float x, float y)
{
	if (!font.loadFromFile("fonts/deltha.ttf"))
	{
		// w przypadku gdy nie uda sie pobrac czcionki wyswietli sie w konsoli domyslny tekst
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
	// ustawienie tekstu
	text.setString("Punkty: \n" + to_string(pointsAmount));
	// wyswietlanie tego tekstu w odpowiednim miejscu
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
		// w przypadku gdy nie uda sie pobrac obrazu wyswietli sie w konsoli domyslny tekst
	}
	fruit.setTexture(texture);
	fruit.setPosition(x, y);
}

Orange::Orange(float x, float y)
{
	if (!texture.loadFromFile("images/orange.png"))
	{
		// w przypadku gdy nie uda sie pobrac obrazu wyswietli sie w konsoli domyslny tekst
	}
	fruit.setTexture(texture);
	fruit.setPosition(x, y);
}

Banana::Banana(float x, float y)
{
	if (!texture.loadFromFile("images/banana.png"))
	{
		// w przypadku gdy nie uda sie pobrac obrazu wyswietli sie w konsoli domyslny tekst
	}
	fruit.setTexture(texture);
	fruit.setPosition(x, y);
}

Cherry::Cherry(float x, float y)
{
	if (!texture.loadFromFile("images/cherry.png"))
	{
		// w przypadku gdy nie uda sie pobrac obrazu wyswietli sie w konsoli domyslny tekst
	}
	fruit.setTexture(texture);
	fruit.setPosition(x, y);
}

Mushroom::Mushroom(float x, float y)
{
	if (!texture.loadFromFile("images/mushroom.png"))
	{
		// w przypadku gdy nie uda sie pobrac obrazu wyswietli sie w konsoli domyslny tekst
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

// funkcja odpowiadajaca za wyswietlanie owocow na planszy w zaleznosci od momentu rozgrywki oraz czy nastapila kolizja z owocem
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
	// ustawienie poczatkowego stanu rozgrywki po uplywie 80 sekund
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
// funkcje odpowiadajace za wyswietlanie lub ustawwienie owocow na kolor przezroczysty (wtedy owoc nie bierze udzialu w grze) 
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

// funkcja zapisujaca i odczytujaca z pliku najlepszy wynik
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