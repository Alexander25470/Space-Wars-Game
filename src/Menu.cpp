#include "Menu.h"

Menu::Menu()
{
}

void Menu::initializer()
{
    sf::SoundBuffer shotSoundBuffer;
    shotSoundBuffer.loadFromFile("sounds\\menuback.wav");

    font.loadFromFile("fonts/PressStart2P-Regular.ttf");
    loadConfig();


    icon.loadFromFile("images/icon.png");


    if (fullScreenn)
        window1.create(sf::VideoMode(width, height), "Space Wars", sf::Style::Fullscreen);
    else
        window1.create(sf::VideoMode(width, height), "Space Wars");

    //window1.create(sf::VideoMode(width,height),"Galaxy Wars");
    //window1.create(sf::VideoMode(width,height),"Galaxy Wars",sf::Style::Fullscreen);

    window1.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

    /*width=_width;
    height=_height;*/
    j = 0;
    k = 0;

    if (language.compare("en") == 0)
    {
        playText.initializer("PLAY", width / 2, 100, font, 100);
        highScoreText.initializer("HIGH SCORE", width / 2, 200, font, 100);
        optionsText.initializer("OPTIONS", width / 2, 300, font, 100);
        exitText.initializer("QUIT", width / 2, 400, font, 100);
    }
    else if (language.compare("es") == 0)
    {
        playText.initializer("JUGAR", width / 2, 100, font, 100);
        highScoreText.initializer("SCORE+ALTO", width / 2, 200, font, 100);
        optionsText.initializer("OPCIONES", width / 2, 300, font, 100);
        exitText.initializer("SALIR", width / 2, 400, font, 100);
    }

    //aca inicializar las cosas
    window1.setFramerateLimit(60);
    //cargo imagen de fondo
    backgroundTexture.loadFromFile("images\\spritesheet.png");
    background.setTexture(&backgroundTexture);
    background.setSize(sf::Vector2f(width, height));

    gameLoop();
}

void Menu::gameLoop()
{
    while (window1.isOpen())
    {
        eventListener();
        //std::cout<<((int)j)<<std::endl<<" "<<((int)k)<<std::endl;
        //sf::Sprite asd(backgroundTexture,sf::IntRect(((int)j)*1500,((int)k)*900,1500,900));
        background.setTextureRect(sf::IntRect(((int)j) * 1500, ((int)k) * 900, 1500, 900));
        j += 0.1f;
        if (((int)j) == 3)
        {
            j = 0;
            k += 1.0f;
        };
        if (((int)k) == 6)
        {
            j = 0;
            k = 0;
        }
        //playText.checkMouseColition(window1);
        playText.update();
        highScoreText.update();
        optionsText.update();
        exitText.update();
        drawWindow();
    }
}
void Menu::eventListener()
{
    while (window1.pollEvent(event))
    {
        //sf::Vector2i mousePos=sf::Mouse::getPosition(window1);
        if (event.type == sf::Event::Closed)
            window1.close();
        if (event.type == sf::Event::MouseMoved)
        {
            if (playText.checkMouseColition(window1))
            {
                playText.updateSelection(true);
            }
            else
            {
                playText.updateSelection(false);
            }
            if (highScoreText.checkMouseColition(window1))
            {
                highScoreText.updateSelection(true);
            }
            else
            {
                highScoreText.updateSelection(false);
            }
            if (optionsText.checkMouseColition(window1))
            {
                optionsText.updateSelection(true);
            }
            else
            {
                optionsText.updateSelection(false);
            }
            if (exitText.checkMouseColition(window1))
            {
                exitText.updateSelection(true);
            }
            else
            {
                exitText.updateSelection(false);
            }
        }

        if (playText.isClicked(window1))
        {
            Game partida_l(width, height, language, window1);
        }
        if (exitText.isClicked(window1))
        {
            window1.close();
        }
        if (optionsText.isClicked(window1))
        {
            optionsMenu();
        }
        if (highScoreText.isClicked(window1))
        {
            highScoreMenu();
        }
    }
}
void Menu::drawWindow()
{
    window1.clear();

    //aca mostrar todo lo necesario
    window1.draw(background);
    playText.draw(window1);
    highScoreText.draw(window1);
    optionsText.draw(window1);
    exitText.draw(window1);

    window1.display();
}

