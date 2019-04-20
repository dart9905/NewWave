//
//  GraphFile.cpp
//  NewWave
//
//  Created by macbook on 18/03/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include "GraphFile.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GLUT/GLUT.h>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"


mouse_t::mouse_t (float angleX, float angleY, float z): angleX_(angleX), angleY_(angleY), z_(z)
{
    
    if (angleX_ > 180) {
        angleX_ -= 360;
    }
    
    if (angleX_ < -180) {
        angleX_ += 360;
    }
    
    if (angleY_ > 89) {
        angleY_ = 89;
    }
    
    if (angleY_ < -89) {
        angleY_ = -89;
    }
    
    
    x_=  R_ * sin(angleX_ / 180 * PI) * cos(angleY_ / 180 * PI);
    
    y_= -R_ * sin(angleY_ / 180 * PI);
    
    float D = RR_ - x_ * x_ - y_ * y_;
    if (D < 0) {
        D = 0;
    }
    
    if ((angleX_ < 90) && (angleX_ > -90)) {
        z_ = sqrt(D);
    } else {
        z_ = -sqrt(D);
    }
}

GLuint LoadTexture(sf::String name)
{
    sf::Image image;
    if (!image.loadFromFile(name))
        return EXIT_FAILURE;
    
    image.flipVertically();
    
    GLuint texture=0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    return texture;
}

int MakeTextures(SkinBox_t* arrayBox)
{
    char num;
    for (int i = 0; i < 6; i++)
    {
        num = '1'+i;
        arrayBox [0] [i] = LoadTexture(resourcePath() + "resources/box_test/" + num + ".jpg");
    }
    
    /*
     arrayBox [SKY] [0] = LoadTexture(resourcePath() + "resources/skybox/skybox_top.bmp");
     arrayBox [SKY] [1] = LoadTexture(resourcePath() + "resources/skybox/skybox_front.bmp");
     arrayBox [SKY]  [2] = LoadTexture(resourcePath() + "resources/skybox/skybox_back.bmp");
     arrayBox [SKY]  [3] = LoadTexture(resourcePath() + "resources/skybox/skybox_left.bmp");
     arrayBox [SKY]  [4] = LoadTexture(resourcePath() + "resources/skybox/skybox_right.bmp");
     arrayBox [SKY]  [5] = LoadTexture(resourcePath() + "resources/skybox/skybox_bottom.bmp");
     //*/
    
    /*
    for (int i = 0; i < 6; i++) {
        arrayBox [SKY]  [i] = LoadTextureSKYBOX(resourcePath() + "resources/skybox/ckybox.png", i);
    }
    //*/
    
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 2000.f);
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return 0;
    //*/
}


void createRectangle(SkinBox_t& box,float x_size, float y_size, float z_size)
{
    x_size = x_size / 2;
    y_size = y_size / 2;
    z_size = z_size / 2;
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.1f);
    glBindTexture(GL_TEXTURE_2D, box [0]);
    glBegin(GL_QUADS);
    //top
    
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0);     glVertex3f(-x_size, y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size, y_size,  z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size, y_size,  z_size);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, box [2]);
    glBegin(GL_QUADS);
    //front/* z+
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size,  y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size,  y_size, -z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [4]);
    glBegin(GL_QUADS);
    //back x-
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0);     glVertex3f( x_size, -y_size, z_size);
    glTexCoord2f(1, 0);     glVertex3f(-x_size, -y_size, z_size);
    glTexCoord2f(1, 1);     glVertex3f(-x_size,  y_size, z_size);
    glTexCoord2f(0, 1);     glVertex3f( x_size,  y_size, z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [1]);
    glBegin(GL_QUADS);
    //left x-
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size,  z_size);
    glTexCoord2f(1, 0);     glVertex3f(-x_size, -y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f(-x_size,  y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size,  y_size,  z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [3]);
    glBegin(GL_QUADS);
    //right x+
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size,  z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size,  y_size,  z_size);
    glTexCoord2f(0, 1);     glVertex3f( x_size,  y_size, -z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [5]);
    glBegin(GL_QUADS);
    //bottom
    
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size,  z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size,  z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size, -y_size, -z_size);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    //glFlush();
    
}


void createBox(SkinBox_t& box,float size)
{
    createRectangle(box, size, size, size);
}


