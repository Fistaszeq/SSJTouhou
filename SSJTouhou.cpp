#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
// =================
// @author Fistaszeq
// @graphics Iwa
// =================



// ==================
// KONFIGURACJA
// ==================
float speed = 1.5f;
float speed_bullet = 1.5f;
float move = 8.f; // Our move
float dmg = 2.f;
int score = 0;

float hp = 100;   // HP gracza
int ki = 100;     // POWER
int max_ki = 100;
int meters = 0;


sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
int a = 1080; //desktopMode.width /2;
int b = 900; //desktopMode.height /2;
std::vector<int> res = {a,b};
std::string title = "SSjTouhou";

// ==================
// STRUKTURA OBIEKTU
// ==================
void test()
{
    std::cout<<"\nJestem tutaj"<<std::endl;
}


struct obiekty
{
    float x;
    float y;
    float hp;
    float max_hp;
};

// ==================
// RANDOM
// ==================
int randint(int min, int max)
{
    static std::random_device rd; // genereuje
    static std::mt19937 gen(rd()); // 
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}


// ==================
// KOLIZJA
// ==================
bool kolizja(sf::Sprite a, sf::Sprite b)
{
    return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

// ==================
// STEROWANIE
// ==================
void sterowanie(obiekty &g, sf::Vector2u size)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && g.x > 0)
        g.x -= move;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && g.x < res[0] - size.x)
        g.x += move;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && g.y > 0)
        g.y -= move;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && g.y < res[1] - size.y)
        g.y += move;
}

