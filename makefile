
all: pi_serial pi_mutex pi_semaphore run

pi_serial: pi_serial.c timer.h
	gcc -o pi_serial pi_serial.c -lm 

pi_mutex: pi_mutex.c timer.h
	gcc -o pi_mutex pi_mutex.c -lpthread -lm 

pi_semaphore: pi_semaphore.c timer.h
	gcc -o pi_semaphore pi_semaphore.c -lm -lpthread 

run: pi_serial pi_mutex pi_semaphore
	@echo -e "\n----------------Running Test----------------\n"
	@echo -e "Running Pi_Serial with user input 4\n"
	./pi_serial 4
	@echo -e "Running Pi_Mutex with user input 4\n"
	./pi_mutex 4
	@echo -e "Running Pi_Semaphore with user input 4\n"
	./pi_semaphore 4

clean:
	rm -f pi_serial pi_mutex pi_semaphore
