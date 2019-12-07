intr: int.c
	gcc -o intr int.c

mymalloc.so: mymalloc.c
	gcc -DRUNTIME -shared -fpic -o mymalloc.so mymalloc.c -ldl

run: mymalloc.so intr
	LD_PRELOAD="./mymalloc.so" ./intr