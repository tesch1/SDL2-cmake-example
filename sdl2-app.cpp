#include <iostream>
#include <SDL.h>

#ifdef __IPHONEOS__
// if we're compiling for iOS (iPhone/iPad)
# include <SDL_opengles.h> // we want to use OpenGL ES
#else
# include <SDL_opengl.h> // otherwise we want to use OpenGL
#endif

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char * argv[])
{
  // Initialize SDL with video
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
  {
    std::cerr << "Error initializing SDL\n";
    return 1;
  }
  atexit(SDL_Quit);

  // Create an SDL window
  SDL_Window* window = SDL_CreateWindow("Test",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        640, 480, SDL_WINDOW_OPENGL);
	
  // if failed to create a window
  if(!window)
  {
    // we'll print an error message and exit
    std::cerr << "Error failed to create window!\n";
    return 1;
  }
	
  // Create an OpenGL context (so we can use OpenGL functions)
  SDL_GLContext context = SDL_GL_CreateContext(window);
	
  // if we failed to create a context
  if(!context)
  {
    // we'll print out an error message and exit
    std::cerr << "Error failed to create a context\n!";
    return 2;
  }
	
  SDL_Event event;	 // used to store any events from the OS
  bool running = true; // used to determine if we're running the game
	
  glClearColor(1, 0, 0, 1);
  while(running)
  {
    // poll for events from SDL
    while(SDL_PollEvent(&event))
    {
      // determine if the user still wants to have the window open
      // (this basically checks if the user has pressed 'X')
      running = event.type != SDL_QUIT;
    }
		
    glClear(GL_COLOR_BUFFER_BIT);
		
    // Swap OpenGL buffers
    SDL_GL_SwapWindow(window);
  }
	
	
  // Destroy the context
  SDL_GL_DeleteContext(context);
	
  // Destroy the window
  SDL_DestroyWindow(window);
	
  // And quit SDL
  SDL_Quit();
	
  return 0;
}
