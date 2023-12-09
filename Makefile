all: Compile Execute Clear_File

SOURCES = $(wildcard *.cpp)

trabalhocg: $(SOURCES)
	g++ -o trabalhocg $(SOURCES) -lGL -lGLU -lglut

trabalhocg_debug: $(SOURCES)
	g++ -o trabalhocg $(SOURCES) -lGL -lGLU -lglut -g

Compile: trabalhocg
	clear

Execute: trabalhocg
	@echo
	@echo
	@echo " ****************************************************************************************"
	@echo " **********************************     EM EXECUÇÃO    **********************************"
	@echo " ****************************************************************************************"
	./trabalhocg
	clear

run: trabalhocg
	./trabalhocg

debug: trabalhocg_debug
	./trabalhocg

Clear_File:
	rm -f *.o trabalhocg
	clear
	@echo " ****************************************************************************************"
	@echo " ************************************** FINALIZADO **************************************"
	@echo " ****************************************************************************************"



