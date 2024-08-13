#include "../include/library.h"

float referenceWidth = 1280.0f;
float referenceHeight = 800.0f;
float referenceTextSize = 30.0f;

// Текущие размеры окна
float currentWidth;
float currentHeight;

int SettingsStatus = 0;

bool exitMenu = false;
bool settingMapCopy = false;
bool button_OFF_ON[2];
bool buttonMouseLeft = false;

std::map<std::string, int> settings_map_copy_map;

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
sf::Text settingsGraphics[10];

sf::RectangleShape button_rectangle_shape[5];
sf::RectangleShape button_shape[5];

sf::ConvexShape triangle[2];


sf::Vector2u windowSize;

int displaySolutionIndex = 0;
int displaySolution[17][2] = {
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
    }

    settings[0].setString("Exit");
    settings[0].setCharacterSize(textSizeOptimization(windowSize, 40.0f));
    settings[1].setString("Audio");
    settings[2].setString("Graphics");
    settings[3].setString("Apply");
    settings[3].setCharacterSize(textSizeOptimization(windowSize, 40.0f));
    settings[4].setString("Keys");

    settings[0].setPosition(xText, percentage(87.5f, windowSize.y));
    settings[1].setPosition(xText, percentage(50.0f, windowSize.y));
    settings[2].setPosition(xText, percentage(37.5f, windowSize.y));
    settings[3].setPosition(percentage(15.63f, windowSize.x), percentage(87.5f, windowSize.y));
    settings[4].setPosition(xText, percentage(62.5f, windowSize.y));


    for (auto& el : settingsGraphics) {
        el.setFont(font);
        el.setCharacterSize(textSizeOptimization(windowSize, 30.0f));
        el.setFillColor(sf::Color::White);
    }

    settingsGraphics[0].setString("Resolution:");
    settingsGraphics[0].setPosition(percentage(23.44f, windowSize.x), percentage(37.5f, windowSize.y));  // X=300/1280=23.44%

    settingsGraphics[1].setString("Fullscreen:");
    settingsGraphics[1].setPosition(percentage(23.44f, windowSize.x), percentage(50.0f, windowSize.y));  // X=300/1280=23.44%

    settingsGraphics[2].setString("Fps:");
    settingsGraphics[2].setPosition(percentage(23.44f, windowSize.x), percentage(62.5f, windowSize.y));  // X=300/1280=23.44%

    settingsGraphics[3].setString("60");
    settingsGraphics[3].setPosition(percentage(36.72f, windowSize.x), percentage(62.5f, windowSize.y));  // X=470/1280=36.72%

    settingsGraphics[4].setString("120");
    settingsGraphics[4].setPosition(percentage(46.88f, windowSize.x), percentage(62.5f, windowSize.y));  // X=600/1280=46.88%

    settingsGraphics[5].setString("Max");
    settingsGraphics[5].setPosition(percentage(60.16f, windowSize.x), percentage(62.5f, windowSize.y));  // X=770/1280=60.16%

    settingsGraphics[6].setString("V-sync");
    settingsGraphics[6].setPosition(percentage(74.22f, windowSize.x), percentage(62.5f, windowSize.y));  // X=950/1280=74.22%

    settingsGraphics[7].setPosition(percentage(68.75f, windowSize.x), percentage(37.5f, windowSize.y));  // X=880/1280=68.75%



    for (int i = 0; i < 17; i++) {
        if (displaySolution[i][0] == windowSize.x && displaySolution[i][1] == windowSize.y) {
            displaySolutionIndex = i;
            settingsGraphics[7].setString(std::to_string(displaySolution[displaySolutionIndex][0])
                    + 'x' + std::to_string(displaySolution[displaySolutionIndex][1]));
            break;
        }
    }

    for (int i = 0; i < 5; i++) {
        button_rectangle_shape[i].setFillColor(sf::Color(255, 255, 255));
        button_shape[i].setFillColor(sf::Color(10,10,10));
    }

    //function buttons
    //fullscreen
    button_rectangle_shape[0].setSize(sf::Vector2f(percentage(1.17f, windowSize.x), percentage(1.88f, windowSize.y)));
    button_rectangle_shape[0].setPosition(percentage(85.94f, windowSize.x), percentage(52.0f, windowSize.y));

    button_shape[0].setSize(sf::Vector2f(percentage(1.02f, windowSize.x), percentage(1.63f, windowSize.y)));
    button_shape[0].setPosition(percentage(86.02f, windowSize.x), percentage(52.13f, windowSize.y));
    //V-sync
    button_rectangle_shape[1].setSize(sf::Vector2f(percentage(1.17f, windowSize.x), percentage(1.88f, windowSize.y)));
    button_rectangle_shape[1].setPosition(percentage(85.94f, windowSize.x), percentage(64.13f, windowSize.y));

    button_shape[1].setSize(sf::Vector2f(percentage(1.02f, windowSize.x), percentage(1.63f, windowSize.y)));
    button_shape[1].setPosition(percentage(86.02f, windowSize.x), percentage(64.25f, windowSize.y));
    //60
    button_rectangle_shape[2].setSize(sf::Vector2f(percentage(1.17f, windowSize.x), percentage(1.88f, windowSize.y)));
    button_rectangle_shape[2].setPosition(percentage(41.8f, windowSize.x), percentage(64.13f, windowSize.y));

    button_shape[2].setSize(sf::Vector2f(percentage(1.02f, windowSize.x), percentage(1.63f, windowSize.y)));
    button_shape[2].setPosition(percentage(41.88, windowSize.x), percentage(64.25f, windowSize.y));
    //120
    button_rectangle_shape[3].setSize(sf::Vector2f(percentage(1.17f, windowSize.x), percentage(1.88f, windowSize.y)));
    button_rectangle_shape[3].setPosition(percentage(53.52f, windowSize.x), percentage(64.13f, windowSize.y));

    button_shape[3].setSize(sf::Vector2f(percentage(1.02f, windowSize.x), percentage(1.63f, windowSize.y)));
    button_shape[3].setPosition(percentage(53.59f, windowSize.x), percentage(64.25f, windowSize.y));
    //Max
    button_rectangle_shape[4].setSize(sf::Vector2f(percentage(1.17f, windowSize.x), percentage(1.88f, windowSize.y)));
    button_rectangle_shape[4].setPosition(percentage(67.19f, windowSize.x), percentage(64.13f, windowSize.y));

    button_shape[4].setSize(sf::Vector2f(percentage(1.02f, windowSize.x), percentage(1.63f, windowSize.y)));
    button_shape[4].setPosition(percentage(67.27f, windowSize.x), percentage(64.25f, windowSize.y));

    // end function buttons


    triangle[0].setPointCount(3);
    triangle[0].setPoint(0, sf::Vector2f(percentage(66.25f, windowSize.x), percentage(40.0f, windowSize.y)));
    triangle[0].setPoint(1, sf::Vector2f(percentage(67.42f, windowSize.x), percentage(41.25f, windowSize.y)));
    triangle[0].setPoint(2, sf::Vector2f(percentage(67.42f, windowSize.x), percentage(38.75f, windowSize.y)));
    triangle[0].setFillColor(sf::Color(10, 10, 10));

    triangle[1].setPointCount(3);
    triangle[1].setPoint(0, sf::Vector2f(percentage(87.11f, windowSize.x), percentage(40.0f, windowSize.y)));
    triangle[1].setPoint(1, sf::Vector2f(percentage(85.94f, windowSize.x), percentage(41.25f, windowSize.y)));
    triangle[1].setPoint(2, sf::Vector2f(percentage(85.94f, windowSize.x), percentage(38.75f, windowSize.y)));
    triangle[1].setFillColor(sf::Color(10, 10, 10));


    std::cout << "INFO: menu initialized is successful" << std::endl;
}

