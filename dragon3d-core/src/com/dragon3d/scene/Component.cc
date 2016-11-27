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


#include <com/dragon3d/scene/Component.h>
#include <com/dragon3d/scene/GameObject.h>
 
Import com::dragon3d::scene;

const Type* Component::TYPE = TypeOf<Component>();

Component::Component() 
    :gameObject(null), active(true) {

}

Component::~Component() {
    SafeRelease(this->gameObject);
}

bool Component::isTypeOf(const Type* type) {
    if (Component::TYPE->equals(type)) {
        return true;
    }

    return false;
}

Object* Component::clone() const {
    Component* newComp = (Component*)Object::clone();
    newComp->gameObject = null;
    return newComp;
}

// propertys
GameObject* Component::getGameObject() {
    return (GameObject*)this->gameObject->retain();
}

void Component::setGameObject(GameObject* gameObject) {
    SafeReplace(this->gameObject, gameObject);
}


// ------------------------------------
void Component::init() {
    
}

void Component::update(Input* input, ReadOnlyTimer* timer) {

}

void Component::destroy() {

}

String* Component::getName() {
    if (this->gameObject != null) {
        return this->gameObject->getName();
    }

    return null;
}

Transform* Component::getTransform() {
    if (this->gameObject != null) {
        return this->gameObject->getTransform();
    }

    return null;
}

bool Component::isActived() {
    return this->active;
}