#include <cstdio>
#include <iostream>
#include "user.h"
#include "map.h"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

int main() {

    char inf[10] = { 'l', 'e', 'n', 'a', '\0', 4, 1, 0, 0, 0 };
    int len_inf = 10;
    User Me(inf);

    int data_size = 512;
    char data[512] = { 0, 0 };
    int width = 0;
    int height = 0;
    size_t received;
    unsigned short s_port = 8888;
    unsigned short r_port;
    std::vector<User> users_v;
    std::string ip;


    std::cout << "Input ip adress of srever: ";
    std::cin >> ip;
    sf::UdpSocket socket;
    if (socket.bind(s_port) != sf::Socket::Done) { return -1; }
    sf::IpAddress server(ip);
    socket.setBlocking(1);
    socket.send(inf, len_inf, server, s_port);
    socket.receive(data, data_size, received, server, r_port);


    height = data[0];
    width = data[1];
    Map map(width, height);
    sf::RenderWindow window(sf::VideoMode(width * 100, height * 100), "my game");


    while (1)
    {
        socket.receive(data, data_size, received, server, r_port);

        for (int i = 0; i < width; i++)
            for (int j = 0; j < height; j++)
                map.map[i][j] = data[2 + width * j + i];

        int num_pl = data[2 + width * height];
        int j = 0;
        int start = 2 + map.width * map.height + 1;
        map.Map_draw(window);
        std::cout << "Logins" << std::endl;
        User user_;
        for (int i = start; num_pl != 0; i++)
        {
            user_.name[j++] = data[i];
            if (data[i] == '\0')
            {
                user_.x = data[i + 1];
                user_.y = data[i + 2];
                i += 2;
                std::cout << user_.name << ' ' << user_.x << ' ' << user_.y << std::endl;
                if (user_.name != Me.name)
                    user_.user_draw(window, map);
                users_v.push_back(user_);
                num_pl--;
                j = 0;
                start = i;
            }
        }
        Me.user_draw(window, map);
        window.display();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Me.action(map);

        inf[5] = Me.x;
        inf[6] = Me.y;
        inf[7] = Me.ch_block[0];
        inf[8] = Me.ch_block[1];
        inf[9] = Me.ch_block[2];

        socket.send(inf, len_inf, server, s_port);

        users_v.clear();
    }

    return 0;
}