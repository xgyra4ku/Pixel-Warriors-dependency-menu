#include "../include/library.h"

int SettingsStatus = 0;

bool exitmenu = false;

sf::Font font;
sf::Text GameNameText;
sf::Text CreateWorldText;
sf::Text SettingsText;
sf::Text ExitText;
sf::Text ModNameText;
sf::Vector2f mousePosition;
sf::Color colorHover(34, 127, 79); // Цвет при наведении
sf::Color colorNormal(255, 255, 255); // Цвет по умолчанию

sf::Text settings[5];
sf::Text settingsGraphics[5];


extern "C" __declspec(dllexport) void initLib(sf::RenderWindow& window) {
    if (!font.loadFromFile("Dependency/font.otf")) {
        std::cerr << "Error loading font" << std::endl;
        window.close();
        return;
    }

    CreateWorldText.setFont(font);
    CreateWorldText.setString("Create World");
    CreateWorldText.setCharacterSize(40);
    CreateWorldText.setFillColor(sf::Color::White);
    CreateWorldText.setPosition(60, 400);

    SettingsText.setFont(font);
    SettingsText.setString("Settings");
    SettingsText.setCharacterSize(40);
    SettingsText.setFillColor(sf::Color::White);
    SettingsText.setPosition(60, 500);

    ModNameText.setFont(font);
    ModNameText.setString("Mods");
    ModNameText.setCharacterSize(40);
    ModNameText.setFillColor(sf::Color::White);
    ModNameText.setPosition(60, 600);

    ExitText.setFont(font);
    ExitText.setString("Exit");
    ExitText.setCharacterSize(40);
    ExitText.setFillColor(sf::Color::White);
    ExitText.setPosition(60, 700);

    GameNameText.setFont(font);
    GameNameText.setString("Pixel-Warriors");
    GameNameText.setCharacterSize(55);
    GameNameText.setFillColor(sf::Color(204, 155, 248));
    GameNameText.setPosition(700, 50);

    for (int i = 0; i < 5; i++) {
        settings[i].setFont(font);
        settings[i].setCharacterSize(30);
        settings[i].setFillColor(sf::Color::White);
    }

    settings[0].setString("Exit");
    settings[0].setCharacterSize(40);
    settings[1].setString("Audio");
    settings[2].setString("Graphics");
    settings[3].setString("Apply");
    settings[3].setCharacterSize(40);
    settings[4].setString("Keys");

    settings[0].setPosition(60, 700);
    settings[1].setPosition(60, 400);
    settings[2].setPosition(60, 300);
    settings[3].setPosition(200, 700);
    settings[4].setPosition(60, 500);

    std::cout << "[INFO]: menu initialized is successful" << std::endl;
}

extern "C" __declspec(dllexport) void menuLib(sf::RenderWindow& window, int& menuStatus) {
    window.clear(sf::Color(43, 63, 114));
    mousePosition = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        exitmenu = true;
    if (menuStatus == 0) {
        //Create World
        if (CreateWorldText.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            CreateWorldText.setFillColor(colorHover);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                menuStatus = 2;
        }
        else {
            CreateWorldText.setFillColor(colorNormal);
        }
        //Settings
        if (SettingsText.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            SettingsText.setFillColor(colorHover);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                menuStatus = 3;
        }
        else {
            SettingsText.setFillColor(colorNormal);
        }
        //Mods
        if (ModNameText.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            ModNameText.setFillColor(colorHover);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                menuStatus = 4;
        }
        else {
            ModNameText.setFillColor(colorNormal);
        }
        //Exit
        if (ExitText.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            ExitText.setFillColor(colorHover);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && exitmenu) {
                std::cout << "Exit" << std::endl;
                window.close();
                exitmenu = false;
                return;
            }
        }
        else {
            ExitText.setFillColor(colorNormal);
        }

        window.draw(GameNameText);
        window.draw(CreateWorldText);
        window.draw(SettingsText);
        window.draw(ModNameText);
        window.draw(ExitText);
    }
    else if (menuStatus == 2) {

    }
    else if (menuStatus == 3) {
        SettingLogic(window, menuStatus);
    }
    else if (menuStatus == 4) {

    }
}
void SettingLogic(sf::RenderWindow& window, int& menuStatus) {
    //exit
    if (settings[0].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        settings[0].setFillColor(colorHover);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && exitmenu) {
            std::cout << "Exit menu" << std::endl;
            menuStatus = 0;
            SettingsStatus = 0;
            exitmenu = false;
        }
    }
    //audio
    if (settings[1].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            SettingsStatus = 1;
    }
    //graphics
    if (settings[2].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            SettingsStatus = 0;
    }
    //keys
    if (settings[4].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            SettingsStatus = 3;
    }
    //apply
    if (settings[3].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        settings[3].setFillColor(colorHover);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            menuStatus = 0;
            SettingsStatus = 0;
        }
    }
    if (SettingsStatus == 0) {
        settings[2].setFillColor(colorHover);
    } else if (SettingsStatus == 1) {
        settings[1].setFillColor(colorHover);
    } else if (SettingsStatus == 3) {
        settings[4].setFillColor(colorHover);
    }

    for (int i = 0; i < 5; i++) {
        window.draw(settings[i]);
        settings[i].setFillColor(colorNormal);
    }
    window.draw(GameNameText);
}
