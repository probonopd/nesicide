#include "nesemulatorrenderer.h"

CGLTextureManager staticGLTextureManager;

CNESEmulatorRenderer::CNESEmulatorRenderer(QWidget *parent, char *imgData)
    : QGLWidget(parent)
{
    textureID = glTextureManager.getNewTextureID();
    imageData = imgData;
    scrollX = 0;
    scrollY = 0;

}

CNESEmulatorRenderer::~CNESEmulatorRenderer()
{
    glTextureManager.freeTextureID(textureID);
}

void CNESEmulatorRenderer::initializeGL()
{
    zoom = 100;
    // Enable flat shading
    glShadeModel(GL_FLAT);

    // Black background color
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);

    // Depth buffer setup
    glClearDepth(1.0f);

    // Use the fastest rendering possible
    glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

    // Disable Blending
    glDisable(GL_BLEND);

    // Enable textures
    glEnable(GL_TEXTURE_2D);

    resizeGL(this->width(), this->height());

    // Create the texture we will be rendering onto
    glBindTexture(GL_TEXTURE_2D, textureID);

    // We want it to be RGBRGB(etc) formatted
    glPixelStorei(GL_UNPACK_ALIGNMENT, textureID);

    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    // Load the actual texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

}

void CNESEmulatorRenderer::updateGL()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    repaint();
}

void CNESEmulatorRenderer::setBGColor(QColor clr)
{
    glClearColor((float)clr.red() / 255.0f, (float)clr.green() / 255.0f, (float)clr.blue() / 255.0f, 0.5f);
}

void CNESEmulatorRenderer::resizeGL(int width, int height)
{
    // Zoom the width and height based on our view zoom. If zoom is 200% and our width is 100
    // then the renderer's width will be 50.
    int newWidth = (int)((float)width / ((float)zoom / 100.0f));
    int newHeight = (int)((float)height / ((float)zoom / 100.0f));

    // Width cannot be 0
    if (width == 0)
        width = 1;

    // Initialize our viewpoint using the actual size so 1 point should = 1 pixel.
    glViewport(0, 0, width, height);

    // We are using a projection matrix.
    glMatrixMode(GL_PROJECTION);

    // Load the default settings for the matrix.
    glLoadIdentity();

    // Set orthogonal mode (since we are doing 2D rendering) with the proper aspect ratio.
    glOrtho(0.0f, newWidth, newHeight, 0.0f, -1.0f, 1.0f);

    // Select and reset the ModelView matrix.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Slightly offset the view to ensure proper pixel alignment
    //glTranslatef(0.375,0.375,0);
}


void CNESEmulatorRenderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture (GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);
        glTexCoord2f (0.0, 0.0);
        glVertex3f(000.0f - scrollX, 000.0f - scrollY, 0.0f);
        glTexCoord2f (1.0, 0.0);
        glVertex3f(256.0f - scrollX, 000.0f - scrollY, 0.0f);
        glTexCoord2f (1.0, 1.0);
        glVertex3f(256.0f - scrollX, 256.0f - scrollY, 0.0f);
        glTexCoord2f (0.0, 1.0);
        glVertex3f(000.0f - scrollX, 256.0f - scrollY, 0.0f);
    glEnd();
}

void CNESEmulatorRenderer::changeZoom(int newZoom)
{
    zoom = newZoom;
    resizeGL(this->width(), this->height());
    this->repaint();
}