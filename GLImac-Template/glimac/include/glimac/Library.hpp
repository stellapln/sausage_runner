#ifndef _LIB_IMPORT_LIBRARY_IMAC_LSM
#define _LIB_IMPORT_LIBRARY_IMAC_LSM
#pragma once

#include <vector>
#include <iostream>
#include <glimac/Model.hpp>

#define NO_COIN_VALUE 5


namespace sausageRunner {
	/*! \class LibElem
	   * \brief
	   *	Mother class for elements
	   *  	and functions
	   */
	class LibElem {
		public:
			/*!
			 *  \brief Bounding box setter
			 */
			virtual void setBbox() = 0;
		
			/*!
			 *  \brief Bounding box getter
			 */
			virtual std::vector<int> getBbox() = 0;
		
			/*!
			 *  \brief ID getter
			 */
			virtual int id() = 0;
		
			/*!
			 *  \brief Describer
			 */
			virtual void descr() {
				std::cout << "Lib Elem" << std::endl;
			}
			~LibElem(){}
	};

	/*! \class Coin
	   * \brief
	   *	Class for coins
	   *  	
	 */
	class Coin : public LibElem {
		private:
			int _posX; /*!< Bonus position x*/
			int _posY; /*!< Bonus position y*/
			std::vector<int> _bbox; /*!< Bounding box*/
		
		public:
			/*!
			 *  \brief Constructor of bonus
			 */
			Coin(int x, int y):_posX(x), _posY(y){
				setBbox();
			}
		
			/*!
			 *  \brief ID getter
			 */
			int id(){return 0;}
		
			/*!
			 *  \brief Pos getter
			 */
			int x(){return _posX;}
		
			/*!
			 *  \brief Pos getter
			 */
			int y(){return _posY;}
		
			/*!
			 *  \brief Bounding box setter
			 */
			void setBbox() override;
		
			/*!
			 *  \brief Bounding box getter
			 */
			std::vector<int> getBbox() override{
				return _bbox;
			} 
		
			/*!
			 *  \brief Describer
			 */
			void descr(){
				std::cout << "Coin Elem" << std::endl;
			}
			~Coin(){}
	};


	/*! \class Bonus
	   * \brief
	   *	Class bonus for magnet and shield
	   *  	
	   */
	class Bonus : public LibElem {
		private:
			int _id; /*!< id of the item int the library*/
			int _posX; /*!< Bonus position x*/
			int _posY; /*!< Bonus position y*/
			std::vector<int> _bbox; /*!< Bounding box*/
		
		public:
			/*!
			 *  \brief Constructor of bonus
			 */
			Bonus(int id, int x, int y):_id(id), _posX(x), _posY(y){
				setBbox();
			}
			/*!
			 *  \brief ID getter
			 */
			int id() override{return _id;}
			/*!
			 *  \brief Pos getter
			 */
			int x(){return _posX;}
			/*!
			 *  \brief Pos getter
			 */
			int y(){return _posY;}
			/*!
			 *  \brief Bounding box setter
			 */
			void setBbox() override;
			/*!
			 *  \brief Bounding box getter
			 */
			std::vector<int> getBbox() override{
				return _bbox;
			}
			~Bonus(){}
	};

	/*! \class Support
	   * \brief
	   *	Class for the market aisle
	   *  
	   */
	class Support : public LibElem {
		private:
			int _id; /*!< id of the item int the library*/
			std::vector<int> _bbox; /*!< Bounding box*/
		public:
			/*!
			 *  \brief Constructor of support
			 */
			Support(int id = 0): _id(id){
				setBbox();
			}
		
			/*!
			 *  \brief ID getter
			 */
			int id(){return _id;}

			/*!
			 *  \brief Setter for bounding box
			 */
			void setBbox() override;
		
			/*!
			 *  \brief Getter for bounding box
			 */
			std::vector<int> getBbox() override{
				return _bbox;
			}
			~Support(){}
	};

	/*! \class Obstacle
	   * \brief
	   *	
	   *  	Class for the obstacles : juice, moustard, ketchup and knives.
	   */
	class Obstacle : public LibElem {
		private:
			int _id; /*!< id of the item int the library*/
			int _posX; /*!< Obstacle position */
			std::vector<int> _bbox; /*!< Bounding box*/
		
