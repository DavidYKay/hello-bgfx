#BGFX_ROOT = /home/dk/Tools/vr/renderer/bgfx
BGFX_ROOT = /home/dk/workspace/current/mccarthy/3rdparty/renderer/bgfx
BGFX_INCLUDE = $(BGFX_ROOT)/include
BX_INCLUDE = $(BGFX_ROOT)/../bx/include
BGFX_LIB = $(BGFX_ROOT)/.build/linux64_gcc/bin

CFLAGS = -std=c99 -I$(BGFX_INCLUDE) -I$(BX_INCLUDE) -I/usr/include
LDFLAGS = -L$(BGFX_LIB) -lbgfxDebug -lSDL2 -lbimgDebug -lbxDebug -lpthread -lstdc++ -lGL -ldl -lm -lXrandr -lXinerama -lXxf86vm -lXcursor -lX11 
#-lglfw -lGL

HelloBgfx: hello.c
		gcc $(CFLAGS) -o HelloBgfx hello.c $(LDFLAGS)

test: HelloBgfx
		./HelloBgfx
clean:
		rm -f HelloBgfx
