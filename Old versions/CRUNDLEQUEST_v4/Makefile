battle_v4: lista.o battle_v4.o arquivo.o
	gcc battle_v4.o lista.o arquivo.o -o battle_v4 -Wall -lm -g

lista.o: lista.c lista.h
	gcc lista.c -c -Wall -lm -g

arquivo.o: arquivo.c arquivo.h lista.h
	gcc arquivo.c -c -Wall -lm -g

battle_v4.o: battle_v4.c lista.h arquivo.h
	gcc battle_v4.c -c -Wall -lm -g

clean:
	rm battle_v4 *.o
