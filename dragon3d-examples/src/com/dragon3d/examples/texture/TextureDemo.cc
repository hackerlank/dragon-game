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
 * Created:     2014/03/15
 **********************************************************************/

#include <dragon/lang/gc/Reference.h>
#include <com/dragon3d/scene/model/geometry/Box.h>
#include <com/dragon3d/scene/camera/Camera.h>
#include <com/dragon3d/scene/SimpleScene.h>
#include <com/dragon3d/util/math/Mathf.h>

#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/examples/texture/TextureDemo.h>

Import dragon::lang::gc;
Import com::dragon3d::examples::texture;
Import dragon::util::logging;

Import com::dragon3d::scene;
Import com::dragon3d::scene::model::geometry;
Import com::dragon3d::scene::camera;
Import com::dragon3d::util::math;

const Type* TextureDemo::TYPE = TypeOf<TextureDemo>();
static Logger* logger = Logger::getLogger(TextureDemo::TYPE, ERROR);

TextureDemo::TextureDemo() {

}

TextureDemo::~TextureDemo() {

}

void TextureDemo::onInit() {
    logger->info("init");

    Scene* scene = this->getCurrentScene();
    Ref<GameObject> root = scene->getRoot();
    
    myBox = new GameObject();
    Box* box = new Box();
    
    Material* material = new Material();
    material->setMainColor(Color::BLACK);
    material->setMainTexture(new Texture("textures/Wood03.tga"));
    box->setMaterial(material);
    
    myBox->addComponent(box);
    
    myBox->getTransform()->setPosition(Vector3(0, 0, 1));
    myBox->getTransform()->setLocalPosition(Vector3(0, 0, 0));
    
    child = new GameObject();
    Box* box2 = new Box();
    child->addComponent(box2);
    
    child->getTransform()->setPosition(Vector3(0, 0, 10));
    child->getTransform()->setLocalPosition(Vector3(0, 2, 0));
    //child->transform->setLocalPosition(Vector3(1, 2, 0));
    child->getTransform()->setParent(myBox->getTransform());
    
    mainCamera = new GameObject();
    Camera* camera = new Camera();
    mainCamera->addComponent(camera);
    
    camera->resize(320, 480);
    //camera->rect = Rect(0.1, 0.1, 0.8, 0.8);
    camera->getTransform()->setPosition(Vector3(0, 1, -5));

    camera->getTransform()->find("abc/bbb/ccc");

    root->addChild(myBox);
    root->addChild(child);
    root->addChild(mainCamera);
    
    SafeRelease(scene);
}

//static double abc = 0.1;

void TextureDemo::onUpdate(Scene* scene, ReadOnlyTimer* timer) {
    //mainCamera->transform->rotate(0, timer->getDeltaTime() * 40, 0, World);

    //myBox->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), World);
    //myBox->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::Self);
    
    myBox->getTransform()->rotate(0, timer->getDeltaTime() * 40, 0, World);
    //myBox->transform->rotate(0, timer->getDeltaTime() * 200, 0, Transform::Space::Self);
    
    //child->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::World);
    //child->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::Self);
    
    //child->transform->rotate(0, timer->getDeltaTime() * 40, 0, Transform::Space::World);
    //child->transform->rotate(0, timer->getDeltaTime() * 200, 0, Transform::Space::Self);
    
    //abc += timer->getDeltaTime() * 2;
    //myBox->transform->setEulerAngles(Vector3(0, abc, 0));
    
    mainCamera->getTransform()->lookAt(child->getTransform());
    
    logger->debug("tps: %f fps: %f curTime: %f", timer->getDeltaTime(), timer->getFrameRate(), timer->getTimeInSeconds());
}

void TextureDemo::onDestroy() {
    logger->info("destroy");
}
