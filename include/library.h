#ifndef MOD_MENU_H
#define MOD_MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

extern "C" __declspec(dllexport) void initLib(sf::RenderWindow& window);
extern "C" __declspec(dllexport) void menuLib(sf::RenderWindow& window, int& menuStatus);
void SettingLogic(sf::RenderWindow& window, int& menuStatus);
float percentage(float percent, unsigned int num);
unsigned int textSizeOptimization(sf::Vector2u currentSize, float textSize);


#endif // MOD_MENU_H
