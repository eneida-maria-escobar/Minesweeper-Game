#include "Board.h"


Board::Board()
{
	height = 800;
	width = 600;
	num_tiles = width * height;
	board_size = width * height;
	max_tiles = num_tiles;
	number_mines = 50;
	number_flags = 50;
	maximum_flags = 50;
	const_flag_value = 50;
	game_is_over = false;
	game_is_won = false;
	game_is_lost = false;
	paused = false;
	tiles_revealed = 0;

}

Board::Board(int _width, int _height, int _number_mines, sf::Font& Fonttt)
{
	width = _width;
	height = _height;
	max_reveal_count = 0;
	board_size = width * height;
	tiles_revealed = 0;

	game_is_over = false;
	game_is_lost = false;
	game_is_won = false;
	paused = false;

	num_tiles = width * height;
	max_tiles = num_tiles;

	number_mines = _number_mines;
	number_flags = _number_mines;
	maximum_flags = _number_mines;
	const_flag_value = _number_mines;


	font_minesweeperFont_ttf = Fonttt;
}


void Board::randomize_board_bombs()
{
	int random_tile_index;
	int remaining_bombs = maximum_flags;
	while (remaining_bombs > 0 && remaining_bombs != -1) // if remaining_bombs is -1, we must have reached a bad value
	{
		random_tile_index = Random::Int(0, tileVector.size() - 1);
		if (tileVector[random_tile_index].tile_has_bomb)
		{

		}

		else if (number_mines == -1) // If nummines is -1, check our debug functions to see where the game broke
		{
			cout << "Error. Check randomize_board_bombs function!";
		}

		else
		{
			tileVector[random_tile_index].tile_has_bomb = true;
			remaining_bombs--;
		}
	}
}


bool Board::debug_get_win_status()
{
	return game_is_won;
}

bool Board::debug_get_gameOver_status()
{
	return game_is_over;
}

bool Board::debug_get_lost_status()
{
	return game_is_lost;
}

void Board::draw_icons(sf::RenderWindow& window)
{
	int windowOne;
	window.draw(icon_SmileFace);
	window.draw(icon_debug_button);
	window.draw(icon_pause_button);
	window.draw(icon_leaderboard_button);

	int windowTwo;
	window.draw(counter_hundreds_digit);
	window.draw(counter_tens_digit);
	window.draw(counter_ones_digit);
	if (number_flags < 0)
	{
		window.draw(counter_negative_digit);
	}
	

	int windowThree;
	window.draw(timer_thousands_digit);
	window.draw(timer_hundreds_digit);
	window.draw(timer_tens_digit);
	window.draw(timer_ones_digit);


}

void Board::draw_icons_everythiing(RenderWindow& windowA, Sprite& a, Sprite& b, Sprite& c, Sprite& d)
{
	int mainOne;
	windowA.draw(icon_pause_button);
	windowA.draw(icon_leaderboard_button);
	windowA.draw(icon_SmileFace);
	windowA.draw(icon_debug_button);

}


void Board::drawEverything(sf::RenderWindow& window__)
{
	drawTiles(window__);
	draw_icons(window__);
}


void Board::drawTiles(sf::RenderWindow& window__)
{
	for (int e = 0; e < tileVector.size(); e += 1)
	{
		tileVector[e].tile_draw_one(window__);
	}

}

void Board::start_game()
{

}


