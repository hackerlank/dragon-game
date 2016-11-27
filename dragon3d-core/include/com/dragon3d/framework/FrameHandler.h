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
 * Created:     2013/09/17
 **********************************************************************/


#ifndef FrameHandler_Framework_Dragon3d_Com_H
#define FrameHandler_Framework_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/util/ArrayList.h>
#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/util/Timer.h>

#include <com/dragon3d/framework/Scene.h>
#include <com/dragon3d/framework/Output.h>
#include <com/dragon3d/framework/Updater.h>

BeginPackage3(com, dragon3d, framework)

Import dragon::util;
Import dragon::util::logging;
Import com::dragon3d::framework;
Import com::dragon3d::util;

/**
 * Does the work needed in a given frame.
 */
class _DragonExport FrameHandler {
public:
	static Logger* logger;

public:
	FrameHandler();
	FrameHandler(Timer* timer);
	virtual ~FrameHandler();

public:
	virtual void init();

	virtual void updateFrame(Scene* scene);

	virtual void addUpdater(Updater* updater);
	virtual void removeUpdater(Updater* updater);

	virtual void addOutput(Output* output);
	virtual bool removeOutput(Output* output);

	virtual int getTimeoutSeconds();
	virtual void setTimeoutSeconds(int timeoutSeconds);

	virtual Timer* getTimer();
	
protected:
	ArrayList<Updater>* updaters;
	ArrayList<Output>* outputs;
	Timer* timer;

	int timeoutSeconds;
};//FrameHandler

EndPackage3 //(com, dragon3d, framework)

#endif //FrameHandler_Framework_Dragon3d_Com_H