void Menu::loadConfig()
{
    std::string s;
    std::vector<std::string> lines;
    std::vector<std::string> configAux;
    std::vector<int> config;
    std::ifstream f("game.cfg");
    if (f.is_open())
    {
        int linea = 0;
        while (!f.eof() && linea <= 4)
        {
            std::getline(f, s);
            lines.push_back(s);
            linea++;
        }
        for (std::string line : lines)
        {
            std::string cosa = line.substr(line.find(": ") + 2, line.find("\n"));
            //cosa.pop_back();
            configAux.push_back(cosa);
        }
        for (std::string cosa : configAux)
        {
            std::cout << cosa << std::endl;
        }

        language = (configAux[0]);
        width = stoi(configAux[2]);
        height = stoi(configAux[3]);
        fullScreenn = stoi(configAux[4]);
    }
    else
    {
        std::cerr << "Error de apertura del archivo." << std::endl;
        std::ofstream f("game.cfg", std::ofstream::out);
        if (f.is_open())
        {
            f << "Language: "
              << "en" << std::endl;
            f << "Difficulty: "
              << "1" << std::endl;
            f << "Width: "
              << "1280" << std::endl;
            f << "Height: "
              << "720" << std::endl;
            f << "FullScreen: "
              << "0" << std::endl;
            std::cout << "nuevo archivo creado" << std::endl;
        }
        else
        {
            std::cout << "error de archivo";
        }
        loadConfig();
    }
}
void Menu::highScoreMenu()
{

    sf::Text title;
    sf::Text score;
    title.setFont(font);
    score.setFont(font);
    title.setColor(sf::Color(255, 255, 255));
    score.setColor(sf::Color(255, 255, 255));
    std::string scoreString;

    scoreString = readHighestScore() >= 0 ? std::to_string(readHighestScore()) + "pts" : (language.compare("es") == 0 ? "No hay puntajes registrados" : "No scores recorded");

    score.setString(scoreString);
    score.setOrigin(score.getGlobalBounds().width / 2, score.getGlobalBounds().height / 2);
    score.setPosition(width / 2, height / 2);

    if (language.compare("en") == 0)
    {
        backButton.initializer("Back", (50 * 3) + 25, height - 50, font, 50);
        title.setString("High score:");
        title.setCharacterSize(45);
    }
    else if (language.compare("es") == 0)
    {
        backButton.initializer("Volver", (50 * 3) + 25, height - 50, font, 50);
        title.setString("La puntuacion mas alta fue:");
        title.setCharacterSize(45);
    }
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setPosition(width / 2, 50);
    bool exit = false;
    while (window1.isOpen() && !exit)
    {
        sf::Event event1;
        while (window1.pollEvent(event1))
        {
            if (event1.type == sf::Event::Closed)
                window1.close();
            if (event1.type == sf::Event::MouseMoved)
            {
                if (backButton.checkMouseColition(window1))
                {
                    backButton.updateSelection(true);
                }
                else
                {
                    backButton.updateSelection(false);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                exit = true;
            }
            if (backButton.isClicked(window1))
            {
                exit = true;
            }
        }

        backButton.update();

        window1.clear();
        backButton.draw(window1);
        window1.draw(title);
        window1.draw(score);
        window1.display();
    }
}
void Menu::changeResolution(int &widthR, int &heightR, bool up)
{
    if (up)
    {
        if (widthR == 1280 && heightR == 720)
        {
            widthR = 1366;
            heightR = 768;
        }
        else if (widthR == 1366 && heightR == 768)
        {
            widthR = 1600;
            heightR = 900;
        }
        else if (widthR == 1600 && heightR == 900)
        {
            widthR = 1920;
            heightR = 1080;
        }
        else
        {
            widthR = 1280;
            heightR = 720;
        }
    }
    else
    {
        if (widthR == 1920 && heightR == 1080)
        {
            widthR = 1600;
            heightR = 900;
        }
        else if (widthR == 1600 && heightR == 900)
        {
            widthR = 1366;
            heightR = 768;
        }
        else if (widthR == 1366 && heightR == 768)
        {
            widthR = 1280;
            heightR = 720;
        }
        else
        {
            widthR = 1920;
            heightR = 1080;
        }
    }
}

void Menu::optionsMenu()
{
    std::string languageAux = language;
    bool fullScreenAux = fullScreenn;
    int widthAux = width;
    int heightAux = height;

    sf::Text resolutionTittle;
    resolutionTittle.setFont(font);
    resolutionTittle.setCharacterSize(50);
    sf::Text languageTittle;
    languageTittle.setFont(font);
    languageTittle.setCharacterSize(50);
    sf::Text winModeTittle;
    winModeTittle.setFont(font);
    winModeTittle.setCharacterSize(50);

    sf::Text resText;
    resText.setFont(font);
    resText.setCharacterSize(40);
    std::string resString = std::to_string(widthAux) + "*" + std::to_string(heightAux);
    resText.setString(resString);

    sf::Text langText;
    langText.setFont(font);
    langText.setCharacterSize(40);
    std::string langString = language;
    langText.setString(langString);

    sf::Text screenModeText;
    screenModeText.setFont(font);
    screenModeText.setCharacterSize(40);
    std::string screenModeString;
    screenModeText.setString(screenModeString);

    SelectableText saveButton;

    SelectableText increaseResButton;
    increaseResButton.initializer("->", (width / 5) * 4, 125, font, 50);
    SelectableText decreaseResButton;
    decreaseResButton.initializer("<-", (width / 5) * 1, 125, font, 50);

    SelectableText increaseLangButton;
    increaseLangButton.initializer("->", (width / 5) * 4, 250, font, 50);
    SelectableText decreaseLangButton;
    decreaseLangButton.initializer("<-", (width / 5) * 1, 250, font, 50);

    SelectableText increaseWindowMode;
    increaseWindowMode.initializer("->", (width / 5) * 4, 375, font, 50);
    SelectableText decreaseWindowMode;
    decreaseWindowMode.initializer("<-", (width / 5) * 1, 375, font, 50);

    if (language.compare("en") == 0)
    {
        backButton.initializer("Back", (50 * 3) + 25, height - 50, font, 50);
        saveButton.initializer("Save", width - ((50 * 2) + 25), height - 50, font, 50);
        resolutionTittle.setString("Resolution");
        languageTittle.setString("Language");
        winModeTittle.setString("Screen Mode");
        screenModeString = fullScreenn == true ? "Full Screen" : "Window";
        langString = "English";
    }
    else if (language.compare("es") == 0)
    {
        backButton.initializer("Volver", (50 * 3) + 25, height - 50, font, 50);
        saveButton.initializer("Guardar", width - ((50 * 3) + 25), height - 50, font, 50);
        resolutionTittle.setString("Resolucion");
        languageTittle.setString("Idioma");
        winModeTittle.setString("Modo");
        screenModeString = fullScreenn == true ? "Pantalla Completa" : "Modo Ventana";
        langString = "espa\xF1ol";
    }
    screenModeText.setString(screenModeString);
    langText.setString(langString);

    resolutionTittle.setOrigin(resolutionTittle.getGlobalBounds().width / 2, resolutionTittle.getGlobalBounds().height / 2);
    resolutionTittle.setPosition(width / 2, 50);
    languageTittle.setOrigin(languageTittle.getGlobalBounds().width / 2, languageTittle.getGlobalBounds().height / 2);
    languageTittle.setPosition(width / 2, 180);
    winModeTittle.setOrigin(winModeTittle.getGlobalBounds().width / 2, winModeTittle.getGlobalBounds().height / 2);
    winModeTittle.setPosition(width / 2, 310);

    resText.setOrigin(resText.getGlobalBounds().width / 2, resText.getGlobalBounds().height / 2);
    resText.setPosition(width / 2, 115);

    langText.setOrigin(langText.getGlobalBounds().width / 2, langText.getGlobalBounds().height / 2);
    langText.setPosition(width / 2, 245);

    screenModeText.setOrigin(screenModeText.getGlobalBounds().width / 2, screenModeText.getGlobalBounds().height / 2);
    screenModeText.setPosition(width / 2, 375);

    sf::Event event1;
    bool exit = false;
    while (window1.isOpen() && !exit)
    {
        while (window1.pollEvent(event1))
        {
            if (event1.type == sf::Event::Closed)
                window1.close();
            if (event1.type == sf::Event::MouseMoved)
            {
                if (backButton.checkMouseColition(window1))
                {
                    backButton.updateSelection(true);
                }
                else
                {
                    backButton.updateSelection(false);
                }
                if (increaseResButton.checkMouseColition(window1))
                {
                    increaseResButton.updateSelection(true);
                }
                else
                {
                    increaseResButton.updateSelection(false);
                }
                if (decreaseResButton.checkMouseColition(window1))
                {
                    decreaseResButton.updateSelection(true);
                }
                else
                {
                    decreaseResButton.updateSelection(false);
                }
                ///------------------
                if (increaseLangButton.checkMouseColition(window1))
                {
                    increaseLangButton.updateSelection(true);
                }
                else
                {
                    increaseLangButton.updateSelection(false);
                }
                if (decreaseLangButton.checkMouseColition(window1))
                {
                    decreaseLangButton.updateSelection(true);
                }
                else
                {
                    decreaseLangButton.updateSelection(false);
                }
                ///------------------
                if (increaseWindowMode.checkMouseColition(window1))
                {
                    increaseWindowMode.updateSelection(true);
                }
                else
                {
                    increaseWindowMode.updateSelection(false);
                }
                if (decreaseWindowMode.checkMouseColition(window1))
                {
                    decreaseWindowMode.updateSelection(true);
                }
                else
                {
                    decreaseWindowMode.updateSelection(false);
                }
                ///------------------
                if (saveButton.checkMouseColition(window1))
                {
                    saveButton.updateSelection(true);
                }
                else
                {
                    saveButton.updateSelection(false);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                exit = true;
            }
            if (backButton.isClicked(window1))
            {
                exit = true;
            }
            if (saveButton.isClicked(window1))
            {
                std::ofstream f("game.cfg", std::ofstream::out);
                if (f.is_open())
                {
                    f << "Language: " << languageAux << std::endl;
                    f << "Difficulty: "
                      << "1" << std::endl;
                    f << "Width: " << widthAux << std::endl;
                    f << "Height: " << heightAux << std::endl;
                    f << "FullScreen: " << fullScreenAux << std::endl;
                    exit = true;
                    std::cout << "guardado";
                    this->initializer();
                }
                else
                {
                    std::cout << "error de archivo";
                }
            }
            if (increaseResButton.isClicked(window1))
            {
                changeResolution(widthAux, heightAux, true);
                resString = std::to_string(widthAux) + "*" + std::to_string(heightAux);
                resText.setString(resString);
                resText.setOrigin(resText.getGlobalBounds().width / 2, resText.getGlobalBounds().height / 2);
                resText.setPosition(width / 2, 115);
            }
            if (decreaseResButton.isClicked(window1))
            {
                changeResolution(widthAux, heightAux, false);
                resString = std::to_string(widthAux) + "*" + std::to_string(heightAux);
                resText.setString(resString);
                resText.setOrigin(resText.getGlobalBounds().width / 2, resText.getGlobalBounds().height / 2);
                resText.setPosition(width / 2, 115);
            }
            //----------------------------------------

            if (increaseLangButton.isClicked(window1) || decreaseLangButton.isClicked(window1))
            {
                languageAux = (languageAux.compare("en") == 0) ? "es" : "en";
                if (language.compare("en") == 0)
                {
                    langString = (languageAux.compare("en") == 0) ? "english" : "spanish";
                }
                else if (language.compare("es") == 0)
                {
                    langString = (languageAux.compare("en") == 0) ? "ingl\xE9s" : "espa\xF1ol";
                }
                langText.setString(langString);
                langText.setOrigin(langText.getGlobalBounds().width / 2, langText.getGlobalBounds().height / 2);
                langText.setPosition(width / 2, 245);
            }

            if (increaseWindowMode.isClicked(window1) || decreaseWindowMode.isClicked(window1))
            {
                //aumentar modo ventana
                fullScreenAux = fullScreenAux ? false : true;
                if (language.compare("en") == 0)
                {
                    screenModeString = (fullScreenAux == true) ? "Full Screen" : "Window";
                }
                else if (language.compare("es") == 0)
                {
                    screenModeString = (fullScreenAux == true) ? "Pantalla Completa" : "Modo Ventana";
                }
                screenModeText.setString(screenModeString);
                screenModeText.setOrigin(screenModeText.getGlobalBounds().width / 2, screenModeText.getGlobalBounds().height / 2);
                screenModeText.setPosition(width / 2, 375);
            }
        }

        backButton.update();
        increaseResButton.update();
        decreaseResButton.update();

        increaseLangButton.update();
        decreaseLangButton.update();

        increaseWindowMode.update();
        decreaseWindowMode.update();

        saveButton.update();

        window1.clear();
        increaseResButton.draw(window1);
        decreaseResButton.draw(window1);
        backButton.draw(window1);
        increaseLangButton.draw(window1);
        decreaseLangButton.draw(window1);
        increaseWindowMode.draw(window1);
        decreaseWindowMode.draw(window1);
        saveButton.draw(window1);
        window1.draw(resolutionTittle);
        window1.draw(languageTittle);
        window1.draw(winModeTittle);
        window1.draw(resText);
        window1.draw(langText);
        window1.draw(screenModeText);
        window1.display();
    }
}
int Menu::readHighestScore()
{
    int leyo;
    int regint;
    FILE *p;
    p = fopen("highScore.dat", "rb");
    if (p == NULL)
        return -1;
    fseek(p, 0, 0); ///es lo mismo que fseek(p,sizeof (regint)*0,0);
    leyo = fread(&regint, sizeof regint, 1, p);
    fclose(p);
    if (leyo == 0)
        return -2;
    return regint;
}
