#include "../include/library.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <FastSfml.hpp>

namespace fsys = std::filesystem;

float g_fReferenceWidth = 1280.0f;
float g_fReferenceHeight = 800.0f;
float g_fReferenceTextSize = 30.0f;

// Текущие размеры окна
float g_fCurrentWidth;
float g_fCurrentHeight;

int g_iSettingsStatus = 0;

bool g_bExitMenu = false;
bool g_bSettingMapCopy = false;
bool g_blsButton_OFF_ON[2];
bool g_bButtonMouseLeft = false;
bool g_bReadDir = true;

std::map<std::string, int> g_mSettings_map_copy_map;
std::vector<std::string> g_vNamesFileSaves;
std::vector<sf::Text> g_vtTextNamesFileSaves;

sf::Font g_sffFont;
sf::Text g_sftGameNameText;
sf::Text g_sftCreateWorldText;
sf::Text g_sftSettingsText;
sf::Text g_sftExitText;
sf::Text g_sftModNameText;
sf::Text g_sftVersionApp;


sf::Vector2f g_vfMousePosition;
sf::Color g_sfcColorHover(34, 127, 79); // Цвет при наведении
sf::Color g_sfcColorNormal(255, 255, 255); // Цвет по умолчанию

sf::Text g_sftSettings[5];
sf::Text g_sftSettingsGraphics[10];

// sf::RectangleShape g_sfrspButton_rectangle_shape[5];
// sf::RectangleShape g_sfrspSButton_shape[5];
sf::RectangleShape g_sfrspShapeCreateWorld[5];


sf::ConvexShape g_sfrcpTriangle[2];


sf::Vector2u g_v2uWindowSize;

sf::Text g_sftCreateWorld[10];

int g_iDisplaySolutionIndex = 0;
int g_iDisplaySolution[17][2] = {
    {800, 600},     // 800x600
    {1024, 768},    // 1024x768
    {1280, 720},    // 1280x720
    {1280, 800},    // 1280x800
    {1366, 768},    // 1366x768
    {1440, 900},    // 1440x900
    {1600, 900},    // 1600x900
    {1680, 1050},   // 1680x1050
    {1920, 1080},   // 1920x1080 (Full HD)
    {1920, 1200},   // 1920x1200
    {2048, 1152},   // 2048x1152
    {2560, 1440},   // 2560x1440 (Quad HD)
    {2560, 1600},   // 2560x1600
    {2880, 1800},   // 2880x1800
    {3200, 1800},   // 3200x1800
    {3840, 2160},   // 3840x2160 (4K)
    {4096, 2160},   // 4096x2160 (DCI 4K)
};



fs::Text::InputText g_tiInput[2];
fs::Mouse* g_mouse;
fs::UI::Slider* g_sliderFPS;

sf::Text g_sftFpsSettings[6];

