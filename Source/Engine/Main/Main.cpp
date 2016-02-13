////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////

///////////////////////
// MY CLASS INCLUDES //  
///////////////////////
#include "EngineStd.h"

#include "Engine.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "opengl32.lib")

#if defined(_M_IX86)
	#if defined(_DEBUG)
      #pragma comment(lib, "glew32sd.lib")
	#else

	#endif
#elif defined(_M_X64)
	#if defined(_DEBUG)

	#else

	#endif
#else
	#error Preprocessor defines can't figure out which Bullet library to use.
#endif


int main( int argc, char *argv[] )
   {
   EngineApp();

   g_pApp->m_EngineOptions.Init();

   g_pApp->Run();

   return 0;
   }