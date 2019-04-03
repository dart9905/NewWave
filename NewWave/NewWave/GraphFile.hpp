//
//  GraphFile.hpp
//  NewWave
//
//  Created by macbook on 18/03/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#ifndef GraphFile_hpp
#define GraphFile_hpp

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GLUT/GLUT.h>
#include <stdio.h>

#define GL_CLAMP_TO_EDGE 0x812F
const float PI          = 3.141592653;   ///< Pi - pizdec
const float GLOBsize    = 32.f;    ///< size texture
const float GLOBsize2   = 16.f;    ///< size texture / 2
const int window_width  = 1500;  ///< size window width
const int window_height = 1200; ///< size window height


/*!
 \brief a skin type that stores textures on all faces of a cube
 this class stores the textures, which will later be superimposed on the volume, you can do it through []
 */
class SkinBox_t
{
    GLuint error_;      ///<erroneous empty texture
    GLuint top_;        ///<top face texture
    GLuint bottom_;     ///<bottom face texture
    GLuint left_;       ///<left face texture
    GLuint back_;       ///<back face texture
    GLuint right_;      ///<righg face texture
    GLuint front_;      ///<front face texture
public:
    ~SkinBox_t() {
        glDeleteShader(error_);
        glDeleteShader(top_);
        glDeleteShader(bottom_);
        glDeleteShader(left_);
        glDeleteShader(back_);
        glDeleteShader(right_);
        glDeleteShader(front_);
    }
    
    GLuint& operator [] (int i) {
        switch (i) {
            case 0:
                return top_;
                break;
            case 1:
                return bottom_;
                break;
            case 2:
                return left_;
                break;
            case 3:
                return front_;
                break;
            case 4:
                return right_;
                break;
            case 5:
                return back_;
                break;
            default:
                return error_;
                break;
        }
    }
};

//*
class mouse_t {
public:
    
    mouse_t () {}
    ~mouse_t() {}
    
    sf::Vector2i posnew_;
    sf::Vector2i posold_;
    
    float angleX_ = 0;
    float angleY_ = 0;
    float x_ = 0;
    float y_ = 0;
    float z_ = 100;
    
    float dx_ = 0;
    float dy_ = 0;
    float dz_ = 0;
    float speed_ = 5;
    
    float R_  = 10;
    float RR_ = R_ * R_;
    
    
    bool checkbut_ = false;
    
};
//*/



/*!
 \brief loads the specified texture from the file specified in the parameter
 \param name string with the address to the loaded texture
 \return returns a texture of type GLuint
 */
GLuint LoadTexture(sf::String name);

/*!
 \brief a function to initialize an array of (different) textures
 \param arrayBox a pointer to the texture array
 \return returns 0
 \warning the function does not control the size of the array, you should manually update the function.
 */
int MakeTextures(SkinBox_t* arrayBox);

/*!
 \brief draws a picture box on the texture of the box using the dimensions specified
 \param box variable to store the texture block.
 \param x_size size x
 \param y_size size y
 \param z_size size z
 \return returns void
 */
void createRectangle(SkinBox_t& box,float x_size, float y_size, float z_size);

/*!
 \brief draws a picture box on the texture of the box using the dimensions specified
 \param box variable to store the texture block.
 \param size size
 \return returns void
 */
void createBox(SkinBox_t& box, float size);


/*!
 \brief draw home in 3d
 \param arrayBox array texture house
 \return void
 */
void drawhouse(SkinBox_t* arrayBox);

#endif /* GraphFile_hpp */
