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
 * Created:     2013/09/15
 **********************************************************************/

#include <map>

#include <dragon/lang/String.h>
#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/scene/model/geometry/Box.h>
#include <com/dragon3d/scene/camera/Camera.h>
#include <com/dragon3d/scene/SimpleScene.h>
#include <com/dragon3d/util/math/Mathf.h>

#include <com/dragon3d/examples/helloworld/HelloWorld.h>

Import dragon::lang;
Import dragon::lang::gc;
Import dragon::util::logging;

Import com::dragon3d::scene;
Import com::dragon3d::examples::helloworld;
Import com::dragon3d::scene::model::geometry;
Import com::dragon3d::scene::camera;
Import com::dragon3d::util::math;

static Logger* logger = Logger::getLogger("com::dragon3d::examples::helloworld::HelloWorld", INFO);


HelloWorld::HelloWorld() {

}

HelloWorld::~HelloWorld() {

}

void HelloWorld::onInit() {
    logger->info("init");

    Ref<Scene> scene = this->getCurrentScene();
    Ref<GameObject> root = scene->getRoot();
    
    myBox = new GameObject("myBox");
    Box* box = new Box();
    myBox->addComponent(box);
    
    myBox->getTransform()->setPosition(Vector3(0, 0, 0));
    //myBox->getTransform()->setScale(Vector3(2, 2, 2));
    
    //myBox->getTransform()->setLocalPosition(Vector3(0, 0, 0));
    
    child = new GameObject("child");
    Box* box2 = new Box();
    child->addComponent(box2);
    
    child->getTransform()->setParent(myBox->getTransform());
    
    //child->getTransform()->setPosition(Vector3(0, 0, 10));
    child->getTransform()->setLocalPosition(Vector3(4, 4, 4));
    //child->getTransform()->setScale(Vector3(0.5, 0.5, 0.5));
    //child->transform->setLocalPosition(Vector3(1, 2, 0));
    
    
    mainCamera = new GameObject("MainCamera");
    Camera* camera = new Camera();
    mainCamera->addComponent(camera);
    
    //camera->rect = Rect(0.1, 0.1, 0.8, 0.8);
    camera->getTransform()->setPosition(Vector3(0, 5, -10));
    //camera->getTransform()->rotate(0, 180, 0);
    camera->getTransform()->find("abc/bbb/ccc");
    
    Vector3 pos = myBox->getTransform()->getPosition();
    logger->info("myBox init pos: %f %f %f", pos.x, pos.y, pos.z);
    
    camera->lookAt(pos, Vector3::UP);
    
    Vector3 right = mainCamera->getTransform()->getRight();
    logger->info("camera right pos: %f %f %f", right.x, right.y, right.z);
 
    Vector3 up = mainCamera->getTransform()->getUp();
    logger->info("camera up pos: %f %f %f", up.x, up.y, up.z);
    
    Vector3 forward = mainCamera->getTransform()->getForward();
    logger->info("camera forward pos: %f %f %f", forward.x, forward.y, forward.z);
    
    root->addChild(myBox);
    root->addChild(mainCamera);
    
    map<int, int> theMap;
    map<int, int>::iterator it = theMap.begin();
    it++;
}

//static double abc = 0.1;

void HelloWorld::onUpdate(Scene* scene, ReadOnlyTimer* timer) {
    //mainCamera->getTransform()->rotate(0, timer->getDeltaTime() * 40, 0, Self);

    //Vector3 pos = myBox->getTransform()->getPosition();
    //logger->info("myBox pre pos: %f %f %f", pos.x, pos.y, pos.z);
    
    
    
    //myBox->getTransform()->translate(Vector3::LEFT.multiply(timer->getDeltaTime() * 5), World);
    //myBox->getTransform()->translate(Vector3::LEFT.multiply(timer->getDeltaTime() * 5), World);
    
    myBox->getTransform()->rotate(0, timer->getDeltaTime() * 40, 0, World);
    //myBox->getTransform()->rotate(0, timer->getDeltaTime() * 40, 0, Self);
    
    //child->getTransform()->rotate(0, timer->getDeltaTime() * 40, 0, Self);
    //child->getTransform()->translate(Vector3::RIGHT.multiply(timer->getDeltaTime() * 5), World);
    
    //float deltaTime = timer->getDeltaTime();
    //logger->debug("delta time: %f", deltaTime);
    
    //myBox->getTransform()->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 0.5), World);
    //myBox->getTransform()->rotate(0, timer->getDeltaTime() * 40, 0, Self);
    
    //myBox->transform->rotate(0, timer->getDeltaTime() * 200, 0, Transform::Space::Self);
    
    //child->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::World);
    //child->transform->translate(Vector3::FORWARD.multiply(timer->getDeltaTime() * 5), Transform::Space::Self);
    
    //child->getTransform()->rotate(0, timer->getDeltaTime() * 40, 0, World);
    //child->transform->rotate(0, timer->getDeltaTime() * 200, 0, Transform::Space::Self);
    
    //abc += timer->getDeltaTime() * 2;
    //myBox->transform->setEulerAngles(Vector3(0, abc, 0));
    
        
    //Vector3 pos = myBox->getTransform()->getPosition();
    //Vector3 localPos = myBox->getTransform()->getLocalPosition();
    
    //logger->info("myBox pos:        %f %f %f", pos.x, pos.y, pos.z);
    //logger->info("myBox local pos : %f %f %f", localPos.x, localPos.y, localPos.z);
    
    /*
    Camera* camera = (Camera*)mainCamera->getFirstComponent(Camera::TYPE);

    Vector3 p = child->getTransform()->getPosition();
    logger->info("myBox local pos : %f %f %f", p.x, p.y, p.z);
    camera->lookAt(p, Vector3::UP);
    */
    
    //mainCamera->getTransform()->lookAt(child->getTransform());
    
    //logger->info("tps: %f fps: %f curTime: %f", timer->getDeltaTime(), timer->getFrameRate(), timer->getTimeInSeconds());
}

void HelloWorld::onDestroy() {
    logger->info("destroy");
}