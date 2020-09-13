#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

#include "functions.hpp"


using namespace std;

vector<vector <Time> > load_data(int n, Address& level_img)
{
	string address_of_txt;
	string line;
	if(n == 1)
		address_of_txt = "level1-waves.txt" ;
	else if(n == 2)
		address_of_txt = "level2-waves.txt" ;
		
	ifstream level (address_of_txt);
	vector<Time> wave;
	vector<vector<Time> > data;
	if (level.is_open())
	{
		bool read_img = true;
		int count_wave = 0;
		while (getline (level,line))
		{
			if(read_img)
			{
				level_img = line.substr(0, line.size()-1) ;
				read_img = false ;
				continue;
			}
			if(line.find_first_of('#') != NOT_FOUND)
			{	
				if(count_wave != 0)
				{
					data.push_back(wave);
					wave.clear();
				}
				count_wave ++ ;
				continue;
			}
			Time mytime;
			mytime.wave = count_wave;
			mytime.time = stoi(line.substr(0, line.find_first_of(',')));
			line = line.substr(line.find_first_of(',')+1);
			while(line.find_first_of(',') != NOT_FOUND)
			{
				int number = stoi(line.substr(0, line.find_first_of(' ')));
				line = line.substr(line.find_first_of(' ')+1);
				string type = line.substr(0, line.find_first_of(','));
				if(type == "armored")
					mytime.num_of_armored += number;
				else if(type == "orc")
					mytime.num_of_orc += number;
				else if(type == "demon")
					mytime.num_of_demon += number;
				else if(type == "wolf")
					mytime.num_of_wolf += number;
				line = line.substr(line.find_first_of(',')+1);	
			}
			wave.push_back(mytime);				
	    }
		data.push_back(wave);
	    level.close();
	}
	return data;
}

vector<Enemy*> initial_wave(vector<Time> data, int level)
{
	vector<Enemy*> wave;
	for (int j = 0; j < data.size(); j++)
	{
		if(data[j].num_of_wolf > 0)
		{
			for (int k = 0; k < data[j].num_of_wolf;k++)
			{
				Enemy* mywolf= new Enemy;
				initial_enemy(mywolf, wolf, level);
				mywolf->y += ((rand() % 20) - 12);
				mywolf->x += ((rand() % 30) - 15);
				wave.push_back(mywolf);
			}
		}
		if(data[j].num_of_demon > 0)
		{
			for (int k = 0; k < data[j].num_of_demon;k++)
			{
				Enemy* mydemon= new Enemy;
				initial_enemy(mydemon, demon, level);
				mydemon->y += ((rand() % 20) - 12);
				mydemon->x += ((rand() % 30) - 15);
				wave.push_back(mydemon);
			}
		}
		if(data[j].num_of_armored > 0)
		{
			for (int k = 0; k < data[j].num_of_armored;k++)
			{
				Enemy* myarmored= new Enemy;
				initial_enemy(myarmored, armored, level);
				myarmored->y += ((rand() % 20) - 12);
				myarmored->x += ((rand() % 30) - 15);
				wave.push_back(myarmored);
			}
		}
		if(data[j].num_of_orc > 0)
		{
			for (int k = 0; k < data[j].num_of_orc;k++)
			{
				Enemy* myorc= new Enemy;
				initial_enemy(myorc, orc, level);
				myorc->y += ((rand() % 20) - 12);
				myorc->x += ((rand() % 30) - 15);
				wave.push_back(myorc);
			}
		}
	}
	return wave;
}

vector<Tower> initial_towers(int level)
{
	vector<Tower> tower(8);
	vector<int> points_of_towers_x_level1 = {485,343,298,147,429,353,531,439};
	vector<int> points_of_towers_y_level1 = {220,220,370,347,489,514,589,630};
	vector<int> points_of_towers_x_level2 = {478,393,305,505,408,380,479,594};
	vector<int> points_of_towers_y_level2 = {278,277,274,424,426,566,560,611};
	Tower mytower;
	mytower.tower_type = none;
	for (int i = 0; i < 8; i++)
	{
		tower[i] = mytower;
		if(level == 1)
		{
			tower[i].x = points_of_towers_x_level1[i];
			tower[i].y = points_of_towers_y_level1[i];
		}
		else if(level == 2)
		{
			tower[i].x = points_of_towers_x_level2[i];
			tower[i].y = points_of_towers_y_level2[i];
		}
	}	
	return tower;
}

