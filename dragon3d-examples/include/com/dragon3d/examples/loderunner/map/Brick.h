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
 * Created:     2014/05/07
 **********************************************************************/


#ifndef Brick_Map_Loderunner_Examples_Dragon3d_Com_H
#define Brick_Map_Loderunner_Examples_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <com/dragon3d/scene/GameObject.h>

BeginPackage5(com, dragon3d, examples, loderunner, map)

Import dragon::lang;
Import com::dragon3d::scene;

class_ Brick extends(GameObject) {
public:
    static const Type* TYPE;
    
public:
    Brick();
    virtual ~Brick();

protected:
    virtual void onInit();
    virtual void onUpdate(Input* input, ReadOnlyTimer* timer);
    virtual void onDestroy();
     
};//Brick

EndPackage5 //(com, dragon3d, examples, loderunner, map)

#endif //Brick_Map_Loderunner_Examples_Dragon3d_Com_H
