#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <fstream>
#include "TextureManager.h"
#include "Tile.h"
#include "Random.h"


struct Board
{
private:

	bool game_is_over;
	bool game_is_lost;
	bool game_is_won;

	bool paused = false;
	bool debug_enabled = false;

	string username;
	int width, height;
	int board_size;

	int num_tiles;
	int max_tiles;

	int tiles_revealed;

	int reveal_count;
	int max_reveal_count;

	int number_flags;
	int number_mines;
	int maximum_flags;
	int const_flag_value;

	

	int clock_time_pause_pressed = 0;
	int clock_time_unpause_pressed = 0;
	int clock_total_timePaused = 0;
	int final_time = 0;

	bool first_game = true;

	/*Leaderboard Variables*/ // Could make a class for this even

	bool gameWon_leaderboardShown = false;
	bool button_pause_clicked = false;

	int leaderboard_first_time;
	int leaderboard_max_first_time;

	int leaderboard_second_time;
	int leaderboard_max_second_time;

	int leaderboard_third_time;
	int leaderboard_max_third_time;

	int leaderboard_fourth_time;
	int leaderboard_max_fourth_time;

	int leaderboard_fifth_time;
	int leaderboard_max_fifth_time;
	
	int leaderboard_index_value;

	
	
	/*End Leaderboard Variables*/

public:
	sf::Clock clock;

	vector<Tile> tileVector;
	vector <string> leaderBoardTop5;

	sf::Sprite icon_SmileFace;
	sf::Sprite icon_pause_button;
	sf::Sprite icon_play_button;
	sf::Sprite icon_debug_button;
	

	sf::Sprite icon_leaderboard_button;

	sf::Sprite timer_thousands_digit;
	sf::Sprite timer_hundreds_digit;
	sf::Sprite timer_tens_digit;
	sf::Sprite timer_ones_digit;

	sf::Sprite counter_hundreds_digit;
	sf::Sprite counter_tens_digit;
	sf::Sprite counter_ones_digit;
	sf::Sprite counter_negative_digit;

	
	sf::Font font_minesweeperFont_ttf;

	sf::Text text_leaderboard_word;
	sf::Text text_leaderboardText_top5;
	sf::Text text_hidden_text;

	/*Begin functions*/
	Board();
	Board(int _width, int _height, int _number_mines, sf::Font& font_minesweeperFont_ttf);

	void game_loop_user_input(sf::RenderWindow& window_, sf::Event& eventListener); // This is our "game loop"
	bool debug_gameLoop_running(sf::RenderWindow& window_);

	void checkForESC(sf::RenderWindow& window_, sf::Event& eventListener);

	bool debug_get_win_status();
	bool debug_get_lost_status();
	bool debug_get_gameOver_status();

	void drawEverything(sf::RenderWindow& window__); // This function both draws tiles and draws icons
	void draw_icons(sf::RenderWindow& window);
	void draw_icons_everythiing(RenderWindow& windowA, Sprite& a, Sprite& b, Sprite& c, Sprite& d);

	void start_game();
	int debug_start_game();
	int debug_start_game2();
	void reset_game();
	void debug_game();
	
	void debug_reset_game();
	
	void set_first_game();

	void printBoardInformation();
	void setBoardInformation();

	void randomize_board_bombs();
	void getToggle_Icon_Numbers();
	void drawTiles(sf::RenderWindow& window__);
	
	void setName(string& userInputt);
	string debug_get_username();
	void set_leaderboard(int widthh, int heightt, sf::Text& text_leaderboard_word, sf::Text& prompt, sf::Text& inputt, sf::Font& Fonttt);
	bool debug_leaderboard_open(sf::RenderWindow& leaderboard_window);
	void update_counter();
	void update_timer();
	void set_icons();
	bool mouseButtonReleased = false;
	bool clicked = false;
	void setGameOver(bool gameO);
	void setGameLost(bool gameL);
	void setGameWon(bool gameW);

	void drawAndDisplay(RenderWindow &window_);

	void read_leaderboard(vector<string>& top5);
	void ReadandSetLeaderBoard(vector<string>& top5, int widthh, int heightt, sf::Text& text_leaderboard_word, sf::Text& prompt, sf::Text& inputt, sf::Font& Fonttt);
	void debug_set_leaderboard_values(vector<string>& leaderboard_top_5);
	bool debug_leaderboard_full(vector<string>& leaderboard_top_5);
	void update_leaderboard(vector<string>& top5, int playerTime, string username);
	
	void cycleLeaderBoard(RenderWindow& windowLeader, sf::Color colorHere, Text& leaderboardWord, Text& leaderboardTop5);

};
