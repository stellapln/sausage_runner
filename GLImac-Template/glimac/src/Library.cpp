#include <glimac/Library.hpp>

using namespace sausageRunner;

Library::Library(Model coin):_coin(coin){}

void Obstacle::setBbox(){
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

void Support::setBbox(){
	if(_id == 0){ //Normal
		_bbox.insert(_bbox.end(),{0,0,0,0,0,0,0,0,0});
	}
	else if(_id == 1){
		_bbox.insert(_bbox.end(),{0,1,1,0,0,0,0,0,0});
	}
	else if(_id == 2){
		_bbox.insert(_bbox.end(),{1,1,0,0,0,0,0,0,0});
	}
	else if(_id == 3){
		_bbox.insert(_bbox.end(),{1,1,0,1,1,0,1,1,0});
	}
	else if(_id == 4){
		_bbox.insert(_bbox.end(),{0,1,1,0,1,1,0,1,1});
	}
	else if(_id == 5){
		_bbox.insert(_bbox.end(),{1,1,1,0,0,0,0,0,0});
	}
}

void Bonus::setBbox(){
	_bbox.insert(_bbox.end(),{0,0,0,0,0,0,0,0,0});
	_bbox[_posY*3 + _posX] = 1;
}

void Coin::setBbox(){
	_bbox.insert(_bbox.end(),{0,0,0,0,0,0,0,0,0});
	_bbox[_posY*3 + _posX] = 1;
}
