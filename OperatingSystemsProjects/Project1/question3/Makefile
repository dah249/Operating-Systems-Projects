


all: prog

prog: prog.c
	@echo "Compiling prog.c"
	@gcc -o prog prog.c -std=c99

run: 
	./prog ls -t -l

clean:
	@echo "Cleaning up..."
	@rm  prog



#Description : Write a program to take a UNIX command from the command line and fork() a child to execute it. The command can be a simple command like: $./prog ls or $./prog ps, Or it can be a 
#command with options such as ./prog ls -t -l. Use argc and argv[] in the main function to pass parameters.
#When the child process is executing the command, the parent process simply waits for the termination of the child process. The process id of the parent and the child should be printed out using 
#getpid() and getppid() functions.


# HOW TO RUN
# Type "make" to compile the program then type any of the given commands, any unix command, or type "make run" to run the program with "./prog ls -t -l" unix command. Then to delete the executable 
# type "make clean".  

