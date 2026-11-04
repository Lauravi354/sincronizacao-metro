sync_car: sync_car-runner.o
	gcc sync_car-runner.o -pthread -o sync_car

sync_car-runner.o: sync_car-runner.c sync_car.c
	gcc -pthread -c sync_car-runner.c

run: sync_car
	./sync_car

clean:
	rm -f *.o sync_car

.PHONY: run clean