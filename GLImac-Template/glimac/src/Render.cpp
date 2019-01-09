#include <glimac/Render.hpp>
#include <iostream>

using namespace sausageRunner;


void Light::sendUniform(GLuint progGLId, int i) const {

    GLuint uPos = glGetUniformLocation(progGLId,("secondaryLights["+std::to_string(i)+"].pos").c_str());
    GLuint uIntensity = glGetUniformLocation(progGLId,("secondaryLights["+std::to_string(i)+"].intensity").c_str());
    GLuint uType = glGetUniformLocation(progGLId,("secondaryLights["+std::to_string(i)+"].type").c_str());

    std::cout << _pos << std::endl;
    glUniform3fv(uPos,1,glm::value_ptr(_pos));
    glUniform3fv(uPos,1,glm::value_ptr(_intensity));
    glUniform1i(uType,_type);
}

Render::Render(std::string vertexShader, std::string fragmentShader){

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


void Render::sendLight(glm::mat4 viewMatrix) const {
    glUniform3fv(_uKd,1,glm::value_ptr(_Kd));
    glUniform3fv(_uKs,1,glm::value_ptr(_Ks));
    glUniform1f(_uShininess,_Shininess);
    glUniform3fv(_uLightPos_vs,1,glm::value_ptr(viewMatrix*_LightPos_vs));
    glUniform3fv(_uLightIntensity,1,glm::value_ptr(_LightIntensity));

    glUniform1i(_uNumberOfSecondaryLights,_secondaryLights.size());

    for(int i = 0;i < _secondaryLights.size();i++)
    {
    	_secondaryLights[i].sendUniform(_prog.getGLId(),i);
    }

}


void Render::sendMatrix(glm::mat4 MVMatrix) const {
	glUniformMatrix4fv(_uMVPMatrix,1,GL_FALSE,glm::value_ptr(_projMatrix*MVMatrix));
	glUniformMatrix4fv(_uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
	glUniformMatrix4fv(_uNormalMatrix,1,GL_FALSE,glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
}