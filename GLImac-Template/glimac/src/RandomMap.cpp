#include <glimac/RandomMap.hpp>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

#define EMPTY 5
#define BLOC 0
#define LEFT_POS 0
#define DOWN_POS 0
#define MIDDLE 1
#define RIGHT_POS 2
#define UP_POS 2

#define STR_BLOC "0"
#define KETCHUP "0"
#define MOUSTARD "1"
#define CONSERVE "2"
#define JUICE "3"

#define STR_EMPTY "5"
#define STR_LEFT_POS "0"
#define STR_DOWN_POS "0"
#define STR_MIDDLE "1"
#define STR_RIGHT_POS "2"
#define STR_UP_POS "2"


namespace sausageRunner {

	std::string random_tile(int *last_broken, int *last_virage, int *last_mob){
		int int_rand = BLOC;
		if (*last_virage == 0){
			int_rand = rand()%2 + 3;
			*last_virage = 9;
			*last_mob = 3;
			*last_broken = 2;
		}
		else if(*last_broken == 0){
			int_rand = rand()%4;
			if (int_rand == 3){
				int_rand = EMPTY;
			}
			if (int_rand != BLOC) {
				*last_broken = 4;
				*last_mob = 3;
			}
		}

		else {
			(*last_broken)--;
			(*last_virage)--;
		}

		std::string string_rand = std::to_string(int_rand);
		return string_rand;
	}

	std::string random_obs(int *last_mob, std::string bloc, int *last_broken, int *last_virage){
		int int_rand = EMPTY;
		if(*last_mob == 0 && bloc == STR_BLOC){
			int_rand = rand()%5;
			if (int_rand == 4){
				int_rand = EMPTY;
			}
			else if (int_rand != EMPTY) {
				*last_mob = 4;
				*last_broken += 2;
				*last_virage +=2;
			}
		}
		else {
			(*last_mob)--;
		}

		std::string string_rand = std::to_string(int_rand);
		return string_rand;
	}

	std::string random_xobs(std::string obs){
		int int_rand = EMPTY;

		if(obs == KETCHUP){
			int_rand = rand()%3;
		}
		else if(obs == MOUSTARD){
			int_rand = rand()%2;
		}
		else if(obs == CONSERVE || obs == JUICE){
			int_rand = LEFT_POS;
		}

		std::string string_rand = std::to_string(int_rand);
		return string_rand;
	}

	std::string random_bonus(int *last_bonus, std::string obs){
		int int_rand = EMPTY;
		if(*last_bonus == 0){
			if(obs != CONSERVE){
				int_rand = rand()%3;
				*last_bonus = 20;
			}
		}
		else {
			(*last_bonus)--;
		}

		std::string string_rand = std::to_string(int_rand);
		return string_rand;
	}

	std::string random_xbon(const std::string bonus, const std::string obs, const std::string xobs){
		int rand_int_x = EMPTY;
		
		if(bonus != STR_EMPTY){
			if (obs != STR_EMPTY) {
				if(obs == KETCHUP){
					if(xobs == STR_LEFT_POS){
						rand_int_x = rand()%2 + 1;
					}
					else if(xobs == STR_MIDDLE){
						rand_int_x = UP_POS;
					}
					else if(xobs == STR_RIGHT_POS){
						rand_int_x = rand()%2;
					}
				}
				else if(obs == MOUSTARD){
					if(xobs == STR_LEFT_POS){
						rand_int_x = UP_POS;
					}
					else{
						rand_int_x = DOWN_POS;
					}
				}
			}
			else{
				rand_int_x = rand()%3;
			}
		}
		else {
			return STR_EMPTY;
		}

		std::string string_rand = std::to_string(rand_int_x);
		return string_rand;
	}

	std::string random_ybon(const std::string bonus, const std::string bloc, const std::string obs){
		std::string int_y = STR_EMPTY;

		if(bonus != STR_EMPTY){
			if (bloc != STR_BLOC || obs == JUICE) {
				int_y = STR_UP_POS;
			}
			else {
				int_y = STR_MIDDLE;
			}
		}
		return int_y;
	}

	std::string random_xcoin(const std::string bonus, const std::string bloc, const std::string obs, const std::string xobs){
		int int_rand = EMPTY;
		if(bloc != STR_BLOC || bonus != STR_EMPTY){
			int_rand = EMPTY;
		}
		else if(obs == CONSERVE){
			int_rand = MIDDLE;
		}
		else if(obs == KETCHUP){
			if(xobs == STR_LEFT_POS){
				int_rand = rand()%2 + 1;
			}
			else if(xobs == STR_MIDDLE){
				int_rand = RIGHT_POS;
			}
			else if(xobs == STR_RIGHT_POS){
				int_rand = rand()%2;
			}
		}
		else if(obs == MOUSTARD){
			if(xobs == STR_LEFT_POS){
				int_rand = RIGHT_POS;
			}
			else{
				int_rand = LEFT_POS;
			}
		}

		else{
			int_rand = rand()%2;
			if(int_rand == 0){
				int_rand = MIDDLE;
			}
			else {
				int_rand = EMPTY;
			}
		}


		std::string string_rand = std::to_string(int_rand);
		return string_rand;
	}

	std::string random_ycoin(const std::string xcoin, const std::string bloc, const std::string obs){
		std::string int_y = STR_EMPTY;

		if(xcoin != STR_EMPTY){
			if (obs == CONSERVE){
				int_y = STR_DOWN_POS;
			}
			else if (bloc != STR_BLOC || obs == JUICE) {
				int_y = STR_UP_POS;
			}
			else {
				int_y = STR_MIDDLE;
			}
		}
		return int_y;
	}

	void random_map(){
		int last_broken = rand()%5 + 2;
		int last_virage = rand()%10 + 5;
		int last_mob = rand()%10 + 3;
		int last_bonus = rand()%10 + 7;

		std::string bloc, obs, xobs, bonus, xbon, ybon, xcoin, ycoin;

		FILE *file = fopen("./levels/LevelRandom", "w+");

		for(int j = 0; j < 5; j++){
			fprintf(file, "%s\n", "0 5 5 5 5 5 5 5");
		}

		for (int i = 0; i < 50; i++){
			bloc = random_tile(&last_broken, &last_virage, &last_mob);
			obs = random_obs(&last_mob, bloc, &last_broken, &last_virage);
			xobs = random_xobs(obs);
			bonus = random_bonus(&last_bonus, obs);
			xbon = random_xbon(bonus, obs, xobs);
			ybon = random_ybon(bonus, bloc, obs);
			xcoin = random_xcoin(bonus, bloc, obs, xobs);
			ycoin = random_ycoin(xcoin, bloc, obs);

			fprintf(file, "%s %s %s %s %s %s %s %s\n", bloc.c_str(), obs.c_str(), xobs.c_str(), bonus.c_str(), xbon.c_str(), ybon.c_str(), xcoin.c_str(), ycoin.c_str() );
		}
		for(int j = 0; j < 3; j++){
			fprintf(file, "%s\n", "0 5 5 5 5 5 5 5");
		}
		fclose(file);
	}
}
