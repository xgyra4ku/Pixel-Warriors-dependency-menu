#ifndef MOD_MENU_H
#define MOD_MENU_H
// old
#include <SFML/Graphics.hpp>
//... lib fs
#include <map>

extern "C" __declspec(dllexport) void initLib(sf::RenderWindow& window);
extern "C" __declspec(dllexport) void menuLib(sf::RenderWindow& window, int& menuStatus, std::map<std::string, int>& settingsMap, const int& mouseEventWheel, const float& time, std::map<std::string, std::string>& map);

void SettingLogic(sf::RenderWindow& window, int& menuStatus, std::map<std::string, int>& settingsMap);
void CreateWorld(sf::RenderWindow& window, int& menuStatus, const int& mouseEventWheel, const float& time, std::map<std::string, std::string>& map);
void ModsLogic(sf::RenderWindow& window, int& menuStatus, std::map<std::string, std::string>& ModsMap);
float percentage(float percent, unsigned int num);
float percentage1280(float percent, unsigned int num);
float percentage800(float percent, unsigned int num);
unsigned int textSizeOptimization(sf::Vector2u currentSize, float textSize);
// bool collisionMouse(const sf::Vector2f& mousePosition, sf::Vector2f shapeSize, sf::Vector2f shapePosition);

#endif
