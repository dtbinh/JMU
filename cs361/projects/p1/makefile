driver: driver.o statemodel.o hardware.o state.o closed.o closing.o opened.o opening.o
	gcc driver.o statemodel.o hardware.o state.o closed.o closing.o opened.o opening.o -o driver

driver.o: driver.c hardware.h statemodel.h
	gcc -c driver.c

hardware.o: hardware.c hardware.h
	gcc -c hardware.c -o hardware.o

statemodel.o: hardware.h statemodel.h statemodel.c 
	gcc -c statemodel.c

state.o: state.h state.c
	gcc -c state.c -o state.o
	
closed.o: state.h closed.h closed.c
	gcc -c closed.c

closing.o: state.h closing.h closing.c
	gcc -c closing.c

opened.o: state.h opened.h opened.c
	gcc -c opened.c

opening.o: state.h opening.h opening.c
	gcc -c opening.c

clean:
	rm *.o ; rm driver 
