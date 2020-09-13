#include <vector> 
#include <string>

#include"rsdl.hpp"


#define  WOLF_LEFT "assets/enemies/wolf/left.png"
#define  WOLF_RIGHT "assets/enemies/wolf/right.png"
#define  WOLF_BACK "assets/enemies/wolf/back.png"
#define  WOLF_FRONT "assets/enemies/wolf/front.png"

#define  ORC_LEFT "assets/enemies/orc/left.png"
#define  ORC_RIGHT "assets/enemies/orc/right.png"
#define  ORC_BACK "assets/enemies/orc/back.png"
#define  ORC_FRONT "assets/enemies/orc/front.png"

#define  DEMON_LEFT "assets/enemies/demon/left.png"
#define  DEMON_RIGHT "assets/enemies/demon/right.png"
#define  DEMON_BACK "assets/enemies/demon/back.png"
#define  DEMON_FRONT "assets/enemies/demon/front.png"

#define  ARMORED_LEFT "assets/enemies/armored/left.png"
#define  ARMORED_RIGHT "assets/enemies/armored/right.png"
#define  ARMORED_BACK "assets/enemies/armored/back.png"
#define  ARMORED_FRONT "assets/enemies/armored/front.png"

#define  ARCHER "assets/towers/archer.png"
#define  CANON "assets/towers/canon.png"
#define  MAGE "assets/towers/mage.png"
#define  ICY "assets/towers/icy.png"

#define BALL_IMG "Ball.png"
#define LOST_IMG "you_lost.png"
#define WIN_IMG "you_won.png"
#define NO_IMG "failed"

#define UNIT (enemy->speed)/(210*5)
#define SIZE_OF_TOWER 70
#define WIDTH_OF_WINDOW 800
#define HEIGHT_OF_WINDOW 801
#define SIZE_OF_ENEMY 35
#define BALL_SIZE 15
#define NOT_FOUND -1

typedef std::string Address;

enum EnemyTypeEnum
{
	orc,
	wolf,
	armored,
	demon
};

enum TowerTypeEnum
{
	archer,
	canon,
	icy,
	mage,
	none
};

struct Enemy
{
	EnemyTypeEnum enemy_type;
	int lives;
	float speed;
	bool is_generated = false;
	bool armor = false;
	bool magic_armor = false;
	int killing_reward;
	int lives_of_gamer;
	float x;
	float y;
	Address front_img;
	Address back_img;
	Address right_img;
	Address left_img;
	Address current_img;
};

struct Tower
{
	TowerTypeEnum tower_type;
	int damage;
	int time_for_each_throw_ms;
	int money_for_building;
	int radius_of_damaging_px;
	int x;
	int y;
	bool damage_to_all;
	std::string image;
	bool magical_attack;
	bool physical_attack;
	double time_of_last_attack=0;
};

struct Gamer
{
	int lives_of_gamer = 15;
	int money = 220;
};

struct  Ball
{
	Address img = BALL_IMG;
	float x;
	float y;
	float speed = 0.8;
	int damage;
	Enemy* enemy;
	bool valid_to_show = true ;
};

struct Time
{
	int time;
	int num_of_armored = 0;
	int num_of_orc = 0;
	int num_of_demon = 0;
	int num_of_wolf = 0;
	int wave = 0;
};

std::vector<Tower> initial_towers(int level);
void initial_tower(Tower& tower);
void initial_enemy(Enemy* enemy, EnemyTypeEnum enemy_type, int level);
void build_tower(int x, int y, char pressed_char, std::vector<Tower>& towers, Gamer& gamer);
std::vector<Ball> generate_balls(std::vector<Tower>& towers, std::vector<Enemy*> wave, double time);
void shoot_the_balls(Window& win, std::vector<Ball> balls, std::vector<Enemy*> wave, 
					std::vector<Tower>& towers, Address level_img, Gamer& gamer);
Address move_level1(Enemy* enemy);
Address move_level2(Enemy* enemy);
Address move_enemy(Enemy* enemy, int level);
void draw_enemies(Window& win,std::vector<Enemy*> enemies);
void draw_towers(Window& win, std::vector<Tower> towers);
void check_enemy_exit(std::vector<Enemy*> enemies, Gamer& gamer);
bool check_if_gamer_won(std::vector<Enemy*> enemies);
std::vector<Enemy*> initial_wave(std::vector<Time> data, int level);
std::vector<std::vector <Time> > load_data(int n, Address& level_img);

std::vector<Enemy*> generate_wave(double time,Window& win,std::vector<Enemy*> wave, 
							std::vector<Time> data, int level);