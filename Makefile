all: Compile Execute Clear_File

trabalhocg: *.cpp
	g++ -o trabalhocg *.cpp -lGL -lGLU -lglut

trabalhocg_debug: *.cpp
	g++ -o trabalhocg *.cpp -lGL -lGLU -lglut -g

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



