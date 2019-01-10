

using namespace sausageRunner;

std::string random_tile(int *last_broken, int *last_virage){
	int int_rand = 0;
	if (*last_virage == 0){
		int_rand = rand()%2 + 3;
		*last_virage = 9;
	}
	else if(*last_broken == 0){
		int_rand = rand()%4;
		if (int_rand == 3){
			int_rand = 5;
		}
		if (int_rand != 0) {
			*last_broken = 4;
		}
	}

	else {
		(*last_broken)--;
		(*last_virage)--;
	}

	std::string string_rand = std::to_string(int_rand);
	return string_rand;
}

std::string random_obs(int *last_mob){
	int int_rand = 5;
	if(*last_mob == 0){
		int_rand = rand()%5;
		if (int_rand == 4){
			int_rand = 5;
		}
		else if (int_rand != 5) {
			*last_mob = 4;
		}
	}
	else {
		(*last_mob)--;
	}

	std::string string_rand = std::to_string(int_rand);
	return string_rand;
}

std::string random_xobs(std::string obs){
	int int_rand = 5;

	if(obs == "0"){
		int_rand = rand()%3;
	}
	else if(obs == "1"){
		int_rand = rand()%2;
	}
	else if(obs == "2" || obs == "3"){
		int_rand = 0;
	}

	std::string string_rand = std::to_string(int_rand);
	return string_rand;
}

std::string random_bonus(int *last_bonus, std::string obs){
	int int_rand = 5;
	if(*last_bonus == 0){
		if(obs != "2"){
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

std::string random_xbon(std::string bonus, std::string obs, std::string xobs){
	int rand_int_y = 5;

	if(bonus != "5"){
		if (obs != "5") {
			if(obs == "0"){
				if(xobs == "0"){
					rand_int_y = rand()%2 + 1;
				}
				else if(xobs == "1"){
					rand_int_y = 2;
				}
				else if(xobs == "2"){
					rand_int_y = rand()%2;
				}
			}
			else if(obs == "1"){
				if(xobs == "0"){
					rand_int_y = 2;
				}
				else{
					rand_int_y = 0;
				}
			}
		}
		else{
			rand_int_y = rand()%3;
		}
	}

	std::string string_rand = std::to_string(rand_int_y);
	return string_rand;
}

std::string random_ybon(std::string bonus, std::string bloc, std::string obs){
	std::string int_y = "5";

	if(bonus != "5"){
		if (bloc != "0" || obs == "3") {
			int_y = "2";
		}
		else {
			int_y = "1";
		}
	}
	return int_y;
}

std::string random_xcoin(std::string bloc, std::string obs, std::string xobs){
	int int_rand = 5;
	if(obs == "2"){
		int rand = 1;
	}
	else if(obs == "0"){
		if(xobs == "0"){
			int_rand = rand()%2 + 1;
		}
		else if(xobs == "1"){
			int_rand = 2;
		}
		else if(xobs == "2"){
			int_rand = rand()%2;
		}
	}
	else if(obs == "1"){
		if(xobs == "0"){
			int_rand = 2;
		}
		else{
			int_rand = 0;
		}
	}

	else{
		int_rand = rand()%3;
	}


	std::string string_rand = std::to_string(int_rand);
	return string_rand;
}

std::string random_ycoin(std::string bonus, std::string bloc, std::string obs){
	std::string int_y = "5";

	if(xcoin != "5"){
		if (bloc != "0" || obs == "3") {
			int_y = "2";
		}
		else {
			int_y = "1";
		}
	}
	return int_y;
}

void random_map(){
	int last_broken = 2;
	int last_virage = 10;
	int last_mob = 5;
	int last_bonus = 6;

	std::string bloc, obs, xobs, bonus, xbon, ybon, xcoin, ycoin;

	FILE *file = fopen("level", "w");

	for(int j = 0; j < 5; j++){
		fprintf(file, "%s\n", "0 5 5 5 5 5 5 5");
	}

	for (int i = 0; i < 50; i++){
		bloc = random_tile(&last_broken, &last_virage);
		obs = random_obs(&last_mob);
		xobs = random_xobs(obs);
		bonus = random_bonus(&last_bonus, obs);
		xbon = random_xbon(bonus, obs, xobs);
		ybon = random_ybon(bonus, bloc, obs);
		xcoin = random_xcoin(bloc, obs, xobs);
		ycoin = random_ycoin(xcoin, bloc, obs);

		fprintf(file, "%s %s %s %s %s %s %s %s\n", bloc.c_str(), obs.c_str(), xobs.c_str(), bonus.c_str(), xbon.c_str(), ybon.c_str(), xcoin.c_str(), ycoin.c_str() );
	}
}
