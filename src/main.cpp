#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

constexpr int mapWidth = 24;
constexpr int mapHeight = 24;
constexpr int screenWidth = 800;
constexpr int screenHeight = 600;

vector<vector<int>> gameMap =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main()
{
    double posX = 12;
    double posY = 12;
    double dirX = -1;
    double dirY = 0;
    double planeX = 0;
    double planeY = 0.66;
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "piotoor's raycaster");
    window.setFramerateLimit(100);

    sf::Font font;
    sf::Text fpsText;
    bool fpsAvailable = true;
    system("pwd");



    if (font.loadFromFile("./fonts/DooM.ttf")) {

        cout << "DooM.ttf loaded successfully" << endl;
        fpsText.setFont(font);
        fpsText.setCharacterSize(24);
        fpsText.setFillColor(sf::Color::Green);
    } else {
        cout << "Error loading DooM.ttf" << endl;
        fpsAvailable = false;
    }
    while (window.isOpen())
    {
        window.clear(sf::Color(40, 40, 40));
        window.clear();
        for (int w = 0; w < screenWidth; ++w) {
            double cameraX = 2 * w / static_cast<double>(screenWidth) - 1;
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            int mapX = static_cast<int>(posX);
            int mapY = static_cast<int>(posY);


            double dx = rayDirX == 1 ? 0 : abs(1 / rayDirX);
            double dy = rayDirY == 1 ? 0 : abs(1 / rayDirY);


            int stepX = 0;
            int stepY = 0;
            double initDistX = 0;
            double initDistY = 0;

            if (rayDirX >= 0) {
                    initDistX = (1 - posX + mapX) * dx;
                    stepX = 1;
            } else {
                    initDistX = (posX - mapX) * dx;
                    stepX = -1;
            }

            if (rayDirY >= 0) {
                    initDistY = (1 - posY + mapY) * dy;
                    stepY = 1;
            } else {
                    initDistY = (posY - mapY) * dy;
                    stepY = -1;
            }

            bool hit = false;
            bool horizontal = true;
            while (!hit) {
                if (initDistX <= initDistY) {
                    horizontal = true;
                    initDistX += dx;
                    mapX += stepX;
                } else {
                    horizontal = false;
                    initDistY += dy;
                    mapY += stepY;
                }
                if (gameMap[mapX][mapY] > 0) {
                    hit = true;
                }
            }
            double perpendicularDistance = 0;
            if (horizontal) {
                double distX = mapX - posX + (1 - stepX) / 2;
                perpendicularDistance = rayDirX == 0 ? distX : distX / rayDirX;
            } else {
                double distY = mapY - posY + (1 - stepY) / 2;
                perpendicularDistance = rayDirY == 0 ? distY : distY / rayDirY;
            }
//            if (w > 318 and w < 322) {
//                cout << endl;
//                cout << w << endl;
//                cout << "perpendicularDistance = " << perpendicularDistance << endl;
//                cout << "distX = " << mapX - posX + (1 - stepX) / 2 << endl;
//                cout << "rayDirX = " << rayDirX << endl;
//                cout << "distY = " << mapY - posY + (1 - stepY) / 2 << endl;
//                cout << "rayDirY = " << rayDirY << endl;
//            }
            int lineHeight = screenHeight / perpendicularDistance;
            int lineStart = max(0, screenHeight / 2 - lineHeight / 2);
            int lineEnd = min(screenHeight / 2 + lineHeight / 2, screenHeight - 1);


            sf::VertexArray line(sf::Lines, 2);



            sf::Color color;
            switch (gameMap[mapX][mapY]) {
                case 1: {
                    color = sf::Color::Red;
                    break;
                }
                case 2: {
                    color = sf::Color::Green;
                    break;
                }
                case 3: {
                    color = sf::Color::Blue;
                    break;
                }
                case 4: {
                    color = sf::Color::White;
                    break;
                }
                case 5: {
                    color = sf::Color::Cyan;
                    break;
                }
                default: {
                    color = sf::Color::Yellow;
                    break;
                }
            }

            line[0].position = sf::Vector2f(w, lineStart);
            line[1].position = sf::Vector2f(w, lineEnd);

            if (horizontal) {
                color.a = color.a / 2;
            }

            double colorModifier = max(1.0, (double)screenHeight / (double)lineHeight);

            color.a /= colorModifier;

            line[0].color = color;
            line[1].color = color;
            window.draw(line);
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();
        double fps = 1000000.0 / static_cast<double>(elapsed.asMicroseconds());
        if (fpsAvailable) {
            fpsText.setString(to_string(fps));

        }

        window.draw(fpsText);
        window.display();

        double moveSpeed = elapsed.asMilliseconds() / 1000.0 * 5.0;
        double rotateSpeed = elapsed.asMilliseconds() / 1000.0 * 3.0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            double oldDirX = dirX;
            dirX = dirX * cos(rotateSpeed) - dirY * sin(rotateSpeed);
            dirY = oldDirX * sin(rotateSpeed) + dirY * cos(rotateSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(rotateSpeed) - planeY * sin(rotateSpeed);
            planeY = oldPlaneX * sin(rotateSpeed) + planeY * cos(rotateSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            double oldDirX = dirX;
            dirX = dirX * cos(-rotateSpeed) - dirY * sin(-rotateSpeed);
            dirY = oldDirX * sin(-rotateSpeed) + dirY * cos(-rotateSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotateSpeed) - planeY * sin(-rotateSpeed);
            planeY = oldPlaneX * sin(-rotateSpeed) + planeY * cos(-rotateSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            int posXi = static_cast<int>(posX + dirX * moveSpeed);
            int posYi = static_cast<int>(posY);
            if (gameMap[posXi][posYi] == 0) {
                posX += dirX * moveSpeed;
            }
            posXi = static_cast<int>(posX);
            posYi = static_cast<int>(posY + dirY * moveSpeed);
            if (gameMap[posXi][posYi] == 0) {
                posY += dirY * moveSpeed;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            int posXi = static_cast<int>(posX - dirX * moveSpeed);
            int posYi = static_cast<int>(posY);
            if (gameMap[posXi][posYi] == 0) {
                posX -= dirX * moveSpeed;
            }
            posXi = static_cast<int>(posX);
            posYi = static_cast<int>(posY - dirY * moveSpeed);
            if (gameMap[posXi][posYi] == 0) {
                posY -= dirY * moveSpeed;
            }
        }




    }

    return 0;
}

