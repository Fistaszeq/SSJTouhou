#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string.h>
#include <random>

/*
- - - - - - - - - - -
Author: Fistaszeq
- - - - - - - - - - - 
*/
// Schowek
float speed = 1.5;


// Resolution and title
std::vector<int> res = {800,600};
std::string title = "Touhou";
//

// Object with x and y. Also path to image.
struct obiekty
{
    float x;
    float y;
    std::string scieszka_grafiki;
};
// // //






// Function to manimpulate object +- xy move
// # Oraz Kolizje z ramkami okna, ramy wspiane na sztywno bo res[] nie gloablny
void sterowanie_obiekt(obiekty &gracz)
{
    // Size of image
    sf::Texture obrazek;
    obrazek.loadFromFile(gracz.scieszka_grafiki);
    sf::Vector2u size = obrazek.getSize();
    // // //


    // Moving
    float move = 3;    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) and gracz.x >= 0)
    {
        gracz.x -= move;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) and gracz.x <= res[0] - size.x)
    {
        gracz.x += move;
    }
    
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and gracz.y <= res[1] - size.y)
    {
        gracz.y += move;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) and gracz.y >= 0)
    {
        gracz.y -= move;
    } 
    // // //
}
// randint
int randint(int min,int max)
{
    // Źródło losowości
    std::random_device rd;
    std::mt19937 gen(rd()); // <- Generator

    std::uniform_int_distribution<> dist(min,max); // Zakres
    int r = dist(gen);// Zapakowanie w zmienną
    return r;
}
// // //


int main()
{   
    // Okno root 
    sf::RenderWindow root(sf::VideoMode(res[0],res[1]),title);
    // // // 

    // Frame rate -> 60
    root.setFramerateLimit(60);
    // // // 

    // Tworzymy gracza po srodku mapy
    obiekty gracz;
    gracz.x = res[0] / 2;
    gracz.y = res[1] / 2 + 100;
    gracz.scieszka_grafiki = "white_roock.png";

    sf::Texture player_texture;
    player_texture.loadFromFile(gracz.scieszka_grafiki);

    sf::Sprite player_sprite;
    player_sprite.setTexture(player_texture);
    player_sprite.setPosition(gracz.x,gracz.y);
    // // //

    // Przeszkody.
    std::vector<obiekty> przeszkody_obiekt = {};
    int przeszkody_ilosc = randint(50,150); // 50-150 przeszkod
    for(int i = 0;i<przeszkody_ilosc; i++)
    {
        obiekty skala;
        skala.x = randint(0,res[0]);
        skala.y = -1 *(i * 30 + randint(0,100)) + 400;
        przeszkody_obiekt.push_back(skala);

    }
    sf::Sprite skala;
    skala.setTexture(player_texture);

    // // //

    // Main loop
    while(root.isOpen())
    {
        sf::Event event;
 
        // Events
        while(root.pollEvent(event))
        {
            if(event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                root.close();
            }
        }
        // // //

        // Sterowanie WSAD +- move
        sterowanie_obiekt(gracz);
        player_sprite.setPosition(gracz.x, gracz.y);
        // // //

        // Drawing and refreshin screen
        
        root.clear(sf::Color(0,139,139));
        
        // Przeszkody
        for(int i = 0;i<przeszkody_ilosc;i++)
        {
            przeszkody_obiekt[i].y += speed;
            
            skala.setPosition(przeszkody_obiekt[i].x,przeszkody_obiekt[i].y);
            skala.setScale(4,4);
            root.draw(skala);
        }
        // // //
        
        root.draw(player_sprite);
        root.display();
        // // //
    }
    // // // 

    return 0;
}
// Trzeba zrobić dużo obiektów nad okenm i poprostu będą spadać a jeśli będą poniżej swojej wysokości od dolenj krawędzi to wtedy mogą być już nie wyświetlane oraz na zaoszczędzenie pamięci nie muszą też spadać.