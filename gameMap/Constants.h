#pragma once

#define SCREENW 1000
#define SCREENH 1000
#define ILNUMLEVEL1 6
#define FRAMERATE 60

#define PLAYERCOLOR sf::Color(0.f, 80.f, 255.f) //, 15.f)
#define TWEENERCOLOR sf::Color(127.f, 127.f, 255.f, 127.f) 
#define DEFAULTCOLOR sf::Color(255.f, 255.f, 255.f)

enum ISLANDSTATUS { NEUTRAL, CONTROLOFPLAYER, CONTROLOFENEMY };