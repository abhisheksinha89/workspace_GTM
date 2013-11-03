#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<time.h>
#include<sstream>
#include<cstdlib>
#include<unistd.h>
#include<random>
#include<chrono>
#include<fstream>

#define COLS_INT22 16
#define LINES_INT22 576
#define COLS_INT21 24
#define LINES_INT21 96
#define COLS_DANGLE 16
#define LINES_DANGLE 8
#define COLS_INT11 24
#define LINES_INT11 24
#define COLS_LOOP 4
#define LINES_LOOP 30
#define COLS_STACK 16
#define LINES_STACK 16
#define LINES_TLOOP 30 // TLOOP has only single array of attributes and another storing the tetraloop structure as a string
#define COLS_TSTACKH 16
#define LINES_TSTACKH 16
#define COLS_TSTACKI 16
#define LINES_TSTACKI 16 


///////////////////////////////////////////////////////////////////////////////
//--------------------global helper structures-------------------------------//
//////////////////////////////////////////////////////////////////////////////

typedef struct DangleStructure
{
	char B1;
	char B2;
	char X;
	char Y;
}HelperDangle;

typedef struct HelperStackStructure
{
	char B1;
	char B2;
	char X;
	char Y;
}HelperStack;

typedef struct Helper1x1Structure
{
	char B1;
	char B2;
	char B11;
	char B22;
	char X;
	char Y;
}Helper1x1;

typedef struct Helper2x1Structure
{
	char B1;
	char B2;
	char B11;
	char B22;
	char X;
	char Y;
	char Y1;
	
}Helper2x1;

typedef struct Helper2x2Structure
{
	char B1;
	char B2;
	char B11;
	char B22;
	char X1;
	char X2;
	char Y1;
	char Y2;

}Helper2x2;

///////////////////////////////////////////////////////////////////////////////
//--------------------global declarations of parameter arrays----------------//
//////////////////////////////////////////////////////////////////////////////


extern float int22[LINES_INT22][COLS_INT22];
extern float int21[LINES_INT21][COLS_INT21];
extern float dangle[LINES_DANGLE][COLS_DANGLE];
extern float int11[LINES_INT11][COLS_INT11];
extern float loop[LINES_LOOP][COLS_LOOP];
extern float stack[LINES_STACK][COLS_STACK];
extern float tloop[LINES_TLOOP];
extern std::string stringTloop[LINES_TLOOP]; 
extern float tstackh[LINES_TSTACKH][COLS_TSTACKH];
extern float tstacki[LINES_TSTACKI][COLS_TSTACKI];

extern float int22_ORIG[LINES_INT22][COLS_INT22];
extern float int21_ORIG[LINES_INT21][COLS_INT21];
extern float dangle_ORIG[LINES_DANGLE][COLS_DANGLE];
extern float int11_ORIG[LINES_INT11][COLS_INT11];
extern float loop_ORIG[LINES_LOOP][COLS_LOOP];
extern float stack_ORIG[LINES_STACK][COLS_STACK];
extern float tloop_ORIG[LINES_TLOOP];
extern std::string stringTloop_ORIG[LINES_TLOOP]; 
extern float tstackh_ORIG[LINES_TSTACKH][COLS_TSTACKH];
extern float tstacki_ORIG[LINES_TSTACKI][COLS_TSTACKI];

///////////////////////////////////////////////////////////////////////////////
//--------------------global declarations of functions-----------------------//
//////////////////////////////////////////////////////////////////////////////
extern std::string currentDateTime();
extern void fileLog(std::string);
extern void fileLog(std::string, std::string, std::string,std::string, std::string,std::string, std::string, std::string,std::string,float,float,float,float,float,int);	//modulename, cbp_option, ibp_option, xy_option, cbp, ibp, char XY, valOption ,val mean stdev param1 param2 
extern void undoModule();
extern void log(char, char, char, char, char, char, char, char);
extern void log(int);
extern float uniformDistributionNumberGenerator(float, float);
extern float normalDistributionNumberGenerator(float, float);
extern std::string findRunPath();
extern std::string getCurrentWorkingDir();
extern void copyOriginalData();
extern void readCategory();
extern void exitFunction();
extern void computeFunction();
extern void lengthBasedModule();
extern void miscModule();
extern void saveModule();
extern void loadModule();
extern void dangleModule();
extern void stackModule();
extern void terminalModule();
extern void helperTerminalModule(std::string);
extern void internalModule();
extern void module1x1();
extern void module2x1();
extern void module2x2();
extern void valueModule();
extern int saveArraysToPath(std::string);
extern int loadArraysFromPath(std::string);
extern void loadInt22(std::string);
extern void loadInt21(std::string);
extern void loadDangle(std::string);
extern void loadInt11(std::string);
extern void loadLoop(std::string);
extern void loadStack(std::string);
extern void loadTloop(std::string);
extern void loadTstackh(std::string);
extern void loadTstacki(std::string);
extern void allValuesModule();
///////////////////////////////////////////////////////////////////////////////
//--------------------global declarations of input options--------------------//
//////////////////////////////////////////////////////////////////////////////
extern std::default_random_engine generator;
extern unsigned RANDOMSEED;
extern std::string category;
extern std::string RUNPATH;
extern std::string CURRENT_WORKING_DIR;
extern std::ofstream logfile;
