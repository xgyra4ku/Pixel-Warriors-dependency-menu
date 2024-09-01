#ifndef MOD_MENU_H
#define MOD_MENU_H

#include <SFML/Graphics.hpp>


extern "C" __declspec(dllexport) void initLib(sf::RenderWindow& window);
extern "C" __declspec(dllexport) void menuLib(sf::RenderWindow& window, int& menuStatus, std::map<std::string, int>& settingsMap);

void SettingLogic(sf::RenderWindow& window, int& menuStatus, std::map<std::string, int>& settingsMap);
void CreateWorld(sf::RenderWindow& window, int& menuStatus);
float percentage(float percent, unsigned int num);
float percentage1280(float percent, unsigned int num);
float percentage800(float percent, unsigned int num);
unsigned int textSizeOptimization(sf::Vector2u currentSize, float textSize);
bool collisionMouse(const sf::Vector2f& mousePosition, sf::Vector2f shapeSize, sf::Vector2f shapePosition);

#endif
