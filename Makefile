battle_v2: lista.o battle_v2.o
	gcc battle_v2.o lista.o -o battle_v2 -Wall -lm -g

lista.o: lista.c lista.h
	gcc lista.c -c -Wall -lm -g

battle_v2.o: battle_v2.c lista.h
	gcc battle_v2.c -c -Wall -lm -g

clean:
	rm battle_v2 *.o
