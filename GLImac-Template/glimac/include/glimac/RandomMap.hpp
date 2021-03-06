#ifndef _LIB_IMPORT_RANDOM_IMAC_LSM
#define _LIB_IMPORT_RANDOM_IMAC_LSM
#pragma once

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

namespace sausageRunner {

	/*!
	 * \brief Create a random tile, paying attention to last obstacles
	 */
	std::string random_tile(int *last_broken, int *last_virage, int *last_mob);

	/*!
	 * \brief Create a random obstacle, paying attention to last obstacles
	 */
	std::string random_obs(int *last_mob, std::string bloc, int *last_broken, int *last_virage);

	/*!
	 * \brief Give the obstacle a random position
	 */
	std::string random_xobs(std::string obs);

	/*!
	 * \brief Create a random bonus, paying attention to the obstacles
	 */
	std::string random_bonus(int *last_bonus, std::string obs);

	/*!
	 * \brief Give the bonus a right x position
	 */
	std::string random_xbon(const std::string bonus, const std::string obs, const std::string xobs);

	/*!
	 * \brief Give the bonus a right y position
	 */
	std::string random_ybon(const std::string bonus, const std::string bloc, const std::string obs);

	/*!
	 * \brief Create a random coin, paying attention to other elements
	 */
	std::string random_xcoin(const std::string bonus, const std::string bloc, const std::string obs, const std::string xobs);

	/*!
	 * \brief Give the coin an appropriate y position according to the other elements
	 */
	std::string random_ycoin(const std::string xcoin, const std::string bloc, const std::string obs);

	/*!
	 * \brief Calling the differents fonctions to create the random map
	 */
	void random_map();
}

#endif
