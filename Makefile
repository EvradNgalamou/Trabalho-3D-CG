all: Compile Execute Clear_File

Compile:
	clear

	g++ -o trabalhocg main.cpp tinyxml2.cpp imageloader.cpp matrix4f.cpp objloader.cpp vector3f.cpp volumes.cpp -lGL -lGLU -lglut
	clear

Execute:
	@echo
	@echo
	@echo " ****************************************************************************************"
	@echo " **********************************     EM EXECUÇÃO    **********************************"
	@echo " ****************************************************************************************"
	./trabalhocg
	clear

Clear_File:
	rm -f *.o trabalhocg
	clear
	@echo " ****************************************************************************************"
	@echo " ************************************** FINALIZADO **************************************"
	@echo " ****************************************************************************************"



