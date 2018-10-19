BGFX_ROOT = /home/dk/Tools/vr/renderer/bgfx
BGFX_INCLUDE = $(BGFX_ROOT)/include
BX_INCLUDE = $(BGFX_ROOT)/../bx/include
BGFX_LIB = $(BGFX_ROOT)/.build/linux64_gcc/bin

CFLAGS = -std=c99 -I$(BGFX_INCLUDE) -I$(BX_INCLUDE)
LDFLAGS = -L$(BGFX_LIB) -lbgfxDebug -lbimgDebug -lbxDebug -lpthread -lstdc++ -lGL -lX11 -ldl 

HelloBgfx: hello.c
		gcc $(CFLAGS) -o HelloBgfx hello.c $(LDFLAGS)


test: HelloBgfx
		./HelloBgfx
clean:
		rm -f HelloBgfx
