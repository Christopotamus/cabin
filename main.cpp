#include <SFML/Graphics.hpp>
#include "game.h"

#include <vector>
#include <iostream>
#include <SFML/OpenGL.hpp>

using namespace std;

//rand();


int main(){

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Rogue Zombies");

    game g;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }

        }

        glClearColor(0.f, 0.f, 0.f, 0.f);

        glDisable(GL_TEXTURE_2D | GL_DEPTH_TEST);
        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glScalef(1.0f,-1.0f,1.0f);
        glOrtho(0, 1280, 0, 720, -1,1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();


        glClear(GL_COLOR_BUFFER_BIT);
        //window.clear();
        glPushMatrix();
        g.draw();
        glPopMatrix();


        g.update();

        glPopMatrix();

        window.display();
    }
    return 0;
}
