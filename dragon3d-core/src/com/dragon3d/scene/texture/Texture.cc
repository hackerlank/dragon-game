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
 * Created:     2014/04/18
 **********************************************************************/

#include <stdlib.h>
#include <string.h>

#include <dragon/lang/gc/Reference.h>
#include <dragon/io/FileInputStream.h>
#include <dragon/util/logging/Logger.h>
#include <dragonx/image/io/ImageIO.h>
#include <com/dragon3d/scene/texture/Texture.h>
#include <com/dragon3d/util/assets/Resource.h>
#include <com/dragon3d/util/assets/AssetsManager.h>
 
Import dragon::io;
Import dragon::lang::gc;
Import dragon::util::logging;
Import dragonx::image::io;
Import com::dragon3d::util::assets;
Import com::dragon3d::scene::texture;

static Logger* logger = Logger::getLogger("com::dragon3d::scene::texture::Texture", INFO);

AtomicInteger* Texture::sequence = new AtomicInteger(0);

int Texture::GetNextTextureID() {
    return sequence->incrementAndGet();
}

Texture::Texture(Resource* res) :id(GetNextTextureID())
    ,nativeData(NULL), image(null) {
   this->load(res);
}

Texture::Texture(const String& resPath) 
    :id(GetNextTextureID())
    ,nativeData(NULL), image(null) {
    Ref<Resource> res = AssetsManager::getInstance()->getResource(resPath);
    this->load(res);
}

Texture::~Texture(void){
    SafeRelease(this->image);
    SafeFree(this->nativeData);
}

void Texture::load(Resource* res) {
    Ref<InputStream> is = res->getInputStream();
    Ref<String> type = res->getType();
    BufferedImage* image = ImageIO::read(is.raw(), type.raw());

    if (image != null) {
        Ref<ColorModel> cm = image->getColorModel();
        int bit = cm->getBitCount();
        this->channels = bit/8;
        SafeReplace(this->image, image);
    }
}

unsigned int Texture::getID() {
    return this->id;
}

int Texture::getWidth() {
    return this->image->getWidth();
}

int Texture::getHeight() {
    return this->image->getHeight();
}

Array<byte> Texture::getData() {
    return this->image->getData();
}

void Texture::setNativeData(void* data) {
    SafeFree(this->nativeData);
    this->nativeData = data;
}

void* Texture::getNativeData() {
    return this->nativeData;
}