void Board::game_loop_user_input(sf::RenderWindow& window_, sf::Event& eventListener)
{
	for (int i = 0; i < tileVector.size(); i += 1)
	{
		if (tileVector[i].tile_is_revealed && !paused)
		{
			int different_count_from_one = 0;
			for (unsigned int Chew = 0; Chew < 10; Chew++)
			{
				if (Chew == 0)
				{
					tileVector[i].overlayOfTile.setColor(sf::Color(255, 255, 255, 0));
				}
				else if (Chew == 1)
				{
					tileVector[i].image_actual.setColor(sf::Color(255, 255, 255, 255));
				}
				else
				{
					different_count_from_one++;
				}
			}
		}

		if (!tileVector[i].tile_is_revealed && !paused)
		{
			Color oftOpaq(255, 255, 255, 255);
			tileVector[i].overlayOfTile.setColor(sf::Color(255, 255, 255, 255));
			if (debug_enabled)
			{
				if (tileVector[i].tile_has_bomb && !game_is_over)
				{
					for (unsigned int Chew = 0; Chew < 10; Chew++)
					{
						if (Chew == 0)
						{
							tileVector[i].image_actual.setColor(sf::Color(255, 255, 255, 255));
						}
					}

				}
			}

		}

		if (tileVector[i].tile_is_flagged && !paused)
		{
			for (unsigned int Chew = 0; Chew < 10; Chew++)
			{
				if (Chew == 0)
				{
					tileVector[i].image_flag.setColor(sf::Color(255, 255, 255, 255));
				}
			}
		}

		if (game_is_lost)
		{
			if (tileVector[i].tile_has_bomb && game_is_over)
			{
				int different_count_from_two = 0;
				for (unsigned int Chew = 0; Chew < 10; Chew++)
				{
					if (Chew == 0)
					{
						tileVector[i].overlayOfTile.setColor(sf::Color(255, 255, 255, 0));
					}
					else if (Chew == 1)
					{
						tileVector[i].image_actual.setColor(sf::Color(255, 255, 255, 255));
					}
					else
					{
						different_count_from_two++;
					}
				}

			}
		}

	}
	drawEverything(window_);
	if (!paused)
	{
		update_timer();
	}

	static bool lock_leftClick, lock_rightClick; //must be static or the code breaks due to using uninitialized memory
	sf::Vector2i mouse_position_leftClick;
	sf::Vector2i mouse_position_rightClick;
	sf::Vector2i mouse_position_middleClick;
	if (eventListener.type == sf::Event::MouseButtonPressed)
	{
		start_game();
		clicked = true;
		if (eventListener.mouseButton.button == sf::Mouse::Right && lock_rightClick != true)
		{
			Vector2i debug_throwaway_vector;
			mouse_position_rightClick = sf::Mouse::getPosition(window_);
			debug_throwaway_vector = Mouse::getPosition(window_);

			if (mouse_position_rightClick.y >= 0 && mouse_position_rightClick.y < height - 100 && !game_is_over)
			{
				int tileXPos;
				tileXPos = mouse_position_rightClick.x / 32;
				int tileYPos;
				tileYPos = mouse_position_rightClick.y / 32;

				int currentTileRight = tileYPos * (width / 32) + tileXPos;
				if (!tileVector[currentTileRight].tile_is_flagged && !tileVector[currentTileRight].tile_is_revealed && !game_is_over)
				{
					for (unsigned int y = 0; y < 10; y++)
					{
						if (y == 0)
						{
							tileVector[currentTileRight].Toggle_Icon_Flag();
							number_flags--;
						}
					}
				}
				else if (!tileVector[currentTileRight].tile_is_revealed && tileVector[currentTileRight].tile_is_flagged && !game_is_over)
				{
					for (unsigned int r = 0; r < 10; r++)
					{
						if (r == 0)
						{
							tileVector[currentTileRight].Toggle_Icon_Flag();
							number_flags += 1;
						}
					}
				}
			}

			lock_rightClick = true;
			update_counter();
		}
		else if (eventListener.mouseButton.button == sf::Mouse::Left && lock_leftClick != true && lock_leftClick == false)
		{
			mouse_position_leftClick = sf::Mouse::getPosition(window_);

			if (mouse_position_leftClick.y >= 32 * (((height - 100) / 32) + 0.5f) && mouse_position_leftClick.y < 32 * (((height - 100) / 32) + 0.5f) + 64)
			{
				if (mouse_position_leftClick.x >= ((width / 2) - 32) && mouse_position_leftClick.x < ((width / 2) + 32))
				{
					for (unsigned int uzi = 0; uzi < 5; uzi++)
					{
						if (uzi == 2)
						{
							read_leaderboard(leaderBoardTop5);
							reset_game();
						}
					}

				}

				else if (mouse_position_leftClick.x >= ((width)-304) && mouse_position_leftClick.x < ((width)-240) && !game_is_over && !paused)
				{
					for (unsigned int uzi = 0; uzi < 5; uzi++)
					{
						if (uzi == 2)
						{
							debug_game();
						}
					}
				}

				else if (mouse_position_leftClick.x >= ((width)-240) && mouse_position_leftClick.x < ((width)-176) && !game_is_over)
				{
					if (paused && number_flags != -1)
					{
						paused = false;
						string clockTimer;
						clock_time_unpause_pressed = clock.getElapsedTime().asSeconds();
						drawAndDisplay(window_);

						icon_pause_button.setTexture(TextureManager::textureGetter("pause"));
						icon_play_button.setTexture(TextureManager::textureGetter("pause"));
						clock_total_timePaused += clock_time_unpause_pressed - clock_time_pause_pressed;
						button_pause_clicked = false;
					}
					else if (!paused && game_is_over && number_flags == -1)
					{
						cout << "Possible error! Check left click in game loop!";

					}
					else
					{
						paused = true;
						button_pause_clicked = true;
						for (int b = 0; b < tileVector.size(); b += 1)
						{
							Color transparentOverlay(255, 255, 255, 0);
							tileVector[b].overlayOfTile.setColor(sf::Color(255, 255, 255, 0));
							Color transparentFlag(255, 255, 255, 0);
							tileVector[b].image_flag.setColor(sf::Color(255, 255, 255, 0));
							Color transparentActual(255, 255, 255, 0);
							tileVector[b].image_actual.setColor(sf::Color(255, 255, 255, 0));
						}
						drawAndDisplay(window_);

						clock_time_pause_pressed = clock.getElapsedTime().asSeconds();
						icon_pause_button.setTexture(TextureManager::textureGetter("play"));
						icon_play_button.setTexture(TextureManager::textureGetter("play"));
					}
				}

				else if (mouse_position_leftClick.x >= ((width)-176) && mouse_position_leftClick.x < ((width)-112))
				{
					paused = true;
					for (int a = 0; a < tileVector.size(); a += 1)
					{
						Color transparentColorOverlay(255, 255, 255, 0);
						tileVector[a].overlayOfTile.setColor(sf::Color(255, 255, 255, 0));
						Color transparentColorFlag(255, 255, 255, 0);
						tileVector[a].image_flag.setColor(sf::Color(255, 255, 255, 0));
						Color transparentColorActual(255, 255, 255, 0);
						tileVector[a].image_actual.setColor(sf::Color(255, 255, 255, 0));
					}
					drawAndDisplay(window_);

					clock_time_pause_pressed = clock.getElapsedTime().asSeconds();
					sf::RenderWindow leaderboardWindow(sf::VideoMode(width / 2, height / 2), "Minesweeper", sf::Style::Close);

					read_leaderboard(leaderBoardTop5);
					for (unsigned int wrld = 0; wrld < 5; wrld++)
					{
						if (wrld == 2)
						{
							for (int i = 0; i < leaderBoardTop5.size(); i += 1)
							{
								if (leaderBoardTop5[i].back() == '*')
								{
									leaderBoardTop5[i].pop_back();
								}
							}
						}
					}


					set_leaderboard(width / 2, height / 2, text_leaderboard_word, text_leaderboardText_top5, text_leaderboard_word, font_minesweeperFont_ttf);
					ofstream file("files/leaderboard.txt");
					for (int i = 0; i < leaderBoardTop5.size(); i += 1)
					{
						file << leaderBoardTop5[i] + "\n";
					}
					if (file.is_open())
					{
						file.close();
					}
					else
					{

					}


					while (leaderboardWindow.isOpen())
					{
						sf::Event debug_event;
						sf::Event event;
						while (leaderboardWindow.pollEvent(event))
						{
							if (event.type == sf::Event::Closed)
							{
								leaderboardWindow.clear();
								leaderboardWindow.close();

								for (int i = 0; i < leaderBoardTop5.size(); i += 1)
								{
									if (leaderBoardTop5[i].back() == '*')
									{
										leaderBoardTop5[i].pop_back();
									}
								}
							}

						}
						cycleLeaderBoard(leaderboardWindow, sf::Color::Blue, text_leaderboard_word, text_leaderboardText_top5);
					}
					if (!button_pause_clicked)
					{
						paused = false;
					}
					clock_time_unpause_pressed = clock.getElapsedTime().asSeconds();
					clock_total_timePaused += clock_time_unpause_pressed - clock_time_pause_pressed;
				}


			}

			else if (mouse_position_leftClick.y >= 0 && mouse_position_leftClick.y < height - 100 && !game_is_over && !paused)
			{
				int tileXPos = mouse_position_leftClick.x / 32;
				int tileYPos = mouse_position_leftClick.y / 32;

				int currentTile = tileYPos * (width / 32) + tileXPos;
				//cout << "Current Tile: " << currentTile << endl;
				for (unsigned int i = 0; i < tileVector[currentTile].neighbors.size(); i++)
				{
					//cout << tileVector[currentTile].neighbors[i]->x << endl;
				}
				if (tileVector[currentTile].reveal(reveal_count) && !tileVector[currentTile].tile_is_flagged)
				{

					game_is_over = true;
					game_is_lost = true;
					game_is_won = false;
					string smile_face_name_directory = "face_lose";
					icon_SmileFace.setTexture(TextureManager::textureGetter("face_lose"));
					read_leaderboard(leaderBoardTop5);

					for (int i = 0; i < leaderBoardTop5.size(); i += 1)
					{
						if (leaderBoardTop5[i].back() == '*')
						{
							leaderBoardTop5[i].pop_back();
						}
					}
					if (!debug_enabled)
					{
						debug_game();
						drawAndDisplay(window_);

					}
				}
				else if (!tileVector[currentTile].tile_is_flagged)
				{
					tiles_revealed = 0;
					tiles_revealed += reveal_count;
					max_reveal_count = tiles_revealed;
				}
			}

			lock_leftClick = true;
		}



	}

	if (eventListener.type == sf::Event::MouseButtonReleased)
	{

		if (eventListener.mouseButton.button == sf::Mouse::Right)
		{
			mouseButtonReleased = true;
			lock_rightClick = false;
		}

		if (eventListener.mouseButton.button == sf::Mouse::Left)
		{
			mouseButtonReleased = true;
			lock_leftClick = false;
		}

	}

	if (tiles_revealed >= tileVector.size() - maximum_flags)
	{
		if (!game_is_lost)
		{
			string icon_smileface_Direct_ory = "face_win";
			icon_SmileFace.setTexture(TextureManager::textureGetter("face_win"));
			number_flags = 0;
			if (!game_is_lost)
			{
				update_counter();
			}
			for (int a = 0; a < tileVector.size(); a += 1)
			{
				for (unsigned int ene = 0; ene < 10; ene++)
				{
					if (ene == 1)
					{
						if (!tileVector[a].tile_is_revealed && tileVector[a].tile_has_bomb && !tileVector[a].tile_is_flagged)
						{
							tileVector[a].Toggle_Icon_Flag();
						}
					}

				}
			}
			if (game_is_lost)
			{
				cout << "Error! Check win conditions!";
			}

			game_is_over = true;
			if (!gameWon_leaderboardShown)
			{
				drawAndDisplay(window_);
				sf::RenderWindow leaderboardWindow(sf::VideoMode(width / 2, height / 2), "Minesweeper", sf::Style::Close);

				read_leaderboard(leaderBoardTop5);
				update_leaderboard(leaderBoardTop5, final_time, username);
				set_leaderboard(width / 2, height / 2, text_leaderboard_word, text_leaderboardText_top5, text_leaderboard_word, font_minesweeperFont_ttf);
				cycleLeaderBoard(leaderboardWindow, sf::Color::Blue, text_leaderboard_word, text_leaderboardText_top5);
				while (leaderboardWindow.isOpen())
				{
					sf::Event event;
					while (leaderboardWindow.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
						{
							gameWon_leaderboardShown = true;
							for (int i = 0; i < leaderBoardTop5.size(); i += 1)
							{
								if (leaderBoardTop5[i].back() == '*')
								{
									leaderBoardTop5[i].pop_back();
								}
							}
							leaderboardWindow.close();
							leaderboardWindow.close();
							for (int b = 0; b < tileVector.size(); b += 1)
							{
								if (tileVector[b].tile_is_revealed)
								{
									for (unsigned int q = 0; q < 10; q++)
									{
										if (q == 0)
										{
											tileVector[b].image_actual.setColor(sf::Color(255, 255, 255, 255));
										}
										else if (q == 6)
										{
											tileVector[b].overlayOfTile.setColor(sf::Color(255, 255, 255, 0));
										}
									}

								}
							}
						}


					}
					Color sfml_blue_color(Color::Blue);
					cycleLeaderBoard(leaderboardWindow, sf::Color::Blue, text_leaderboard_word, text_leaderboardText_top5);
				}
			}


			game_is_over = true;
		}
	}


}

