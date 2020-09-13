#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

#include "functions.hpp"

using namespace std;

int main()
{
	srand(time(NULL));
	int level_number;
	cin >> level_number;
	Address level_img;
	Event event;
	Gamer gamer;
	vector<vector<Time> > data = load_data(level_number, level_img);
	vector<Tower> towers = initial_towers(level_number);
	vector<vector<Enemy*> > waves;
	for (int i = 0; i < data.size(); i++)
		waves.push_back(initial_wave(data[i], level_number));
	Window win(WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
	int mouse_x, mouse_y;
	char pressed_char;
	bool lclick_pressed = false;
	vector<Ball> all_balls ;
	time_t start = clock();	
	while (true) 
	{
		double passed_time = float(clock() - start)/CLOCKS_PER_SEC;
		vector<Enemy*> all_enemies ;
		win.clear();
		win.draw_png(level_img, 0, 0, WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
		event = win.pollForEvent();
		if(event.type() == QUIT)
			break;
		if(event.type() == LCLICK)
		{
			lclick_pressed = true;
			mouse_x = event.mouseX();
			mouse_y = event.mouseY();
		}
		if(event.type() == KEY_PRESS && lclick_pressed)
		{
			pressed_char = event.pressedKey();
			build_tower(mouse_x, mouse_y, pressed_char, towers,gamer);
			lclick_pressed = false;
		}
		draw_towers(win, towers);
		for (int i = 0; i < waves.size(); i++)
			waves[i] = generate_wave(passed_time, win, waves[i], data[i], level_number);
		for (int j = 0; j < waves.size(); j++ )
		{
			for (int i = 0; i < waves[j].size(); i++)
				all_enemies.push_back(waves[j][i]);	
		}
		// for (int i = 0; i < all_enemies.size(); i++)
		// {
		// 	cout << i << " " << all_enemies[i]->lives  << endl;
		// }

		draw_enemies(win, all_enemies);
		vector<Ball> balls = generate_balls(towers, all_enemies, passed_time);
		shoot_the_balls(win, balls, all_enemies, towers, level_img, gamer);
		check_enemy_exit(all_enemies, gamer);
		if(check_if_gamer_won(all_enemies))
		{
			win.clear();
			win.draw_png(WIN_IMG, 0, 0, WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
			win.update_screen();
			Delay(3000);
			break;
		}	
		if(gamer.lives_of_gamer < 1)
		{
			win.clear();
			win.draw_png(LOST_IMG, 0, 0, WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
			win.update_screen();
			Delay(3000);
			break;
		}	
		win.update_screen();
	}
}
