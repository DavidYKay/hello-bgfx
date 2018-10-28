/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_video.h>
#include <bgfx/c99/bgfx.h>
#include <bgfx/c99/platform.h>

#include "logo.h"


uint16_t uint16_max(uint16_t _a, uint16_t _b)
{
  return _a < _b ? _b : _a;
}

void assert(bool s) {
  if (!s) {
    exit(-1);
  }
}

int main(int32_t argc, char** argv) {
  uint32_t width  = 1280;
  uint32_t height = 720;
  uint32_t debug  = BGFX_DEBUG_TEXT;
  uint32_t reset  = BGFX_RESET_VSYNC;

  assert(SDL_Init(SDL_INIT_VIDEO) == 0);

  SDL_Window* window = SDL_CreateWindow("hello_sdl2", 300, 300, width, height, SDL_WINDOW_SHOWN);
  //assert(window != null);

  SDL_SysWMinfo wmi;
  SDL_version v;
  SDL_VERSION(&v);
  wmi.version = v;
  assert(SDL_GetWindowWMInfo(window, &wmi));

  bgfx_platform_data_t pd;
  pd.ndt          = wmi.info.x11.display;
  pd.nwh          = (void*) wmi.info.x11.window;
  pd.context      = NULL;
  pd.backBuffer   = NULL;
  pd.backBufferDS = NULL;
  bgfx_set_platform_data(&pd);

  bgfx_init_t init;
  bgfx_init_ctor(&init);

  //init.platformData = pd;

  printf("initialized BGFX ctor\n");

  printf("initializing BGFX...\n");
  bgfx_init(&init);
  printf("initialized BGFX\n");
  printf("BGFX RESET\n");

  bgfx_reset(width, height, reset, init.resolution.format);
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
