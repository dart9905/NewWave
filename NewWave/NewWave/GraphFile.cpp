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

int MakeTextures(SkinBox_t* arrayBox) {
    char num;
    for (int i = 0; i < 6; i++) {
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
    glTexCoord2f(0, 0);     glVertex3f(-x_size, y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size, y_size,  z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size, y_size,  z_size);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, box [2]);
    glBegin(GL_QUADS);
    //front/* z+
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size,  y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size,  y_size, -z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [4]);
    glBegin(GL_QUADS);
    //back x-
    glTexCoord2f(0, 0);     glVertex3f( x_size, -y_size, z_size);
    glTexCoord2f(1, 0);     glVertex3f(-x_size, -y_size, z_size);
    glTexCoord2f(1, 1);     glVertex3f(-x_size,  y_size, z_size);
    glTexCoord2f(0, 1);     glVertex3f( x_size,  y_size, z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [1]);
    glBegin(GL_QUADS);
    //left x-
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size,  z_size);
    glTexCoord2f(1, 0);     glVertex3f(-x_size, -y_size, -z_size);
    glTexCoord2f(1, 1);     glVertex3f(-x_size,  y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size,  y_size,  z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [3]);
    glBegin(GL_QUADS);
    //right x+
    glTexCoord2f(0, 0);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size,  z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size,  y_size,  z_size);
    glTexCoord2f(0, 1);     glVertex3f( x_size,  y_size, -z_size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, box [5]);
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    //bottom
    glTexCoord2f(0, 0);     glVertex3f(-x_size, -y_size,  z_size);
    glTexCoord2f(1, 0);     glVertex3f( x_size, -y_size,  z_size);
    glTexCoord2f(1, 1);     glVertex3f( x_size, -y_size, -z_size);
    glTexCoord2f(0, 1);     glVertex3f(-x_size, -y_size, -z_size);
    glEnd();
    glDisable(GL_ALPHA_TEST);
    
}


void createBox(SkinBox_t& box,float size)
{
    createRectangle(box, size, size, size);
}


void drawhouse(SkinBox_t* arrayBox) {
    
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
