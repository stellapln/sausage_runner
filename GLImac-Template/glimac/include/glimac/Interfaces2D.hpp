#ifndef _INTERFACES2D_HPP__
#define _INTERFACES2D_HPP__

#include <iostream>
#include <numeric> 
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <GL/glew.h>
#include <glimac/Image.hpp>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/SDLWindowManager.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define COORDINATES_WINDOW 0

using namespace glm;
using namespace glimac;

// Template matrices for transformations (rotation, translate, scale)
glm::mat3 rotate(float angle)
{
    float a = radians(angle);
    return mat3 (vec3(cos(a), sin(a), 0), vec3(-sin(a),cos(a),0), vec3(0,0,1));
};

glm::mat3 translate(float x, float y)
{
    return mat3 (vec3(1, 0, 0), vec3(0, 1, 0), vec3(x, y, 1));
};

glm::mat3 scale(float x, float y)
{
    return mat3 (vec3(x, 0, 0), vec3(0, y, 0), vec3(0, 0, 1));
};

struct Vertex2DUV {
    glm::vec2 position;
    glm::vec2 texture;
    public:
        Vertex2DUV(glm::vec2 p, glm::vec2 t)
            : position(p),texture(t){};
        Vertex2DUV(){};
};

class Image2D {
    private:
        unsigned int _nb_vertices = 6;
        glimac::FilePath _path;
        std::string _name;
        GLuint _sampler2D;
        GLuint _matrixLocation;
        GLuint _texture;
        GLuint _vao;
        GLuint _vbo;

    public:
        Image2D(glimac::FilePath p, std::string name)
            : _path(p), _name(name){};

        ~Image2D()
        {
            glDeleteBuffers(1, &_vbo);
            glDeleteVertexArrays(1, &_vao);
            glDeleteTextures(1, &_texture);
        }

        // Getters
        inline glimac::FilePath path() const
        {
            return _path;
        }
        inline GLuint sampler2D() const
        {
            return _sampler2D;
        }
        inline GLuint Location() 
        {
            return _matrixLocation;
        }
        inline GLuint texture() const
        {
            return _texture;
        }
        inline GLuint& texture() 
        {
            return _texture;
        }
        inline std::string name() const
        {
            return _name;
        }
        // Setters
        inline void Path(const glimac::FilePath &p)
        {
            _path = p;
        }
        inline void Sampler2D(const GLuint &s)
        {
            _sampler2D = s;
        }
        inline void Location(const GLuint &l)
        {
            _matrixLocation = l;
        }
        inline void Texture(const GLuint &t)
        {
            _texture = t;
        }

        // Functions load image with _path attribute
        // add try catch around it when called
        std::unique_ptr<glimac::Image> createImage()
        {
            std::unique_ptr<glimac::Image> image = loadImage(_path);
            if(image == NULL){
                std::string message = std::string(_name) + std::string(" image not loaded correctly (null pointer)");
                throw message;
            }
            return image;
        }
        // Texture initialization with program, samplerPath, matrixLocationPath and the image loaded
        void textureInitialization(GLuint sampler, GLuint matrixLocation, std::unique_ptr<glimac::Image> &i)
        {
            _sampler2D = sampler;
            _matrixLocation = matrixLocation;

            glGenTextures(1, &_texture);
            // Bind
            glBindTexture(GL_TEXTURE_2D, _texture);
            glTexImage2D(GL_TEXTURE_2D,
                    0,
                    GL_RGBA,
                    i->getWidth(),
                    i->getHeight(),
                    0,
                    GL_RGBA,
                    GL_FLOAT,
                    i->getPixels());

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Debind
            glBindTexture(GL_TEXTURE_2D, 0);

            setVAO();
        }

        void setVAO()
        {
            // Création d'un seul VBO
            glGenBuffers(1, &_vbo);
            // variable vbo contient identifiant d'1 vbo

            // Binding d'1 VBO sur la cible GL_ARRAY_BUFFER:
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            // On peut à présent modifier le VBO en passant par la cible GL_ARRAY_BUFFER
            
            Vertex2DUV vertices[] = {
                Vertex2DUV(glm::vec2(-1.f, 1.f),glm::vec2(0.f, 0.f)),
                Vertex2DUV(glm::vec2(-1.f, -1.f),glm::vec2(0.f, 1.f)),
                Vertex2DUV(glm::vec2(1.f, -1.f),glm::vec2(1.f, 1.f)),

                Vertex2DUV(glm::vec2(1.f, -1.f),glm::vec2(1.f, 1.f)),
                Vertex2DUV(glm::vec2(1.f, 1.f),glm::vec2(1.f, 0.f)),
                Vertex2DUV(glm::vec2(-1.f, 1.f),glm::vec2(0.f, 0.f))

            };
            // Get the number of elements in vertices[]
            unsigned int nb_vertices = sizeof(vertices)/sizeof(vertices[0]);

            // envoi des données
            glBufferData(GL_ARRAY_BUFFER, nb_vertices * sizeof(Vertex2DUV), vertices, GL_STATIC_DRAW);

            // debindage de la cible
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glGenVertexArrays(1, &_vao);
            // binding
            glBindVertexArray(_vao);
            // utilisation de l'attribut 0 du tableau
            const GLuint VERTEX_ATTR_POSITION = 0;
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

            // attribut couleur
            const GLuint VERTEX_ATTR_TEXTURE = 1;
            glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

            // rebinding d'1 VBO sur la cible GL_ARRAY_BUFFER:
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            // On peut à présent modifier le VBO en passant par la cible GL_ARRAY_BUFFER
            // indication des sommets pour lire les info associées à chaque sommet
            // définit quelle partie du vbo sert à quoi
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)(offsetof(Vertex2DUV, position)));

            glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)(offsetof(Vertex2DUV, texture)));
            // redebindage de la cible
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // debindage du VAO
            glBindVertexArray(0);
        }

        void drawImage()
        {
            glBindVertexArray(_vao);
            glBindTexture(GL_TEXTURE_2D,_texture);
            glUniform1i(_sampler2D,0);
            glDrawArrays(GL_TRIANGLES, 0, _nb_vertices);
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

};

