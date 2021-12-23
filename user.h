#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "map.h"

class User {
private:
    int turn = 1;
public:
    std::string name = "user";
    int x = 1;
    int y = 1;
    char ch_block[3] = { 0,0,0 };
    bool block_ch = 0;

    User() {}
    User(std::string Name) : name(Name) {}
    User(std::string Name, int X, int Y) : name(Name), x(X), y(Y) {}
    User(User const& player) : name(player.name), x(player.x), y(player.y) {}

    void user_draw(sf::RenderWindow& window, Map& map) {
        sf::RectangleShape block(sf::Vector2f(100.f, 100.f));
        sf::Texture pos_wait;
        pos_wait.loadFromFile("Textures/wait.png");
        sf::Texture pos_0;
        pos_0.loadFromFile("Textures/turn0.png");
        sf::Texture pos_1;
        pos_1.loadFromFile("Textures/turn1.png");
        sf::Texture pos_2;
        pos_2.loadFromFile("Textures/turn2.png");

        block.setPosition(100 * (x - 1), 100 * (map.height - y));
        if (turn == -1)
            block.setTexture(&pos_wait);
        if (turn == 0)
            block.setTexture(&pos_0);
        if (turn == 1)
            block.setTexture(&pos_1);
        if (turn == 2)
            block.setTexture(&pos_2);
        window.draw(block);
        sf::Text name_pr;
        sf::Font font;
        font.loadFromFile("Textures/Voracessk.ttf");
        name_pr.setFont(font);
        name_pr.setCharacterSize(12);
        name_pr.setFillColor(sf::Color(255, 0, 0));
        name_pr.setString(name);
        name_pr.setPosition(100 * (x - 1) + 48 - name_pr.getLocalBounds().width / 2, 100 * (map.height - y));
        window.draw(name_pr);

    }




    bool check_move(Map& map, int try_x) {
        if (x + try_x > map.width || x + try_x < 1)
            return 0;
        int k = 0;
        if (map.map[x + try_x - 1][map.height - y] == 0) {
            while ((map.map[x + try_x - 1][map.height - y + 1 + k] == 0) && (y - k != 1)) {
                k++;
            }
            y -= k;
        }
        else {
            while (map.map[x + try_x - 1][map.height - y - k] == 1) {
                if (y + k == map.height)
                    return 0;
                k++;
            }
            y += k;
        }
        x += try_x;
        if (try_x == 1)
            turn = 2;
        else
            turn = 0;
        return 1;
    }


    bool change_blo(Map& map) {
        if (y == map.height) {
            return 0;
        }
        turn = 1;
        ch_block[1] = x - 1;
        ch_block[0] = y;
        ch_block[2] = 1;
        y += 1;
        return 1;
    }



    void action(Map& map) {
        ch_block[0] = 0;
        ch_block[1] = 0;
        ch_block[2] = 0;
        sf::Clock clock;
        double time = 0;
        while (time < 50)
            time = clock.getElapsedTime().asMilliseconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            if (!check_move(map, 1))
                turn = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            if (!check_move(map, -1))
                turn = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            turn = (turn + 1) % 3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (!change_blo(map))
                turn = -1;
        }

    }

};