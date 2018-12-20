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
        std::unique_ptr<glimac::Image> createImage();
        // Texture initialization with program, samplerPath, matrixLocationPath and the image loaded
        void textureInitialization(GLuint sampler, GLuint matrixLocation, std::unique_ptr<glimac::Image> &i);
        // Config the VAO and VBO of the current object
        void setVAO();
        // Config the Image settings to display it
        void drawImage();
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
        bool mouseOn(const int x, const int y) const;
        inline friend std::ostream &operator<<(std::ostream &os, const Button btn) 
        {
            os << "( " ;
            os << btn.x() << " " << btn.y() << " " ;
            os << ")";
            return os;
        }
        // Calls the drawImage method
        void drawButton();
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
        // Fill the vector _buttons
        void addButton(const Button &b);
        // Returns the button on which the mouse is
        Button* activeButton(const int x, const int y);
        // Calls the drawImage method
        void drawWindow();
};

#endif