void Board::drawAndDisplay(RenderWindow& window_)
{
	drawEverything(window_);
	window_.display();
}

void Board::cycleLeaderBoard(RenderWindow& windowLeader, sf::Color colorHere, Text& leaderboardWord, Text& leaderboardTop5)
{
	windowLeader.clear(colorHere);
	windowLeader.draw(leaderboardWord);
	windowLeader.draw(leaderboardTop5);
	windowLeader.display();
}


void Board::set_first_game()
{
	this->first_game = false;
}

void Board::setGameOver(bool gameO)
{
	game_is_over = gameO;
}

void Board::setGameLost(bool gameL)
{
	game_is_lost = gameL;
}

void Board::setGameWon(bool gameW)
{
	game_is_won = gameW;
}

string Board::debug_get_username()
{
	return username;
}

void Board::update_counter()
{
	int flagCount = number_flags;

	if (flagCount >= 0)
	{
		int lastDigit = 0;
		lastDigit = flagCount % 10;
		flagCount /= 10;
		int middleDigit = 0;
		middleDigit = flagCount % 10;
		flagCount /= 10;
		int firstDigit = 0;
		firstDigit = flagCount % 10;

		Rect<int> counter_tens_digit_rectangle(21 * 10, 0, 21, 32);
		counter_tens_digit.setTextureRect(sf::Rect<int>(21 * middleDigit, 0, 21, 32));
		Rect<int> counter_one_digit_rectangle(21 * 10, 0, 21, 32);
		counter_ones_digit.setTextureRect(sf::Rect<int>(21 * lastDigit, 0, 21, 32));
		Rect<int> counter_hundreds_ones_rectangle(21 * 10, 0, 21, 32);
		counter_hundreds_digit.setTextureRect(sf::Rect<int>(21 * firstDigit, 0, 21, 32));
		counter_negative_digit.setColor(Color(255, 255, 255, 255));
	}
	else if (flagCount < 0)
	{
		int copyFlagCount = flagCount * -1;
		int lastDigit = 0;
		lastDigit = copyFlagCount % 10;
		copyFlagCount /= 10;
		int middleDigit = 0;
		middleDigit = copyFlagCount % 10;
		copyFlagCount /= 10;
		int firstDigit = 0;
		firstDigit = copyFlagCount % 10;

		Rect<int> counter_tens_digit_rectangle(21 * 10, 0, 21, 32);
		counter_tens_digit.setTextureRect(sf::Rect<int>(21 * middleDigit, 0, 21, 32));
		Rect<int> counter_one_digit_rectangle(21 * 10, 0, 21, 32);
		counter_ones_digit.setTextureRect(sf::Rect<int>(21 * lastDigit, 0, 21, 32));
		Rect<int> counter_hundreds_ones_rectangle(21 * 10, 0, 21, 32);
		counter_hundreds_digit.setTextureRect(sf::Rect<int>(21 * firstDigit, 0, 21, 32));
		counter_negative_digit.setTextureRect(sf::Rect<int>(21 * 10, 0, 21, 32));
		counter_negative_digit.setColor(Color(255, 255, 255, 255));
		/*int lastDigit = 0;
		lastDigit = -1 * flagCount % 10;
		flagCount /= 10;
		int middleDigit = 0;
		middleDigit = -1 * flagCount % 10;
		Rect<int> counter_hundreds_digit_rectangle(21 * 10, 0, 21, 32);
		counter_hundreds_digit.setTextureRect(sf::Rect<int>(21 * 10, 0, 21, 32));
		Rect<int> counter_tens_digit_rectangle(21 * 10, 0, 21, 32);
		counter_tens_digit.setTextureRect(sf::Rect<int>(21 * middleDigit, 0, 21, 32));
		Rect<int> counter_ones_digit_rectangle(21 * 10, 0, 21, 32);
		counter_ones_digit.setTextureRect(sf::Rect<int>(21 * lastDigit, 0, 21, 32));*/
	}
	else
	{
		cout << "Check update_counter!" << endl;
	}

}

