
/*

The main.cpp file initializes and controls the flow of the Minesweeper game. It starts by reading the configuration file (board_config.cfg) to determine 
the game's dimensions (number of rows and columns) and the number of mines to be placed. It then creates an initial welcome window where the user can enter 
their name, which is used for the leaderboard. Once the player starts the game, the main function sets up the game window with the specified dimensions 
and initializes a Board object to handle the game logic, rendering, and interactions. Inside the main game loop, it continuously checks for events like mouse 
clicks to reveal tiles, place flags, and handle other user actions until the window is closed or the game ends. Finally, the textures and resources are cleared 
when the game concludes.


*/



#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Board.h"
using namespace std;
using namespace sf;

void ConfigFile(int& columns, int& rows, int& numbMines)
{
    ifstream readFile("files/board_config.cfg");
    string read_lineInFile;

    getline(readFile, read_lineInFile);
    int checkThis = stoi(read_lineInFile);
    columns = stoi(read_lineInFile);
    getline(readFile, read_lineInFile);
    checkThis = stoi(read_lineInFile);
    rows = stoi(read_lineInFile);
    getline(readFile, read_lineInFile);
    int mines = stoi(read_lineInFile);
    numbMines = stoi(read_lineInFile);
    readFile.close();
}

void readFont(sf::Font &Font) // I break everything into functions for readability
{
    Font.loadFromFile("files/font.ttf");
}



void WelcomeWindowSetup(int width, int height, sf::Text& welcomeText, sf::Text& enterName, sf::Text& userInputt, sf::Font& textFont)
{
    //This runs only once, therefore these are just the default values.
    welcomeText.setString("WELCOME TO MINESWEEPER!");
    welcomeText.setFont(textFont);
    welcomeText.setCharacterSize(24);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    sf::FloatRect welcomeTextBounds = welcomeText.getLocalBounds();
    welcomeText.setOrigin(welcomeTextBounds.left + welcomeTextBounds.width / 2.0f, welcomeTextBounds.top + welcomeTextBounds.height / 2.0f);
    const Vector2f welcomeTextOrigin = welcomeText.getOrigin();
    welcomeText.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 150));
    //Enter your name: 
    enterName.setString("Enter your name: ");
    enterName.setFont(textFont);
    enterName.setCharacterSize(20);
    enterName.setStyle(sf::Text::Bold);
    sf::FloatRect enterNameBounds = enterName.getLocalBounds();
    enterName.setOrigin(enterNameBounds.left + enterNameBounds.width / 2.0f, enterNameBounds.top + enterNameBounds.height / 2.0f);
    const Vector2f enterNameOrigin = enterName.getOrigin();
    enterName.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 75));
    //User Input
    userInputt.setString("|");
    userInputt.setFont(textFont);
    userInputt.setFillColor(sf::Color::Yellow);
    userInputt.setCharacterSize(18);
    userInputt.setStyle(sf::Text::Bold);
    if (width > 0)
    {
    sf::FloatRect inputTextRect = userInputt.getLocalBounds();
    int newplace = width * height;
    userInputt.setOrigin(inputTextRect.left + inputTextRect.width / 2.0f, inputTextRect.top + inputTextRect.height / 2.0f);
    const Vector2f userInputtOrigin = userInputt.getOrigin();
    userInputt.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 45));
    }
    
}


void WelcomeWindowDraw(sf::RenderWindow& welcomeWindow, sf::Text& welcomeText, sf::Text& enterName, sf::Text& userInput)
{
    bool completed = false;
    welcomeWindow.draw(welcomeText);
    welcomeWindow.draw(enterName);
    welcomeWindow.draw(userInput);
    completed = true;
}

void GameWindow()
{

}


