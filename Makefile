#
# Makefile pour le TP "Anneau de processus" 
#

#
# Fichiers objets 
#
tempsmoy_fich_obj = tempsmoy.o 

#
# Option de compilation 
#

opt = -g -Wall 
CCOBJ = gcc -c 
CCLNK = gcc 


#
# Executables
#

BIN = tempsmoy com1 com2 com3 com4

tempsmoy : $(tempsmoy_fich_obj)
	$(CCLNK) $(opt) $(tempsmoy_fich_obj) -o tempsmoy

tempsmoy.o : tempsmoy.c
	$(CCOBJ) $(opt) tempsmoy.c -o tempsmoy.o

com1 : com1.c
	$(CCLNK) $(opt) com1.c -o com1
com1.o : com1.c
	$(CCOBJ) $(opt) com1.c -o com1.o

com2 : com2.c
	$(CCLNK) $(opt) com2.c -o com2
com2.o : com2.c
	$(CCOBJ) $(opt) com2.c -o com2.o

com3 : com3.c
	$(CCLNK) $(opt) com3.c -o com3
com3.o : com3.c
	$(CCOBJ) $(opt) com3.c -o com3.o

com4 : com4.c
	$(CCLNK) $(opt) com4.c -o com4
com4.o : com4.c
	$(CCOBJ) $(opt) com4.c -o com4.o

#
# Utilitaires
#

clean : 
	- rm *.o 
	- rm $(BIN) 
	- rm *~

all : $(BIN)