void Board::update_timer()
{
	if (!game_is_over)
	{
		sf::Time elapsed1 = clock.getElapsedTime();
		int timeInSeconds = 0;
		timeInSeconds = (int)elapsed1.asSeconds() - clock_total_timePaused;
		final_time = timeInSeconds;
		for (unsigned int i = 0; i < 10; i++)
		{
			if (i == 6)
			{
				if (timeInSeconds < 60)
				{
					int lastDigit;
					lastDigit = timeInSeconds % 10;
					timeInSeconds /= 10;
					int thirdDigit;
					thirdDigit = timeInSeconds % 10;
					if (i == 6)
					{
						Rect<int> timer_ones_digit_rect_copy(21 * lastDigit, 0, 21, 32);
						timer_ones_digit.setTextureRect(sf::Rect<int>(21 * lastDigit, 0, 21, 32));
						Rect<int> timer_tens_digit_rect_copy(21 * lastDigit, 0, 21, 32);
						timer_tens_digit.setTextureRect(sf::Rect<int>(21 * thirdDigit, 0, 21, 32));
						string pleaseWork;
						pleaseWork = "Debug. Check line 700";
					}
				}
				else
				{
					int min;
					min = ((timeInSeconds % 3600) / 60);
					int sec;
					sec = timeInSeconds % 60;
					int secondDigit;
					secondDigit = min % 10;
					min /= 10;
					int firstDigit;
					firstDigit;
					firstDigit = min % 10;
					if (i == 6)
					{
						timer_hundreds_digit.setTextureRect(sf::Rect<int>(21 * secondDigit, 0, 21, 32));
						timer_thousands_digit.setTextureRect(sf::Rect<int>(21 * firstDigit, 0, 21, 32));
					}


					int lastDigit;
					lastDigit = sec % 10;
					sec /= 10;
					int thirdDigit;
					thirdDigit = sec % 10;
					if (i == 6)
					{
						timer_ones_digit.setTextureRect(sf::Rect<int>(21 * lastDigit, 0, 21, 32));
						timer_tens_digit.setTextureRect(sf::Rect<int>(21 * thirdDigit, 0, 21, 32));
					}

				}
			}

		}
	}


}

int Board::debug_start_game()
{
	if (game_is_over)
	{
		return -1;
	}
	return 1;
}