extern "C" __declspec(dllexport) void initLib(sf::RenderWindow& window) {
    if (!g_sffFont.loadFromFile("Dependency/font.otf")) {
        std::cerr << "ERROR: Failed to initialize menu. Failed to load font" << std::endl;
        window.close();
        return;
    }
    g_v2uWindowSize = window.getSize();
    g_mouse = new fs::Mouse(window);
    g_sliderFPS = new fs::UI::Slider(window);
    g_sliderFPS->setSize({600, 35});
    g_sliderFPS->setPosition({percentage(23.44f, g_v2uWindowSize.x), percentage(50.0f, g_v2uWindowSize.y)});
    g_sliderFPS->setOption(250);
    g_sliderFPS->setHoverColor(sf::Color(70, 70, 70));



    const float xText = percentage(4.69f, g_v2uWindowSize.x);

    for (auto& el : g_tiInput) {
        el.setFont(g_sffFont);
        el.setCharacterSize(textSizeOptimization(g_v2uWindowSize, 22.0f));
        el.setRectSize(sf::Vector2f(300, 35));
    }
    g_tiInput[0].setPosition(sf::Vector2f(percentage1280(792, g_v2uWindowSize.x), percentage800(70, g_v2uWindowSize.y)));
    g_tiInput[1].setPosition(sf::Vector2f(percentage1280(792, g_v2uWindowSize.x), percentage800(120, g_v2uWindowSize.y)));

    g_sfrspShapeCreateWorld[2].setSize(sf::Vector2f(percentage1280(550, g_v2uWindowSize.x), percentage800(90, g_v2uWindowSize.y)));
    g_sfrspShapeCreateWorld[2].setPosition(sf::Vector2f(percentage1280(685, g_v2uWindowSize.x), percentage800(700, g_v2uWindowSize.y)));
    g_sfrspShapeCreateWorld[2].setFillColor(sf::Color::White);

    g_sftCreateWorldText.setFont(g_sffFont);
    g_sftCreateWorldText.setString("Create World");
    g_sftCreateWorldText.setCharacterSize(textSizeOptimization(g_v2uWindowSize, 40.0f));
    g_sftCreateWorldText.setFillColor(sf::Color::White);
    g_sftCreateWorldText.setPosition(xText, percentage(50.0f, g_v2uWindowSize.y));

    g_sftSettingsText.setFont(g_sffFont);
    g_sftSettingsText.setString("Settings");
    g_sftSettingsText.setCharacterSize(textSizeOptimization(g_v2uWindowSize, 40.0f));
    g_sftSettingsText.setFillColor(sf::Color::White);
    g_sftSettingsText.setPosition(xText, percentage(62.5f, g_v2uWindowSize.y));

    g_sftModNameText.setFont(g_sffFont);
    g_sftModNameText.setString("Mods");
    g_sftModNameText.setCharacterSize(textSizeOptimization(g_v2uWindowSize, 40.0f));
    g_sftModNameText.setFillColor(sf::Color::White);
    g_sftModNameText.setPosition(xText, percentage(75.0f, g_v2uWindowSize.y));

    g_sftExitText.setFont(g_sffFont);
    g_sftExitText.setString("Exit");
    g_sftExitText.setCharacterSize(textSizeOptimization(g_v2uWindowSize, 40.0f));
    g_sftExitText.setFillColor(sf::Color::White);
    g_sftExitText.setPosition(xText, percentage(87.5f, g_v2uWindowSize.y));

    g_sftGameNameText.setFont(g_sffFont);
    g_sftGameNameText.setString("Pixel-Warriors");
    g_sftGameNameText.setCharacterSize(textSizeOptimization(g_v2uWindowSize, 60.0f));
    g_sftGameNameText.setFillColor(sf::Color(204, 155, 248));
    g_sftGameNameText.setPosition(percentage(54.69, g_v2uWindowSize.x), 50);

    for (auto & setting : g_sftSettings) {
        setting.setFont(g_sffFont);
        setting.setCharacterSize(textSizeOptimization(g_v2uWindowSize, 30.0f));
        setting.setFillColor(sf::Color::White);
    }

    g_sftSettings[0].setString("Exit");
    g_sftSettings[0].setCharacterSize(textSizeOptimization(g_v2uWindowSize, 40.0f));
    g_sftSettings[1].setString("Audio");
    g_sftSettings[2].setString("Graphics");
    g_sftSettings[3].setString("Apply");
    g_sftSettings[3].setCharacterSize(textSizeOptimization(g_v2uWindowSize, 40.0f));
    g_sftSettings[4].setString("Keys");

    g_sftSettings[0].setPosition(xText, percentage(87.5f, g_v2uWindowSize.y));
    g_sftSettings[1].setPosition(xText, percentage(50.0f, g_v2uWindowSize.y));
    g_sftSettings[2].setPosition(xText, percentage(37.5f, g_v2uWindowSize.y));
    g_sftSettings[3].setPosition(percentage(15.63f, g_v2uWindowSize.x), percentage(87.5f, g_v2uWindowSize.y));
    g_sftSettings[4].setPosition(xText, percentage(62.5f, g_v2uWindowSize.y));


    for (auto& el : g_sftSettingsGraphics) {
        el.setFont(g_sffFont);
        el.setCharacterSize(textSizeOptimization(g_v2uWindowSize, 30.0f));
        el.setFillColor(sf::Color::White);
    }

    g_sftSettingsGraphics[0].setString("Resolution:");
    g_sftSettingsGraphics[0].setPosition(percentage(23.44f, g_v2uWindowSize.x), percentage(37.5f, g_v2uWindowSize.y));  // X=300/1280=23.44%



    g_sftFpsSettings[0].setString("0");

    g_sftFpsSettings[1].setString("Max");

    g_sftFpsSettings[2].setString("V-sync");


    for (auto& el : g_sftFpsSettings) {
        el.setFont(g_sffFont);
        el.setCharacterSize(textSizeOptimization(g_v2uWindowSize, 30.0f));
        el.setFillColor(sf::Color::White);
        el.setPosition({percentage(68.75f, g_v2uWindowSize.x), percentage(50.0f, g_v2uWindowSize.y)});
    }

    g_sftSettingsGraphics[7].setPosition(percentage(68.75f, g_v2uWindowSize.x), percentage(37.5f, g_v2uWindowSize.y));  // X=880/1280=68.75%



    for (int i = 0; i < 17; i++) {
        if (g_iDisplaySolution[i][0] == g_v2uWindowSize.x && g_iDisplaySolution[i][1] == g_v2uWindowSize.y) {
            g_iDisplaySolutionIndex = i;
            g_sftSettingsGraphics[7].setString(std::to_string(g_iDisplaySolution[g_iDisplaySolutionIndex][0])
                    + 'x' + std::to_string(g_iDisplaySolution[g_iDisplaySolutionIndex][1]));
            break;
        }
    }
    //
    // for (int i = 0; i < 5; i++) {
    //     g_sfrspButton_rectangle_shape[i].setFillColor(sf::Color(255, 255, 255));
    //     g_sfrspSButton_shape[i].setFillColor(sf::Color(10,10,10));
    // }
    //
    // //function buttons
    // //fullscreen
    // g_sfrspButton_rectangle_shape[0].setSize(sf::Vector2f(percentage(1.17f, g_v2uWindowSize.x), percentage(1.88f, g_v2uWindowSize.y)));
    // g_sfrspButton_rectangle_shape[0].setPosition(percentage(85.94f, g_v2uWindowSize.x), percentage(52.0f, g_v2uWindowSize.y));
    //
    // g_sfrspSButton_shape[0].setSize(sf::Vector2f(percentage(1.02f, g_v2uWindowSize.x), percentage(1.63f, g_v2uWindowSize.y)));
    // g_sfrspSButton_shape[0].setPosition(percentage(86.02f, g_v2uWindowSize.x), percentage(52.13f, g_v2uWindowSize.y));
    // //V-sync
    // g_sfrspButton_rectangle_shape[1].setSize(sf::Vector2f(percentage(1.17f, g_v2uWindowSize.x), percentage(1.88f, g_v2uWindowSize.y)));
    // g_sfrspButton_rectangle_shape[1].setPosition(percentage(85.94f, g_v2uWindowSize.x), percentage(64.13f, g_v2uWindowSize.y));
    //
    // g_sfrspSButton_shape[1].setSize(sf::Vector2f(percentage(1.02f, g_v2uWindowSize.x), percentage(1.63f, g_v2uWindowSize.y)));
    // g_sfrspSButton_shape[1].setPosition(percentage(86.02f, g_v2uWindowSize.x), percentage(64.25f, g_v2uWindowSize.y));
    // //60
    // g_sfrspButton_rectangle_shape[2].setSize(sf::Vector2f(percentage(1.17f, g_v2uWindowSize.x), percentage(1.88f, g_v2uWindowSize.y)));
    // g_sfrspButton_rectangle_shape[2].setPosition(percentage(41.8f, g_v2uWindowSize.x), percentage(64.13f, g_v2uWindowSize.y));
    //
    // g_sfrspSButton_shape[2].setSize(sf::Vector2f(percentage(1.02f, g_v2uWindowSize.x), percentage(1.63f, g_v2uWindowSize.y)));
    // g_sfrspSButton_shape[2].setPosition(percentage(41.88, g_v2uWindowSize.x), percentage(64.25f, g_v2uWindowSize.y));
    // //120
    // g_sfrspButton_rectangle_shape[3].setSize(sf::Vector2f(percentage(1.17f, g_v2uWindowSize.x), percentage(1.88f, g_v2uWindowSize.y)));
    // g_sfrspButton_rectangle_shape[3].setPosition(percentage(53.52f, g_v2uWindowSize.x), percentage(64.13f, g_v2uWindowSize.y));
    //
    // g_sfrspSButton_shape[3].setSize(sf::Vector2f(percentage(1.02f, g_v2uWindowSize.x), percentage(1.63f, g_v2uWindowSize.y)));
    // g_sfrspSButton_shape[3].setPosition(percentage(53.59f, g_v2uWindowSize.x), percentage(64.25f, g_v2uWindowSize.y));
    // //Max
    // g_sfrspButton_rectangle_shape[4].setSize(sf::Vector2f(percentage(1.17f, g_v2uWindowSize.x), percentage(1.88f, g_v2uWindowSize.y)));
    // g_sfrspButton_rectangle_shape[4].setPosition(percentage(67.19f, g_v2uWindowSize.x), percentage(64.13f, g_v2uWindowSize.y));
    //
    // g_sfrspSButton_shape[4].setSize(sf::Vector2f(percentage(1.02f, g_v2uWindowSize.x), percentage(1.63f, g_v2uWindowSize.y)));
    // g_sfrspSButton_shape[4].setPosition(percentage(67.27f, g_v2uWindowSize.x), percentage(64.25f, g_v2uWindowSize.y));

    // end function buttons


    g_sfrcpTriangle[0].setPointCount(3);
    g_sfrcpTriangle[0].setPoint(0, sf::Vector2f(percentage(66.25f, g_v2uWindowSize.x), percentage(40.0f, g_v2uWindowSize.y)));
    g_sfrcpTriangle[0].setPoint(1, sf::Vector2f(percentage(67.42f, g_v2uWindowSize.x), percentage(41.25f, g_v2uWindowSize.y)));
    g_sfrcpTriangle[0].setPoint(2, sf::Vector2f(percentage(67.42f, g_v2uWindowSize.x), percentage(38.75f, g_v2uWindowSize.y)));
    g_sfrcpTriangle[0].setFillColor(sf::Color(10, 10, 10));

    g_sfrcpTriangle[1].setPointCount(3);
    g_sfrcpTriangle[1].setPoint(0, sf::Vector2f(percentage(87.11f, g_v2uWindowSize.x), percentage(40.0f, g_v2uWindowSize.y)));
    g_sfrcpTriangle[1].setPoint(1, sf::Vector2f(percentage(85.94f, g_v2uWindowSize.x), percentage(41.25f, g_v2uWindowSize.y)));
    g_sfrcpTriangle[1].setPoint(2, sf::Vector2f(percentage(85.94f, g_v2uWindowSize.x), percentage(38.75f, g_v2uWindowSize.y)));
    g_sfrcpTriangle[1].setFillColor(sf::Color(10, 10, 10));

    g_sftVersionApp.setFont(g_sffFont);
    g_sftVersionApp.setCharacterSize(textSizeOptimization(g_v2uWindowSize, 15.0f));
    g_sftVersionApp.setFillColor(sf::Color::White);
    g_sftVersionApp.setString("version-0.24-ALPHA--menu-version-0.55");
    g_sftVersionApp.setPosition(0, percentage800(780, g_v2uWindowSize.y));


    for (auto& el : g_sftCreateWorld) {
        el.setFont(g_sffFont);
        el.setCharacterSize(textSizeOptimization(g_v2uWindowSize, 30.0f));
        el.setFillColor(sf::Color::White);
    }
    g_sftCreateWorld[0].setCharacterSize(textSizeOptimization(g_v2uWindowSize, 50.0f));
    g_sftCreateWorld[0].setString("\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|");
    g_sftCreateWorld[0].setPosition(percentage1280(636, g_v2uWindowSize.x), percentage800(-58.5, g_v2uWindowSize.y));

    g_sftCreateWorld[1].setString("Saves");
    g_sftCreateWorld[1].setPosition(percentage1280(212, g_v2uWindowSize.x), percentage800(10, g_v2uWindowSize.y));

    g_sftCreateWorld[2].setString("Create World");
    g_sftCreateWorld[2].setPosition(percentage1280(836, g_v2uWindowSize.x), percentage800(10, g_v2uWindowSize.y));

    g_sftCreateWorld[3].setString("Name:");
    g_sftCreateWorld[3].setPosition(percentage1280(685, g_v2uWindowSize.x), percentage800(70, g_v2uWindowSize.y));

    g_sftCreateWorld[4].setString("Seed:");
    g_sftCreateWorld[4].setPosition(percentage1280(685, g_v2uWindowSize.x), percentage800(120, g_v2uWindowSize.y));

    g_sftCreateWorld[5].setString("Create World");
    g_sftCreateWorld[5].setPosition(percentage1280(840, g_v2uWindowSize.x), percentage800(720, g_v2uWindowSize.y));
    g_sftCreateWorld[5].setFillColor(sf::Color(0,0,0));


    g_sfrspShapeCreateWorld[0].setSize(sf::Vector2f(static_cast<float>(g_v2uWindowSize.x), percentage800(65, g_v2uWindowSize.y)));
    g_sfrspShapeCreateWorld[1].setSize(sf::Vector2f(static_cast<float>(g_v2uWindowSize.x), percentage800(120, g_v2uWindowSize.y)));
    g_sfrspShapeCreateWorld[0].setFillColor(sf::Color(43, 63, 114));
    g_sfrspShapeCreateWorld[1].setFillColor(sf::Color(43, 63, 114));
    g_sfrspShapeCreateWorld[0].setPosition(0,0);
    g_sfrspShapeCreateWorld[1].setPosition(0,percentage800(710, g_v2uWindowSize.y));


    std::cout << "INFO: menu initialized is successful" << std::endl;
}