		public:
			/*!
			 *  \brief Setter for bounding box
			 */
			void setBbox() override;
			
			/*!
			 *  \brief Constructor of obstacle
			 */
			Obstacle(int m,int x): _id(m), _posX(x){
				setBbox();
			}
		
			/*!
			 *  \brief ID getter
			 */
			int id(){return _id;}
		
			/*!
			 *  \brief Position getter
			 */
			int x(){return _posX;}

			/*!
			 *  \brief Getter for bounding box
			 */
			std::vector<int> getBbox() override{
				return _bbox;
			}
			~Obstacle(){}
			
	};

	/*! \class Tile
	 * \brief
	 *	Contains all the objects on the tile
	 *  	
	 */
	class Tile{
		public:
			Support _support; /*!< Support of the tile */
			Obstacle _obstacle; /*!< Obstacles on the tile */
			Bonus _bonus; /*!< Bonus on the tile */
			Coin _coin; /*!< Coins on the tile */

			bool bonusTaken = false; /*!< Bool variable : bonus taken ? */
			bool coinTaken = false; /*!< Bool variable : coin taken ? */
		
			/*!
			 *  \brief Constructor of tile
			 */
			Tile(int s,int o,int ox,int b,int bx,int by,int cx,int cy)
				: _support(s),_obstacle(o, ox),_bonus(b, bx, by),_coin(cx,cy){}
			
			/*!
			 *  \brief Bool : tile have bonus ?
			 */
			bool haveBonus(){
				return !bonusTaken;
			}
		
			/*!
			 *  \brief Bool : tile have coin ?
			 */
			bool haveCoin(){
				return (!coinTaken && _coin.x() != NO_COIN_VALUE && _coin.y() != NO_COIN_VALUE);
			}
		
			/*!
			 *  \brief Player takes bonus
			 */
			void takeBonus(){
				bonusTaken = true;
			}
		
			/*!
			 *  \brief Player takes coin
			 */
			void takeCoin(){
				coinTaken = true;
			}
		
			/*!
			 *  \brief Reset coin and bonus on a tile
			 */
			void reset(){
				bonusTaken = false;
				coinTaken = false;
			}
			~Tile(){}
	};

	/*! \class Library
	   * \brief
	   *	Libraries of items in vectors
	   *  
	   */
	class Library {
		private:
			std::vector<Model> _persos; /*!< Vector countaining characters */
			std::vector<Model> _supports; /*!< Vector countaining supports */
			std::vector<Model> _obstacles; /*!< Vector countaining obstacles */
			std::vector<Model> _bonus; /*!< Vector countaining bonus */
			std::vector<Model> _skybox; /*!< Vector countaining skybox */
			std::vector<Model> _specials; /*!< Vector countaining specials objects */
			Model _coin; /*!< .obj of the coin */

		public:
			/*!
			 *  \brief Constructor of Library
			 */
			Library(Model coin);
		
			/*!
			 *  \brief Adding models to library
			 */
			void addPerso(Model m){
				_persos.push_back(m);
			}
			void addSupport(Model m){
				_supports.push_back(m);
			}
			void addBonus(Model m){
				_bonus.push_back(m);
			}
			void addObstacle(Model m){
				_obstacles.push_back(m);
			}
			void addSkybox(Model m){
				_skybox.push_back(m);
			}
			void addSpecial(Model m){
				_specials.push_back(m);
			}
			void setCoin(Model m){_coin = m;}

			/*!
			 *  \brief Getters for libraries
			 */
			Model perso(unsigned int i) const {return _persos[i];}
			Model support(unsigned int i) const {return _supports[i];}
			Model bonus(unsigned int i) const {return _bonus[i];}
			Model obstacle(unsigned int i) const {return _obstacles[i];}
			Model skybox(unsigned int i) const {return _skybox[i];}
			Model special(unsigned int i) const {return _specials[i];}
			Model coin() const {return _coin;}

			/*!
			 *  \brief Get numbers of models
			 */
			int nPerso() const {return _persos.size();}
			int nSupport() const {return _supports.size();}
			int nBonus() const {return _bonus.size();}
			int nObstacle() const {return _obstacles.size();}
			int nSkybox() const {return _skybox.size();}
			int nSpecial() const {return _specials.size();}

			~Library(){}
	};
}

#endif
