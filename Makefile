battle_v2: lista.o battle_v2.o
	gcc battle_v2.o lista.o -o battle_v2 -Wall -lm

lista.o: lista.c lista.h
	gcc lista.c -c -Wall -lm

battle_v2.o: battle_v2.c lista.h
	gcc battle_v2.c -c -Wall -lm

clean:
	rm battle_v2 *.o
