#ifndef _LIB_IMPORT_RENDER_IMAC_LSM
#define _LIB_IMPORT_RENDER_IMAC_LSM
#pragma once

#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <deque>
#include <iostream>

#define MAX_LIGHT 50
#define UNIFORM_KD_VALUE 0.5
#define UNIFORM_KS_VALUE 0.5
#define UNIFORM_SHININESS_VALUE 0.5
#define GLOBAL_LIGHT_DRIECTION glm::vec4(2.0,2.0,0.0,0.0)
#define GLOBAL_LIGHT_INTENSITY glm::vec3(0.8,0.8,0.8)


namespace sausageRunner {

	/*! \class Light
		* \brief
		*	Describe lights
		*
		*/
	class Light
	{
		private:
			glm::vec3 _pos;
			glm::vec3 _intensity;
			int _type;
		public:
			Light(glm::vec3 p, glm::vec3 i, int t):_pos(p), _intensity(i), _type(t){}
			void sendUniform(GLuint progGLId, int i) const;
			~Light(){}
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
			glm::vec3 _Kd = glm::vec3(UNIFORM_KD_VALUE,UNIFORM_KD_VALUE,UNIFORM_KD_VALUE);
			glm::vec3 _Ks = glm::vec3(UNIFORM_KS_VALUE,UNIFORM_KS_VALUE,UNIFORM_KS_VALUE);
			float _Shininess = UNIFORM_SHININESS_VALUE;
			glm::vec4 _LightPos_vs = GLOBAL_LIGHT_DRIECTION;
			glm::vec3 _LightIntensity = GLOBAL_LIGHT_INTENSITY;

			std::deque<Light> _secondaryLights; 

		public:

		    glimac::Program _prog;

		    // Definition of Matrix

			glm::mat4 _projMatrix = glm::perspective(glm::radians(70.f),8.0f/6.0f,0.1f,100.f);

			Render(std::string vertexShader, std::string fragmentShader);

			void reset() const {
	        	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	        }
	        void sendLight(glm::mat4 viewMatrix) const;
	        void sendMatrix(glm::mat4 MVMatrix) const;
			void use() const
			{
				_prog.use();
			}
			void addLight(Light *l)
			{
				_secondaryLights.push_back(*l);
			}
	        void removeLight()
	        {
	        	_secondaryLights.pop_front();
	        }
	        ~Render(){}
	};
}
#endif