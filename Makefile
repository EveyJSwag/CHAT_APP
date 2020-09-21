objects = source/main.o class/client.o class/server.o 
cFiles = source/main.cpp class/client.cpp class/server.cpp 

ChatServer : $(objects)
	g++ -o ChatServer $?

$(objects) : $(cFiles)
	g++ -c $*.cpp -o $@

.PHONY: clean
clean:
	rm source/*.o class/*.o