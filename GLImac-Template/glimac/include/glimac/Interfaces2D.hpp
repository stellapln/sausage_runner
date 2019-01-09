#ifndef _INTERFACES2D_HPP__
#define _INTERFACES2D_HPP__
#pragma once

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
#include <glimac/Except.hpp>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <SDL/SDL_ttf.h>

#include <SDL/SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define COORDINATES_WINDOW 0

using namespace glm;
using namespace glimac;


namespace sausageRunner {
    class Image2D
    {
        /*! \class Image2D
        * \brief
        *	class for 2D Interface Images
        *  	attributes and functions
        */
        private:
            unsigned int _nb_vertices = 6; /*!< Number of vertices: each square has 6 vertices */
            glimac::FilePath _path; /*!< Image path */
            std::string _name;/*!< Image name */
            GLuint _sampler2D; /*!< Image sampler2D for the shader assets */
            GLuint _matrixLocation; /*!< Location used for the image */
            GLuint _texture; /*!< Texture linked to the image */
            GLuint _vao; /*!< Image vao */
            GLuint _vbo; /*!< Image vbo */

        public:
            Image2D(std::string p, std::string name)
                : _path(p), _name(name){};
            ~Image2D()
            {
                glDeleteBuffers(1, &_vbo);
                glDeleteVertexArrays(1, &_vao);
                glDeleteTextures(1, &_texture);
            }
            /*!
             *  \brief Getters
             */
            /*!
             *  \brief Path file getter
             */
            inline glimac::FilePath path() const
            {
                return _path;
            }
            /*!
             *  \brief GLuint sampler2D getter for the Uniform value in shader
             */
            inline GLuint sampler2D() const
            {
                return _sampler2D;
            }
            /*!
             *  \brief Get the location of the used matrix for the texture
             */
            inline GLuint Location() 
            {
                return _matrixLocation;
            }
            /*!
             *  \brief Get the GLuint texture
             */
            inline GLuint texture() const
            {
                return _texture;
            }
            /*!
             *  \brief To get and/or set the texture GLuint
             */
            inline GLuint& texture() 
            {
                return _texture;
            }
            /*!
             *  \brief Get the name of the image
             */
            inline std::string name() const
            {
                return _name;
            }
            /*!
             *  \brief Setters
             */
            /*!
             *  \brief To set the image path
             */
            inline void Path(const glimac::FilePath &p)
            {
                _path = p;
            }
            /*!
             *  \brief Set the sampler 2D GLuint
             */
            inline void Sampler2D(const GLuint &s)
            {
                _sampler2D = s;
            }
            /*!
             *  \brief Set the location of the used matrix
             */
            inline void Location(const GLuint &l)
            {
                _matrixLocation = l;
            }       
            /*!
             *  \brief Set the texture
             */
            inline void Texture(const GLuint &t)
            {
                _texture = t;
            }
            /*!
             *  \brief Functions load image with _path attributes -try catch added around it when called -> exceptions used-
             */
            std::unique_ptr<glimac::Image> createImage();
            /*!
             *  \brief <Texture initialization with program, samplerPath, matrixLocationPath and the image loaded
             */
            void textureInitialization(GLuint sampler, GLuint matrixLocation, std::unique_ptr<glimac::Image> &i);
            /*!
             *  \brief Config the VAO and VBO of the current object
             */
            void setVAO();
            /*!
             *  \brief Config the Image settings to display it 
             */
            void drawImage();
    };

    class Button
    {
        /*! \class Button
        * \brief
        *	Each interface 2D has buttons
        *  	Here are attributes and functions dedicated each button
        */
        private:
            int _x; /*!< Positon x*/
            int _y; /*!< Position y*/
            int _width; /*!< Button Width */
            int _height; /*!< Button Height */
            Image2D* _image; /*!< Image corresponding to the button */
            Image2D* _hover_image; /*!< Image corresponding to the button when hovering */
            bool _is_hover = false; /*!< Indicator of the hover mouse event */
            std::function <int()> _action; /*!< Lambda function to get the active button */

        public:
            Button(Image2D *i, Image2D* hi, std::function <int()> f, int x = 0, int y = 0, int w = 0, int h = 0)
                : _image(i), _hover_image(hi), _action(f), _x(x), _y(y), _width(w), _height(h){};
            ~Button(){};
            /*!
             *  \brief Getters
             */
            /*!
             *  \brief Get the button width
             */
            inline int width() const
            { 
                return _width; 
            }
            /*!
             *  \brief Get the image height
             */
            inline int height() const
            { 
                return _height; 
            }
            /*!
             *  \brief Get the x button position
             */
            inline int x() const
            { 
                return _x; 
            }        
            /*!
             *  \brief Get the y button position 
             */
            inline int y() const
            { 
                return _y; 
            }       
            /*!
             *  \brief Get the image button
             */
            inline Image2D* image() const
            { 
                return _image; 
            }        
            /*!
             *  \brief Get the action/lambda function of the button
             */
            inline std::function <int()> action() const
            { 
                return _action; 
            }
            /*!
             *  \brief Get the hover event as a bool -active or not-
             */
            inline bool isHover() const
            { 
                return _is_hover;
            }
            /*!
             *  \brief Setters 
             */
            /*!
             *  \brief Set the Width
             */
            inline void Width(const int w)
            {
                _width = w;
            }
            /*!
             *  \brief Set the Height
             */
            inline void Height(const int h)
            {
                _height = h;
            }
            /*!
             *  \brief Set the X position
             */
            inline void X(const int x)
            {
                _x = x;
            }
            /*!
             *  \brief Set the Y position
             */
            inline void Y(const int y)
            {
                _y = y;
            }
            /*!
             *  \brief Set the image button
             */
            inline void setImage(Image2D *i)
            {
                _image = i;
            }
            /*!
             *  \brief Set the hover state
             */
            inline void Is_Hover(bool b)
            {
                _is_hover = b;
            }
            /*!
             *  \brief Is the mouse on the button? True or false return
             */
            bool mouseOn(const int x, const int y) const;
            inline friend std::ostream &operator<<(std::ostream &os, const Button btn) 
            {
                os << "( " ;
                os << btn.x() << " " << btn.y() << " " ;
                os << ")";
                return os;
            }
            /*!
             *  \brief Draw each button image and calls the drawImage method
             */
            void drawButton();
    };

