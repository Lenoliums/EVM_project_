#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include "user.h"

class Map {
public:
    int height = 0;
    int width = 0;
    char** map = nullptr;

    Map() {}
    Map(int w, int h) : height(h), width(w) {
        map = new char* [w];
        for (int i = 0; i < w; i++) {
            map[i] = new char[h];
            for (int j = 0; j < h; j++) {
                map[i][j] = 0;
            }
        }
    }
    Map(int w, int h, char** m) : height(h), width(w) {
        map = new char* [w];
        for (int i = 0; i < w; i++) {
            map[i] = new char[h];
            for (int j = 0; j < h; j++) {
                map[i][j] = m[i][j];
            }
        }
    }
    Map(Map const& copy) : Map(copy.width, copy.height, copy.map) {}


    void Map_draw(sf::RenderWindow& window) {
        sf::RectangleShape block(sf::Vector2f(100.f, 100.f));
        sf::Texture sky;
        sky.loadFromFile("Textures/sky.png");
        sf::Texture ground;
        ground.loadFromFile("Textures/ground.png");
        sf::Texture Tground;
        Tground.loadFromFile("Textures/Tground.png");
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                block.setPosition(100 * i, 100 * j);
                if (map[i][j] == 0)
                    block.setTexture(&sky);
                else {
                    if (j != 0) {
                        if (map[i][j - 1] == 0)
                            block.setTexture(&Tground);
                        else
                            block.setTexture(&ground);
                    }
                    if (j == 0)
                        block.setTexture(&Tground);
                }
                window.draw(block);
            }
        }

    }

    ~Map()
    {
        for (int i = 0; i < width; ++i)
            delete[] map[i];
        delete[] map;
    }


};