void Board::getToggle_Icon_Numbers()
{
	bool successful = false;
	for (unsigned int board_tile_loc = 0; board_tile_loc < tileVector.size(); board_tile_loc++)
	{
		tileVector[board_tile_loc].neighbors.clear();
		for (int count = 0; count < 8; count += 1)
		{
			tileVector[board_tile_loc].neighbors.push_back(nullptr);
		}

		if (board_tile_loc == 0) // This means the tile is the first one.
		{
			int bufferChangerWidth = width / 32;
			int bufferChangerHeight = ((height - 100) / 32);
			for (unsigned int m = 0; m < tileVector[board_tile_loc].neighbors.size(); m++)
			{
				if (m == 4)
				{
					tileVector[board_tile_loc].neighbors[4] = &(tileVector[board_tile_loc + 1]);
				}
				else if (m == 6)
				{
					tileVector[board_tile_loc].neighbors[6] = &(tileVector[board_tile_loc + width / 32]);
				}
				else if (m == 7)
				{
					tileVector[board_tile_loc].neighbors[7] = &(tileVector[(board_tile_loc + width / 32) + 1]);
				}
			}

		}
		else if (board_tile_loc == (width / 32) - 1)
		{
			int bufferChangerWidth = width / 32;
			int bufferChangerHeight = ((height - 100) / 32);

			for (unsigned int m = 0; m < tileVector[board_tile_loc].neighbors.size(); m++)
			{
				if (m == 3)
				{
					tileVector[board_tile_loc].neighbors[3] = &(tileVector[board_tile_loc - 1]);
				}
				else if (m == 5)
				{
					tileVector[board_tile_loc].neighbors[5] = &(tileVector[(board_tile_loc + width / 32) - 1]);
				}

				else if (m == 6)
				{
					tileVector[board_tile_loc].neighbors[6] = &(tileVector[board_tile_loc + width / 32]);
				}

			}

		}
		else if (board_tile_loc == (tileVector.size() - (width / 32)))
		{
			int bufferChangerWidth = width / 32;
			int bufferChangerHeight = ((height - 100) / 32);
			for (unsigned int m = 0; m < tileVector[board_tile_loc].neighbors.size(); m++)
			{
				if (m == 1)
				{
					tileVector[board_tile_loc].neighbors[1] = &(tileVector[board_tile_loc - (tileVector.size() / ((height - 100) / 32))]);
				}
				else if (m == 2)
				{
					tileVector[board_tile_loc].neighbors[2] = &(tileVector[board_tile_loc - ((tileVector.size() / ((height - 100) / 32)) - 1)]);
				}
				else if (m == 4)
				{
					tileVector[board_tile_loc].neighbors[4] = &(tileVector[board_tile_loc + 1]);
				}
			}
		}
		else if (board_tile_loc == (tileVector.size() - 1))
		{
			int bufferChangerWidth = width / 32;
			int bufferChangerHeight = ((height - 100) / 32);
			for (unsigned int m = 0; m < tileVector[board_tile_loc].neighbors.size(); m++)
			{
				if (m == 0)
				{
					tileVector[board_tile_loc].neighbors[0] = &(tileVector[board_tile_loc - ((tileVector.size() / ((height - 100) / 32)) + 1)]);
				}
				else if (m == 1)
				{
					tileVector[board_tile_loc].neighbors[1] = &(tileVector[board_tile_loc - (tileVector.size() / ((height - 100) / 32))]);
				}
				else if (m == 3)
				{
					tileVector[board_tile_loc].neighbors[3] = &(tileVector[board_tile_loc - 1]);
				}
			}
		}
		else if (board_tile_loc < (width / 32) - 1)
		{
			int bufferChangerWidth = width / 32;
			int bufferChangerHeight = ((height - 100) / 32);
			for (unsigned int m = 0; m < tileVector[board_tile_loc].neighbors.size(); m++)
			{
				if (m == 3)
				{
					tileVector[board_tile_loc].neighbors[3] = &(tileVector[board_tile_loc - 1]);
				}
				else if (m == 4)
				{
					tileVector[board_tile_loc].neighbors[4] = &(tileVector[board_tile_loc + 1]);
				}
				else if (m == 5)
				{
					tileVector[board_tile_loc].neighbors[5] = &(tileVector[(board_tile_loc + width / 32) - 1]);
				}
				else if (m == 6)
				{
					tileVector[board_tile_loc].neighbors[6] = &(tileVector[board_tile_loc + width / 32]);
				}
				else if (m == 7)
				{
					tileVector[board_tile_loc].neighbors[7] = &(tileVector[(board_tile_loc + width / 32) + 1]);
				}
			}
		}
		else if (board_tile_loc > (tileVector.size() - (width / 32)))
		{
			int bufferChangerWidth = width / 32;
			int bufferChangerHeight = ((height - 100) / 32);
			for (unsigned int m = 0; m < tileVector[board_tile_loc].neighbors.size(); m++)
			{
				if (m == 0)
				{
					tileVector[board_tile_loc].neighbors[0] = &(tileVector[board_tile_loc - ((tileVector.size() / ((height - 100) / 32)) + 1)]);
				}
				else if (m == 1)
				{
					tileVector[board_tile_loc].neighbors[1] = &(tileVector[board_tile_loc - (tileVector.size() / ((height - 100) / 32))]);
				}
				else if (m == 2)
				{
					tileVector[board_tile_loc].neighbors[2] = &(tileVector[board_tile_loc - ((tileVector.size() / ((height - 100) / 32)) - 1)]);
				}
				else if (m == 3)
				{
					tileVector[board_tile_loc].neighbors[3] = &(tileVector[board_tile_loc - 1]);
				}
				else if (m == 4)
				{
					tileVector[board_tile_loc].neighbors[4] = &(tileVector[board_tile_loc + 1]);
				}
			}

		}
		else if ((board_tile_loc % (width / 32)) == 0)
		{
			int bufferChangerWidth = width / 32;
			int bufferChangerHeight = ((height - 100) / 32);
			for (unsigned int m = 0; m < tileVector[board_tile_loc].neighbors.size(); m++)
			{
				if (m == 1)
				{
					tileVector[board_tile_loc].neighbors[1] = &(tileVector[board_tile_loc - (tileVector.size() / ((height - 100) / 32))]);
				}
				else if (m == 2)
				{
					tileVector[board_tile_loc].neighbors[2] = &(tileVector[board_tile_loc - ((tileVector.size() / ((height - 100) / 32)) - 1)]);
				}
				else if (m == 4)
				{
					tileVector[board_tile_loc].neighbors[4] = &(tileVector[board_tile_loc + 1]);
				}
				else if (m == 6)
				{
					tileVector[board_tile_loc].neighbors[6] = &(tileVector[board_tile_loc + width / 32]);
				}
				else if (m == 7)
				{
					tileVector[board_tile_loc].neighbors[7] = &(tileVector[(board_tile_loc + width / 32) + 1]);
				}
			}

		}
		else if (((board_tile_loc - (width / 32) + 1) % (width / 32)) == 0)
		{
			int bufferChangerWidth = width / 32;
			int bufferChangerHeight = ((height - 100) / 32);
			for (unsigned int m = 0; m < tileVector[board_tile_loc].neighbors.size(); m++)
			{
				if (m == 0)
				{
					tileVector[board_tile_loc].neighbors[0] = &(tileVector[board_tile_loc - ((tileVector.size() / ((height - 100) / 32)) + 1)]);
				}
				else if (m == 1)
				{
					tileVector[board_tile_loc].neighbors[1] = &(tileVector[board_tile_loc - (tileVector.size() / ((height - 100) / 32))]);
				}
				else if (m == 3)
				{
					tileVector[board_tile_loc].neighbors[3] = &(tileVector[board_tile_loc - 1]);
				}
				else if (m == 5)
				{
					tileVector[board_tile_loc].neighbors[5] = &(tileVector[(board_tile_loc + width / 32) - 1]);
				}
				else if (m == 6)
				{
					tileVector[board_tile_loc].neighbors[6] = &(tileVector[board_tile_loc + width / 32]);
				}
			}
		}
		else
		{
			int bufferChangerWidth = width / 32;
			int bufferChangerHeight = ((height - 100) / 32);
			for (unsigned int m = 0; m < 8; m++)
			{
				if (m == 0)
				{
					tileVector[board_tile_loc].neighbors[0] = &(tileVector[board_tile_loc - ((tileVector.size() / ((height - 100) / 32)) + 1)]);
				}
				else if (m == 1)
				{
					tileVector[board_tile_loc].neighbors[1] = &(tileVector[board_tile_loc - (tileVector.size() / ((height - 100) / 32))]);
				}
				else if (m == 2)
				{
					tileVector[board_tile_loc].neighbors[2] = &(tileVector[board_tile_loc - ((tileVector.size() / ((height - 100) / 32)) - 1)]);
				}
				else if (m == 3)
				{
					tileVector[board_tile_loc].neighbors[3] = &(tileVector[board_tile_loc - 1]);
				}
				else if (m == 4)
				{
					tileVector[board_tile_loc].neighbors[4] = &(tileVector[board_tile_loc + 1]);
				}
				else if (m == 5)
				{
					tileVector[board_tile_loc].neighbors[5] = &(tileVector[(board_tile_loc + width / 32) - 1]);
				}
				else if (m == 6)
				{
					tileVector[board_tile_loc].neighbors[6] = &(tileVector[board_tile_loc + width / 32]);
				}
				else if (m == 7)
				{
					tileVector[board_tile_loc].neighbors[7] = &(tileVector[(board_tile_loc + width / 32) + 1]);
				}
			}

		}

		tileVector[board_tile_loc].Toggle_Icon_Number();
	}
	if (tileVector.size() == num_tiles)
	{
		successful = true;
	}
}

