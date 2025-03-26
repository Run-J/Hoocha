# =======================================================
#                  	DR Program
# =======================================================
# FINAL BINARY Target
./bin/DR : ./obj/dr.o ../Common/obj/sharedMemoryHandler.o ../Common/obj/messageQueueHandler.o ../Common/obj/masterListHandler.o ../Common/obj/logger.o
	cc ./obj/dr.o ../Common/obj/sharedMemoryHandler.o ../Common/obj/messageQueueHandler.o ../Common/obj/masterListHandler.o ../Common/obj/logger.o -o ./bin/DR
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/dr.o : ./src/dr.c ../Common/inc/masterList.h ../Common/inc/messageQueueHandler.h ../Common/inc/masterList.h ../Common/inc/messagePrototype.h
	cc -c ./src/dr.c -o ./obj/dr.o
                  

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o



