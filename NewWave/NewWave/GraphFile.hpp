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
#include <math.h>

#define GL_CLAMP_TO_EDGE 0x812F

const float PI          = 3.141592653;   ///< Pi - pizdec
const float GLOBsize    = 8.f;    ///< size texture
const float GLOBsize2   = 4.f;    ///< size texture / 2
const int window_width  = 2560;  ///< size window width
const int window_height = 1800; ///< size window height


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
    ~SkinBox_t()
    {
        glDeleteShader(error_);
        glDeleteShader(top_);
        glDeleteShader(bottom_);
        glDeleteShader(left_);
        glDeleteShader(back_);
        glDeleteShader(right_);
        glDeleteShader(front_);
    }
    
    GLuint& operator [] (int i)
    {
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

/*!
 \brief the mouse class is needed to store the master data coming from the mouse during operation.
 */
class mouse_t
{
public:
    
    mouse_t () {}
    mouse_t (float angleX, float angleY, float z);
    ~mouse_t() {}
    
    sf::Vector2i posnew_;       ///<position the mouse slider in the window
    sf::Vector2i posold_;       ///old location of the mouse slider in the window
    
    float angleX_ = 0;          ///<the offset between the old and new coordinates of the mouse slider by x
    float angleY_ = 0;          //<the offset between the old and new coordinates of the mouse slider by y
    float x_ = 0;               ///<the coordinates of the camera x
    float y_ = 0;               ///<the coordinates of the camera y
    float z_ = 200;             ///<the coordinates of the camera z
    
    float dx_ = 0;              ///<camera speed x
    float dy_ = 0;              ///<camera speed y
    float dz_ = 0;              ///<camera speed z
    float speed_ = 10;          ///<camera speed
    
    float RR_ = x_ * x_ + z_ * z_ + y_ * y_;///<the square of the size of the radius of the distance between the origin and the point of the camera
    float R_  = sqrt(RR_);      ///<the size of the radius of the distance between the origin and the point of the camera
    
    
    bool checkbut_ = false;     ///<flag clicking on the mouse button
    
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

/*!
 \brief draw a house in 3D at x y z coordinates
 \param arrayBox array texture house
 \param x first coordinate
 \param y second coordinate
 \param z third coordinate
 \return void
 */
void drawhouse(SkinBox_t* arrayBox, int x, int y, int z, int angle);

/*!
 \brief draw the x y z axes which have the corresponding colors red, green, blue
 \return void
 */
void linepole();


void xyz();

#endif /* GraphFile_hpp */
