#include <gb/gb.h>
#include <rand.h>
//#include <stdio.h>
#include "tiles.c"
#include "dungeon.c"
#include "ball.c"
#define empty 0x00
#define curve 0x40
#define spring_back 0x4C
#define left_tri 0x43
#define right_tri 0x42
#define dimond 0x3F
#define diglett 0x3D
#define fifty 0x44
#define twenty 0x45
#define ten 0x47
#define zero 0x48



UINT8 gridxDD, gridyDD;


void init();
void checkInput();
void updateSwitches();
typedef enum { false, true } bool;


UINT8 player[2];

UINT8 spring[2];

UINT8 score_hun[2];

UINT8 score_ten[2];

UINT8 score_ge[2];

UINT8 Life_hun[2];

UINT8 Life_ten[2];

UINT8 Life_ge[2];

UINT8 Step;

bool hitback;

bool end;

UINT8 coin;

UINT16 * classNumber;


extern void update();

void main() {
	//* classNumber = 308;
	//char * s = "Welcome to GAMEBOY \n Project!!\nPress Start";
	//printf(s);
	//printf("%d\n", *classNumber)
	//waitpad(J_START);
	
	init();
	
	SWITCH_ROM_MBC1(1);
	update();
	
}

void init() {
	
	DISPLAY_ON;						// Turn on the display
	set_bkg_data(0, 150, tiles);		// Load 23 tiles into background memory
	
	set_bkg_tiles(0,0,20,18,dungeon); 
	
	
	set_sprite_data(0, 12, ball);

	//ball and spring
	set_sprite_tile(0,0);
	
	set_sprite_tile(1,1);
	
	
	//score
	set_sprite_tile(2,3);
	
	set_sprite_tile(3,3);
	
	set_sprite_tile(4,3);
	
	
	
	player[0] = 144;
	player[1] = 136;
	
	spring[0] = 144;
	spring[1] = 144;
	
	score_hun[0] = 64;
	score_hun[1] = 24;
	
	score_ten[0] = 72;
	score_ten[1] = 24;
	
	score_ge[0] = 80;
	score_ge[1] = 24;
	
	Step = 0;
	
	hitback = false;
	end = false;
}

void updateSwitches() {
	
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
	
}

int gridPosDD(int addx, int addy){
    gridxDD = (player[0]/8) + addx;
    gridyDD = (player[1]/8) + addy;
    return dungeon[((20*gridyDD) + gridxDD)];
}



void checkInput() {


	if (joypad() & J_A)
	{
		if(end == true){
			hitback = false;		
			player[0] = 144;
			player[1] = 136;
			end = false;
		}
	} 	

    if (joypad() & J_B) {
		
		if(player[0] == 144 && player[1] == 136)
		{
			if(Step < 255){
				Step += 3;
			}else{
				Step = 255;
			}
			
		}
		
		set_sprite_tile(1,2);
    }else{
		
		if(Step > 0)
		{
			if(player[1] > 50)
			{
				player[1]--;
			}
			else if(player[1] == 50)
			{
				player[1]--;
				player[0]--;
			}
			else if(player[0] > 16 && hitback == false)
			{
				player[0]--;
			}				
			else
			{
				hitback++;
				player[0]++;
			}
			Step --;
		}
		else if(player[0] == 144 && player[1] < 136)
		{
			player[1]++;
		}
		else if(player[1] < 144 && player[0] != 144){
			
			if(gridPosDD(0,1) == dimond || gridPosDD(0,1) == diglett){
				coin = rand() % 2;
				if(coin == 0){
					if(gridPosDD(1,0) == empty){
						player[0] = (player[0]/8+1)*8;
					}
				}else{
					if(gridPosDD(-1,0) == empty){
						player[0] = (player[0]/8-1)*8;
					}
				}
			}
			if(gridPosDD(0,1) == left_tri){
				if(gridPosDD(1,0) == empty){
					player[0] = (player[0]/8+1)*8;
				}
			}
			if(gridPosDD(0,1) == right_tri){
				if(gridPosDD(-1,0) == empty){
					player[0] = (player[0]/8-1)*8;
				}
			}else{
				
					player[1]++;
				
			}
		}
		else{
			if(player[0] == 16|| player[0] == 128){
				set_sprite_tile(3,8);
			}else if(player[0] == 32|| player[0] == 112){
				set_sprite_tile(3,5);
			}else if(player[0] == 48|| player[0] == 98){
				set_sprite_tile(3,4);
			}
			
			
		}
		if(player[1] == 136 && player[0] != 144)
		{
			end = true;
		}
		set_sprite_tile(1,1);
	}
	
	// Move the sprite in the first movable sprite list (0)
	//  to the position of X (player[0]) and y (player[1])
	move_sprite(0, player[0], player[1]);
	
	move_sprite(1, spring[0], spring[1]);
	
	//set place of score
	move_sprite(2, score_hun[0], score_hun[1]);
	
	move_sprite(3, score_ten[0], score_ten[1]);
	
	move_sprite(4, score_ge[0], score_ge[1]);
	
}