    class Window
    {
        /*! \class Window
        * \brief
        *	Each interface2D is a Window
        *  	Here are attributes and functions dedicated each window
        */
        private:
            std::vector <Button> _buttons; /*!< Vector of buttons which are in the window */
            Image2D* _image; /*!< Window image/background */

        public:
            Window(Image2D *i)
                : _image(i){};
            ~Window(){};
            /*!
             *  \brief Getters
             */
            /*!
             *  \brief Get the window buttons
             */
            inline std::vector <Button> buttons()
            {
                return _buttons;
            }
            /*!
             *  \brief Get the window image
             */
            inline Image2D* image() const
            { 
                return _image; 
            }
            /*!
             *  \brief Fill the vector _buttons
             */
            void addButton(const Button &b);
            /*!
             *  \brief Returns the button on which the mouse is
             */
            Button* activeButton(const int x, const int y);
            /*!
             *  \brief Draw the window background image -> calls the drawButton method & drawImage method for the background
             */
            void drawWindow();
    };

    class Score 
    {       
        /*! \class Score
        * \brief
        *	Each player has a score
        *  	Here are attributes and functions dedicated the score during the game/its diplay
        */
        private:
            int _x; /*!< Position x of the score */
            int _y; /*!< Position y of the score */
            int _value;  /*!< Value of the score corresponding to the points of the player */

        public:
            Score(int x = 0, int y = 0)
                : _x(x), _y(y), _value(0){};
            ~Score(){};
            /*!
             *  \brief Getters
             */            
            /*!
             *  \brief Get the x position
             */
            inline int x() const
            { 
                return _x; 
            }        
            /*!
             *  \brief Get the y position
             */
            inline int y() const
            { 
                return _y; 
            }       
            /*!
             *  \brief Get the value
             */
            inline int value() const
            { 
                return _value; 
            }        
            /*!
             *  \brief Set the x position
             */
            inline void X(const int x)
            {
                _x = x;
            }        
            /*!
             *  \brief Set the y position
             */
            inline void Y(const int y)
            {
                _y = y;
            }       
            /*!
             *  \brief Set the value
             */
            inline void Value(const int value)
            {
                _value = value;
            }
            /*!
             *  \brief Manage the score to draw it then
             */
            // void scoreTTF(int points, SDL_Surface* screen, TTF_Font *font);
            /*!
             *  \brief Call the drawImage method to draw the score
             */
            void drawScore();

    };
}

/*

namespace Text {
    class RenderText{
    private:
        SDL_Surface* m_scoreSurface;
        GLuint m_scoreImg;
        SDL_Surface* m_timeSurface;
        GLuint m_timeImg;

        SDL_Surface* m_SP_titleSurface;
        SDL_Surface* m_SP_pointsSurface;
        SDL_Surface* m_SP_timeSurface;
        SDL_Surface* m_SP_pointsScoreSurface;
        SDL_Surface* m_SP_timeScoreSurface;
        SDL_Surface* m_SP_Surface;
        GLuint m_SP_titleImg;
        GLuint m_SP_pointsImg;
        GLuint m_SP_timeImg;
        GLuint m_SP_pointsScoreImg;
        GLuint m_SP_timeScoreImg;

        glm::mat4 m_ProjMatrix;
        glm::mat4 m_MVMatrix;
        glm::mat4 m_NormalMatrix;
        glm::mat4 m_OriginalMatrix;

        std::string m_time;

        TTF_Font* m_font;
        GLuint m_planeVBO;
        GLuint m_planeIBO;
        GLuint m_planeVAO;

        SDLWindowManager* m_windowManager;
        SDL_Surface* m_screen;



    public:
        void initText();

        TTF_Font* loadFont(int size);

        SDL_Surface* createTextTexture(GLuint* textImg, std::string text, SDL_Color color);

        void clean();

        SDL_Surface* createTextTexture(GLuint* textImg, std::string text, SDL_Color color);

        void drawText(SDL_Surface* textSurface, GLuint textImg, float size, float x, float y);

        void drawText(SDL_Surface* textSurface, GLuint textImg, float size, glm::mat4 matrix);

        void createScorePanel(int points);

        void drawScorePanel(int points);

    };
}*/

#endif