// ==================
// MAIN
// ==================
int main()
{


    sf::Clock cooldownClock;
    const sf::Time cooldownTime05 = sf::seconds(0.5f); // 500ms cooldown
    const sf::Time cooldownTime005 = sf::seconds(0.05f); // 50ms cooldown
    
    sf::Clock distanse_timer;
    const sf::Time distanse_cooldown_025s = sf::seconds(0.25f); // co 1 sek 1 metr


    sf::RenderWindow root(sf::VideoMode(res[0],res[1]),"SSJTouhou");

    root.setFramerateLimit(60);

    // ==================
    // TEKSTURY
    sf::Texture glaz_texture;
    glaz_texture.loadFromFile("glaz4.png");


    sf::Texture chmura_texture;
    chmura_texture.loadFromFile("chmura-1.png");

    sf::Texture all;
    all.loadFromFile("background.png");

    sf::Texture bg_space;
    bg_space.loadFromFile("bg_space.jpg");

    sf::Texture bg_water;
    bg_water.loadFromFile("bg_water.jpeg");

    sf::Texture bg_water_end;
    bg_water_end.loadFromFile("bg_water_end.jpeg");

    sf::Texture blast0;
    blast0.loadFromFile("ki_blast_0.png");

    sf::Texture blast1;
    blast1.loadFromFile("ki_blast_1.png");

    sf::Texture blast2;
    blast2.loadFromFile("ki_blast_2.png");



    sf::Texture baze;
    baze.loadFromFile("Goku-1.png.png");

    sf::Texture ssj1;
    ssj1.loadFromFile("Goku-2.png.png");

    sf::Texture ssjB;
    ssjB.loadFromFile("Goku-3.png.png");
    // ==================


    // ==================
    // GRACZ
    obiekty gracz;
    gracz.x = res[0] / 2;
    gracz.y = res[1] - 100;

    sf::Sprite player;
    player.setTexture(baze);
    player.setScale(1.8f,1.8f);
    // ==================
    


    // ==================
    // Text
    sf::Font fiseye;
    fiseye.loadFromFile("Noserta.otf");
    sf::Text socre_text;
    socre_text.setPosition(15,50);
    socre_text.setFillColor(sf::Color::Yellow);
    socre_text.setFont(fiseye);
    socre_text.setCharacterSize(30);
    // ==================

    // ==================
    // PRZESZKODY
    std::vector<obiekty> przeszkody;
    std::vector<int> skale;
    int ilosc = 200;
    for(int i = 0; i < ilosc; i++)
    {
        int s = randint(1,6);
        obiekty o;
        o.x = randint(0, res[0]-30);
        o.y = -i * 60;
        o.max_hp = s * 10;
        o.hp = o.max_hp;

        przeszkody.push_back(o);
        skale.push_back(s);
    }
    sf::Sprite przeszkoda(chmura_texture);
    // ==================

    // ==================
    // POCISKI
    std::vector<obiekty> pociski;
    sf::Sprite pocisk(blast0);
    pocisk.setScale(1.2f,1.2f);
    std::vector<int> niecelnosc;
    // ==================


    // ==================
    // UI
    sf::Text power_text;
    power_text.setFont(fiseye);
    power_text.setCharacterSize(10);
    power_text.setFillColor(sf::Color::Black);
    power_text.setPosition({60,10});

    sf::RectangleShape power_bg({200, 10});
    sf::RectangleShape power({200, 10});
    power_bg.setPosition(60, 10);
    power.setPosition(60, 10);
    power_bg.setFillColor(sf::Color(60,60,60));
    power.setFillColor(sf::Color::Cyan);

    sf::RectangleShape hp_bg({200, 10});
    sf::RectangleShape hp_bar({200, 10});
    hp_bg.setPosition(60, 30);
    hp_bar.setPosition(60, 30);
    hp_bg.setFillColor(sf::Color(60,0,0));
    hp_bar.setFillColor(sf::Color::Red);

    sf::RectangleShape mob_hp_bg({30, 4});
    sf::RectangleShape mob_hp({30, 4});
    mob_hp_bg.setFillColor(sf::Color(40,40,40));
    mob_hp.setFillColor(sf::Color::Green);
    sf::Text score_screen;
        
    sf::Sprite back;
    float background_y = -5800; // -5800
    back.setTexture(all);
    int shooting = 1;
    bool czySSJ = false;
    bool czySSJB = false;
    float bg_move = 1.5;
    float back_x = 0;

    // Win text
    sf::Text win_text;
    win_text.setString("WYGRAŁEŚ!!!");
    win_text.setPosition(res[0]/2,res[1]/2);
    win_text.setFont(fiseye);


   
    // Ikonka formy
    float image = 5;
    sf::Vector2f pozycja_image = {50,50};
    sf::Sprite ui_ki_0;
    ui_ki_0.setTexture(blast0);
    ui_ki_0.rotate(180);
    ui_ki_0.setPosition(pozycja_image);
    ui_ki_0.setScale(image,image);

    sf::Sprite ui_ki_1;
    ui_ki_1.setTexture(blast1);
    ui_ki_1.setRotation(180);
    ui_ki_1.setPosition(pozycja_image);
    ui_ki_1.setScale(image,image);

    sf::Sprite ui_ki_2;
    ui_ki_2.setTexture(blast2);
    ui_ki_2.setRotation(180);
    ui_ki_2.setPosition(pozycja_image);
    ui_ki_2.setScale(image,image);
    bool win = false;
    // -- -- -- -- -- -- --
    // ==================


    // ==================
    // LOOP
    // ==================
    while(root.isOpen())
    {
        sf::Event e;
        while(root.pollEvent(e))
        {
            if(e.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                root.close();
            }

            
            // ==================
            // Typy Strzelania
            // ==================
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                shooting = 1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                shooting = 2;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                shooting = 3;
            }
        }

        // ============
        // Dystants
        
        if(distanse_timer.getElapsedTime() >= distanse_cooldown_025s)
        {
            meters += 1;
            distanse_timer.restart();
            background_y -= 0.01;
        }

        
        // if(meters > 100)
        // {
        //     // back.setTexture(bg_water_end);
        //     // back_x = bg_water_end.getSize().x;
        // }
        // else {  
        //     back.setTexture(bg_water);
        //     // back_x = bg_water.getSize().x;
        // }
        
        

        // ============

        // Precyzyjne poruszanie sie
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            move = 4.f;
        }
        else {
            move = 8.f;
        }
        // -- -- -- --

        // Background Przesowanie
        background_y += bg_move;
        // -- -- -- -- 



        // ==================
        // GAME OVER
        if(hp<=0 or sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        {
            // std::getchar();
            root.close();
            std::cout<<"Hp = 0 Przergales!!!" << " Twoj score to: "<< score << std::endl;
        }
        // ==================

        // ==================
        // YOU WIN
        if(background_y >= 0)
        {
            bool win = true;
        }



        // ==================
        // NEW FORMY SJJ
        if(score > 2500)
        {
            player.setTexture(ssjB);
            pocisk.setTexture(blast2);
            power.setFillColor(sf::Color::Blue);
            max_ki = 225;
            dmg = 6;
            speed = 12;
            power_bg.setSize({450, 10});
        }
        
        else if(score > 400)
        {
            player.setTexture(ssj1);
            pocisk.setTexture(blast1);

            power.setFillColor(sf::Color::Yellow);
            max_ki = 150;
            dmg = 4;
            speed = 6;
            power_bg.setSize({300, 10});
        }
        
        else {
            player.setTexture(baze);
            pocisk.setTexture(blast0);
            max_ki = 100;
            dmg = 2;
            speed = 4;
            power_bg.setSize({200,10});
            power.setFillColor(sf::Color::Cyan);
        }
        // ==================
        
        
        // ==================
        // RECHARGE
        // ==================
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) and ki < max_ki and !(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and hp>0))
        {
            ki++;
            // Kara za power
            hp -= 0.1;
            if(!(score <= 0))
            {
                int i = randint(1,4);
                if(i == 1)
                {
                    score -= 1;
                }
                
            }

        }

        // ==================
        // STRZELANIE
        // ==================
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and ki > 0)
        {
            if(shooting == 1 and ki>=15) 
            {
                if (cooldownClock.getElapsedTime() >= cooldownTime05)
                {
                    for(int i = 0;i<randint(7,8);i++)
                    {
                        obiekty p;
                        // Respienie sie pociskow
                        p.x = gracz.x + randint(-10,10) + 25;
                        p.y = gracz.y + 10 + randint(-10,10);
                        // - - - - - 

                        niecelnosc.push_back(randint(-1,1));
                        pociski.push_back(p);
                    }
                    // Koszt za strzal
                    ki -= 15;
                    cooldownClock.restart(); // Resetuj licznik
                }

                if(ki <= 15) {
                    shooting = 2;
                }  
            }


            
                

            else if(shooting == 2 and ki >= 2)
            {
            // Ten mocniejszy
                if(cooldownClock.getElapsedTime() >= cooldownTime005)
                {
                    for(int i =0;i<1;i++)
                    {
                        obiekty p;
                        // Respienie sie pociskow
                        p.x = gracz.x + randint(-10,10) + 25;
                        p.y = gracz.y + 10;
                        // - - - - - - -
                        niecelnosc.push_back(randint(-1,1));
                        pociski.push_back(p);

                    }
                    ki -= 3;
                    cooldownClock.restart();
                }
            }

            
                
            
        }

        

        // ==================
        // STEROWANIE
        sterowanie(gracz, baze.getSize());
        player.setPosition(gracz.x, gracz.y);
        // ==================
        

 

        // ==================
        // UPDATE
        root.clear(sf::Color::Black);

        back.setPosition(0,background_y);
        root.draw(back);

        if(win)
        {
            root.draw(win_text);
            win_text.setString("nacisnij h to continue");
            win_text.move({3,15});
            root.draw(win_text);
            std::getchar();
            
        }
        std::cout<<background_y << std::endl;
        // ==================      
        
        
        // Przeszkody
        for(int i = 0; i < przeszkody.size(); i++)
        {
            przeszkody[i].y += speed / skale[i];
            przeszkoda.setScale(skale[i], skale[i]);
            przeszkoda.setPosition(przeszkody[i].x, przeszkody[i].y);

            // Kolizja z graczem
            if(kolizja(player, przeszkoda))
            {
                hp--;
                przeszkody[i].hp --;
            }

            // HP BAR
            float r = przeszkody[i].hp / przeszkody[i].max_hp;
            
            mob_hp.setSize({25 * r * skale[i], 4});
            mob_hp_bg.setSize({25.f * skale[i],4});
            mob_hp_bg.setPosition(przeszkody[i].x, przeszkody[i].y - 6);
            mob_hp.setPosition(przeszkody[i].x, przeszkody[i].y - 6);

            root.draw(przeszkoda);
            root.draw(mob_hp_bg);
            root.draw(mob_hp);
        }

        // Pociski
        for(int i = 0; i < pociski.size(); )
        {
            // Ruch
            pociski[i].y -= speed_bullet * 5;
            pociski[i].x += niecelnosc[i];
            // - - - - - - - - -
           
            
            pocisk.setPosition(pociski[i].x, pociski[i].y);
            if(shooting == 3)
            {
                pocisk.setScale(3.f,3.f);
            }


            bool hit = false;
            for(int j = 0; j < przeszkody.size(); j++)
            {
                przeszkoda.setScale(skale[j],skale[j]);
                przeszkoda.setPosition(przeszkody[j].x, przeszkody[j].y);
                
                if(kolizja(pocisk, przeszkoda))
                {
                    przeszkody[j].hp -= dmg;
                    hit = true;
                    break;
                }
            }


            if(hit || pociski[i].y < 0)
                pociski.erase(pociski.begin() + i);
            else
            {
                root.draw(pocisk);
                i++;
            }
        }

        // Usuwanie martwych
        for(int i = 0; i < przeszkody.size(); )
        {
            if(przeszkody[i].hp <= 0)
            {
                // Przywileje za zabicie
                przeszkody.erase(przeszkody.begin() + i);
                skale.erase(skale.begin() + i);
                ki += 6 * skale[i];
                hp += 1 * skale[i];
                score += 25 * skale[i];

            }
            else i++;
        }

        // UI
        power.setSize({200 * (ki / 100.f), 10});
        hp_bar.setSize({200 * (hp / 100.f), 10});

        root.draw(power_bg);
        root.draw(power);
        power_text.setString(std::to_string(ki));
        root.draw(power_text);
        root.draw(hp_bg);
        root.draw(hp_bar);

        root.draw(player);

        sf::String meters_str = std::to_string(meters);
        sf::String pkt = "Score: " + std::to_string(score) + "\n SSJ -> 400 \n SSJ Blue -> 2500" +"\n Dystans: " +meters_str;
        socre_text.setString(pkt);
        root.draw(socre_text);  

        if(score > 2500)
        {
            root.draw(ui_ki_2);
        }
        else if(score > 400)
        {
            root.draw(ui_ki_1);
        }
        else 
        {
            root.draw(ui_ki_0);
        }

        root.display();
    
    }
    return 0;
}
