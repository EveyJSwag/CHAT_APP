objects = source/main.o class/client.o class/server.o
cFiles = source/main.cpp class/client.cpp class/server.cpp

ChatServer : $(objects)
	clang++ -o ChatServer $?

$(objects) : $(cFiles)
	clang++ -std=c++17 -c $*.cpp -o $@

.PHONY: clean
clean:
	rm source/*.o class/*.o