void Board::update_leaderboard(vector<string>& top5, int playerTime, string username)
{
	string timeMin, timeSec;
	int leaderboardTimer = 0;
	bool doneleaderboardUpdate = false;
	int min = 0;
	int sec = 0;

	min = ((playerTime % 3600) / 60);
	sec = playerTime % 60;

	if (min < 10)
	{
		for (unsigned int timerIterator = 0; timerIterator < 10; timerIterator++)
		{
			if (timerIterator == 0)
			{
				timeMin = "0" + to_string(min);
			}
		}

	}
	else
	{
		for (unsigned int timerIterator = 0; timerIterator < 10; timerIterator++)
		{
			if (timerIterator == 0)
			{
				timeMin = to_string(min);
			}
		}

	}

	if (sec < 10)
	{
		for (unsigned int timerIterator = 0; timerIterator < 10; timerIterator++)
		{
			if (timerIterator == 0)
			{
				timeSec = "0" + to_string(sec);
			}
		}

	}
	else
	{
		for (unsigned int timerIterator = 0; timerIterator < 10; timerIterator++)
		{
			if (timerIterator == 0)
			{
				timeSec = to_string(sec);
			}
		}

	}
	for (unsigned int i = 0; i < 10; i++)
	{
		if (i == 0)
		{
			if (playerTime < leaderboard_first_time)
			{
				for (unsigned int bieb = 0; bieb < 5; bieb++)
				{
					if (bieb == 1)
					{
						top5.insert(top5.begin(), (timeMin)+":" + timeSec + "," + username + "*");
						top5.pop_back();
					}
				}


			}
			else if (playerTime < leaderboard_second_time && playerTime > leaderboard_first_time)
			{
				for (unsigned int bieb = 0; bieb < 5; bieb++)
				{
					if (bieb == 1)
					{
						top5.insert(top5.begin() + 1, (timeMin)+":" + timeSec + "," + username + "*");
						top5.pop_back();
					}
				}

			}
			else if (playerTime < leaderboard_third_time && playerTime > leaderboard_second_time)
			{
				for (unsigned int bieb = 0; bieb < 5; bieb++)
				{
					if (bieb == 1)
					{
						top5.insert(top5.begin() + 2, (timeMin)+":" + timeSec + "," + username + "*");
						top5.pop_back();
					}
				}

			}
			else if (playerTime < leaderboard_fourth_time && playerTime > leaderboard_third_time)
			{
				for (unsigned int bieb = 0; bieb < 5; bieb++)
				{
					if (bieb == 1)
					{
						top5.insert(top5.begin() + 3, (timeMin)+":" + timeSec + "," + username + "*");
						top5.pop_back();
					}
				}

			}
			else if (playerTime < leaderboard_fifth_time && playerTime > leaderboard_fourth_time)
			{
				for (unsigned int bieb = 0; bieb < 5; bieb++)
				{
					if (bieb == 1)
					{
						top5.insert(top5.begin() + 4, (timeMin)+":" + timeSec + "," + username + "*");
						top5.pop_back();
					}
				}

			}
		}

	}


	ofstream file("files/leaderboard.txt");
	for (int i = 0; i < leaderBoardTop5.size(); i += 1)
	{
		file << leaderBoardTop5[i] + "\n";
	}
	file.close();
	doneleaderboardUpdate = true;
}

void Board::debug_game()
{
	if (debug_enabled == false)
	{
		debug_enabled = true;
	}
	else
	{
		debug_enabled = false;
	}
	for (int tiles = 0; tiles < tileVector.size(); tiles += 1)
	{
		tileVector[tiles].Toggle_Icon_Mine();
	}
}

void Board::ReadandSetLeaderBoard(vector<string>& top5, int widthh, int heightt, sf::Text& text_leaderboard_word, sf::Text& prompt, sf::Text& inputt, sf::Font& Fonttt)
{

}


