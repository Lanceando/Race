#include <SFML/Graphics.hpp>
#include <conio.h> // чтобы отследить нажата ли клавиша
#include <ctime> // чтобы сделать рандомное число
#include <game.h>

using namespace sf;


int main()
{
    RenderWindow window (VideoMode(650,900), "Race");
    bool game = true;

    Image icon;  // загружаем иконку
    icon.loadFromFile("images/cattouchretcr 1.png");
    window.setIcon(30,20,icon.getPixelsPtr());


    srand(time(NULL)); // для рандомного числа

    Texture trasa; // загружаем дорогу
    trasa.loadFromFile("images/road.png");

    Sprite road(trasa); // загружаем дорогу


    mt::Car car("Group.png", 402, 589,156,300); //создание машины

    int se = rand() % 4; // рандомное число

    mt::Object object("obs.png",50,-100,se); // создание препятсвия

    Clock clock;

    Texture gg; // загружаем фото с окончанием игры
    gg.loadFromFile("images/Frame1.png");

    Sprite gameover(gg);
    gameover.setPosition(-1000,-1000);
    gameover.setColor(sf::Color(sf::Color::Red));

    Texture sc; // загружаем фото с цифрами для счёта
    sc.loadFromFile("images/score.png");
    Sprite score[5]; // массив с фото
    float fs[5];  // доп массив для введения счёта
    for (int i = 0; i < 5; i++) { //заполняем массив спрайтов и доп массив
        score[i].setTexture(sc);
        score[i].setTextureRect(IntRect(0, 0, 44, 55));
        score[i].setPosition(45 * i, 5);
        fs[i] = 0;
    }


    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (game){ // пока игра идёт
            float time = clock.getElapsedTime().asMicroseconds(); // Штука для правлного движения
            clock.restart();
            time = time / 800;

            car.Controls(time); // управляем машины из класса Car


            object.sprite.move(0, 0.7 * time); // объект двигается вниз (по y)
            Vector2f pos_obs = object.sprite.getPosition(); // получаем координаты объекта
            if (pos_obs.y > 910) { // если объект ушёл вниз за поле, то перемещаем его вверх
                se = rand() % 4;
                object.sprite.setPosition(50 + 100 * se, -150);
            }
            if (car.sprite.getGlobalBounds().intersects(object.sprite.getGlobalBounds())) // если объекты столкнулись то завершаем игру
                game = false;

            fs[4] += 0.005; // добавляем очки
            if (fs[4] > 10) {
                fs[4] -= 10;

                fs[3]++;
                if (fs[3] > 9) {
                    fs[3] -= 10;

                    fs[2]++;
                    if (fs[2] > 9) {
                        fs[2] -= 10;

                        fs[1]++;
                        if (fs[1] > 9) {
                            fs[1] -= 10;

                            fs[0]++;
                            if (fs[0] > 9)
                                fs[0] -= 10;
                            score[0].setTextureRect(IntRect(44 * int(fs[0]), 0, 44, 55)); // меняем значение счёта по доп. массиву
                        }
                        score[1].setTextureRect(IntRect(44 * int(fs[1]), 0, 44, 55));
                    }
                    score[2].setTextureRect(IntRect(44 * int(fs[2]), 0, 44, 55));
                }
                score[3].setTextureRect(IntRect(44 * int(fs[3]), 0, 44, 55));
            }
            score[4].setTextureRect(IntRect(44 * int(fs[4]), 0, 44, 55));
        }
        else if(!game){ // если игра = false то показываем спрайт с окончание игры.
            gameover.setPosition(0,0);
        }
        window.clear();
        window.draw(road);
        window.draw(object.sprite);
        window.draw(car.sprite);
        window.draw(gameover);
        for (int i = 0; i < 5; i++) // рисуем счёта
            window.draw(score[i]);
        window.display();
    }

    return 0;
}
