#ifndef _LIB_IMPORT_RANDOM_IMAC_LSM
#define _LIB_IMPORT_RANDOM_IMAC_LSM
#pragma once

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

namespace sausageRunner {

	std::string random_tile(int *last_broken, int *last_virage, int *last_mob);

	std::string random_obs(int *last_mob, std::string bloc, int *last_broken, int *last_virage)

	std::string random_xobs(std::string obs);

	std::string random_bonus(int *last_bonus, std::string obs);

	std::string random_xbon(std::string bonus, std::string obs, std::string xobs);

	std::string random_ybon(std::string bonus, std::string bloc, std::string obs);

	std::string random_xcoin(std::string bloc, std::string obs, std::string xobs);

	std::string random_ycoin(std::string xcoin, std::string bloc, std::string obs);

	void random_map();
}

#endif
