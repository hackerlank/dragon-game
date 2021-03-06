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
 * Created:     2014/04/23
 **********************************************************************/

#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/util/HashMap.h>
#include <com/dragon3d/output/graphics/shader/glsl/GLSLShader.h>

Import dragon::util;
Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::output::graphics::shader::glsl;

const Type* GLSLShader::TYPE = TypeOf<GLSLShader>();
static Logger* logger = Logger::getLogger(GLSLShader::TYPE, ERROR);


GLSLShader::GLSLShader() 
    :programObject(0), 
    name(null) {
    this->nameMap = new HashMap<String, String>();
}

GLSLShader::~GLSLShader() {
    SafeRelease(this->name);
    SafeRelease(this->nameMap);
}
    

void GLSLShader::init() {
    //this->nameMap->put("tex", new String("TEXCOORD"));
}

void GLSLShader::prepare() {
    this->nameMap->put("uv", new String("TEXCOORD0"));
}

String* GLSLShader::queryNameMapping(const char* name) {
    String* find = this->nameMap->get(name);

    if (find != null) {
        return find;
    }

    return new String(name);
}

void GLSLShader::registerNameMapping(const String& name, String* mappingName) {
    this->nameMap->put(name, mappingName);
}

int GLSLShader::getID() {
    return this->programObject;
}

String* GLSLShader::getName() {
    return (String*)this->name->retain();
}

void GLSLShader::setName(const String& name) {
    SafeRelease(this->name);
    this->name = new String(name);
}
