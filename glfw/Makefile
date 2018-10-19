CFLAGS = -std=c99 -I/usr/include
LDFLAGS = -lglfw -lGL
#-L$(BGFX_LIB) 
#/usr/lib/x86_64-linux-gnu/libglfw.so

# -lpthread -lGL -ldl -lm -lXrandr -lXinerama -lXxf86vm -lXcursor -lX11 

HelloGlfw: hello.c
		gcc $(CFLAGS) -o HelloGlfw hello.c $(LDFLAGS)

test: HelloGlfw
		./HelloGlfw
clean:
		rm -f HelloGlfw