class Button
{
    private:
        int _x;
        int _y;
        int _width;
        int _height;
        Image2D* _image;
        Image2D* _hover_image;
        bool _is_hover = false;
        std::function <int()> _action; // Lambda function to get the active button

    public:
        Button(Image2D *i, Image2D* hi, std::function <int()> f, int x = 0, int y = 0, int w = 0, int h = 0)
            : _image(i), _hover_image(hi), _action(f), _x(x), _y(y), _width(w), _height(h){};
        ~Button(){};
        // Getters
        inline int width() const
        { 
            return _width; 
        }
        inline int height() const
        { 
            return _height; 
        }
        inline int x() const
        { 
            return _x; 
        }
        inline int y() const
        { 
            return _y; 
        }
        inline Image2D* image() const
        { 
            return _image; 
        }
        inline std::function <int()> action() const
        { 
            return _action; 
        }
        inline bool isHover() const
        { 
            return _is_hover;
        }
        // Setters
        inline void Width(const int w)
        {
            _width = w;
        }
        inline void Height(const int h)
        {
            _height = h;
        }
        inline void X(const int x)
        {
            _x = x;
        }
        inline void Y(const int y)
        {
            _y = y;
        }
        inline void setImage(Image2D *i)
        {
            _image = i;
        }
        inline void Is_Hover(bool b)
        {
            _is_hover = b;
        }
        // Is the mouse on the button? True or false
        inline bool mouseOn(const int x, const int y) const
        {
            if( x >= _x && x <= _x + _width)
            {
                if(y >= _y && y <= _y + _height)
                {
                    return true;
                }
            }
            return false;
        }
        inline friend std::ostream &operator<<(std::ostream &os, const Button btn) 
        {
            os << "( " ;
            os << btn.x() << " " << btn.y() << " " ;
            os << ")";
            return os;
        }
        inline void drawButton()
        {
            float w = 1.0/float(WINDOW_WIDTH)*float(_width);
            float h = 1.0/float(WINDOW_HEIGHT)*float(_height);

            float tx = (float(_x+_width/2.0)/float(WINDOW_WIDTH)*2.0)-1.0;
            float ty = 1.0-float(_y+_height/2.0)/float(WINDOW_HEIGHT)*2.0;

            if(_is_hover)
            {
                glUniformMatrix3fv(_hover_image->Location(), 1, GL_FALSE, glm::value_ptr(translate(tx,ty)*scale(w,h)));
                _hover_image->drawImage();
            }
            else
            {  
                glUniformMatrix3fv(_image->Location(), 1, GL_FALSE, glm::value_ptr(translate(tx,ty)*scale(w,h)));
                _image->drawImage();
            }
        }
};

class Window
{
    private:
        std::vector <Button> _buttons;
        Image2D* _image;

    public:
        Window(Image2D *i)
            : _image(i){};
        ~Window(){};
        // Getter
        inline std::vector <Button> buttons()
        {
            return _buttons;
        }
        inline Image2D* image() const
        { 
            return _image; 
        }
        inline const void addButton(const Button &b)
        {
            if(b.x() >= COORDINATES_WINDOW && b.y() >= COORDINATES_WINDOW)
            {
                if(b.x() <= WINDOW_WIDTH && b.y() <= WINDOW_HEIGHT)
                {
                    _buttons.push_back(b);
                }
            }
            else
            {
                throw "Not addable into the window, coordinates not included";
            }                
        }
        // Returns the button on which the mouse is
        Button* activeButton(const int x, const int y)
        {
            Button * tmp = nullptr;
            for(unsigned int i = 0 ; i < _buttons.size() ; i++)
            {
                if(_buttons.at(i).mouseOn(x,y) == true)
                {
                    tmp = &(_buttons.at(i));
                }
                else
                {
                    _buttons.at(i).Is_Hover(false);   
                }
            }
            return tmp;
        }
        void drawWindow()
        {
            glUniformMatrix3fv(_image->Location(), 1, GL_FALSE, glm::value_ptr(glm::mat3()));
            _image->drawImage();
            std::function<void(Button b)> drawButton = [](Button b)
            {   
                // std::cout << b.image()->name() << std::endl;
                b.drawButton();
                b.Is_Hover(false);
            };
            for_each(_buttons.begin(), _buttons.end(), drawButton);
        }
};

#endif