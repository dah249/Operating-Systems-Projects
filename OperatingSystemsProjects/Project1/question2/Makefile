all: pre sort pipe

pre: pre.c
	gcc -o pre pre.c -std=c99

sort: sort.c
	gcc -o sort sort.c -std=c99

pipe: pipe.c
	gcc -o pipe pipe.c -std=c99

run: 
	./pipe -std=c99

clean:
	rm  pre sort pipe

#description: Write a c program pipe.c to set up a parent-TO-child pipe; the parent should 'exec' to perform a "pre" process and its output should be connected to the pipe connected to the child, 
#which should 'exec' to perform a "sort" process.

#HOW TO RUN:
#first run "make" to compile pre.c, sort.c, and pipe.c. Then type "make run" to run the program.You will not be prompted to enter the names and gpas. So after you run the code you have to type in 
#the name and gpa. Then the program will figure out who has a gpa higher than 3.0 using pre.c and then sort the names using sort.c.  After the program is done running type "make clean" to delete the 
#3 exe's.
