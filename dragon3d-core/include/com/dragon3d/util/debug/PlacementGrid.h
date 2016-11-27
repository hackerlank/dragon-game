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
 * Created:     2013/10/06
 **********************************************************************/


#ifndef PlacementGrid_Debug_Util_Dragon3d_Com_H
#define PlacementGrid_Debug_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>

#include <com/dragon3d/framework/Scene.h>
#include <com/dragon3d/scene/camera/Camera.h>
#include <com/dragon3d/output/graphics/GraphicsRenderer.h>
#include <com/dragon3d/output/graphics/Renderable.h>

BeginPackage4(com, dragon3d, util, debug)

Import dragon::lang;
Import com::dragon3d::output;
Import com::dragon3d::framework;
Import com::dragon3d::scene::camera;
Import com::dragon3d::output::graphics;

class _DragonExport PlacementGrid extends(Object) 
    implements1(Renderable) {
public:
    PlacementGrid();
    virtual ~PlacementGrid();

public:
    virtual Bounds* getBounds();
    virtual void renderUnto(GraphicsRenderer* gr, Scene* scene, Camera* camera); 

protected:
    int size;
    Color color;
    Bounds* bounds;
};//PlacementGrid

EndPackage4 //(com, dragon3d, util, debug)

#endif //PlacementGrid_Debug_Util_Dragon3d_Com_H
