#define  _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  

#include <iostream>

//#include "SceneOpenGL.h"
#include "engine_core.h"

#include "FileUtil.h"

using namespace std;

int main(int argc, char** argv){
	FileUtil::startlog("log.txt");
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	/*SceneOpenGL scene("OpenGL33 engine", 960, 600);
	scene.initialiserFenetre();
	scene.initGL();
	scene.bouclePrincipale();*/

	//_crtBreakAlloc = 159; //163,162,159
	//float test[6] = {0.0,25.0,56.56,0.0,560,6.0};
	//FileUtil::arrayToFile("dev_test/arr.txt", test, 0, 3,2, MODE_ADD);
	//printf("charsize=%i", sizeof(char));
	engine_core engine(960,600,"OpenGL 3.3 Engine", 60);
	//engine_core engine(1440,900,"OpenGL 3.3 Engine", 60);
	engine.init();
	engine.mainLoop();
	_CrtDumpMemoryLeaks();
	//system("pause");
	return 0;
}