void initial_tower(Tower& tower)
{
	if(tower.tower_type == archer)
	{
		tower.damage = 50;
		tower.time_for_each_throw_ms = 350;
		tower.money_for_building = 70;
		tower.radius_of_damaging_px = 85;
		tower.damage_to_all = false;
		tower.image = ARCHER;
		tower.physical_attack = true;
		tower.magical_attack = false;
	}
	else if(tower.tower_type == canon)
	{
		tower.damage = 140;
		tower.time_for_each_throw_ms = 1000;
		tower.money_for_building = 125;
		tower.radius_of_damaging_px = 85; 	
		tower.damage_to_all = true;
		tower.image = CANON;
		tower.physical_attack = true;
		tower.magical_attack = false;
	}
	else if(tower.tower_type == mage)
	{
		tower.damage = 140;
		tower.time_for_each_throw_ms = 750;
		tower.money_for_building = 90;
		tower.radius_of_damaging_px = 85; 	
		tower.damage_to_all = false;
		tower.image = MAGE;
		tower.physical_attack = false;
		tower.magical_attack = true;
	}
	else if(tower.tower_type == icy)
	{
		tower.damage = 30;
		tower.time_for_each_throw_ms = 1000;
		tower.money_for_building = 80;
		tower.radius_of_damaging_px = 85; 	
		tower.damage_to_all = true;
		tower.image = ICY;
		tower.physical_attack = false;
		tower.magical_attack = true;
	}
}

void initial_enemy(Enemy* enemy, EnemyTypeEnum enemy_type, int level)
{
	if(level == 1)
	{
		enemy->x = 798;
		enemy->y = 275;
	}
	else if(level == 2)
	{
		enemy->x=507;
		enemy->y = 20;
	}
	if(enemy_type == orc)
	{
		enemy->enemy_type = orc;
		enemy->lives = 200;
		enemy->speed = 42;
		enemy->armor = false;
		enemy->magic_armor = false;
		enemy->killing_reward = 5;
		enemy->lives_of_gamer = 1;
		enemy->front_img = ORC_FRONT;
		enemy->back_img = ORC_BACK;
		enemy->right_img = ORC_RIGHT;
		enemy->left_img = ORC_LEFT;
	}
	if(enemy_type == wolf)
	{
		enemy->enemy_type = wolf;
		enemy->lives = 100;
		enemy->speed = 85;
		enemy->armor = false;
		enemy->magic_armor = false;
		enemy->killing_reward = 4;
		enemy->lives_of_gamer = 1;
		enemy->front_img = WOLF_FRONT;
		enemy->back_img = WOLF_BACK;
		enemy->right_img = WOLF_RIGHT;
		enemy->left_img = WOLF_LEFT;
	}
	if(enemy_type == armored)
	{
		enemy->enemy_type = armored;		
		enemy->lives = 450;
		enemy->speed = 21;
		enemy->armor = true;
		enemy->magic_armor = false;
		enemy->killing_reward = 8;
		enemy->lives_of_gamer = 3;
		enemy->front_img = ARMORED_FRONT;
		enemy->back_img = ARMORED_BACK;
		enemy->right_img = ARMORED_RIGHT;
		enemy->left_img = ARMORED_LEFT;
	}
	if(enemy_type == demon)
	{
		enemy->enemy_type = demon;
		enemy->lives = 400;
		enemy->speed = 28;
		enemy->armor = false;
		enemy->magic_armor = true;
		enemy->killing_reward = 8;
		enemy->lives_of_gamer = 3;		
		enemy->front_img = DEMON_FRONT;
		enemy->back_img = DEMON_BACK;
		enemy->right_img = DEMON_RIGHT;
		enemy->left_img = DEMON_LEFT;
	}	
}

Address move_level2(Enemy* enemy)
{
	if(enemy->y < 180)
	{
		enemy->y += 0.625*UNIT;
		return enemy->front_img;
	}	
	else if(enemy->x > 235 && enemy->x < 530 && enemy->y < 230 && enemy->y > 155)
	{
		enemy->x -= 0.625*UNIT;
		return enemy->left_img;
	}	
	else if(enemy->x > 180 && enemy->x < 255 && enemy->y < 325 && enemy->y > 150)
	{
		enemy->y += 0.625*UNIT;
		return enemy->front_img;
	}	
	else if(enemy->x > 230 && enemy->x < 580 && enemy->y < 380 && enemy->y > 305)
	{
		enemy->x += 0.625*UNIT;
		return enemy->right_img;
	}
	else if(enemy->x > 540 && enemy->x < 640 && enemy->y < 460 && enemy->y > 320)
	{
		enemy->y += 0.625*UNIT;
		return enemy->front_img;
	}	
	else if(enemy->x > 285 && enemy->x < 615 && enemy->y < 530 && enemy->y > 450)
	{
		enemy->x -= 0.625*UNIT;
		return enemy->left_img;
	}	
	else if(enemy->x > 245 && enemy->x < 320 && enemy->y < 610 && enemy->y > 450)
	{
		enemy->y += 0.625*UNIT;
		return enemy->front_img;
	}
	else if(enemy->x > 270 && enemy->x < 520 && enemy->y < 660 && enemy->y > 580)
	{
		enemy->x += 0.625*UNIT;
		return enemy->right_img;
	}	
	else if(enemy->x > 480 && enemy->x < 570 && enemy->y < 790 && enemy->y > 590)
	{
		enemy->y += 0.625*UNIT;
		return enemy->front_img;
	}
	else
		return NO_IMG;	
}

