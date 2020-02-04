# Author: Abinav Bukkaraya
# ID: 0951030
# Compiler and flags
CC = gcc
FLAGS = -o

# Thread Library
THREADED = -lpthread

BINS = thr_create fork proc_manage proc_shared thr_shared ibadcnt 


all: $(BINS)


thr_create:
	$(CC) $(FLAGS) $@ $@.c $(THREADED)

fork: fork.c
	$(CC) $(FLAGS) $@ $@.c

proc_manage:
	$(CC) $(FLAGS) $@ $@.c

proc_shared:
	$(CC) $(FLAGS) $@ $@.c

thr_shared:
	$(CC) $(FLAGS) $@ $@.c $(THREADED)

ibadcnt:
	$(CC) $(FLAGS) $@ $@.c $(THREADED)

# Clean all files
clean:
	rm -rf $(BINS)

# Zip all files
zip:
	zip -r cis3110_a1_nbukkara.zip ./*


