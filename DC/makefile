# =======================================================
#                  	DC Program
# =======================================================
# FINAL BINARY Target
./bin/DC : ./obj/dc.o ../Common/obj/masterListHandler.o ../Common/obj/messageQueueHandler.o ../Common/obj/logger.o
	cc ./obj/dc.o ../Common/obj/masterListHandler.o ../Common/obj/messageQueueHandler.o ../Common/obj/logger.o -o ./bin/DC
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/dc.o : ./src/dc.c ../Common/inc/messageQueueHandler.h ../Common/inc/messagePrototype.h
	cc -c ./src/dc.c -o ./obj/dc.o
                  

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o

