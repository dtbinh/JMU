all: driver factoryline supervisor

driver: driver.o statemodel.o actions.o state.o accepting.o processing.o manufacturing.o shipping.o
	gcc driver.o statemodel.o actions.o state.o accepting.o processing.o manufacturing.o shipping.o -o driver -pthread

factoryline: factoryline.o
	gcc factoryline.o -o factoryline -pthread

supervisor: supervisor.o
	gcc supervisor.o -o supervisor -pthread

factoryline.o: factoryline.c message.h
	gcc -c factoryline.c -o factoryline.o -pthread

supervisor.o: supervisor.c
	gcc -c supervisor.c -o supervisor.o -pthread

driver.o: driver.c actions.h statemodel.h
	gcc -c driver.c

actions.o: actions.c actions.h
	gcc -c actions.c -o actions.o -pthread

statemodel.o: actions.h statemodel.h statemodel.c 
	gcc -c statemodel.c

state.o: state.h state.c
	gcc -c state.c -o state.o
	
accepting.o: state.h accepting.h accepting.c
	gcc -c accepting.c

processing.o: state.h processing.h processing.c
	gcc -c processing.c

manufacturing.o: state.h manufacturing.h manufacturing.c
	gcc -c manufacturing.c

shipping.o: state.h shipping.h shipping.c
	gcc -c shipping.c

clean:
	rm *.o ; rm driver ; rm factoryline ; rm supervisor

