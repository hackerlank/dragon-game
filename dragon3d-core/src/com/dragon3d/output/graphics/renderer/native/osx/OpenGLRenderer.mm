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

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <Cocoa/Cocoa.h>

#include <com/dragon3d/output/graphics/renderer/OpenGLRenderer.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>

#include <dragon/util/logging/Logger.h>

Import dragon::util::logging;
Import com::dragon3d::output::graphics;
Import com::dragon3d::output::graphics::renderer;

static Logger* logger = Logger::getLogger("com::dragon3d::output::graphics::renderer::OpenGLRenderer#osx", INFO);

// mine thread handle
typedef struct {
    NSAutoreleasePool *pool;
    NSWindow* window;
    NSOpenGLView* dgView;
} NativeData;

void OpenGLRendererNativeInit(GraphicsDevice* graphicsDevice) {
    logger->debug("native init");
}

void OpenGLRenderer::flushBuffer() {
    logger->debug("flush buffer");

    NativeData* data = (NativeData*)this->graphicsDevice->getNativeData();
    NSOpenGLView* glView = (NSOpenGLView*)data->dgView;
    [[glView openGLContext] flushBuffer];
}

// include commons
#include "../../OpenGLRenderer.cc"


