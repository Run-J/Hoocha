# =======================================================
#                  	DX Program
# =======================================================
# FINAL BINARY Target
./bin/DX : ./obj/dx.o ../Common/obj/sharedMemoryHandler.o ../Common/obj/logger.o
	cc ./obj/dx.o ../Common/obj/sharedMemoryHandler.o ../Common/obj/logger.o -o ./bin/DX
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/dx.o : ./src/dx.c ../Common/inc/masterList.h ../Common/inc/sharedMemoryHandler.h ../Common/inc/logger.h
	cc -c ./src/dx.c -o ./obj/dx.o

                  

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o



