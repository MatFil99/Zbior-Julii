
all: main.o genJulia.o interface.o fractalJulia.o
	g++ -o Julia main.o genJulia.o interface.o fractalJulia.o `pkg-config --cflags --libs allegro-5 allegro_ttf-5 allegro_primitives-5 allegro_physfs-5 allegro_memfile-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_dialog-5 allegro_color-5 allegro_audio-5 allegro_acodec-5`

main.o: main.cpp interface.h fractalJulia.h
	g++ -c -g main.cpp interface.h fractalJulia.h

interface.o: interface.cpp interface.h fractalJulia.h
	g++ -c interface.cpp interface.h fractalJulia.h

fractalJulia.o: fractalJulia.cpp fractalJulia.h
	g++ -c fractalJulia.cpp fractalJulia.h

genJulia.o: genJulia.s
	nasm -f elf64 genJulia.s

clean:
	rm -f *.o *.gch

