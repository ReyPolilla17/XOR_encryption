xor.out: xor.o misc.o message.o key.o decode.o binaries.o args.o
	gcc -o xor.out xor.o misc.o message.o key.o decode.o binaries.o args.o -lm

xor.o: xor.c
	gcc -c xor.c

misc.o: misc.c
	gcc -c misc.c

message.o: message.c
	gcc -c message.c

key.o: key.c
	gcc -c key.c

decode.o: decode.c
	gcc -c decode.c

binaries.o: binaries.c
	gcc -c binaries.c

args.o: args.c
	gcc -c args.c

clean:
	rm *.o
	rm *.out
