#include "Klasy.h"

//wzorzec funkcji sprawdzającej czy dochodzi do kolizji między obiektami
template <class T1, class T2> 
bool collisionPacmanGhost(T1& A, T2& B) // ZMIENIĆ NAZWĘ
{
    if ((A.right() >= B.left() && A.left() <= B.right()
        && A.bottom() >= B.top() && A.top() <= B.bottom()) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//
//template <class T1, class T2> bool isIntersecting(T1& A, T2& B)
//{
//    return A.right() >= B.left() && A.left() <= B.right()
//        && A.bottom() >= B.top() && A.top() <= B.bottom();
//}


//bool collisionPacmanGhost(Pacman& packman, Ghost& ghost)
//{
//    if (!isIntersecting(packman, ghost))
//    {
//        return false;
//    }
//    else
//    {
//        return true;
//    }
//}

int main()
{
    bool back = false;

    // Ustawienie domyślnego okna z tytułem Pacman o podanej rozdzielczości
    RenderWindow window{ VideoMode{800,600}, "Pacman" };
    // utworzenie obiektów
    Menu menu(window.getSize().x, window.getSize().y);
    SubMenu subMenu(window.getSize().x, window.getSize().y);
    // aby gameloop działał 60 razy na sekunde
    window.setFramerateLimit(60);
    // dowolne wydarzenie interakcji z użytkownikiem
    Event event;
    int frame{};
    //głowna pętla
    while (true)
    {
        while (window.pollEvent(event))
        {
            Pacman pacman(400, 300);
            Ghost ghost1(200, 100, "red");
            Ghost ghost2(400, 100, "green");
            Ghost ghost3(200, 400, "magenta");
            Ghost ghost4(500, 500, "cyan");
            switch (event.type)
            {
            case Event::KeyReleased:
                // poruszanie się użytkownika w menu startowym
                switch (event.key.code)
                {
                case Keyboard::Up:
                    menu.moveUp(menu.menu, menu.color);
                    break;
                case Keyboard::Down:
                    menu.moveDown(menu.menu, menu.color);
                    break;
                case Keyboard::Return:
                    // w zależności od tego czy wybierzemy play, options lub exit to wykonają się odpowienie czynności
                    switch (menu.getPressedItem())
                    {
                    case 0:
                        std::cout << "Play button" << endl;
                        while (true)
                        {
                            frame++;
                            window.clear(Color::Black);
                            //window.pollEvent(event);
                            if (event.type == Event::Closed)
                            {
                                window.close();
                                break;
                            }
                            // jeśli doszło do kolizji pacmana z którymś duszkiem to wracamy do menu startowego
                            if (collisionPacmanGhost(pacman, ghost1) == true || collisionPacmanGhost(pacman, ghost2) == true
                                || collisionPacmanGhost(pacman, ghost3) == true || collisionPacmanGhost(pacman, ghost4) == true)
                            {
                                break;
                                
                            }
                            //aktualizowanie stanu gry      
                            pacman.update();

                            ghost1.update(frame);
                            ghost2.update(frame);
                            ghost3.update(frame);
                            ghost4.update(frame);

                            //rysowanie obiektów
                            window.draw(pacman);
                            window.draw(ghost1);
                            window.draw(ghost2);
                            window.draw(ghost3);
                            window.draw(ghost4);
                            window.display();
                        }
                        break;
                    case 1:
                        std::cout << "Option button" << endl;
                        while (back != true)
                        {
                            while (window.pollEvent(event))
                            {
                                //window.clear(Color::Black);
                                switch (event.type)
                                {
                                case Event::KeyReleased:
                                    // poruszanie się użytkownika w menu startowym
                                    switch (event.key.code)
                                    {
                                    case Keyboard::Up:
                                        subMenu.moveUp(subMenu.subMenu, subMenu.color);
                                        break;
                                    case Keyboard::Down:
                                        subMenu.moveDown(subMenu.subMenu, subMenu.color);
                                        break;
                                    case Keyboard::Return:
                                        // w zależności od tego czy wybierzemy play, options lub exit to wykonają się odpowienie czynności
                                        switch (subMenu.getPressedItem())
                                        {
                                        case 0:
                                            std::cout << "instrukcje hyhy" << endl;

                                            break;
                                        case 1:
                                            std::cout << "level button hyhy" << endl;
                                            break;
                                        case 2:
                                            std::cout << "wroc do menu" << endl;
                                            back = true;
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
                        back = false;
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