extern "C" __declspec(dllexport) void menuLib(sf::RenderWindow& window, int& menuStatus, std::map<std::string, int>& settingsMap, const int& mouseEventWheel, const float& time, std::map<std::string, std::string>& map) {

    window.clear(sf::Color(43, 63, 114));
    g_vfMousePosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));
    std::cout << g_mouse->getMousePosition().x << " " << g_mouse->getMousePosition().y << std::endl;
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        g_bExitMenu = true;
    if (menuStatus == 0) {

        //Create World
        if (g_sftCreateWorldText.getGlobalBounds().contains(g_vfMousePosition.x, g_vfMousePosition.y)) {
            g_sftCreateWorldText.setFillColor(g_sfcColorHover);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                menuStatus = 2;
        }
        else {
            g_sftCreateWorldText.setFillColor(g_sfcColorNormal);
        }
        //Settings
        if (g_sftSettingsText.getGlobalBounds().contains(g_vfMousePosition.x, g_vfMousePosition.y)) {
            g_sftSettingsText.setFillColor(g_sfcColorHover);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                menuStatus = 3;
        }
        else {
            g_sftSettingsText.setFillColor(g_sfcColorNormal);
        }
        //Mods
        if (g_sftModNameText.getGlobalBounds().contains(g_vfMousePosition.x, g_vfMousePosition.y)) {
            g_sftModNameText.setFillColor(g_sfcColorHover);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                menuStatus = 4;
        }
        else {
            g_sftModNameText.setFillColor(g_sfcColorNormal);
        }
        //Exit
        if (g_sftExitText.getGlobalBounds().contains(g_vfMousePosition.x, g_vfMousePosition.y)) {
            g_sftExitText.setFillColor(g_sfcColorHover);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                g_bExitMenu = true; // Устанавливаем флаг перед закрытием
                window.close();
                return;
            }
        } else {
            g_bExitMenu = false; // Сбрасываем флаг, если мышь не над кнопкой
        }


        window.draw(g_sftGameNameText);
        window.draw(g_sftCreateWorldText);
        window.draw(g_sftSettingsText);
        window.draw(g_sftModNameText);
        window.draw(g_sftExitText);
        g_bReadDir = true;
    }
    else if (menuStatus == 2) {
        CreateWorld(window, menuStatus, mouseEventWheel, time, map);
    }
    else if (menuStatus == 3) {
        SettingLogic(window, menuStatus, settingsMap);
    }
    else if (menuStatus == 4) {

    }

    window.draw(g_sftVersionApp);
    g_bButtonMouseLeft = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
