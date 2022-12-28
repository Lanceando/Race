#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;
namespace mt{

    class Car{
    public:
        int x, w, y, h;
        std::string File;
        Texture texture;
        Sprite sprite;


        Car( std::string f, int xx, int yy,  int ww, int hh){ // обявление машины (названия файла(фото), координаты машины, ширина высота)
            File = f;
            x = xx;
            y = yy;
            w = ww;
            h = hh;
            texture.loadFromFile("images/"+File);
            sprite.setTexture(texture);
            sprite.setTextureRect(IntRect(0,0,w,h));
            sprite.setPosition(x,y);
        }

        void Controls(float time) // управление машиной
        {
            Vector2f ca = sprite.getPosition(); // получаем координаты машины

            if (!_kbhit()) // если нет нажатия машина едет прямо
                sprite.setTextureRect(IntRect(0, 0, w, h));
            if (Keyboard::isKeyPressed(Keyboard::Left)) { // если нажата стрелка влево
                if (ca.x > 35) // и машина не заходит за рамки дороги слева, то передвигаем её и берём фото с поворотом
                    sprite.move(-0.5 * time, 0);
                sprite.setTextureRect(IntRect(165, 0, w, h));
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)) { // если нажата стрелка вправо
                if (ca.x < 465) //  и машина не заходит за рамки дороги справа, то передвигаем её и берём фото с поворотом
                    sprite.move(0.5 * time, 0);
                sprite.setTextureRect(IntRect(165 * 2, 0, w, h));
            }


        }

    };

    class Object{
    public:
        int x, w, y, h;
        std::string File;
        Texture texture;
        Sprite sprite;

        Object(std::string F, int xx, int yy, int se) // объявление объекта (имя файла(фото), кординаты, se - рандомное число для рандомного появления на дороге)
        {
            File = F;
            x = xx;
            y = yy;
            se = 0;
            texture.loadFromFile("images/"+File);
            sprite.setTexture(texture);
            sprite.setPosition(x + 100*se, y);
        }

    };


}