void drawhouse(SkinBox_t* arrayBox)
{
    
    glTranslatef(0, 0, 5 * GLOBsize2);
    createRectangle(arrayBox [0], GLOBsize * 5, GLOBsize * 5, GLOBsize / 5);
    glTranslatef(0, 0, -5 * GLOBsize2);
    
    glTranslatef(0, 0, -5 * GLOBsize2);
    createRectangle(arrayBox [0], GLOBsize * 5, GLOBsize * 5, GLOBsize / 5);
    glTranslatef(0, 0, 5 * GLOBsize2);
    
    
    glTranslatef(5 * GLOBsize2, 0, 0);
    createRectangle(arrayBox [0], GLOBsize / 5, GLOBsize * 5, GLOBsize * 5);
    glTranslatef(-5 * GLOBsize2, 0, 0);
    
    
    glTranslatef(-5 * GLOBsize2, 0, 0);
    createRectangle(arrayBox [0], GLOBsize / 5, GLOBsize * 5, GLOBsize * 5);
    glTranslatef(5 * GLOBsize2, 0, 0);
    
    
    glTranslatef(0, -5 * GLOBsize2, 0);
    createRectangle(arrayBox [0], GLOBsize * 5, GLOBsize / 5, GLOBsize * 5);
    glTranslatef(0, 5 * GLOBsize2, 0);
    
    
    glTranslatef(0, 5 * GLOBsize2, 0);
    glRotated(45, 1, 0, 0);
    glTranslatef(0, 0.7 * 5 * GLOBsize2, 0);
    createRectangle(arrayBox [0], GLOBsize * 5, GLOBsize / 5, GLOBsize * 5);
    glTranslatef(0, - 0.7 * 5 * GLOBsize2, 0);
    glRotated(-90, 1, 0, 0);
    glTranslatef(0, 0.7 * 5 * GLOBsize2, 0);
    createRectangle(arrayBox [0], GLOBsize * 5, GLOBsize / 5, GLOBsize * 5);
    glTranslatef(0, -0.7 * 5 * GLOBsize2, 0);
    glRotated(45, 1, 0, 0);
    glTranslatef(0, -5 * GLOBsize2, 0);
    return;
}


void drawhouse(SkinBox_t* arrayBox, int x, int y, int z, int angle)
{
    glTranslatef(5 * GLOBsize2 * x, 5 * GLOBsize2 * y, 5 * GLOBsize2 * z);
    glRotated(angle, 0, 1, 0);
    drawhouse(arrayBox);
    glRotated(-angle, 0, 1, 0);
    glTranslatef(-5 * GLOBsize2 * x, -5 * GLOBsize2 * y, -5 * GLOBsize2 * z);
}


void linepole()
{
    
    
    GLfloat arrayline0 [11] [2] [3];
    for (int i = 0; i < 11; i++)
    {
        arrayline0 [i] [0] [0] = i * GLOBsize * 5 -GLOBsize * 25;
        arrayline0 [i] [0] [1] = 0;
        arrayline0 [i] [0] [2] = -GLOBsize * 25;
        arrayline0 [i] [1] [0] = i * GLOBsize * 5 -GLOBsize * 25;
        arrayline0 [i] [1] [1] = 0;
        arrayline0 [i] [1] [2] = GLOBsize * 25;
    }
    
    GLfloat arrayline1 [11] [2] [3];
    for (int i = 0; i < 11; i++)
    {
        arrayline1 [i] [0] [0] = -GLOBsize * 25;
        arrayline1 [i] [0] [1] = 0;
        arrayline1 [i] [0] [2] = i * GLOBsize * 5 -GLOBsize * 25;
        arrayline1 [i] [1] [0] = GLOBsize * 25;
        arrayline1 [i] [1] [1] = 0;
        arrayline1 [i] [1] [2] = i * GLOBsize * 5 -GLOBsize * 25;
    }
    
    GLfloat arrayline [] = {0,0,0};
    
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3d(1, 1, 1);
    for (int i = 0; i < 11; i++)
    {
        if (i == 5)
        {
            glVertex3fv(arrayline0 [i] [0]);
            glVertex3fv(arrayline);
            glVertex3fv(arrayline1 [i] [0]);
            glVertex3fv(arrayline);
            i++;
        }
        glVertex3fv(arrayline0 [i] [0]);
        glVertex3fv(arrayline0 [i] [1]);
        glVertex3fv(arrayline1 [i] [0]);
        glVertex3fv(arrayline1 [i] [1]);
    }
    glEnd();
    return;
}


void xyz()
{
    
    
    GLfloat arrayline [3] [2] [3];
    arrayline [0] [0] [0] = 0;
    arrayline [0] [0] [1] = 0;
    arrayline [0] [0] [2] = 0;
    arrayline [0] [1] [0] = 30 * GLOBsize;
    arrayline [0] [1] [1] = 0;
    arrayline [0] [1] [2] = 0;
    
    arrayline [1] [0] [0] = 0;
    arrayline [1] [0] [1] = 0;
    arrayline [1] [0] [2] = 0;
    arrayline [1] [1] [0] = 0;
    arrayline [1] [1] [1] = 30 * GLOBsize;
    arrayline [1] [1] [2] = 0;
    
    arrayline [2] [0] [0] = 0;
    arrayline [2] [0] [1] = 0;
    arrayline [2] [0] [2] = 0;
    arrayline [2] [1] [0] = 0;
    arrayline [2] [1] [1] = 0;
    arrayline [2] [1] [2] = 30 * GLOBsize;
    
    
    glLineWidth(3);
    glBegin(GL_LINES);
    for (int i = 0; i < 3; i++)
    {
        switch (i)
        {
            case 0:
                glColor3d(1, 0, 0);
                break;
            case 1:
                glColor3d(0, 1, 0);
                break;
            case 2:
                glColor3d(0, 0, 1);
                break;
                
            default:
                break;
        }
        glVertex3fv(arrayline [i] [0]);
        glVertex3fv(arrayline [i] [1]);
    }
    glEnd();
    return;
}
