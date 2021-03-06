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
 * Created:     2014/05/01
 **********************************************************************/


#include <dragon/util/ArrayList.h>

#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/output/graphics/renderqueue/RenderQueue.h>

Import dragon::util;

Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::output::graphics::renderqueue;

const Type* RenderQueue::TYPE = TypeOf<RenderQueue>();
static Logger* logger = Logger::getLogger(RenderQueue::TYPE, ERROR);

RenderQueue::RenderQueue() {
    this->queue = new ArrayList<Renderable>();
}

RenderQueue::~RenderQueue() {
    SafeRelease(this->queue);
}

void RenderQueue::clear() {
    this->queue->clear();
}

void RenderQueue::add(Renderable* renderable) {
    this->queue->add(renderable);
}

void RenderQueue::addAll(List<Renderable>* renderables) {
    this->queue->addAll(renderables);
}

Iterator<Renderable>* RenderQueue::iterator() {
    return this->queue->iterator();
}

void RenderQueue::sort() {

}

int RenderQueue::size() {
    return this->queue->size();
}
