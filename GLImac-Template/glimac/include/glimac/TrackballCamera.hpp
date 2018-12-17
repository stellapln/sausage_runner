#ifndef _LIB_IMPORT_TRACKBALLCAMERA_IMAC_LSM
#define _LIB_IMPORT_TRACKBALLCAMERA_IMAC_LSM
#pragma once

class TrackballCamera
{
	private:
		float _fDistance;
		float _fAngleX;
		float _fAngleY;
	public:
		TrackballCamera(float d=5.0f,float ax=0.0f,float ay=0.0f):_fDistance(d),_fAngleX(ax),_fAngleY(ay){}
		void moveFront(const float delta){
			_fDistance -= delta;
		}
		void rotateLeft(const float degrees){
			_fAngleX+=degrees;
		}
		void rotateTop(const float degrees){
			_fAngleY+=degrees;
		}

		glm::mat4 getMatrixView() const{
			glm::mat4 view = glm::translate(glm::mat4(),glm::vec3(0.0,0.0,-_fDistance));
			view = glm::rotate(view,glm::radians(_fAngleX),glm::vec3(1.0,0.0,0.0));
			view = glm::rotate(view,glm::radians(_fAngleY),glm::vec3(0.0,0.0,1.0));
			return view;
		}
};
#endif