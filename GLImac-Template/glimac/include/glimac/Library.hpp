#ifndef _LIB_IMPORT_LIBRARY_IMAC_LSM
#define _LIB_IMPORT_LIBRARY_IMAC_LSM
#pragma once


/*! \class Bonus
   * \brief
   *	Class bonus for magnet and shield
   *  	
   */
class Bonus {
	private:
		int _id; /*!< id of the item int the library*/
		int _posX; /*!< Bonus position x*/
		int _posY; /*!< Bonus position y*/
	
		// + lambda fonction pour coder le comportement
	public:
		/*!
		 *  \brief Constructor of bonus
		 */
		Bonus(int x, int y): _posX(x), _posY(y){}
};

/*! \class Support
   * \brief
   *	Class for the market aisle
   *  
   */
class Support{
	private:
		int _id; /*!< id of the item int the library*/
	public:
		/*!
		 *  \brief Constructor of support
		 */
		Support(int id = 0): _id(id){}
};

/*! \class Obstacle
   * \brief
   *	
   *  	Class for the obstacles : juice, moustard, ketchup and knives.
   */
class Obstacle {
	private:
		int _id; /*!< id of the item int the library*/
		int _posX; /*!< Obstacle position x*/
		std::vector<int> _bbox; /*!< Bounding box*/
	
	public:
		/*!
		 *  \brief Constructor of obstacle
		 */
		Obstacle(int m,int x): _id(m), _posX(x){
			setBbox();
		}
		
		/*!
		 *  \brief Setter for bounding box
		 */
		void setBbox(){
			if(_id == 0){ //Ketchup
				if(_posX == 0){
					_bbox.insert(_bbox.end(),{1,0,0,1,0,0,1,0,0});
				}
				else if(_posX == 1){
					_bbox.insert(_bbox.end(),{0,1,0,0,1,0,0,1,0});
				}
				else if(_posX == 2){
					_bbox.insert(_bbox.end(),{0,0,1,0,0,1,0,0,1});
				}
			}
			else if(_id == 1){ //Moutarde
				if(_posX == 0){
					_bbox.insert(_bbox.end(),{1,1,0,1,1,0,0,0,0});
				}
				else if(_posX == 1){
					_bbox.insert(_bbox.end(),{0,1,1,0,1,1,0,0,0});
				}
			}
			else if(_id == 2){ //Conserve
				_bbox.insert(_bbox.end(),{1,0,1,1,1,1,1,1,1});
			}
			else if(_id == 3){ //Jus
				_bbox.insert(_bbox.end(),{1,1,1,0,0,0,0,0,0});
			}
		}
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
	
		int _x_coin; /*!< Pos x of the coins */
		int _y_coin; /*!< Pos y of the coins */
	
		/*!
		 *  \brief Constructor of tile
		 */
		Tile(int s,int o,int ox,int b,int bx,int by,int cx,int cy)
			: _support(s),_obstacle(o, ox),_bonus(bx, by),_x_coin(cx), _y_coin(cy){}
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
		void setCoin(Model m){_coin = m;}

		Model perso(unsigned int i) const {return _persos[i];}
		Model support(unsigned int i) const {return _supports[i];}
		Model bonus(unsigned int i) const {return _bonus[i];}
		Model obstacle(unsigned int i) const {return _obstacles[i];}
		Model skybox(unsigned int i) const {return _skybox[i];}
		Model coin() const {return _coin;}

		int nPerso() const {return _persos.size();}
		int nSupport() const {return _supports.size();}
		int nBonus() const {return _bonus.size();}
		int nObstacle() const {return _obstacles.size();}
		int nSkybox() const {return _skybox.size();}
};

#endif
