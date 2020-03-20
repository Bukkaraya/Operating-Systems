CC = gcc

all: ibadcnt igoodcnt

ibadcnt: ibadcnt.c
	gcc -o $@ $< -lpthread -lrt

igoodcnt: igoodcnt.c
	gcc -o $@ $< -lpthread -lrt

clean:
	rm -rf ibadcnt igoodcnt