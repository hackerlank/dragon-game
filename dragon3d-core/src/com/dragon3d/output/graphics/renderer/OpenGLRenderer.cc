/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/09/28
 **********************************************************************/

#include <com/dragon3d/output/graphics/renderer/OpenGLRenderer.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>
#include <com/dragon3d/util/math/Mathf.h>

Import dragon::util::logging;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::renderer;
Import com::dragon3d::util::math;

OpenGLRenderer::OpenGLRenderer(GraphicsDevice* graphicsDevice) {
    this->graphicsDevice = graphicsDevice;
}

OpenGLRenderer::~OpenGLRenderer() {

}

GraphicsDevice* OpenGLRenderer::getDisplay() {
    return this->graphicsDevice;
}

void OpenGLRendererNativeInit(GraphicsDevice* graphicsDevice);

void OpenGLRenderer::init() {
	logger->info("init");

    OpenGLRendererNativeInit(this->graphicsDevice);

    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading

    Color c("#474747");
    //Color c("#FF0000");
    glClearColor(c.r, c.g, c.b, 0.5f);                  // Black Background

    glClearDepth(1.0f);                                 // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations

    glPointSize(2);
    glLineWidth(2);

    // The following commands should induce OpenGL to create round points and   
    // antialias points and lines.  (This is implementation dependent unfortunately).  
    //RGBA mode antialias need cooperate with blend function.  
    glEnable(GL_POINT_SMOOTH);  
    glEnable(GL_LINE_SMOOTH);  
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points  
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines  
    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRenderer::clearBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
    glLoadIdentity();
}

//native void OpenGLRenderer::flushBuffer();

void OpenGLRenderer::setViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

void OpenGLRenderer::drawSample() {
	logger->debug("draw sample shape.");

	glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.85f, 0.35f);

    glBegin(GL_TRIANGLES);
    
    {

        glVertex3f(  0.0,  0.6, 0.0);
        glVertex3f( -0.2, -0.3, 0.0);
        glVertex3f(  0.2, -0.3 ,0.0);

    }

    glEnd();
}


GLuint OpenGLRendererInitTexture(Texture* texture) {
    GLuint textureID;

    glGenTextures(1, &textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    int textureType = GL_RGB;
    
    if(texture->channels == 4)
        textureType = GL_RGBA;
    
    //gluBuild2DMipmaps(GL_TEXTURE_2D, texture->channels, texture->width, 
    //    texture->height, textureType, GL_UNSIGNED_BYTE, texture->data);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);                         
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    return textureID;
}

void OpenGLRendererSetupCamera(Camera* camera) {
    // setup camera
    if (camera != null) {
        com::dragon3d::util::math::Rect viewport = camera->getViewPortRect();
        glViewport(viewport.x, viewport.y, viewport.width, viewport.height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); 
        
        Matrix4x4 projMatrix = camera->getModelViewProjectionMatrix();
        glMultMatrixf(projMatrix.getData());
    }
}


void OpenGLRenderer::drawLine(const Vector3& startV, const Vector3& endV, const Color& color, Camera* camera) {
    // setup camera
    OpenGLRendererSetupCamera(camera);

    // set color
    glColor3f(color.r, color.g, color.b);

    glMatrixMode(GL_MODELVIEW); 

    glBegin(GL_LINES);
        glVertex3f(startV.x, startV.y, startV.z);
        glVertex3f(endV.x, endV.y, endV.z);
    glEnd();
}

void OpenGLRendererDrawMeshData(Mesh* mesh) {
    // draw mesh
    if (mesh->hasUV() || mesh->hasUV2()) {
        glEnable(GL_TEXTURE_2D);
    }

    List<Vector3>* vertices = mesh->getVertices();
    List<Vector2>* uvs = mesh->getUVs();

    int count = mesh->getSubMeshCount();

    for(int i=0; i<count; i++) {
        Array<int> indices = mesh->getIndices(i);

        const int* data = indices.raw();
        int vCount = indices.length();

        glBegin(GL_TRIANGLES);

            for (int i=0; i< vCount; i++) {
                int pos = data[i];

                //set texCoord
                if (mesh->hasUV()) {
                    Vector2* uv = uvs->get(pos);
                    glTexCoord2f(uv->x, uv->y);
                }

                //set vertext
                if (mesh->hasVertices()) {
                    Vector3* v = vertices->get(pos);
                    glVertex3f(v->x, v->y, v->z);
                }
            }

        glEnd();
    }

    SafeRelease(uvs);
    SafeRelease(vertices);

    if (mesh->hasUV() || mesh->hasUV2()) {
        glDisable(GL_TEXTURE_2D);
    }
}

void OpenGLRenderer::drawMesh(Mesh* mesh, const Matrix4x4& matrix, Material* material, Camera* camera, int submeshIndex) {
    // setup camera
    OpenGLRendererSetupCamera(camera);

    // setup material
    if (material != null) {
        // setup color
        Color c = material->getMainColor();
        glColor3f(c.r, c.g, c.b);

        // setup texture
        Texture* mainTexture = material->getMainTexture();

        if (mainTexture != null) {
            GLuint textureID = OpenGLRendererInitTexture(mainTexture);
            glBindTexture(GL_TEXTURE_2D, textureID);
        }
    }

    // transform mesh
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
    glScalef(-1.0f, 1.0f, 1.0f); //change to left handle coordinate system
    glMultMatrixf((float *)matrix.m);

    // draw mesh
    OpenGLRendererDrawMeshData(mesh);
}

