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
 * Created:     2013/10/04
 **********************************************************************/


#ifndef Vector2_Math_Util_Dragon3d_Com_H
#define Vector2_Math_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/lang/Array.h>

BeginPackage4(com, dragon3d, util, math)

Import dragon::lang;
Import com::dragon3d::util::math;

class _DragonExport Vector2 extends(Object) {
public:
    static const Type* TYPE;
    
public:
    static const Vector2 ZERO; //Shorthand for writing Vector2(0, 0)
    static const Vector2 ONE; //Shorthand for writing Vector2(1, 1)

public:
    Vector2();
    Vector2(float x, float y);

public:
    const float* getData() const;
    const Array<float> toFloatArray() const;

public:
    float x;
    float y;
};//Vector2

EndPackage4 //(com, dragon3d, util, math)

#endif //Vector2_Math_Util_Dragon3d_Com_H
