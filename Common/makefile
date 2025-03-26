# =======================================================
#                  	Common Directory Makefile
# =======================================================

.PHONY: clean

all: ./obj/sharedMemoryHandler.o ./obj/masterListHandler.o ./obj/logger.o ./obj/messageQueueHandler.o

./obj/sharedMemoryHandler.o : ./src/sharedMemoryHandler.c ./inc/sharedMemoryHandler.h ./inc/logger.h
	cc -c ./src/sharedMemoryHandler.c -o ./obj/sharedMemoryHandler.o

./obj/masterListHandler.o : ./src/masterListHandler.c ./inc/masterListHandler.h ./inc/masterList.h ./inc/logger.h
	cc -c ./src/masterListHandler.c -o ./obj/masterListHandler.o
		
./obj/logger.o : ./src/logger.c ./inc/logger.h
	cc -c ./src/logger.c -o ./obj/logger.o
	
./obj/messageQueueHandler.o : ./src/messageQueueHandler.c ./inc/masterList.h ./inc/messageQueueHandler.h ./inc/messagePrototype.h
	cc -c ./src/messageQueueHandler.c -o ./obj/messageQueueHandler.o


clean:
	rm -f ./bin/*
	rm -f ./obj/*.o



