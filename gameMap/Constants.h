#pragma once

#define SCREENW 1080
#define SCREENH 720
#define FRAMERATE 60
#define INF 999

#define PLAYERCOLOR sf::Color(0.f, 80.f, 255.f) //, 15.f)
#define ENEMYCOLOR sf::Color(255.f, 20.f, 0.f)
#define TXTPLAYERCOLOR sf::Color(127.f, 127.f, 255.f, 127.f) 
#define TXTENEMYCOLOR sf::Color(255.f, 127.f, 127.f, 127.f) 
#define DEFAULTCOLOR sf::Color(255.f, 255.f, 255.f)

enum ISLANDSTATUS { NEUTRAL, CONTROLOFPLAYER, CONTROLOFENEMY };
enum SCREENTYPE { MENU, CREDITS, GAME, EXIT };
