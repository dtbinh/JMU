all:
	gcc driver.c actions.c statemodel.c state.c processing.c shipping.c accepting.c manufacturing.c mySock.c -o driver
	gcc server.c mySock.c -o server
	gcc client.c mySock.c -o client
clean:
	rm driver server client
