BGFX_ROOT = /home/dk/Tools/vr/renderer/bgfx
BGFX_INCLUDE = $(BGFX_ROOT)/include
BX_INCLUDE = $(BGFX_ROOT)/../bx/include
BGFX_LIB = $(BGFX_ROOT)/.build/linux64_gcc/bin

CFLAGS = -std=c99 -I$(BGFX_INCLUDE) -I$(BX_INCLUDE)
LDFLAGS = -L$(BGFX_LIB) -lbgfxDebug -lbimgDebug -lbxDebug -lpthread -lstdc++ -lGL -lX11 -ldl 


# -lbimg_decodeDebug
#`pkg-config --static --libs GL` -lGL 


# libbimgDebug.a
# libbimg_decodeDebug.a
# libbimg_decodeRelease.a
# libbimg_encodeDebug.a
# libbimg_encodeRelease.a
# libbimgRelease.a

MyProgram: hello.c
		gcc $(CFLAGS) -o MyProgram hello.c $(LDFLAGS)
