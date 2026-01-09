#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>

// ==================
// KONFIGURACJA
// ==================
float speed = 1.5f;
float speed_bullet = 1.5f;
float move = 12.f;
float dmg = 2.f;

float hp = 100;   // HP gracza
int ki = 100;     // POWER
int max_ki = 100;
int score = 0;
bool first = true;
sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
int a = 1600; //desktopMode.width /2;
int b = 900; //desktopMode.height /2;
std::vector<int> res = {a,b};
std::string title = "SSjTouhou";

// ==================
// STRUKTURA OBIEKTU
// ==================
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


    sf::RenderWindow root(sf::VideoMode(res[0],res[1]),"SSJTouhou");

    
    


    root.setFramerateLimit(60);

    // ==================
    // TEKSTURA
    // ==================
    sf::Texture tex;
    tex.loadFromFile("glaz2.png");

    sf::Texture background;
    background.loadFromFile("space.jpg");

    sf::Texture blast;
    blast.loadFromFile("white_roock.png");

    sf::Texture baze;
    baze.loadFromFile("Goku-1.png.png");

    sf::Texture ssj1;
    ssj1.loadFromFile("Goku-2.png.png");

    sf::Texture ssjB;
    ssjB.loadFromFile("Goku-3.png.png");

    // ==================
    // GRACZ
    // ==================
    obiekty gracz;
    gracz.x = res[0] / 2;
    gracz.y = res[1] - 100;

    sf::Sprite player(baze);
    player.setScale(1.8f,1.8f);

    // ==================
    // PRZESZKODY
    // ==================
    std::vector<obiekty> przeszkody;
    std::vector<int> skale;
    int ilosc = 200;
    for(int i = 0; i < ilosc; i++)
    {
        int s = randint(2,10);
        obiekty o;
        o.x = randint(0, res[0]);
        o.y = -i * 60;
        o.max_hp = s * 10;
        o.hp = o.max_hp;

        przeszkody.push_back(o);
        skale.push_back(s);
    }

    sf::Sprite przeszkoda(tex);

    // ==================
    // POCISKI
    // ==================
    std::vector<obiekty> pociski;
    sf::Sprite pocisk(blast);
    pocisk.setScale(0.4f, 0.4f);
    std::vector<int> niecelnosc;

    // ==================
    // UI
    // ==================
    sf::RectangleShape power_bg({200, 10});
    sf::RectangleShape power({200, 10});
    power_bg.setPosition(10, 10);
    power.setPosition(10, 10);
    power_bg.setFillColor(sf::Color(60,60,60));
    power.setFillColor(sf::Color::Cyan);

    sf::RectangleShape hp_bg({200, 10});
    sf::RectangleShape hp_bar({200, 10});
    hp_bg.setPosition(10, 30);
    hp_bar.setPosition(10, 30);
    hp_bg.setFillColor(sf::Color(60,0,0));
    hp_bar.setFillColor(sf::Color::Red);

    sf::RectangleShape mob_hp_bg({30, 4});
    sf::RectangleShape mob_hp({30, 4});
    mob_hp_bg.setFillColor(sf::Color(40,40,40));
    mob_hp.setFillColor(sf::Color::Green);
    sf::Text score_screen;

    // ==================
    // LOOP
    // ==================
    while(root.isOpen())
    {

        sf::Clock shootClock;
        const sf::Time shootCooldown = sf::milliseconds(120);

        sf::Event e;
        while(root.pollEvent(e))
        {
            if(e.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                root.close();
        }




        // ==================
        // GAME OVER
        // ==================
        if(hp<=0)
        {
            root.close();
            std::cout<<"Hp = 0 Przergales!!!" << std::endl;
        }


        // ==================
        // NEW FORMY SJJ
        // ==================
        if(ki >100 and first)
        {
            first = false;
            player.setTexture(ssj1);

            power.setFillColor(sf::Color::Yellow);
            max_ki = 150;
            dmg = 4;
            speed = 8;
            power_bg.setSize({300, 10});
            power_bg.setPosition(10, 10);
            power_bg.setFillColor(sf::Color(60,60,60));
            // speed_bullet = 4.f;
        }
        
        if(ki > 250)
        {
            player.setTexture(ssjB);
            power.setFillColor(sf::Color::Blue);
            max_ki = 225;
            dmg = 8;
            speed = 16;
            // speed_bullet = 8.f;
            power_bg.setSize({375, 10});
        }

        // ==================
        // RECHARGE
        // ==================
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) and ki < max_ki and !(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and hp>0))
        {
            
            
            ki++;

            // Kara za power
            hp -= 0.1;
            score -= 1;
        }
        else
        {
            move = std::min(3.f, move + 0.01f);
        }

        // ==================
        // STRZELANIE
        // ==================
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and ki > 0)
        {
            obiekty p;
            p.x = gracz.x + randint(-2,2) + 25;
            p.y = gracz.y + 10;
            niecelnosc.push_back(randint(-2,2));
            pociski.push_back(p);
            // Koszt za strzal
            // ki -= 2;
        }

        

        // ==================
        // STEROWANIE
        // ==================
        sterowanie(gracz, tex.getSize());
        player.setPosition(gracz.x, gracz.y);

        // ==================
        // UPDATE
        // ==================
        root.clear(sf::Color::Black);
        sf::Sprite back;
        back.setTexture(background);
        root.draw(back);

        // Przeszkody
        for(int i = 0; i < przeszkody.size(); i++)
        {
            przeszkody[i].y += speed / skale[i];
            przeszkoda.setScale(skale[i], skale[i]);
            przeszkoda.setPosition(przeszkody[i].x, przeszkody[i].y);

            // Kolizja z graczem
            if(kolizja(player, przeszkoda))
                hp--;

            // HP BAR
            float r = przeszkody[i].hp / przeszkody[i].max_hp;
            mob_hp.setSize({30 * r, 4});
            mob_hp_bg.setPosition(przeszkody[i].x, przeszkody[i].y - 6);
            mob_hp.setPosition(przeszkody[i].x, przeszkody[i].y - 6);

            root.draw(przeszkoda);
            root.draw(mob_hp_bg);
            root.draw(mob_hp);
        }

        // Pociski
        for(int i = 0; i < pociski.size(); )
        {
            pociski[i].y -= speed_bullet * 5;
            pociski[i].x += speed_bullet *  niecelnosc[i];
           
            std::cout<<pociski.size()<<std::endl;
            pocisk.setPosition(pociski[i].x, pociski[i].y);

            bool hit = false;
            for(int j = 0; j < przeszkody.size(); j++)
            {
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
                przeszkody.erase(przeszkody.begin() + i);
                skale.erase(skale.begin() + i);
                ki += 25;
                hp += 1;
                score += 100;

            }
            else i++;
        }

        // UI
        power.setSize({200 * (ki / 100.f), 10});
        hp_bar.setSize({200 * (hp / 100.f), 10});

        root.draw(power_bg);
        root.draw(power);
        root.draw(hp_bg);
        root.draw(hp_bar);

        root.draw(player);
        root.display();
    
    }
    return 0;
}
