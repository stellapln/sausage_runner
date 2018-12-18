#ifndef _LIB_IMPORT_LIBRARY_IMAC_LSM
#define _LIB_IMPORT_LIBRARY_IMAC_LSM
#pragma once



class Bonus {
	private:
		int _id;
		int _posX;
		int _posY;
		// + lambda fonction pour coder le comportement
	public:
		Bonus(int x, int y): _posX(x), _posY(y){}
};

class Obstacle {
	private:
		int _model;
		int _posX;
		std::vector<int> _bbox;
	
	public:
		Obstacle(int m,int x): _model(m), _posX(x){
			setBbox();
		}
			
		void setBbox(){
			if(_model == 0){ //Ketchup
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
			else if(_model == 1){ //Moutarde
				if(_posX == 0){
					_bbox.insert(_bbox.end(),{1,1,0,1,1,0,0,0,0});
				}
				else if(_posX == 1){
					_bbox.insert(_bbox.end(),{0,1,1,0,1,1,0,0,0});
				}
			}
			else if(_model == 2){ //Conserve
				_bbox.insert(_bbox.end(),{1,0,1,1,1,1,1,1,1});
			}
			else if(_model == 3){ //Jus
				_bbox.insert(_bbox.end(),{1,1,1,0,0,0,0,0,0});
			}
		}
};

class Tile{
	public:
		Support _support;
		Obstacle _obstacle;
		Bonus _bonus;
	
		int _x_coin; // pos x coin
		int _y_coin; // pos y coin
	
		Tile(int s,int o,int ox,int b,int bx,int by,int cx,int cy): _x_coin(cx), _y_coin(cy){
			_support = Support(s);
			_obstacle = Obstacle(o, ox);
			_bonus = Bonus(bx, by);
		}
};

class Support{
	private:
		int _id;
	public:
		Support(int id): _id(id){}
};

class Library {
	private:
		std::vector<Model> _persos;
		std::vector<Model> _supports;
		std::vector<Model> _obstacles;
		std::vector<Model> _bonus;
		std::vector<Model> _skybox;
		Model _coin;

	public:
		Library(Model coin);
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
