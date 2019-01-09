#ifndef _LIB_IMPORT_RENDER_IMAC_LSM
#define _LIB_IMPORT_RENDER_IMAC_LSM
#pragma once

#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <queue>

#define DIRECTIONNAL 0
#define POINT 1
#define MAX_LIGHT 50


namespace sausageRunner {
	class Light
	{
		private:
			glm::vec3 _pos;
			float _intensity;
			int _type;
		public:
			Light(glm::vec3 p, float i, int t):_pos(p), _intensity(i), _type(t){}
			void sendUniform(GLuint progGLId, int i){

			    GLuint uPos = glGetUniformLocation(progGLId,("secondaryLights["+std::to_string(i)+"].pos").c_str());
			    GLuint uIntensity = glGetUniformLocation(progGLId,("secondaryLights["+std::to_string(i)+"].intensity").c_str());
			    GLuint uType = glGetUniformLocation(progGLId,("secondaryLights["+std::to_string(i)+"].type").c_str());

		        glUniform3fv(uPos,1,glm::value_ptr(_pos));
		        glUniform1f(uIntensity, _intensity);
		        glUniform1i(uType,_type);
			}
	};

	/*! \class Render
		* \brief
		*	Contain all Matrix and values for the link between the light,
		*	the shaders and the MVMatrix
		*
		*/
	class Render {

		private:

		    // Uniform variable

		    GLuint _uMVPMatrix;
		    GLuint _uMVMatrix;
		    GLuint _uNormalMatrix;

		    GLuint _uKd;
		    GLuint _uKs;
		    GLuint _uShininess;
		    GLuint _uLightPos_vs;
		    GLuint _uLightIntensity;
		    GLuint _uNumberOfSecondaryLights;

			// Light parameters

			glm::vec3 _Kd = glm::vec3(0.5,0.5,0.5);
			glm::vec3 _Ks = glm::vec3(0.5,0.5,0.5);
			float _Shininess = 0.5;
			glm::vec4 _LightPos_vs = glm::vec4(2.0,2.0,2.0,0.0);
			glm::vec3 _LightIntensity = glm::vec3(2.0,2.0,2.0);

			std::vector<Light *> _secondaryLights;

		public:

		    glimac::Program _prog;

		    // Definition of Matrix

			glm::mat4 _projMatrix = glm::perspective(glm::radians(70.f),8.0f/6.0f,0.1f,100.f);

			Render(std::string vertexShader, std::string fragmentShader){

				_prog = glimac::loadProgram(vertexShader, fragmentShader);

				// Set uniform variables

			    _uMVPMatrix = glGetUniformLocation(_prog.getGLId(),"uMVPMatrix");
			    _uMVMatrix = glGetUniformLocation(_prog.getGLId(),"uMVMatrix");
			    _uNormalMatrix = glGetUniformLocation(_prog.getGLId(),"uNormalMatrix");

			    _uKd = glGetUniformLocation(_prog.getGLId(),"uKd");
			    _uKs = glGetUniformLocation(_prog.getGLId(),"uKs");
			    _uShininess = glGetUniformLocation(_prog.getGLId(),"uShininess");
			    _uLightPos_vs = glGetUniformLocation(_prog.getGLId(),"uLightPos_vs");
			    _uLightIntensity = glGetUniformLocation(_prog.getGLId(),"uLightIntensity");

			    _uNumberOfSecondaryLights = glGetUniformLocation(_prog.getGLId(),"numberOfSecondaryLights");

			    _prog.use();
			}
			void reset() const {
	        	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	        }
	        void addLight(Light &l)
	        {
	        	if(_secondaryLights.size() < MAX_LIGHT)
	        		_secondaryLights.push_back(&l);
	        }
	        void removeLight()
	        {
	        	//_secondaryLights.pop_front();
	        }
	        void sendLight(glm::mat4 viewMatrix) const {
		        glUniform3fv(_uKd,1,glm::value_ptr(_Kd));
		        glUniform3fv(_uKs,1,glm::value_ptr(_Ks));
		        glUniform1f(_uShininess,_Shininess);
		        glUniform3fv(_uLightPos_vs,1,glm::value_ptr(viewMatrix*_LightPos_vs));
		        glUniform3fv(_uLightIntensity,1,glm::value_ptr(_LightIntensity));

		        glUniform1i(_uNumberOfSecondaryLights,_secondaryLights.size());

		        for(int i = 0;i < _secondaryLights.size();i++)
		        {
		        	_secondaryLights[i]->sendUniform(_prog.getGLId(),i);
		        }

			}
	        void sendMatrix(glm::mat4 MVMatrix) const {
		    	glUniformMatrix4fv(_uMVPMatrix,1,GL_FALSE,glm::value_ptr(_projMatrix*MVMatrix));
		    	glUniformMatrix4fv(_uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
		    	glUniformMatrix4fv(_uNormalMatrix,1,GL_FALSE,glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
			}
			void use()
			{
				_prog.use();
			}
	};
}
#endif