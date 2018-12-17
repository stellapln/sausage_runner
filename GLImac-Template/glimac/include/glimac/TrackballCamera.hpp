#ifndef _LIB_IMPORT_TRACKBALLCAMERA_IMAC_LSM
#define _LIB_IMPORT_TRACKBALLCAMERA_IMAC_LSM
#pragma once

class SimpleAxeCam
{
	protected:
		float _fDistance;
		float _fAngleX;
		float _fAngleY;
		SimpleAxeCam(float ax=0.0f,float ay=0.0f):_fAngleX(ax),_fAngleY(ay);
		void rotateLeft(const float degrees) = 0;
		void rotateTop(const float degrees) = 0;

};

class TrackballCamera : public SimpleAxeCam
{
	protected:
		float _fDistance;
	public:
		TrackballCamera(float d=5.0f,float ax=0.0f,float ay=0.0f):_fDistance(d),SimpleAxeCam(ax,ay){}
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
			view = glm::rotate(view,glm::radians(_fAngleY),glm::vec3(0.0,1.0,0.0));
			return view;
		}
};

class EyesCam : public SimpleAxeCam
{
	private:
		float _maxAngle = 90.0f;
		glm::vec3 _position = glm::vec3(0.0f,-1.2f,0.2f);
	public:
		EyesCam(float ax=0.0f,float ay=0.0f):TrackballCamera(0.0,ax,ay){}
		void setMaxAngle(float m)
		{
			_maxAngle = m;
		}
		void setPosition(const glm::vec3 &p)
		{
			//_position = p;
		}
		void rotateLeft(const float degrees) override{
			float newAngle = _fAngleX+degrees;
			std::cout << newAngle << std::endl;
			if(newAngle > -_maxAngle && newAngle < _maxAngle)
				_fAngleX = newAngle;
		}
		void rotateTop(const float degrees) override{
			float newAngle = _fAngleY+degrees;
			if(newAngle > -_maxAngle && newAngle < _maxAngle)
				_fAngleY = newAngle;
		}
		void moveFront(const float delta){}

		glm::mat4 getMatrixView() const{
			glm::mat4 view  = glm::rotate(glm::mat4(),glm::radians(_fAngleX),glm::vec3(1.0,0.0,0.0));
			view = glm::rotate(view,glm::radians(_fAngleY),glm::vec3(0.0,1.0,0.0));
			view = glm::translate(view,_position);
			return view;
		}
};
#endif