void Board::reset_game()
{
	start_game();
	if (!first_game)
	{
		if (game_is_over == true && !game_is_lost)
		{
			for (int i = 0; i < leaderBoardTop5.size(); i += 1)
			{
				if (leaderBoardTop5[i].back() == '*')
				{
					leaderBoardTop5[i].pop_back();
				}
			}
		}

		ofstream file("files/leaderboard.txt");
		for (int i = 0; i < leaderBoardTop5.size(); i += 1)
		{
			file << leaderBoardTop5[i] + "\n";
		}
		file.close();
	}
	tiles_revealed = 0;
	game_is_over = false;
	game_is_lost = false;
	paused = false;
	debug_enabled = false;
	gameWon_leaderboardShown = false;

	reveal_count = 0;
	clock_total_timePaused = 0;
	clock_time_pause_pressed = 0;
	clock_time_unpause_pressed = 0;
	maximum_flags = const_flag_value;
	number_flags = const_flag_value;

	icon_SmileFace.setTexture(TextureManager::textureGetter("face_happy"));

	tileVector.clear();
	set_icons();

}

int Board::debug_start_game2()
{
	if (game_is_over)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void Board::set_leaderboard(int widthh, int heightt, sf::Text& text_leaderboard_word, sf::Text& prompt, sf::Text& inputt, sf::Font& font_minesweeperFont_ttf)
{
	string leaderboard_word = "LEADERBOARD";
	text_leaderboard_word.setString("LEADERBOARD");

	text_leaderboard_word.setCharacterSize(20);
	prompt.setCharacterSize(18);


	text_leaderboard_word.setFont(font_minesweeperFont_ttf);
	prompt.setFont(font_minesweeperFont_ttf);

	text_leaderboard_word.setStyle(sf::Text::Bold | sf::Text::Underlined);
	prompt.setStyle(sf::Text::Bold);

	sf::FloatRect text_rectangle_leaderboardText;
	for (unsigned int luci = 0; luci < 5; luci++)
	{
		if (luci == 0)
		{
			text_rectangle_leaderboardText = text_leaderboard_word.getLocalBounds();
		}
	}

	text_leaderboard_word.setOrigin(text_rectangle_leaderboardText.left + text_rectangle_leaderboardText.width / 2.0f, text_rectangle_leaderboardText.top + text_rectangle_leaderboardText.height / 2.0f);
	text_leaderboard_word.setPosition(sf::Vector2f(widthh / 2.0f, heightt / 2.0f - 120));

	string leaderboardNames = "";
	for (int i = 0; i < leaderBoardTop5.size(); i += 1)
	{
		leaderboardNames += to_string(i + 1) + ".\t" + leaderBoardTop5[i].substr(0, 5) + "\t" + leaderBoardTop5[i].substr(6) + "\n\n";
	}

	prompt.setString(leaderboardNames);
	sf::FloatRect text_rectangle_names;
	for (unsigned int luci = 0; luci < 5; luci++)
	{
		if (luci == 0)
		{
			text_rectangle_names = prompt.getLocalBounds();

		}
	}
	string test;
	prompt.setOrigin(text_rectangle_names.left + text_rectangle_names.width / 2.0f, text_rectangle_names.top + text_rectangle_names.height / 2.0f);
	test = "a";
	prompt.setPosition(sf::Vector2f(widthh / 2.0f, heightt / 2.0f + 20));
	test = "b";


}

void Board::debug_set_leaderboard_values(vector<string>& leaderboard_top_5)
{
	for (unsigned int i = 0; i < leaderboard_top_5.size(); i++)
	{
		leaderboard_top_5[i].erase(); // clears out leaderboard
	}
}

void Board::set_icons()
{
	clock.restart();
	Time firstTime = clock.getElapsedTime();
	clock.restart();

	string smile_file_name = "face_happy";
	icon_SmileFace.setTexture(TextureManager::textureGetter(smile_file_name));
	string debug_file_name = "debug";
	icon_debug_button.setTexture(TextureManager::textureGetter(debug_file_name));
	string pause_file_name = "pause";
	icon_pause_button.setTexture(TextureManager::textureGetter(pause_file_name));

	string play_file_name = "play";
	icon_play_button.setTexture(TextureManager::textureGetter(play_file_name));

	string leaderboard_file_name = "leaderboard";
	icon_leaderboard_button.setTexture(TextureManager::textureGetter(leaderboard_file_name));

	int icon_pause_location_bufffer = (width) / 32;
	icon_pause_button.setPosition(((width / 32) * 32) - 240, 32 * (((height - 100) / 32) + 0.5f));
	int icon_button_location_bufffer = (width) / 36;
	icon_debug_button.setPosition(((width / 32) * 32) - 304, 32 * (((height - 100) / 32) + 0.5f));
	int icon_leaderboard_location_bufffer = (width) / 36;
	icon_leaderboard_button.setPosition(((width / 32) * 32) - 176, 32 * (((height - 100) / 32) + 0.5f));
	int icon_SmileFace_location_bufffer = (width) / 32;
	icon_SmileFace.setPosition((((width / 32) / 2.0) * 32) - 32, 32 * (((height - 100) / 32) + 0.5f));

	int counter_hundreds_location_buffer = height - 100 / 32;
	counter_hundreds_digit.setPosition(33, 32 * (((height - 100) / 32) + 0.5f) + 16);
	string counter_hundreds_digit_file_name = "digits";
	counter_hundreds_digit.setTexture(TextureManager::textureGetter(counter_hundreds_digit_file_name));
	counter_hundreds_digit.setTextureRect(sf::Rect<int>(0, 0, 21, 32));

	string counter_tens_digit_file_name = "digits";
	counter_tens_digit.setTexture(TextureManager::textureGetter(counter_tens_digit_file_name));
	int counter_tens_location_bufffer = 32 * height - 100;
	counter_tens_digit.setTextureRect(sf::Rect<int>(0, 0, 21, 32));
	Rect<int> counter_tens_textureRect(0, 0, 21, 32);
	int counter_tens_location_buffer = height - 100 / 32;
	counter_tens_digit.setPosition(54, 32 * (((height - 100) / 32) + 0.5f) + 16);

	string counter_one_digit_file_name = "digits";
	counter_ones_digit.setTexture(TextureManager::textureGetter(counter_one_digit_file_name));
	counter_ones_digit.setTextureRect(sf::Rect<int>(0, 0, 21, 32));
	Rect<int> counter_ones_textureRect(0, 0, 21, 32);
	string enei = "";
	counter_ones_digit.setPosition(75, 32 * (((height - 100) / 32) + 0.5f) + 16);
	counter_negative_digit.setTexture(TextureManager::textureGetter(counter_one_digit_file_name));
	counter_negative_digit.setTextureRect(sf::Rect<int>(21 * 10, 0, 21, 32));
	counter_negative_digit.setPosition(12, 32 * (((height - 100) / 32) + 0.5f) + 16);
	counter_negative_digit.setColor(Color(255, 255, 255, 0));

	string timer_thousands_digit_file_name = "digits";
	timer_thousands_digit.setTexture(TextureManager::textureGetter(timer_thousands_digit_file_name));
	timer_thousands_digit.setTextureRect(sf::Rect<int>(0, 0, 21, 32));
	Rect<int> timer_thousands_textureRect(0, 0, 21, 32);
	int timer_thousands_location_buffer = height - 100 / 32;
	timer_thousands_digit.setPosition((width)-97, 32 * (((height - 100) / 32) + 0.5f) + 16);

	string timer_hundreds_digit_file_name = "digits";
	timer_hundreds_digit.setTexture(TextureManager::textureGetter(timer_hundreds_digit_file_name));
	timer_hundreds_digit.setTextureRect(sf::Rect<int>(0, 0, 21, 32));

	string timer_tens_digit_file_name = "digits";
	timer_tens_digit.setTexture(TextureManager::textureGetter(timer_tens_digit_file_name));
	timer_tens_digit.setTextureRect(sf::Rect<int>(0, 0, 21, 32));

	string timer_one_digit_file_name = "digits";
	timer_ones_digit.setTexture(TextureManager::textureGetter(timer_one_digit_file_name));
	timer_ones_digit.setTextureRect(sf::Rect<int>(0, 0, 21, 32));

	int timer_hundreds_location_bufffer = (width)-76;
	timer_hundreds_digit.setPosition((width)-76, 32 * (((height - 100) / 32) + 0.5f) + 16);
	int timer_tens_location_bufffer = (width)-76;
	timer_tens_digit.setPosition((width)-54, 32 * (((height - 100) / 32) + 0.5f) + 16);
	int timer_ones_location_bufffer = (width)-76;
	timer_ones_digit.setPosition((width)-33, 32 * (((height - 100) / 32) + 0.5f) + 16);

	Tile debugTile;
	update_counter();

	Tile oneTile = Tile(false, 0, 0, false);
	int buffered_height = ((height - 100) / 32);


	for (int i = 0; i < ((height - 100) / 32); i += 1)
	{
		for (int innerLoop = 0; innerLoop < (width / 32); innerLoop += 1)
		{
			oneTile.x = innerLoop * 32;
			oneTile.y = i * 32;
			if (tileVector.size() != -1)
			{
				tileVector.push_back(oneTile);
			}

		}
	}

	randomize_board_bombs();
	int ticktok = debug_start_game();
	getToggle_Icon_Numbers();

	for (unsigned int i = 0; i < tileVector.size(); i += 1)
	{
		Color opaqueFlagFinal(255, 255, 255, 0);
		if (i != -1)
		{
			tileVector[i].image_flag.setColor(sf::Color(255, 255, 255, 0));
		}
		Color opaqueActualFinal(255, 255, 255, 0);
		if (i != -1)
		{
			tileVector[i].image_actual.setColor(sf::Color(255, 255, 255, 0));
		}
		if (tileVector[i].tile_has_bomb)
		{
			for (unsigned int sug = 0; sug < 7; sug++)
			{
				if (sug == 2)
				{
					tileVector[i].image_actual.setTexture(TextureManager::textureGetter("mine"));
				}
			}
		}

	}
}


void Board::read_leaderboard(vector<string>& top5)
{
	for (unsigned int i = 0; i < top5.size(); i++)
	{
		top5[i] = "";
	}
	top5.clear();

	ifstream inFile("files/leaderboard.txt");
	string read_lineInFile;

	for (int i = 0; i < 5; i += 1)
	{
		string checker_first_part;
		getline(inFile, read_lineInFile);
		top5.push_back(read_lineInFile);
		checker_first_part = read_lineInFile;
	}
	int leaderboardTimer = 0;
	leaderboard_first_time = stoi(top5[0].substr(0, 2));
	leaderboard_first_time *= 60;
	leaderboard_first_time += stoi(top5[0].substr(3, 5));
	leaderboardTimer += leaderboard_first_time;

	leaderboard_second_time = stoi(top5[1].substr(0, 2));
	leaderboard_second_time *= 60;
	leaderboard_second_time += stoi(top5[1].substr(3, 5));
	leaderboardTimer += leaderboard_second_time;

	leaderboard_third_time = stoi(top5[2].substr(0, 2));
	leaderboard_third_time *= 60;
	leaderboard_third_time += stoi(top5[2].substr(3, 5));
	leaderboardTimer += leaderboard_third_time;

	leaderboard_fourth_time = stoi(top5[3].substr(0, 2));
	leaderboard_fourth_time *= 60;
	leaderboard_fourth_time += stoi(top5[3].substr(3, 5));
	leaderboardTimer += leaderboard_fourth_time;

	leaderboard_fifth_time = stoi(top5[4].substr(0, 2));
	leaderboard_fifth_time *= 60;
	leaderboard_fifth_time += stoi(top5[4].substr(3, 5));
	leaderboardTimer += leaderboard_fifth_time;

	inFile.close();
}


bool Board::debug_leaderboard_full(vector<string>& leaderboard_top_5)
{
	int leaderboard_vector_size;
	leaderboard_vector_size = leaderboard_top_5.size();
	if (leaderboard_vector_size >= 5)
	{
		return true;
	}
	else
	{
		return false;
	}
}



void Board::setName(string& userInputt)
{
	username = userInputt;
}
