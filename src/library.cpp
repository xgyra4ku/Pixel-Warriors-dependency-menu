#include "../include/library.h"

float referenceWidth = 1280.0f;
float referenceHeight = 800.0f;
float referenceTextSize = 30.0f;

// Текущие размеры окна
float currentWidth;
float currentHeight;

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

sf::Vector2u windowSize;


extern "C" __declspec(dllexport) void initLib(sf::RenderWindow& window) {
    if (!font.loadFromFile("Dependency/font.otf")) {
        std::cerr << "ERROR: Failed to initialize menu. Failed to load font" << std::endl;
        window.close();
        return;
    }

    windowSize = window.getSize();

    float xText = percentage(4.69f, windowSize.x);

    CreateWorldText.setFont(font);
    CreateWorldText.setString("Create World");
    CreateWorldText.setCharacterSize(textSizeOptimization(windowSize, 40.0f));
    CreateWorldText.setFillColor(sf::Color::White);
    CreateWorldText.setPosition(xText, percentage(50.0f, windowSize.y));

    SettingsText.setFont(font);
    SettingsText.setString("Settings");
    SettingsText.setCharacterSize(textSizeOptimization(windowSize, 40.0f));
    SettingsText.setFillColor(sf::Color::White);
    SettingsText.setPosition(xText, percentage(62.5f, windowSize.y));

    ModNameText.setFont(font);
    ModNameText.setString("Mods");
    ModNameText.setCharacterSize(textSizeOptimization(windowSize, 40.0f));
    ModNameText.setFillColor(sf::Color::White);
    ModNameText.setPosition(xText, percentage(75.0f, windowSize.y));

    ExitText.setFont(font);
    ExitText.setString("Exit");
    ExitText.setCharacterSize(textSizeOptimization(windowSize, 40.0f));
    ExitText.setFillColor(sf::Color::White);
    ExitText.setPosition(xText, percentage(87.5f, windowSize.y));

    GameNameText.setFont(font);
    GameNameText.setString("Pixel-Warriors");
    GameNameText.setCharacterSize(textSizeOptimization(windowSize, 60.0f));
    GameNameText.setFillColor(sf::Color(204, 155, 248));
    GameNameText.setPosition(percentage(54.69, windowSize.x), 50);

    for (int i = 0; i < 5; i++) {
        settings[i].setFont(font);
        settings[i].setCharacterSize(textSizeOptimization(windowSize, 30.0f));
        settings[i].setFillColor(sf::Color::White);

        settingsGraphics[i].setFont(font);
        settingsGraphics[i].setCharacterSize(textSizeOptimization(windowSize, 30.0f));
        settingsGraphics[i].setFillColor(sf::Color::White);
    }

    settings[0].setString("Exit");
    settings[0].setCharacterSize(40);
    settings[1].setString("Audio");
    settings[2].setString("Graphics");
    settings[3].setString("Apply");
    settings[3].setCharacterSize(40);
    settings[4].setString("Keys");

    settings[0].setPosition(xText, percentage(87.5f, windowSize.y));
    settings[1].setPosition(xText, percentage(50.0f, windowSize.y));
    settings[2].setPosition(xText, percentage(37.5f, windowSize.y));
    settings[3].setPosition(percentage(15.63f, windowSize.x), percentage(87.5f, windowSize.y));
    settings[4].setPosition(xText, percentage(62.5f, windowSize.y));

    std::cout << "INFO: menu initialized is successful" << std::endl;
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


float percentage(float percent, unsigned int num) {
    return (percent / 100) * num;
}

unsigned int textSizeOptimization(sf::Vector2u currentSize, float textSize) {
    return int(textSize * (std::sqrt(std::pow((currentSize.x / 1280.0f), 2) + std::pow((currentSize.y / 800.0f), 2)) / std::sqrt(2)));
}

