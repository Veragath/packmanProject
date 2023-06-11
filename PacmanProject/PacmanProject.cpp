#include "Klasy.h"
#include <chrono>
#include <thread>

//wzorzec funkcji sprawdzaj�cej czy dochodzi do kolizji mi�dzy obiektami
template <class T1, class T2>
bool collision(T1& A, T2& B) // ZMIENI� NAZW�
{
    if ((A.right() >= B.left() && A.left() <= B.right()
        && A.bottom() >= B.top() && A.top() <= B.bottom()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    
    //tworzymy tablice, ktora przechowuje bloczki, ktore skladaja sie na labirynt
    
    Block tableBlocks[blocksAmount] = {
     Block(0, 0, 650.0f, 10.0f),
    Block(0, 610, 650.0f, 10.0f),
    Block(650, 0, 10.0f, 620.0f),
    Block(0, 10, 10.0f, 600.0f),

    Block(35, 35, 63.0f, 39.0f),
    Block(35, 99, 63.0f, 23.0f),
    Block(123, 35, 85.0f, 39.0f),
    Block(233, 10, 19.0f, 64.0f),
    Block(277, 35, 85.0f, 39.0f),
    Block(387, 35, 63.0f, 39.0f),
    Block(475, 10, 19.0f, 64.0f),
    Block(519, 35, 63.0f, 39.0f),
    Block(607, 35, 18.0f, 39.0f),
    Block(35, 147, 63.0f, 23.0f),
    Block(123, 99, 19.0f, 103.0f),
    Block(140, 147, 68.0f, 23.0f),
    Block(167, 99, 151.0f, 23.0f),
    Block(35, 195, 63.0f, 7.0f),
    Block(35, 227, 63.0f, 10.0f),
    Block(10, 288, 88.0f, 10.0f),
    Block(86, 237, 12.0f, 51.0f),
    Block(10, 323, 88.0f, 10.0f),
    Block(35, 384, 63.0f, 10.0f),
    Block(86, 333, 12.0f, 51.0f),
    Block(35, 419, 63.0f, 23.0f),
    Block(10, 467, 40.0f, 10.0f),
    Block(79, 435, 19.0f, 42.0f),
    Block(35, 499, 173.0f, 23.0f),
    Block(35, 547, 63.0f, 38.0f),
    Block(123, 227, 20.0f, 71.0f),
    Block(123, 323, 20.0f, 71.0f),
    Block(123, 419, 60.0f, 23.0f),
    Block(123, 467, 20.0f, 35.0f),
    Block(233, 122, 19.0f, 48.0f),
    Block(343, 99, 19.0f, 103.0f),
    Block(277, 147, 66.0f, 23.0f),
    Block(565, 227, 60.0f, 10.0f),
    Block(565, 288, 85.0f, 10.0f),
    Block(565, 323, 85.0f, 10.0f),
    Block(565, 384, 60.0f, 10.0f),
    Block(565, 237, 12.0f, 51.0f),
    Block(565, 333, 12.0f, 51.0f),
    Block(123, 547, 85.0f, 38.0f),
    Block(233, 547, 41.0f, 38.0f),
    Block(299, 547, 129.0f, 38.0f),
    Block(453, 547, 107.0f, 38.0f),
    Block(585, 547, 40.0f, 38.0f),
    Block(453, 499, 172.0f, 23.0f),
    Block(610, 467, 40.0f, 10.0f),
    Block(565, 419, 60.0f, 23.0f),
    Block(565, 435, 20.0f, 42.0f),
    Block(475, 419, 63.0f, 23.0f),
    Block(520, 467, 20.0f, 35.0f),
    Block(165, 467, 130.0f, 10.0f),
    Block(233, 467, 19.0f, 55.0f),
    Block(277, 499, 151.0f, 23.0f),
    Block(320, 467, 20.0f, 35.0f),
    Block(365, 467, 130.0f, 10.0f),
    Block(610, 99, 15.0f, 39.0f),
    Block(387, 99, 151.0f, 23.0f),
    Block(387, 147, 19.0f, 55.0f),
    Block(390, 195, 82.0f, 7.0f),
    Block(431, 122, 41.0f, 48.0f),
    Block(563, 99, 19.0f, 103.0f),
    Block(610, 163, 15.0f, 39.0f),
    Block(520, 227, 20.0f, 71.0f),
    Block(520, 323, 20.0f, 71.0f),
    Block(167, 195, 151.0f, 7.0f),
    Block(167, 227, 19.0f, 71.0f),
    Block(299, 227, 19.0f, 71.0f),
    Block(211, 227, 63.0f, 71.0f),
    Block(299, 323, 105.0f, 71.0f),
    Block(385, 330, 10.0f, 40.0f),
    Block(167, 323, 19.0f, 71.0f),
    Block(211, 323, 63.0f, 23.0f),
    Block(211, 371, 63.0f, 23.0f),
    Block(211, 419, 63.0f, 23.0f),
    Block(299, 419, 105.0f, 23.0f),
    Block(431, 323, 19.0f, 121.0f),
    Block(475, 323, 19.0f, 71.0f),
    Block(343, 275, 107.0f, 23.0f),
    Block(343, 227, 19.0f, 50.0f),
    Block(475, 227, 19.0f, 71.0f),
    Block(387, 227, 63.0f, 23.0f),
    Block(211, 323, 63.0f, 20.0f),
    Block(497, 147, 41.0f, 55.0f)
    };
    Point tablePoints[29 * 37] = {};

    bool collisionPacmanApple = false;
    bool collisionPacmanOrange = false;
    bool collisionPacmanBanana = false;
    bool collisionPacmanCherry = false;
    bool collisionPacmanMushroom = false;

    int pointIndex = 0;
    //petla, ktora dodaje do tablicy punkty
    for (int i = 22; i < 650; i += 22)
    {
        for (int j = 22; j < 600; j += 16)
        {
            tablePoints[pointIndex++].shape.setPosition(i, j);
        }
    }

    bool collisionPackmanBlock;

    // ponizsze odpowiadaja za mierzenie czasu
    Clock clockElapsed;
    Clock clockGhost;
    Clock clockFruit;
    Time periodGhost = seconds(0);
    Time periodFruit = seconds(0);
    Time elapsed;

    srand(time(NULL));

    //zmienne potrzebne dla menu
    bool backToMenu = false;
    bool backToSubmenu = false;

    // Ustawienie domy�lnego okna z tytu�em Pacman o podanej rozdzielczo�ci
    RenderWindow window{ VideoMode{windowWith, windowHeight}, "Pacman" };
    // utworzenie obiekt�w


    Image logo;
    if (!logo.loadFromFile("images/pacman.png"))
    {

    }

    window.setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());

    SoundPlayer soundPoint("sounds/point.wav");
    SoundPlayer soundFruit("sounds/fruit.wav");
    SoundPlayer soundEnd("sounds/end.wav");
    Menu menu(window.getSize().x, window.getSize().y);
    SubMenu subMenu(window.getSize().x, window.getSize().y);
    Information instruction(window.getSize().x, window.getSize().y);
    Information aboutUs(window.getSize().x, window.getSize().y);

    Panel panelPoints(680, 50);
    Panel panelTimeElapsed(680, 140);
    Panel panelLifeAmount(680, 230);
    Panel panelPower(680, 320);
    Panel panelLevel(680, 410);
    Panel panelRecord(680, 500);
    Pacman pacmanLife[3] =
    {
        Pacman(690, 270),
        Pacman(715, 270),
        Pacman(740, 270)
    };
    Apple applePanel(680, 350);
    Orange orangePanel(702, 350);
    Banana bananaPanel(724, 350);
    Cherry cherryPanel(746, 350);
    Mushroom mushroomPanel(768, 350);

    GameOver gameOverTitle(250, 50);
    GameOver gameOverPoints(250, 180);
    GameOver gameOverTime(250, 300);
    GameOver gameOverRecord(250, 420);

    // aby gameloop dzia�a� 60 razy na sekunde
    window.setFramerateLimit(60);
    // dowolne wydarzenie interakcji z u�ytkownikiem
    Event event;
    //zmienne potrzebne dla poruszania sie duszka
    int directionGhost1 = 1;
    int directionGhost2 = 1;
    int directionGhost3 = 1;
    int directionGhost4 = 1;
    int pointsAmount = 0;
    int onlyPoints = 0;
    int level = 0;
    // liczba zyc
    int life = 3;
    //g�owna p�tla
    Pacman pacman(325, 308);
    Ghost ghost1(25, 20, "red");
    Ghost ghost2(25, 595, "green");
    Ghost ghost3(640, 20, "magenta");
    Ghost ghost4(640, 595, "cyan");

    Apple apple(100, 60);
    Orange orange(13, 92);
    Banana banana(58, 77);
    Cherry cherry(158, 77);
    Mushroom mushroom(178, 77);

    applePanel.fruit.setColor(Color(255, 255, 255, 100));
    orangePanel.fruit.setColor(Color(255, 255, 255, 100));
    bananaPanel.fruit.setColor(Color(255, 255, 255, 100));
    cherryPanel.fruit.setColor(Color(255, 255, 255, 100));
    mushroomPanel.fruit.setColor(Color(255, 255, 255, 100));
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
        while (window.pollEvent(event))
        {

            // utworzenie obiektow 
            switch (event.type)
            {
            case Event::KeyReleased:
                // poruszanie si� u�ytkownika w menu startowym
                switch (event.key.code)
                {
                case Keyboard::Up:
                    menu.moveUp(menu.menu, menu.color);
                    break;
                case Keyboard::Down:
                    menu.moveDown(menu.menu, menu.color);
                    break;
                case Keyboard::Return:
                    // w zale�no�ci od tego czy wybierzemy play, options lub exit to wykonaj� si� odpowienie czynno�ci
                    switch (menu.getPressedItem())
                    {
                    case 0:
                        std::cout << "Play button" << endl;


                        for (int i = 0; i < 29 * 37; i++)
                        {
                            tablePoints[i].shape.setFillColor(Color::White);

                            for (int j = 0; j < blocksAmount; j++)
                            {
                                // w przypadku gdy dochodzi do kolizji punktu z labiryntem to zmieniamy kolor punktu na przezroczysty
                                if (collision(tablePoints[i], tableBlocks[j]) == true)
                                {
                                    tablePoints[i].changeColor();
                                }
                            }
                        }

                        //(zeby owoce pokazywaly sie od nowa)
                        clockElapsed.restart();
                        periodFruit = seconds(0);

                        pointsAmount = 0;
                        life = 3;

                        for (int i = 0; i < 3; i++)
                        {
                            pacmanLife[i].pacman.setColor(Color::White);
                        }

                        while (backToMenu != true)
                        {
                            collisionPackmanBlock = false;

                            setFruit(periodFruit, collisionPacmanApple, collisionPacmanOrange, collisionPacmanBanana, collisionPacmanCherry, collisionPacmanMushroom, apple, orange, banana, cherry, mushroom);


                            window.clear(Color::Black);
                            if (event.type == Event::Closed)
                            {
                                window.close();
                                break;
                            }
                            // je�li dosz�o do kolizji pacmana z kt�rym� duszkiem
                            if (collision(pacman, ghost1) == true || collision(pacman, ghost2) == true
                                || collision(pacman, ghost3) == true || collision(pacman, ghost4) == true)
                            {
                                soundEnd.play();
                                pacman.pacman.setPosition(325, 308);
                                pacman.pacman.setRotation(0);
                                ghost1.ghost.setPosition(25, 20);
                                ghost2.ghost.setPosition(25, 595);
                                ghost3.ghost.setPosition(640, 20);
                                ghost4.ghost.setPosition(640, 595);
                                life--;
                                pacmanLife[life].pacman.setColor(Color(255, 255, 255, 100));
                                cout << life;
                                if (life == 0)
                                {
                                    while (backToMenu != true)
                                    {
                                        while (window.pollEvent(event))
                                        {
                                            switch (event.type)
                                            {
                                            case Event::KeyReleased:
                                                switch (event.key.code)
                                                {
                                                case Keyboard::Enter:
                                                    backToMenu = true;
                                                    break;
                                                }
                                                break;
                                            case Event::Closed:
                                                window.close();
                                                break;
                                            }
                                        }

                                        window.clear(Color::Black);
                                        
                                        gameOverTitle.showingTitle(window, gameOverTitle.text, "Game Over");                                        
                                        gameOverPoints.showingPoints(window, gameOverPoints.text, pointsAmount);
                                        gameOverTime.showingTime(window, gameOverTime.text, elapsed);
                                        gameOverRecord.showingRecord(window, gameOverRecord.text, pointsAmount);

                                        window.display();
                                    }
                                }
                            }

                            //sprawdzanie czy nie dojdzie do kolziji pacmana z bloczkiem w zaleznosci od ruchu uzytkownika
                            for (int i = 0; i < blocksAmount; i++)
                            {
                                if (Keyboard::isKeyPressed(Keyboard::Key::Right))
                                {
                                    if ((pacman.right() + 5) >= tableBlocks[i].left() && (pacman.left() + 5) <= tableBlocks[i].right()
                                        && pacman.bottom() >= tableBlocks[i].top() && pacman.top() <= tableBlocks[i].bottom())
                                    {
                                        collisionPackmanBlock = true;
                                        break;
                                    }

                                }
                                else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
                                {
                                    if ((pacman.right() - 5) >= tableBlocks[i].left() && pacman.left() - 5 <= tableBlocks[i].right()
                                        && pacman.bottom() >= tableBlocks[i].top() && pacman.top() <= tableBlocks[i].bottom())
                                    {
                                        collisionPackmanBlock = true;
                                        break;
                                    }

                                }
                                else if (Keyboard::isKeyPressed(Keyboard::Key::Up))
                                {
                                    if ((pacman.right()) >= tableBlocks[i].left() && pacman.left() <= tableBlocks[i].right()
                                        && pacman.bottom() - 5 >= tableBlocks[i].top() && pacman.top() - 5 <= tableBlocks[i].bottom())
                                    {
                                        collisionPackmanBlock = true;
                                        break;
                                    }

                                }
                                else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
                                {
                                    if ((pacman.right()) >= tableBlocks[i].left() && pacman.left() <= tableBlocks[i].right()
                                        && pacman.bottom() + 5 >= tableBlocks[i].top() && pacman.top() + 5 <= tableBlocks[i].bottom())
                                    {
                                        collisionPackmanBlock = true;
                                        break;
                                    }

                                }
                            }
                            periodFruit += clockFruit.restart();
                            if (apple.fruit.getColor() != Color::Transparent && collision(pacman, apple) == true)
                            {
                                collisionPacmanApple = true;
                                soundFruit.play();
                                pointsAmount = pointsAmount + 25;
                                applePanel.fruit.setColor(Color::White);
                            }
                            if (periodFruit >= seconds(20) && collisionPacmanApple == true)
                            {
                                collisionPacmanApple = false;
                                applePanel.fruit.setColor(Color(255, 255, 255, 100));
                            }

                            if (orange.fruit.getColor() != Color::Transparent && collision(pacman, orange) == true)
                            {
                                collisionPacmanOrange = true;
                                orangePanel.fruit.setColor(Color::White);
                                soundFruit.play();
                            }
                            if (periodFruit >= seconds(35) && collisionPacmanOrange == true)
                            {
                                collisionPacmanOrange = false;
                                orangePanel.fruit.setColor(Color(255, 255, 255, 100));
                            }
                            if (banana.fruit.getColor() != Color::Transparent && collision(pacman, banana) == true)
                            {
                                collisionPacmanBanana = true;
                                bananaPanel.fruit.setColor(Color::White);
                                soundFruit.play();
                            }
                            if (periodFruit >= seconds(50) && collisionPacmanBanana == true)
                            {
                                collisionPacmanBanana = false;
                                bananaPanel.fruit.setColor(Color(255, 255, 255, 100));
                            }
                            if (cherry.fruit.getColor() != Color::Transparent && collision(pacman, cherry) == true)
                            {
                                collisionPacmanCherry = true;
                                cherryPanel.fruit.setColor(Color::White);
                                soundFruit.play();
                            }
                            if (periodFruit >= seconds(65) && collisionPacmanCherry == true)
                            {
                                collisionPacmanCherry = false;
                                cherryPanel.fruit.setColor(Color(255, 255, 255, 100));
                            }
                            if (mushroom.fruit.getColor() != Color::Transparent && collision(pacman, mushroom) == true)
                            {
                                collisionPacmanMushroom = true;
                                mushroomPanel.fruit.setColor(Color::White);
                                soundFruit.play();
                            }
                            if (periodFruit >= seconds(80) && collisionPacmanMushroom == true)
                            {
                                collisionPacmanMushroom = false;
                                mushroomPanel.fruit.setColor(Color(255, 255, 255, 100));
                            }

                            //aktualizowanie stanu gry
                            if (collisionPackmanBlock == false)
                            {
                                pacman.update(collisionPacmanMushroom, periodFruit);
                            }

                            periodGhost += clockGhost.restart();

                            // zmienianie ruchu duszkow co sekunde
                            if (periodGhost >= seconds(1))
                            {
                                directionGhost1 = ghost1.whichDirection();
                                directionGhost2 = ghost2.whichDirection();
                                directionGhost3 = ghost3.whichDirection();
                                directionGhost4 = ghost4.whichDirection();

                                periodGhost = seconds(0);
                            }
                            for (int i = 0; i < blocksAmount; i++)
                            {
                                directionGhost1 = collisionGhostBlock(ghost1, tableBlocks[i], directionGhost1);
                                directionGhost2 = collisionGhostBlock(ghost2, tableBlocks[i], directionGhost2);
                                directionGhost3 = collisionGhostBlock(ghost3, tableBlocks[i], directionGhost3);
                                directionGhost4 = collisionGhostBlock(ghost4, tableBlocks[i], directionGhost4);
                            }

                            ghost1.updateChange(directionGhost1, periodFruit, collisionPacmanCherry, level);
                            ghost2.updateChange(directionGhost2, periodFruit, collisionPacmanCherry, level);
                            ghost3.updateChange(directionGhost3, periodFruit, collisionPacmanCherry, level);
                            ghost4.updateChange(directionGhost4, periodFruit, collisionPacmanCherry, level);

                            for (int i = 0; i < blocksAmount; i++)
                            {
                                window.draw(tableBlocks[i]);
                            }

                            if (collisionPacmanOrange == true)
                            {
                                for (int i = 0; i < blocksAmount; i++)
                                {
                                    if (Keyboard::isKeyPressed(Keyboard::Key::Right))
                                    {
                                        if ((pacman.right() + 10) >= tableBlocks[i].left() && (pacman.left() + 10) <= tableBlocks[i].right()
                                            && pacman.bottom() >= tableBlocks[i].top() && pacman.top() <= tableBlocks[i].bottom())
                                        {
                                            collisionPackmanBlock = true;
                                            break;
                                        }

                                    }
                                    else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
                                    {
                                        if ((pacman.right() - 10) >= tableBlocks[i].left() && pacman.left() - 10 <= tableBlocks[i].right()
                                            && pacman.bottom() >= tableBlocks[i].top() && pacman.top() <= tableBlocks[i].bottom())
                                        {
                                            collisionPackmanBlock = true;
                                            break;
                                        }

                                    }
                                    else if (Keyboard::isKeyPressed(Keyboard::Key::Up))
                                    {
                                        if ((pacman.right()) >= tableBlocks[i].left() && pacman.left() <= tableBlocks[i].right()
                                            && pacman.bottom() - 10 >= tableBlocks[i].top() && pacman.top() - 10 <= tableBlocks[i].bottom())
                                        {
                                            collisionPackmanBlock = true;
                                            break;
                                        }

                                    }
                                    else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
                                    {
                                        if ((pacman.right()) >= tableBlocks[i].left() && pacman.left() <= tableBlocks[i].right()
                                            && pacman.bottom() + 10 >= tableBlocks[i].top() && pacman.top() + 10 <= tableBlocks[i].bottom())
                                        {
                                            collisionPackmanBlock = true;
                                            break;
                                        }

                                    }
                                }
                                if (collisionPackmanBlock == false)
                                {
                                    pacman.update(collisionPacmanMushroom, periodFruit);
                                }
                            }
                            cout << level << endl;
                            if (level >= 10)
                            {
                                while (backToMenu != true)
                                {
                                    while (window.pollEvent(event))
                                    {
                                        switch (event.type)
                                        {
                                        case Event::KeyReleased:
                                            switch (event.key.code)
                                            {
                                            case Keyboard::Enter:
                                                backToMenu = true;
                                                break;
                                            }
                                            break;
                                        case Event::Closed:
                                            window.close();
                                            break;
                                        }
                                    }

                                    window.clear(Color::Black);

                                    gameOverTitle.showingTitle(window, gameOverTitle.text, "Wygrales");
                                    gameOverPoints.showingPoints(window, gameOverPoints.text, pointsAmount);
                                    gameOverTime.showingTime(window, gameOverTime.text, elapsed);
                                    gameOverRecord.showingRecord(window, gameOverRecord.text, pointsAmount);

                                    window.display();
                                }
                            }

                            if ((onlyPoints % 553) == 0)
                            {
                                level++;
                            }
                            for (int i = 0; i < 29 * 37; i++)
                            {
                                if (collision(tablePoints[i], pacman) == true &&
                                    tablePoints[i].shape.getFillColor() != Color::Transparent)
                                {
                                    if (collisionPacmanBanana == true)
                                    {
                                        pointsAmount++;
                                    }
                                    soundPoint.play();
                                    pointsAmount++;
                                    onlyPoints++;
                                    tablePoints[i].changeColor();
                                }

                                if ((onlyPoints % 553) == 0)
                                {
                                    tablePoints[i].shape.setFillColor(Color::White);
                                    for (int j = 0; j < blocksAmount; j++)
                                    {
                                        // w przypadku gdy dochodzi do kolizji punktu z labiryntem to zmieniamy kolor punktu na przezroczysty
                                        if (collision(tablePoints[i], tableBlocks[j]) == true)
                                        {
                                            tablePoints[i].changeColor();
                                        }
                                    }
                                }                                                     
                                window.draw(tablePoints[i]);

                            }

                            //rysowanie obiekt�w
                            window.draw(pacman);
                            window.draw(ghost1);
                            window.draw(ghost2);
                            window.draw(ghost3);
                            window.draw(ghost4);

                            window.draw(apple);
                            window.draw(orange);
                            window.draw(banana);
                            window.draw(cherry);
                            window.draw(mushroom);

                            panelPoints.showingPoints(window, panelPoints.text, pointsAmount);
                            elapsed = clockElapsed.getElapsedTime();
                            panelTimeElapsed.showingTime(window, panelTimeElapsed.text, elapsed);
                            panelLifeAmount.showingLife(window, panelLifeAmount.text);
                            for (int i = 0; i < 3; i++)
                            {
                                window.draw(pacmanLife[i]);
                            }
                            panelPower.showingPower(window, panelPower.text);
                            window.draw(applePanel);
                            window.draw(orangePanel);
                            window.draw(bananaPanel);
                            window.draw(cherryPanel);
                            window.draw(mushroomPanel);
                            panelLevel.showingLevel(window, panelLevel.text, level);
                            panelRecord.showingRecord(window, panelRecord.text, pointsAmount);

                            window.display();
                        }
                        backToMenu = false;
                        break;
                    case 1:
                        std::cout << "Option button" << endl;
                        while (backToMenu != true)
                        {
                            while (window.pollEvent(event))
                            {
                                //window.clear(Color::Black);
                                switch (event.type)
                                {
                                case Event::KeyReleased:
                                    // poruszanie si� u�ytkownika w podmenu
                                    switch (event.key.code)
                                    {
                                    case Keyboard::Escape:
                                        backToMenu = true;
                                        break;
                                    case Keyboard::Up:
                                        subMenu.moveUp(subMenu.subMenu, subMenu.color);
                                        break;
                                    case Keyboard::Down:
                                        subMenu.moveDown(subMenu.subMenu, subMenu.color);
                                        break;
                                    case Keyboard::Return:
                                        // w zale�no�ci od tego czy wybierzemy play, options lub exit to wykonaj� si� odpowienie czynno�ci
                                        switch (subMenu.getPressedItem())
                                        {
                                        case 0:
                                            std::cout << "instrukcje hyhy" << endl;
                                            while (backToSubmenu != true)
                                            {
                                                while (window.pollEvent(event))
                                                {
                                                    switch (event.type)
                                                    {
                                                    case Event::KeyReleased:
                                                        switch (event.key.code)
                                                        {
                                                        case Keyboard::Escape:
                                                            backToSubmenu = true;
                                                            break;
                                                        }
                                                        break;
                                                    case Event::Closed:
                                                        window.close();
                                                        break;
                                                    }
                                                }

                                                window.clear(Color::Black);

                                                instruction.informationShowing(window, instruction.text, "txt/instruction.txt");
                                                window.display();
                                            }
                                            backToSubmenu = false;
                                            break;
                                        case 1:
                                            cout << "o nas hyhy" << endl;
                                            while (backToSubmenu != true)
                                            {
                                                while (window.pollEvent(event))
                                                {
                                                    switch (event.type)
                                                    {
                                                    case Event::KeyReleased:
                                                        switch (event.key.code)
                                                        {
                                                        case Keyboard::Escape:
                                                            backToSubmenu = true;
                                                            break;
                                                        }
                                                        break;
                                                    case Event::Closed:
                                                        window.close();
                                                        break;
                                                    }
                                                }

                                                window.clear(Color::Black);

                                                aboutUs.informationShowing(window, instruction.text, "txt/aboutUs.txt");
                                                window.display();
                                            }
                                            backToSubmenu = false;
                                            break;
                                        case 2:
                                            std::cout << "wroc do menu" << endl;
                                            backToMenu = true;
                                            break;
                                        }
                                        break;
                                    }
                                    break;
                                case Event::Closed:
                                    window.close();
                                    break;
                                }
                            }

                            window.clear(Color::Black);

                            subMenu.draw(window, subMenu.subMenu);
                            window.display();
                        }
                        backToMenu = false;
                        break;
                    case 2:
                        window.close();
                        break;
                    }
                    break;
                }
                break;
            case Event::Closed:
                window.close();
                break;
            }
        }
        window.clear(Color::Black);

        menu.draw(window, menu.menu);
        window.display();
    }
}