Address move_level1(Enemy* enemy)
{
	if(enemy->x > 570 && enemy->x < 800)
	{
		enemy->x -= 0.625*UNIT;
		return enemy->left_img;
	}
	else if(enemy->x > 500 && enemy->y > 130 && enemy->y < 310)
	{
		enemy->x -= 0.125*UNIT;
		enemy->y -= 0.5*UNIT;
		return enemy->back_img;
	}
	else if(enemy->x > 420 && enemy->y > 120 && enemy->y < 240)
	{
		enemy->x -= 0.625*UNIT;
		return enemy->left_img;
	}
	else if(enemy->x > 350 && enemy->x < 445 && enemy->y > 120 && enemy->y < 290)
	{
		enemy->x -= 0.25*UNIT;
		enemy->y += 0.5*UNIT;
		return enemy->front_img;
	}
	else if(enemy->x > 220 && enemy->x < 420 && enemy->y > 250 && enemy->y < 320)
	{
		enemy->x -= 0.75*UNIT;
		enemy->y += 0.125*UNIT;
		return enemy->left_img;
	}
	else if(enemy->x > 210 && enemy->x < 230 && enemy->y > 270 && enemy->y < 420)
	{
		enemy->y += 0.625*UNIT;
		return enemy->front_img;
	}
	else if(enemy->x > 210 && enemy->x < 455 && enemy->y < 430)
	{
		enemy->x += 0.625*UNIT;
		return enemy->right_img;
	}
	else if(enemy->x > 440 && enemy->x < 510 && enemy->y > 400 && enemy->y < 520)
	{
		enemy->x += 0.125*UNIT;
		enemy->y += 0.5*UNIT;
		return enemy->front_img;
	}
	else if(enemy->x > 340 && enemy->x < 550 && enemy->y > 500 && enemy->y < 585)
	{
		enemy->x -= 0.625*UNIT;
		enemy->y += 0.125*UNIT;
		return enemy->left_img;
	}
	else if(enemy->y > 540 && enemy->x > 320 && enemy->x < 500)
	{
		enemy->y += 0.625*UNIT;
		return enemy->front_img;
	}
	else
		return NO_IMG;
}

Address move_enemy(Enemy* enemy, int level)
{
	Address address_of_img;
	if(level == 1)
		address_of_img = move_level1(enemy);
	else if(level == 2)
		address_of_img = move_level2(enemy);
	return address_of_img;
}

void build_tower(int x, int y, char pressed_char, vector<Tower>& towers, Gamer& gamer)
{
	for(int i = 0; i < towers.size(); i++)
	{
		if(abs(x - towers[i].x) < 25 && abs(y - towers[i].y) < 25 && towers[i].tower_type == none)
		{
			if(pressed_char == 'M' || pressed_char == 'm' && gamer.money > 90)
			{
				towers[i].tower_type = mage ;
				initial_tower(towers[i]);
				gamer.money -= towers[i].money_for_building;
			}	
			if(pressed_char == 'A' || pressed_char == 'a' && gamer.money > 70)
			{
				towers[i].tower_type = archer ;
				initial_tower(towers[i]);
				gamer.money -= towers[i].money_for_building;
			}
			if(pressed_char == 'C' || pressed_char == 'c' && gamer.money > 125)
			{
				towers[i].tower_type = canon ;
				initial_tower(towers[i]);
				gamer.money -= towers[i].money_for_building;
			}
			if(pressed_char == 'I' || pressed_char == 'i' && gamer.money > 80)
			{
			 	towers[i].tower_type = icy ;			
				initial_tower(towers[i]);
				gamer.money -= towers[i].money_for_building;
			}
		}
	}
}

