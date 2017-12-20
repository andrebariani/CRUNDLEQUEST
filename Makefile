battle_v4: lista.o battle_final.o arquivo.o
	gcc battle_final.o lista.o arquivo.o -o battle_final -Wall -lm -g

lista.o: lista.c lista.h
	gcc lista.c -c -Wall -lm -g

arquivo.o: arquivo.c arquivo.h lista.h
	gcc arquivo.c -c -Wall -lm -g

battle_v4.o: battle_final.c lista.h arquivo.h
	gcc battle_final.c -c -Wall -lm -g

clean:
	rm battle_final *.o
