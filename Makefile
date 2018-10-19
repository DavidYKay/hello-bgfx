BGFX_ROOT = /home/dk/Tools/vr/renderer/bgfx
BGFX_INCLUDE = $(BGFX_ROOT)/include
BX_INCLUDE = $(BGFX_ROOT)/../bx/include
BGFX_LIB = $(BGFX_ROOT)/.build/linux64_gcc/bin

CFLAGS = -std=c99 -I$(BGFX_INCLUDE) -I$(BX_INCLUDE)
LDFLAGS = -L$(BGFX_LIB) -lbgfxDebug -lglfw3 -lbimgDebug -lbxDebug -lpthread -lstdc++ -lGL -ldl -lm -lXrandr -lXinerama -lXxf86vm -lXcursor -lX11 
# -lSDL2

HelloBgfx: hello.c
		gcc $(CFLAGS) -o HelloBgfx hello.c $(LDFLAGS)

test: HelloBgfx
		./HelloBgfx
clean:
		rm -f HelloBgfx