int main()
{
    //Might need a boolean for window closed

    bool beginGame = false;
    string nameText;
    int columns;
    int rows;
    int number_mines;
    string gameTitle = "Minesweeper";
    ConfigFile(columns, rows, number_mines);
    //int width = 800;
    //int height = 612;
    int width = columns * 32;
    int height = (rows * 32) + 100;
    int mineCount = number_mines;
    string filePath = "files/";
    bool checkedString = false;
    sf::Text welcomeMinesweeper, enterName, userInput;
    sf::Font Font;
    readFont(Font);
    nameText = "";
    sf::RenderWindow WelcomeWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
    const Vector2f userInputOrigin;
    WelcomeWindowSetup(width, height, welcomeMinesweeper, enterName, userInput, Font);
    while (WelcomeWindow.isOpen())
    {
        sf::Event event;
        while (WelcomeWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            { // User presses X
                beginGame = false;
                WelcomeWindow.close();
            }   

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && nameText.length() > 0)
            {
                WelcomeWindow.close();
                if (beginGame == false)
                {
                    beginGame = true;
                }
                else
                {
                    beginGame = true;
                }
            }

            if (event.type == sf::Event::TextEntered)
            {
                int nameLength;
                if (nameText.length() < 10)
                {
                    if ((nameText.length() == -69) || (event.text.unicode < 90 && event.text.unicode > 64) || (event.text.unicode < 123 && event.text.unicode > 96))
                    {
                        //I have a function to set nameText equal to -69 for testing. Hopefully that statement does not run
                        bool check = false;
                        int count = 0;
                        nameLength = 0;
                        nameText += static_cast<char>(event.text.unicode);
                        nameText[0] = toupper(nameText[0]);
                        string suppercase = nameText;
                        suppercase[0] = toupper(nameText[0]);
                        if (suppercase == ("~"))
                        {
                            cout << "Something broke! Check user input!";
                        }
                        for (unsigned int i = 1; i < nameText.length(); i+=1)
                        {
                            nameText[i] = tolower(nameText[i]);
                            count+=1;
                        }
                        userInput.setString(nameText + "|");
                        nameLength = nameText.length();
                        sf::FloatRect inputTextRect = userInput.getLocalBounds(); // This recenters the code
                        userInput.setOrigin(inputTextRect.left + inputTextRect.width / 2.0f,
                         inputTextRect.top + inputTextRect.height / 2.0f);
                         //userInputOrigin = userInput.getOrigin();
                        userInput.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 45));
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
                {

                    if (nameText.length() < 0)
                    {
                        nameText = "";
                        nameLength = nameText.length();
                    }

                    if (nameText.length() > 0)
                    {
                        nameText = nameText.substr(0, nameText.length() - 1);
                        nameText[0] = toupper(nameText[0]);
                        string uppercase = nameText;
                        uppercase[0] = toupper(nameText[0]);
                        if (uppercase == ("~"))
                        {
                            cout << "Something broke! Check user input!";
                        }
                        for (unsigned int i = 1; i < nameText.length(); i+=1)
                        {
                            nameText[i] = tolower(nameText[i]);
                        }
                        userInput.setString(nameText + "|");
                        nameLength = nameText.length();
                        sf::FloatRect inputTextRect = userInput.getLocalBounds();
                        userInput.setOrigin(inputTextRect.left + inputTextRect.width / 2.0f,
                            inputTextRect.top + inputTextRect.height / 2.0f);
                         //userInputOrigin = userInput.getOrigin();
                        userInput.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f - 45));
                    }
                }

            }


        }

        WelcomeWindow.clear(sf::Color::Blue);
        WelcomeWindowDraw(WelcomeWindow, welcomeMinesweeper, enterName, userInput);
        WelcomeWindow.display();
    }

    if (beginGame)
    {
        sf::RenderWindow GameWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
        bool leaderboardOpen = false;
        Board board(width, height, mineCount, Font);
        board.setName(nameText);
        board.set_icons();
        board.reset_game();
        board.set_first_game();
        while (GameWindow.isOpen() && beginGame)
        {
            sf::Event event;
            while (GameWindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    GameWindow.close();

                }

                if (leaderboardOpen == true)
                {

                }

            }
            GameWindow.clear(sf::Color::White);
            board.game_loop_user_input(GameWindow, event);
            GameWindow.display();
        }
    }

    TextureManager::Clear();
    return 0;
}

