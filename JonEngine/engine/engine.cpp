// engine.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "engine.h"
#include <stdlib.h>
#include <iostream>
#include "engine_global.h"

// This is an example of an exported variable
ENGINE_API int nengine=0;
GLFWwindow* glWindow;

// This is the constructor of a class that has been exported.
CEngine::CEngine()
{
    loaded = false;
    gEngine = new CEngineGlobal();
    return;
}

void CEngine::Load(int width, int height, const char* name) {
    printf("Engine loaded. \n");
    loaded = true;

    //must be run last
    gEngine->Load(width, height, name);


}

void CEngine::UnLoad() {
    printf("Engine unloaded. \n");
    loaded = false;
}

bool CEngine::IsLoaded() {
    return loaded;
}

