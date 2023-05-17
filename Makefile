LIBS=-lGL -lglfw -lGLEW
HEADERS=
FILES=main_file.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.

all: main_file