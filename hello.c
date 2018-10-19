/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx/c99/bgfx.h>
#include <stdio.h>
#include "logo.h"

#define GLFW_EXPOSE_NATIVE_GLX
#define GLFW_EXPOSE_NATIVE_X11

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

//#include <SDL2/SDL.h>
//#include <SDL2/SDL_syswm.h>

extern bool entry_process_events(uint32_t* _width, uint32_t* _height, uint32_t* _debug, uint32_t* _reset);

uint16_t uint16_max(uint16_t _a, uint16_t _b)
{
  return _a < _b ? _b : _a;
}

void onFatal(bgfx_callback_interface_t* _this, const char* _filePath, uint16_t _line, bgfx_fatal_t _code, const char* _str) {
  printf("on fatal error\n");
}

int main(int32_t _argc, char** _argv) {
  uint32_t width  = 1280;
  uint32_t height = 720;
  uint32_t debug  = BGFX_DEBUG_TEXT;
  uint32_t reset  = BGFX_RESET_VSYNC;
  (void)_argc;
  (void)_argv;

  bgfx_init_t init;
  bgfx_callback_vtbl_t vtbl;
  vtbl.fatal = onFatal;
  bgfx_callback_interface_t callback;
  callback.vtbl = &vtbl;

  init.callback = &callback;

  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit()) return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  bgfx_platform_data_t pd;
  pd.ndt          = glfwGetX11Display();
  pd.nwh          = (void*)(uintptr_t)glfwGetX11Window(window);
  pd.context      = NULL;
  pd.backBuffer   = NULL;
  pd.backBufferDS = NULL;

  // hypothesis: these structs are not properly initialized
  init.platformData = pd;

  // printf("init: %s\n", init);
  // printf("platformdata: %s\n", pd);

  bgfx_init_ctor(&init);

  printf("initialized BGFX ctor\n");

  printf("initializing BGFX...\n");
  bgfx_init(&init);
  printf("initialized BGFX\n");
  bgfx_reset(width, height, reset, init.resolution.format);
  printf("BGFX RESET\n");

  // Enable debug text.
  bgfx_set_debug(debug);

  bgfx_set_view_clear(0
                      , BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
                      , 0x303030ff
                      , 1.0f
                      , 0
                      );

  //while (!entry_process_events(&width, &height, &debug, &reset) )
  while (true) {
    // Set view 0 default viewport.
    bgfx_set_view_rect(0, 0, 0, (uint16_t)width, (uint16_t)height);

    // This dummy draw call is here to make sure that view 0 is cleared
    // if no other draw calls are submitted to view 0.
    bgfx_touch(0);

    // Use debug font to print information about this example.
    bgfx_dbg_text_clear(0, false);
    bgfx_dbg_text_image(
                        uint16_max( (uint16_t)width /2/8, 20)-20
                        , uint16_max( (uint16_t)height/2/16, 6)-6
                        , 40
                        , 12
                        , s_logo
                        , 160
                        );
    bgfx_dbg_text_printf(0, 1, 0x4f, "bgfx/examples/25-c99");
    bgfx_dbg_text_printf(0, 2, 0x6f, "Description: Initialization and debug text with C99 API.");

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx_frame(false);
	}

	// Shutdown bgfx.
	bgfx_shutdown();

	return 0;
}