extern "C" __declspec(dllexport) void menuLib(sf::RenderWindow& window, int& menuStatus, std::map<std::string, int>& settingsMap) {
    window.clear(sf::Color(43, 63, 114));
    mousePosition = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    //std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        exitMenu = true;
    if (menuStatus == 0) {

        //Create World
        if (CreateWorldText.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            CreateWorldText.setFillColor(colorHover);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                menuStatus = -1;
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
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && exitMenu) {
                std::cout << "INFO: Exit" << std::endl;
                window.close();
                exitMenu = false;
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
        SettingLogic(window, menuStatus, settingsMap);
    }
    else if (menuStatus == 4) {

    }

    buttonMouseLeft = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
void SettingLogic(sf::RenderWindow& window, int& menuStatus, std::map<std::string, int>& settingsMap) {
    if (!settingMapCopy) {
        settings_map_copy_map = settingsMap;
        settingMapCopy = true;
    }
    //exit
    if (settings[0].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        settings[0].setFillColor(colorHover);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && exitMenu) {
            std::cout << "Exit menu" << std::endl;
            menuStatus = 0;
            SettingsStatus = 0;
            exitMenu = false;
            settingMapCopy = false;
        }
    }
    //audio
    if (settings[1].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            SettingsStatus = 1;
            settings[1].setFillColor(colorHover);
        }
    }
    //graphics
    if (settings[2].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            SettingsStatus = 0;
            settings[2].setFillColor(colorHover);
        }
    }
    //keys
    if (settings[4].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            SettingsStatus = 3;
            settings[4].setFillColor(colorHover);
        }
    }
    //apply
    if (settings[3].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        settings[3].setFillColor(colorHover);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !buttonMouseLeft) {
            menuStatus = -2;
            settings_map_copy_map["windowWidth"] = displaySolution[displaySolutionIndex][0];
            settings_map_copy_map["windowHeight"] = displaySolution[displaySolutionIndex][1];
            settingsMap = settings_map_copy_map;
            settingMapCopy = false;
        }
    }
    if (SettingsStatus == 0) {

        if (collisionMouse(mousePosition, button_rectangle_shape[0].getSize(), button_rectangle_shape[0].getPosition())) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !buttonMouseLeft) {
                settings_map_copy_map["fullscreen"] = !settings_map_copy_map["fullscreen"];
            }
        }
        if (collisionMouse(mousePosition, button_rectangle_shape[1].getSize(), button_rectangle_shape[1].getPosition())) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !buttonMouseLeft) {
                settings_map_copy_map["V-sync"] = !settings_map_copy_map["V-sync"];
                settings_map_copy_map["fps"] = 0;
            }
        }
        if (collisionMouse(mousePosition, button_rectangle_shape[2].getSize(), button_rectangle_shape[2].getPosition())) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !buttonMouseLeft) {
                settings_map_copy_map["fps"] = 60;
                settings_map_copy_map["V-sync"] = 0;
            }
        }
        if (collisionMouse(mousePosition, button_rectangle_shape[3].getSize(), button_rectangle_shape[3].getPosition())) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !buttonMouseLeft) {
                settings_map_copy_map["fps"] = 120;
                settings_map_copy_map["V-sync"] = 0;
            }
        }
        if (collisionMouse(mousePosition, button_rectangle_shape[4].getSize(), button_rectangle_shape[4].getPosition())) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !buttonMouseLeft) {
                settings_map_copy_map["fps"] = -1;
                settings_map_copy_map["V-sync"] = 0;
            }
        }

        if (collisionMouse(mousePosition, sf::Vector2f(15,15), sf::Vector2f(percentage(85.94f, windowSize.x), percentage(38.75f, windowSize.y)))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !buttonMouseLeft) {

                if (displaySolutionIndex >= 16) {
                    displaySolutionIndex = 0;
                } else {
                    displaySolutionIndex++;
                }
                settingsGraphics[7].setString(std::to_string(displaySolution[displaySolutionIndex][0])
                    + 'x' + std::to_string(displaySolution[displaySolutionIndex][1]));
            }
        }

        if (collisionMouse(mousePosition, sf::Vector2f(15,15), sf::Vector2f(percentage(66.25f, windowSize.x), percentage(38.75f, windowSize.y)))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !buttonMouseLeft) {

                if (displaySolutionIndex <= 0) {
                    displaySolutionIndex = 16;
                } else {
                    displaySolutionIndex--;
                }
                settingsGraphics[7].setString(std::to_string(displaySolution[displaySolutionIndex][0])
                    + 'x' + std::to_string(displaySolution[displaySolutionIndex][1]));
            }
        }

        //draw
        for (const auto &el : settingsGraphics) {
            window.draw(el);
        }
        for (const auto &el : button_rectangle_shape) {
            window.draw(el);
        }

        if (settings_map_copy_map["fullscreen"] == 1) {
            window.draw(button_shape[0]);
        }
        if (settings_map_copy_map["V-sync"] == 1) {
            window.draw(button_shape[1]);
        } else {
             switch (settings_map_copy_map["fps"]) {
            case -1:
                window.draw(button_shape[4]);
                 break;
            case 60:
                window.draw(button_shape[2]);
                 break;
            case 120:
                window.draw(button_shape[3]);
                 break;
            default:
                 break;
            }
        }
        window.draw(triangle[0]);
        window.draw(triangle[1]);
        //std::cout << "Display solution index: "<< displaySolutionIndex << std::endl;

    } else if (SettingsStatus == 1) {

    } else if (SettingsStatus == 3) {

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
bool collisionMouse(const sf::Vector2f& mousePosition, const sf::Vector2f shapeSize, const sf::Vector2f shapePosition) {
    if (float(mousePosition.x) >= shapePosition.x &&
        float(mousePosition.x) <= shapePosition.x + shapeSize.x &&
        float(mousePosition.y) >= shapePosition.y &&
        float(mousePosition.y) <= shapePosition.y + shapeSize.y) {
        return true;
    }
    return false;
}