vector<Ball> generate_balls(vector<Tower>& towers, vector<Enemy*> wave, double time)
{
	vector<Ball> balls;
	for(int i = 0; i < towers.size(); i++)
	{
		if(towers[i].tower_type == none)
			continue;
		for (int j = 0; j < wave.size(); j++)
		{
			if(wave[j]->lives <= 0 || wave[j]->is_generated == false)	continue;
			if(abs(wave[j]->x - towers[i].x) < towers[i].radius_of_damaging_px 
				&& abs(wave[j]->y - towers[i].y) < towers[i].radius_of_damaging_px 
				&& (time-towers[i].time_of_last_attack) > float(towers[i].time_for_each_throw_ms)/1000)		
			{	
				Ball ball;
				if((wave[j]->armor && towers[i].physical_attack) || 
					(wave[j]->magic_armor && towers[i].magical_attack))
					ball.damage = (towers[i].damage/2);
				else
					ball.damage = towers[i].damage;
				ball.x = towers[i].x ;
				ball.y = towers[i].y ;
				ball.enemy = wave[j];
				balls.push_back(ball);
				towers[i].time_of_last_attack=time;
				if(towers[i].damage_to_all == false)
					break;
			}
		}
	}
	return balls;
}

void shoot_the_balls(Window& win, vector<Ball> balls, vector<Enemy*> wave, vector<Tower>& towers, Address level_img, Gamer& gamer)
{
	while(true)
	{
		for (int i = 0; i < balls.size(); i++)
		{
			if(abs(balls[i].x - balls[i].enemy->x)<15 && abs(balls[i].y - balls[i].enemy->y)<15)
			{
				balls[i].valid_to_show = false;
				balls[i].enemy->lives -= balls[i].damage;
				if(balls[i].enemy->lives <= 0)
					gamer.money += balls[i].enemy->killing_reward;
			}
			win.clear();
			win.draw_png(level_img, 0, 0, WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
			draw_enemies(win, wave);
			draw_towers(win, towers);
			if(balls[i].valid_to_show)
			{	
				win.draw_png(BALL_IMG, balls[i].x, balls[i].y, BALL_SIZE, BALL_SIZE);
				float distance_x = balls[i].enemy->x - balls[i].x;
			    float distance_y = balls[i].enemy->y - balls[i].y;
			    if(abs(distance_y) < 1)
			      distance_y = 1;
			    if(abs(distance_x) < 1)
			      distance_x = 1;
			    float abs_distance = pow(pow(distance_x, 2) + pow(distance_y, 2), 0.5);
			    balls[i].x += balls[i].speed * distance_x / abs_distance;
			    balls[i].y += balls[i].speed * distance_y / abs_distance;
			}
			win.update_screen();
		}
		int num_of_invalid_ball = 0;
		for (int i = 0; i < balls.size(); i++)
		{
			if(balls[i].valid_to_show == false)
				num_of_invalid_ball ++ ;
		}
		if(num_of_invalid_ball == balls.size())
		{
			balls.clear();
			break;
		}
	}
}

void draw_towers(Window& win, vector<Tower> towers)
{
	for(int i = 0; i < towers.size(); i++)
	{
		if(towers[i].tower_type == none)
			continue;
		else
			win.draw_png(towers[i].image,towers[i].x-40 ,towers[i].y-40, SIZE_OF_TOWER, SIZE_OF_TOWER);
	}
}

void draw_enemies(Window& win, vector<Enemy*> enemies)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i]->lives <= 0 || enemies[i]->is_generated == false || enemies[i]->current_img == NO_IMG)	
			continue;
		win.draw_png(enemies[i]->current_img, enemies[i]->x, enemies[i]->y, SIZE_OF_ENEMY, SIZE_OF_ENEMY);
	}
}

void check_enemy_exit(vector<Enemy*> enemies, Gamer& gamer)
{

	for (int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i]->y > 730 && enemies[i]->lives > 0)
		{
			gamer.lives_of_gamer -= enemies[i]->lives_of_gamer ;
			enemies[i]->lives = 0;
			enemies[i]->is_generated = false;
		}
	}
}

bool check_if_gamer_won(vector<Enemy*> enemies)
{
	int num_of_enemies_went_away = 0;
	for (int i = 0; i < enemies.size() ; i++)
	{
		if(enemies[i]->lives <= 0)
			num_of_enemies_went_away++;
	}
	if(num_of_enemies_went_away == enemies.size())
			return true;
	else
		return false;
}

vector<Enemy*> generate_wave(double time, Window& win, vector<Enemy*> wave, 
							vector<Time> data, int level)
{
	int last_num_of_enemies = 0;
	for (int j = 0; j < data.size(); j++)
	{
		int num_of_enemies = data[j].num_of_orc + data[j].num_of_armored
							+ data[j].num_of_wolf + data[j].num_of_demon;
		int all_enemies = num_of_enemies + last_num_of_enemies;
		if(time >= data[j].time)
		{
			for(int i = last_num_of_enemies; i < all_enemies; i++)
			{
				wave[i]->is_generated = true;
				wave[i]->current_img = move_enemy(wave[i], level);
			}	
		}
		last_num_of_enemies += num_of_enemies;
	}
	return wave;	
}