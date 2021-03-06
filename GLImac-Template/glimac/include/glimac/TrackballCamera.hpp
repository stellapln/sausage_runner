#ifndef _LIB_IMPORT_TRACKBALLCAMERA_IMAC_LSM
#define _LIB_IMPORT_TRACKBALLCAMERA_IMAC_LSM
#pragma once

#define INITIAL_EYE_POSITION glm::vec3(0.0f,-1.2f,0.2f)
#define MAX_ANGLE_EYE_CAM 90.0f

class SimpleAxeCam
{
	protected:
		float _fDistance;
		float _fAngleX;
		float _fAngleY;
	public:
		SimpleAxeCam(const float ax=0.0f,const float ay=0.0f):_fAngleX(ax),_fAngleY(ay){};
		virtual void rotateLeft(const float degrees) = 0;
		virtual void rotateTop(const float degrees) = 0;
		virtual void moveFront(const float delta) = 0;
		virtual glm::mat4 getMatrixView() const = 0;
		virtual void setPosition(const glm::vec3 &p) = 0;
		virtual void reset(const float d,const float ax,const float ay) = 0;

		~SimpleAxeCam(){}
};

class TrackballCamera : public SimpleAxeCam
{
	protected:
		float _fDistance;
	public:
		TrackballCamera(const float d=5.0f,const float ax=0.0f,const float ay=0.0f):_fDistance(d),SimpleAxeCam(ax,ay){}

		void reset(const float d,const float ax,const float ay){
			_fDistance = d;
			_fAngleX = ax;
			_fAngleY = ay;
		}
		void moveFront(const float delta) override{
			_fDistance -= delta;
		}
		void rotateLeft(const float degrees) override{
			_fAngleX+=degrees;
		}
		void rotateTop(const float degrees) override{
			_fAngleY+=degrees;
		}
		void setPosition(const glm::vec3 &p) override{}

		glm::mat4 getMatrixView() const override{
			glm::mat4 view = glm::translate(glm::mat4(),glm::vec3(0.0,0.0,-_fDistance));
			view = glm::rotate(view,glm::radians(_fAngleX),glm::vec3(1.0,0.0,0.0));
			view = glm::rotate(view,glm::radians(_fAngleY),glm::vec3(0.0,1.0,0.0));
			return view;
		}
		~TrackballCamera(){}
};

class EyesCam : public SimpleAxeCam
{
	private:
		float _maxAngle = MAX_ANGLE_EYE_CAM;
		glm::vec3 _position = INITIAL_EYE_POSITION;
	public:
		EyesCam(float ax=0.0f,float ay=0.0f):SimpleAxeCam(ax,ay){}
		void reset(float d,float ax,float ay){
			_fAngleX = ax;
			_fAngleY = ay;
		}
		void setMaxAngle(float m)
		{
			_maxAngle = m;
		}
		void setPosition(const glm::vec3 &p) override
		{
			_position = p;
		}
		void rotateLeft(const float degrees) override{
			float newAngle = _fAngleX+degrees;
			if(newAngle > -_maxAngle && newAngle < _maxAngle)
				_fAngleX = newAngle;
		}
		void rotateTop(const float degrees) override{
			float newAngle = _fAngleY+degrees;
			if(newAngle > -_maxAngle && newAngle < _maxAngle)
				_fAngleY = newAngle;
		}
		void moveFront(const float delta) override{}

		glm::mat4 getMatrixView() const override{
			glm::mat4 view  = glm::rotate(glm::mat4(),glm::radians(_fAngleX),glm::vec3(1.0,0.0,0.0));
			view = glm::rotate(view,glm::radians(_fAngleY),glm::vec3(0.0,1.0,0.0));
			view = glm::translate(view,_position);
			return view;
		}
		~EyesCam(){}
};



/*class TrackballCamera
{
	protected:
		float _fDistance;
		float _fDistance;
		float _fAngleX;
		float _fAngleY;
		float _maxAngle = 90.0f;
		glm::vec3 _position = glm::vec3(0.0f,0.0f,0.0f);
	public:
		TrackballCamera(float d=5.0f,float ax=0.0f,float ay=0.0f):_fDistance(d),SimpleAxeCam(ax,ay){}
		void moveFront(const float delta) override{
			_fDistance -= delta;
		}
		void rotateLeft(const float degrees) override{
			_fAngleX+=degrees;
		}
		void rotateTop(const float degrees) override{
			_fAngleY+=degrees;
		}
		void setPosition(const glm::vec3 &p)
		{
			//_position = p;
		}

		glm::mat4 getMatrixView() const{
			glm::mat4 view = glm::translate(glm::mat4(),glm::vec3(0.0,0.0,-_fDistance));
			view = glm::rotate(view,glm::radians(_fAngleX),glm::vec3(1.0,0.0,0.0));
			view = glm::rotate(view,glm::radians(_fAngleY),glm::vec3(0.0,1.0,0.0));
			return view;
		}
};*/

#endif