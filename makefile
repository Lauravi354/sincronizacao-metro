sync_car: sync_car-runner.o sync_car.o
	gcc sync_car-runner.o sync_car.o -pthread -o sync_car

sync_car-runner.o: sync_car-runner.c sync_car.h
	gcc -pthread -c sync_car-runner.c

sync_car.o: sync_car.c sync_car.h
	gcc -pthread -c sync_car.c

run: sync_car
	./sync_car

clean:
	rm -f *.o sync_car

.PHONY: run clean