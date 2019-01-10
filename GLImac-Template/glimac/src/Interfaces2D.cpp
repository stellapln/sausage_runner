#include "glimac/Interfaces2D.hpp"

using namespace sausageRunner;

// Fucntions for transformations matrices (translate, scale)

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


// IMAGE 2D METHODS
std::unique_ptr<glimac::Image> Image2D::createImage()
{
    std::unique_ptr<glimac::Image> image = loadImage(_path);
    if(image == NULL){
        std::string message = std::string(_name) + std::string(" image not loaded correctly (null pointer)");
        throw Except(message,__FILE__,__LINE__);
    }
    return image;
}

void Image2D::textureInitialization(GLuint sampler, GLuint matrixLocation, std::unique_ptr<glimac::Image> &i)
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

void Image2D::setVAO()
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

void Image2D::drawImage()
{
    glBindVertexArray(_vao);
    glBindTexture(GL_TEXTURE_2D,_texture);
    glUniform1i(_sampler2D,0);
    glDrawArrays(GL_TRIANGLES, 0, _nb_vertices);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// BUTTON METHODS
bool Button::mouseOn(const int x, const int y) const
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
void Button::drawButton()
{
    float w = 1.0/float(WINDOW_WIDTH)*float(_width);
    float h = 1.0/float(WINDOW_HEIGHT)*float(_height);

    float tx = (float(_x+_width/2.0)/float(WINDOW_WIDTH)*2.0)-1.0;
    float ty = 1.0-float(_y+_height/2.0)/float(WINDOW_HEIGHT)*2.0;

    if(_is_hover)
    {
        glUniformMatrix3fv(_hover_image->Location(), 1, GL_FALSE, glm::value_ptr(translate(tx,ty)*scale(w,h)));
        _hover_image->drawImage();
        glUniformMatrix3fv(_hover_image->Location(), 1, GL_FALSE, glm::value_ptr(glm::mat3()));

    }
    else
    {  
        glUniformMatrix3fv(_image->Location(), 1, GL_FALSE, glm::value_ptr(translate(tx,ty)*scale(w,h)));
        _image->drawImage();
        glUniformMatrix3fv(_image->Location(), 1, GL_FALSE, glm::value_ptr(glm::mat3()));
    }
}

// WINDOW METHODS
void Window::addButton(const Button &b)
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
        throw Except("Not addable into the window, coordinates not included",__FILE__,__LINE__);
    }                
}
Button* Window::activeButton(const int x, const int y)
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
void Window::drawWindow()
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

Text::Text(const std::string &text, const unsigned int x, const unsigned int y, const unsigned int fontSize) 
: _posX(x), _posY(y), _text(text), _fontSize(fontSize), _textWidth(100), _textHeight(100), _textColor({255, 0, 0})
{

}

void Text::drawText()
{
  TTF_Init();
 
    // Font loading
    TTF_Font* font = TTF_OpenFont("./assets/fonts/arial.ttf", _fontSize);
 
    if(NULL != font)
    { 
        SDL_Surface* text = TTF_RenderText_Blended(font,"coucou", _textColor);
 
        // Free font
        TTF_CloseFont(font);

        // Text dimensions
        _textWidth = text->w;
        _textHeight = text->h;
 
        // Transparency
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
        // Texture handling
        GLuint textTexture;
        glGenTextures( 1, &textTexture );
        glBindTexture( GL_TEXTURE_2D, textTexture ); 
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, 4, _textWidth, _textHeight, 0,
                      GL_RGBA, GL_UNSIGNED_BYTE, text->pixels );
 
        // Free text image
        SDL_FreeSurface(text);
 
        glBindTexture(GL_TEXTURE_2D, textTexture);
 
        // Draw the quad with texture containing text
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        //glColor3f(1.0, 1.0, 1.0);
            /*glTexCoord2d(0, 1); glVertex2f( _posX, WINDOW_HEIGHT - _posY + _textHeight);
            glTexCoord2d(0, 0); glVertex2f( _posX, WINDOW_HEIGHT - _posY);
            glTexCoord2d(1, 0); glVertex2f( _posX + _textWidth, WINDOW_HEIGHT - _posY);
            glTexCoord2d(1, 1); glVertex2f( _posX + _textWidth, WINDOW_HEIGHT - _posY + _textHeight);*/
            glTexCoord2d(0, 1); glVertex2f( 0.0, 1.0);
            glTexCoord2d(0, 0); glVertex2f( 0.0, 0.0);
            glTexCoord2d(1, 0); glVertex2f( 1.0,0.0);
            glTexCoord2d(1, 1); glVertex2f( 1.0, 1.0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
 
        glDeleteTextures(1, &textTexture);
    }
 
    TTF_Quit();
}


void Text::checkHovering(const int x, const int y)
{ 
    if(x > _posX && x < _posX + _textWidth && y < _posY && y > _posY - _textHeight)
    {
        _textColor = {214, 27, 20};
    }
    else 
    {
        _textColor = {0, 0, 0};
    }
 
}

bool Text::checkClick(const int x, const int y) const
{ 
    if(x > _posX && x < _posX + _textWidth && y < _posY && y > _posY - _textHeight)
    {
        return true;
    }
   
    return false; 
}

void Text::updateText(const std::string &newText)
{
  _text = newText;
}