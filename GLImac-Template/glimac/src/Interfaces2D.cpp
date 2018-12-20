#include "glimac/Interfaces2D.hpp"


// Fucntions for transformations matrices (rotation, translate, scale)
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


// IMAGE 2D METHODS
std::unique_ptr<glimac::Image> Image2D::createImage()
{
    std::unique_ptr<glimac::Image> image = loadImage(_path);
    if(image == NULL){
        std::string message = std::string(_name) + std::string(" image not loaded correctly (null pointer)");
        throw message;
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
    }
    else
    {  
        glUniformMatrix3fv(_image->Location(), 1, GL_FALSE, glm::value_ptr(translate(tx,ty)*scale(w,h)));
        _image->drawImage();
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
        throw "Not addable into the window, coordinates not included";
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

void Score::scoreToTab(int points){
    std::vector<int> tab(5);
    /* unité */
    if(points >= 0){
        tab[0] = points;
        /* décimal */
        if(points >= 10){
            tab[1] = points/10;
            tab[0] = points-tab[1]*10;
            /* centimal */
            if(points >= 100){
                tab[2] = points/100;
                tab[1] = tab[1]-tab[2]*10;
                /* millimal */
                if(points >= 1000){
                    tab[3] = points/1000;
                    tab[2] = tab[2]-tab[3]*10;
                    /* dix-millimal */
                    if(points >= 10000){
                        tab[4] = points/10000;
                        tab[3] = tab[3]-tab[4]*10;
                    }
                    else{
                        tab[4] =0;
                    }
                }
                else{
                    tab[3] = 0;
                    tab[4] = 0;
                }
            }
            else{
                tab[2] = 0;
                tab[3] = 0;
                tab[4] = 0;
            }
        }
        else{
            tab[1] = 0;
            tab[2] = 0;
            tab[3] = 0;
            tab[4] = 0;
        }
    }
    std::cout << points << std::endl;
}