void CreateWorld(sf::RenderWindow& window, int& menuStatus, const int& mouseEventWheel, const float& time, std::map<std::string, std::string>& map) {
    g_tiInput[0].listen(time);
    g_tiInput[1].listen(time);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && g_mouse->collision(g_sfrspShapeCreateWorld[2].getSize(), g_sfrspShapeCreateWorld[2].getPosition())) {
        g_sfrspShapeCreateWorld[2].setFillColor(sf::Color(175, 175, 175));
        if (g_tiInput[0].getString()[0] != '\0' && g_tiInput[0].getString()[0] != '\0') {
            map["name"] = g_tiInput[0].getString();
            map["seed"] = g_tiInput[1].getString();
            menuStatus = -4;
            g_tiInput[0].setString("");
            g_tiInput[1].setString("");
            // отображение надписи "не удалось создать мир"
        }
    } else {
        g_sfrspShapeCreateWorld[2].setFillColor(sf::Color::White);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !g_bButtonMouseLeft) {
        if (g_mouse->collision(g_tiInput[0].getRectSize(), g_tiInput[0].getPosition())) {
            g_tiInput[0].setInput(true);
            g_tiInput[1].setInput(false);
        } else if (g_mouse->collision(g_tiInput[1].getRectSize(), g_tiInput[1].getPosition())) {
            g_tiInput[1].setInput(true);
            g_tiInput[0].setInput(false);
        } else {
            g_tiInput[0].setInput(false);
            g_tiInput[1].setInput(false);
        }
    }
    if (g_bReadDir) {
        g_vtTextNamesFileSaves.clear();
        sf::Vector2f pos = {50,70};
        // Укажите путь к вашей директории
        const fsys::path dir_path = "worlds/";

        // Проверяем, существует ли директория
        if (!is_directory(dir_path)) {
            std::cerr << "INFO: There is no save world directory";
            return;
        }
        // Перебираем файлы в директории
        for (const auto& entry : fsys::directory_iterator(dir_path)) {
            // Проверяем, является ли запись файлом (или директорией)
            if (fsys::is_regular_file(entry.status())) {
                g_vNamesFileSaves.push_back(entry.path().filename().string());
                sf::Text text;
                text.setFillColor(sf::Color::White);
                text.setFont(g_sffFont);

                text.setString(entry.path().filename().string().substr(0, entry.path().filename().string().rfind(".json")));
                text.setPosition(pos);
                pos = sf::Vector2f(pos.x, pos.y+65);
                g_vtTextNamesFileSaves.push_back(text);
            }
        }
        g_bReadDir = false;
    }

    if (g_mouse->collision(sf::Vector2f(percentage(50.0f, g_v2uWindowSize.x), static_cast<float>(g_v2uWindowSize.y)), sf::Vector2f(0,0))) {
        if (mouseEventWheel > 0) {
            for (auto& el : g_vtTextNamesFileSaves) {
                sf::Vector2f posEl = el.getPosition();
                el.setPosition(sf::Vector2f(posEl.x, posEl.y+=4*time));
            }
        } else if (mouseEventWheel < 0 ) {
            for (auto& el : g_vtTextNamesFileSaves) {
                sf::Vector2f posEl = el.getPosition();
                el.setPosition(sf::Vector2f(posEl.x, posEl.y-=4*time));
            }
        }

    }
    for (auto& el : g_vtTextNamesFileSaves) {
         if (el.getGlobalBounds().contains(g_vfMousePosition.x, g_vfMousePosition.y)) {
             el.setFillColor(g_sfcColorHover);
             if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !g_bButtonMouseLeft) {
                 map["name"] = el.getString();
                 menuStatus = -3;
             }
        }
        window.draw(el);
        el.setFillColor(g_sfcColorNormal);
    }
    window.draw(g_sfrspShapeCreateWorld[0]);
    window.draw(g_sfrspShapeCreateWorld[1]);
    window.draw(g_sfrspShapeCreateWorld[2]);
    for (const auto& el : g_sftCreateWorld) {
        window.draw(el);
    }
    g_tiInput[0].draw(window);
    g_tiInput[1].draw(window);
}
void SettingLogic(sf::RenderWindow& window, int& menuStatus, std::map<std::string, int>& settingsMap) {
    g_sliderFPS->logic();
    if (!g_bSettingMapCopy) {
        g_sliderFPS->setStatus(settingsMap["fps"]);
        g_mSettings_map_copy_map = settingsMap;
        g_bSettingMapCopy = true;
    }
    //exit
    if (g_sftSettings[0].getGlobalBounds().contains(g_vfMousePosition.x, g_vfMousePosition.y)) {
        g_sftSettings[0].setFillColor(g_sfcColorHover);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && g_bExitMenu) {
            std::cout << "Exit menu" << std::endl;
            menuStatus = 0;
            g_iSettingsStatus = 0;
            g_bExitMenu = false;
            g_bSettingMapCopy = false;
        }
    }
    //audio
    if (g_sftSettings[1].getGlobalBounds().contains(g_vfMousePosition.x, g_vfMousePosition.y)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            g_iSettingsStatus = 1;
            g_sftSettings[1].setFillColor(g_sfcColorHover);
        }
    }
    //graphics
    if (g_sftSettings[2].getGlobalBounds().contains(g_vfMousePosition.x, g_vfMousePosition.y)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            g_iSettingsStatus = 0;
            g_sftSettings[2].setFillColor(g_sfcColorHover);
        }
    }
    //keys
    if (g_sftSettings[4].getGlobalBounds().contains(g_vfMousePosition.x, g_vfMousePosition.y)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            g_iSettingsStatus = 3;
            g_sftSettings[4].setFillColor(g_sfcColorHover);
        }
    }
    //apply
    if (g_sftSettings[3].getGlobalBounds().contains(g_vfMousePosition.x, g_vfMousePosition.y)) {
        g_sftSettings[3].setFillColor(g_sfcColorHover);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !g_bButtonMouseLeft) {
            menuStatus = -2;
            g_mSettings_map_copy_map["windowWidth"] = g_iDisplaySolution[g_iDisplaySolutionIndex][0];
            g_mSettings_map_copy_map["windowHeight"] = g_iDisplaySolution[g_iDisplaySolutionIndex][1];
            g_mSettings_map_copy_map["fps"] = g_sliderFPS->getStatus();
            settingsMap = g_mSettings_map_copy_map;
            g_bSettingMapCopy = false;
        }
    }
    if (g_iSettingsStatus == 0) {
        //
        // if (g_mouse->collision(g_sfrspButton_rectangle_shape[0].getSize(), g_sfrspButton_rectangle_shape[0].getPosition())) {
        //     if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !g_bButtonMouseLeft) {
        //         g_mSettings_map_copy_map["fullscreen"] = !g_mSettings_map_copy_map["fullscreen"];
        //     }
        // }
        // if (g_mouse->collision(g_sfrspButton_rectangle_shape[1].getSize(), g_sfrspButton_rectangle_shape[1].getPosition())) {
        //     if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !g_bButtonMouseLeft) {
        //         g_mSettings_map_copy_map["V-sync"] = !g_mSettings_map_copy_map["V-sync"];
        //         g_mSettings_map_copy_map["fps"] = 0;
        //     }
        // }
        // if (g_mouse->collision(g_sfrspButton_rectangle_shape[2].getSize(), g_sfrspButton_rectangle_shape[2].getPosition())) {
        //     if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !g_bButtonMouseLeft) {
        //         g_mSettings_map_copy_map["fps"] = 60;
        //         g_mSettings_map_copy_map["V-sync"] = 0;
        //     }
        // }
        // if (g_mouse->collision(g_sfrspButton_rectangle_shape[3].getSize(), g_sfrspButton_rectangle_shape[3].getPosition())) {
        //     if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !g_bButtonMouseLeft) {
        //         g_mSettings_map_copy_map["fps"] = 120;
        //         g_mSettings_map_copy_map["V-sync"] = 0;
        //     }
        // }
        // if (g_mouse->collision(g_sfrspButton_rectangle_shape[4].getSize(), g_sfrspButton_rectangle_shape[4].getPosition())) {
        //     if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !g_bButtonMouseLeft) {
        //         g_mSettings_map_copy_map["fps"] = -1;
        //         g_mSettings_map_copy_map["V-sync"] = 0;
        //     }
        // }

        if (g_mouse->collision(sf::Vector2f(15,15), sf::Vector2f(percentage(85.94f, g_v2uWindowSize.x), percentage(38.75f, g_v2uWindowSize.y)))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !g_bButtonMouseLeft) {

                if (g_iDisplaySolutionIndex >= 16) {
                    g_iDisplaySolutionIndex = 0;
                } else {
                    g_iDisplaySolutionIndex++;
                }
                g_sftSettingsGraphics[7].setString(std::to_string(g_iDisplaySolution[g_iDisplaySolutionIndex][0])
                    + 'x' + std::to_string(g_iDisplaySolution[g_iDisplaySolutionIndex][1]));
            }
        }

        if (g_mouse->collision(sf::Vector2f(15,15), sf::Vector2f(percentage(66.25f, g_v2uWindowSize.x), percentage(38.75f, g_v2uWindowSize.y)))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !g_bButtonMouseLeft) {

                if (g_iDisplaySolutionIndex <= 0) {
                    g_iDisplaySolutionIndex = 16;
                } else {
                    g_iDisplaySolutionIndex--;
                }
                g_sftSettingsGraphics[7].setString(std::to_string(g_iDisplaySolution[g_iDisplaySolutionIndex][0])
                    + 'x' + std::to_string(g_iDisplaySolution[g_iDisplaySolutionIndex][1]));
            }
        }

        //draw
        for (const auto &el : g_sftSettingsGraphics) {
            window.draw(el);
        }
        g_sliderFPS->draw();
        if (g_sliderFPS->getStatus() == 0) {
            window.draw(g_sftFpsSettings[2]);
        } else if (g_sliderFPS->getStatus() == 250) {
            window.draw(g_sftFpsSettings[1]);
        } else {
            g_sftFpsSettings[0].setString(std::to_string(g_sliderFPS->getStatus()));
            window.draw(g_sftFpsSettings[0]);
        }

        window.draw(g_sfrcpTriangle[0]);
        window.draw(g_sfrcpTriangle[1]);
        //std::cout << "Display solution index: "<< displaySolutionIndex << std::endl;

    } else if (g_iSettingsStatus == 1) {

    } else if (g_iSettingsStatus == 3) {

    }

    for (auto & setting : g_sftSettings) {
        window.draw(setting);
        setting.setFillColor(g_sfcColorNormal);
    }
    window.draw(g_sftGameNameText);
}


float percentage(const float percent, const unsigned int num) {
    return (percent / 100) * static_cast<float>(num);
}
float percentage1280(const float percent, const unsigned int num) {
    const float i = (percent / 1280) * 100;
    return percentage(i, num);
}
float percentage800(const float percent, const unsigned int num) {
    const float i = (percent / 800) * 100;
    return percentage(i, num);
}

unsigned int textSizeOptimization(sf::Vector2u currentSize, float textSize) {
    return static_cast<int>(textSize * (std::sqrt(
                                            std::pow((static_cast<float>(currentSize.x) / 1280.0f), 2) + std::pow(
                                                (static_cast<float>(currentSize.y) / 800.0f), 2)) / std::sqrt(2)));
}
bool collisionMouse(const sf::Vector2f& mousePosition, const sf::Vector2f shapeSize, const sf::Vector2f shapePosition) {
    if (static_cast<float>(mousePosition.x) >= shapePosition.x &&
        static_cast<float>(mousePosition.x) <= shapePosition.x + shapeSize.x &&
        static_cast<float>(mousePosition.y) >= shapePosition.y &&
        static_cast<float>(mousePosition.y) <= shapePosition.y + shapeSize.y) {
        return true;
    }
    return false;
}

