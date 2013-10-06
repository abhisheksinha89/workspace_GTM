#include "defs.h"
using namespace std;

float int22[LINES_INT22][COLS_INT22];
float int21[LINES_INT21][COLS_INT21];
float dangle[LINES_DANGLE][COLS_DANGLE];
float int11[LINES_INT11][COLS_INT11];
float loop[LINES_LOOP][COLS_LOOP];
float stack[LINES_STACK][COLS_STACK];
float tloop[LINES_TLOOP];
std::string stringTloop[LINES_TLOOP]; 
float tstackh[LINES_TSTACKH][COLS_TSTACKH];
float tstacki[LINES_TSTACKI][COLS_TSTACKI];

float int22_ORIG[LINES_INT22][COLS_INT22];
float int21_ORIG[LINES_INT21][COLS_INT21];
float dangle_ORIG[LINES_DANGLE][COLS_DANGLE];
float int11_ORIG[LINES_INT11][COLS_INT11];
float loop_ORIG[LINES_LOOP][COLS_LOOP];
float stack_ORIG[LINES_STACK][COLS_STACK];
float tloop_ORIG[LINES_TLOOP];
std::string stringTloop_ORIG[LINES_TLOOP]; 
float tstackh_ORIG[LINES_TSTACKH][COLS_TSTACKH];
float tstacki_ORIG[LINES_TSTACKI][COLS_TSTACKI];

std::string CURRENT_WORKING_DIR;
unsigned RANDOMSEED;
std::ofstream logfile;

int getNumLines(FILE *fp)
{
	int count = 0;

	char tempBuffer[500];

	while(fgets(tempBuffer, 500, fp) != NULL)
	{
		count++;
	}

	return count;
}

void loadInt21(string fpath)
{
	FILE *fp;
	fp = fopen(fpath.c_str(),"r");
	if(fp == NULL)
	{cout<<"\n>>Error loading param files....exiting"; exit(0);}
	for(int i=0; i<LINES_INT21; i++)
	{
		fscanf(fp, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &int21[i][0], &int21[i][1],&int21[i][2],&int21[i][3],&int21[i][4],&int21[i][5],&int21[i][6],&int21[i][7],&int21[i][8],&int21[i][9],&int21[i][10],&int21[i][11],&int21[i][12],&int21[i][13],&int21[i][14],&int21[i][15],&int21[i][16],&int21[i][17],&int21[i][18],&int21[i][19],&int21[i][20],&int21[i][21],&int21[i][22],&int21[i][23]);
	}
	
	fclose(fp);

	//store also in ORIG arrays
	for(int i=0; i<LINES_INT21; i++)
	{
		for(int j=0; j<COLS_INT21; j++)
		{
			int21_ORIG[i][j] = int21[i][j];
		}
	}
	
	//cout<<int21_ORIG[2][4];
}

void loadInt22(string fpath)
{
	
	
	FILE *fp;
	fp = fopen(fpath.c_str(),"r");
	//numLines = getNumLines(fp);
	//rewind(fp);
	//cout<<numLines;
	if(fp == NULL)
	{cout<<"\n>>Error loading param files....exiting"; exit(0);}
	for(int i=0; i < LINES_INT22; i++)
	{
		fscanf(fp, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &int22[i][0], &int22[i][1], &int22[i][2], &int22[i][3], &int22[i][4], &int22[i][5], &int22[i][6], &int22[i][7], &int22[i][8], &int22[i][9], &int22[i][10], &int22[i][11], &int22[i][12], &int22[i][13], &int22[i][14], &int22[i][15]);
		
	}
	
	fclose(fp);

	//store also in ORIG arrays
	for(int i=0; i<LINES_INT22; i++)
	{
		for(int j=0; j<COLS_INT22; j++)
		{
			int22_ORIG[i][j] = int22[i][j];
		}
	}
}

void loadDangle(string fpath)
{
	FILE *fp;
	fp = fopen(fpath.c_str(),"r");
	if(fp == NULL)
	{cout<<"\n>>Error loading param files....exiting"; exit(0);}
	for(int i=0; i< LINES_DANGLE; i++)
	{
		fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",&dangle[i][0],&dangle[i][1],&dangle[i][2],&dangle[i][3],&dangle[i][4],&dangle[i][5],&dangle[i][6],&dangle[i][7],&dangle[i][8],&dangle[i][9],&dangle[i][10],&dangle[i][11],&dangle[i][12],&dangle[i][13],&dangle[i][14],&dangle[i][15]);
	}
	
	//cout<<dangle[7][15];

	fclose(fp);
	//store also in ORIG arrays
	for(int i=0; i<LINES_DANGLE; i++)
	{
		for(int j=0; j<COLS_DANGLE; j++)
		{
			dangle_ORIG[i][j] = dangle[i][j];
		}
	}
}

void loadInt11(string fpath)
{
	FILE *fp;
	fp = fopen(fpath.c_str(),"r");
	if(fp == NULL)
	{cout<<"\n>>Error loading param files....exiting"; exit(0);}
	for(int i=0; i<LINES_INT11; i++)
	{
		fscanf(fp, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &int11[i][0], &int11[i][1],&int11[i][2],&int11[i][3],&int11[i][4],&int11[i][5],&int11[i][6],&int11[i][7],&int11[i][8],&int11[i][9],&int11[i][10],&int11[i][11],&int11[i][12],&int11[i][13],&int11[i][14],&int11[i][15],&int11[i][16],&int11[i][17],&int11[i][18],&int11[i][19],&int11[i][20],&int11[i][21],&int11[i][22],&int11[i][23]);
	}
	
	//cout<<int11[3][0];
	fclose(fp);
	//store also in ORIG arrays
	for(int i=0; i<LINES_INT11; i++)
	{
		for(int j=0; j<COLS_INT11; j++)
		{
			int11_ORIG[i][j] = int11[i][j];
		}
	}	
}

void loadLoop(string fpath)
{
	FILE *fp;
	fp = fopen(fpath.c_str(),"r");
	if(fp == NULL)
	{cout<<"\n>>Error loading param files....exiting"; exit(0);}
	for(int i=0;i<LINES_LOOP;i++)
	{
		fscanf(fp, "%f %f %f %f",&loop[i][0], &loop[i][1],&loop[i][2], &loop[i][3]);
	}
	
	//cout<<loop[0][1];
	fclose(fp);
	//store also in ORIG arrays
	for(int i=0; i<LINES_LOOP; i++)
	{
		for(int j=0; j<COLS_LOOP; j++)
		{
			loop_ORIG[i][j] = loop[i][j];
		}
	}

}

void loadStack(string fpath)
{
	FILE *fp;
	fp = fopen(fpath.c_str(),"r");
	if(fp == NULL)
	{cout<<"\n>>Error loading param files....exiting"; exit(0);}
	for(int i=0; i< LINES_STACK; i++)
	{
		fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",&stack[i][0],&stack[i][1],&stack[i][2],&stack[i][3],&stack[i][4],&stack[i][5],&stack[i][6],&stack[i][7],&stack[i][8],&stack[i][9],&stack[i][10],&stack[i][11],&stack[i][12],&stack[i][13],&stack[i][14],&stack[i][15]);
	}
	
	//cout<<stack[15][15];

	fclose(fp);
	//store also in ORIG arrays
	for(int i=0; i<LINES_STACK; i++)
	{
		for(int j=0; j<COLS_STACK; j++)
		{
			stack_ORIG[i][j] = stack[i][j];
		}
	}
}

void loadTloop(string fpath)
{
	FILE *fp;
	fp = fopen(fpath.c_str(),"r");
	if(fp == NULL)
	{cout<<"\n>>Error loading param files....exiting"; exit(0);}
	//make a temp char * string buffer
	char tempStrTloop[LINES_TLOOP][7];
	
	for(int i=0; i<LINES_TLOOP; i++)
	{
		fscanf(fp, "%s %f",tempStrTloop[i], &tloop[i]);
	}
	
	for(int i=0;i< LINES_LOOP; i++)
	{
		stringTloop[i].assign(tempStrTloop[i]);
	}
	
	fclose(fp);
	//store also in ORIG arrays
	for(int i=0; i<LINES_TLOOP; i++)
	{
		tloop_ORIG[i] = tloop[i];
	}
	for(int i=0; i<LINES_TLOOP; i++)
	{
		stringTloop_ORIG[i] = stringTloop[i]; 
	}
}

void loadTstackh(string fpath)
{
	FILE *fp;
	fp = fopen(fpath.c_str(),"r");
	if(fp == NULL)
	{cout<<"\n>>Error loading param files....exiting"; exit(0);}
	
	for(int i=0; i< LINES_TSTACKH; i++)
	{
		fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",&tstackh[i][0],&tstackh[i][1],&tstackh[i][2],&tstackh[i][3],&tstackh[i][4],&tstackh[i][5],&tstackh[i][6],&tstackh[i][7],&tstackh[i][8],&tstackh[i][9],&tstackh[i][10],&tstackh[i][11],&tstackh[i][12],&tstackh[i][13],&tstackh[i][14],&tstackh[i][15]);
	}
	

	fclose(fp);
	//store also in ORIG arrays
	for(int i=0; i<LINES_TSTACKH; i++)
	{
		for(int j=0; j<COLS_TSTACKH; j++)
		{
			tstackh_ORIG[i][j] = tstackh[i][j];
		}
	}
	
}

void loadTstacki(string fpath)
{
	FILE *fp;
	fp = fopen(fpath.c_str(),"r");
	if(fp == NULL)
	{cout<<"\n>>Error loading param files....exiting"; exit(0);}
	
	for(int i=0; i< LINES_TSTACKI; i++)
	{
		fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",&tstacki[i][0],&tstacki[i][1],&tstacki[i][2],&tstacki[i][3],&tstacki[i][4],&tstacki[i][5],&tstacki[i][6],&tstacki[i][7],&tstacki[i][8],&tstacki[i][9],&tstacki[i][10],&tstacki[i][11],&tstacki[i][12],&tstacki[i][13],&tstacki[i][14],&tstacki[i][15]);
	}
	
	//cout<<tstacki[2][15];
	fclose(fp);
	//store also in ORIG arrays
	for(int i=0; i<LINES_TSTACKI; i++)
	{
		for(int j=0; j<COLS_TSTACKI; j++)
		{
			tstacki_ORIG[i][j] = tstacki[i][j];
		}
	}
}

int main(int argc,char **argv)
{
	///////////////////////////////////////////////////////////////////////////////
	//------------------------ Some initialization code--------------------------//
	//////////////////////////////////////////////////////////////////////////////
	
	if(getCurrentWorkingDir() == "")
	{	
		cout<<"\n>>Error getting Current Working Dir...exiting\n";
		return 0;
	}
	CURRENT_WORKING_DIR = getCurrentWorkingDir();
	RANDOMSEED = chrono::system_clock::now().time_since_epoch().count();
	char tempBuffer[500];
	logfile.open("Logfile.txt", ios::out | ios::app);
	if(logfile.is_open())
	{
		//do nothing
	}
	else
	{
		cout<<"\n>>Error opening LogFile...exiting program";
		return -1;
	}


	///////////////////////////////////////////////////////////////////////////////
	//--------------------	Start GTMmain code block-----------------------------//
	//////////////////////////////////////////////////////////////////////////////
	
	//load from the current working directory the param files on start-up
	string pathInt22 = CURRENT_WORKING_DIR+"/int22.DAT";
	string pathInt21 = CURRENT_WORKING_DIR+"/int21.DAT";
	string pathDangle = CURRENT_WORKING_DIR+"/dangle.DAT";
	string pathInt11 = CURRENT_WORKING_DIR+"/int11.DAT";
	string pathLoop = CURRENT_WORKING_DIR+"/loop.DAT";
	string pathStack = CURRENT_WORKING_DIR+"/stack.DAT";
	string pathTloop = CURRENT_WORKING_DIR+"/tloop.DAT";
	string pathTstackh = CURRENT_WORKING_DIR+"/tstackh.DAT";
	string pathTstacki = CURRENT_WORKING_DIR+"/tstacki.DAT";

	loadInt22(pathInt22);
	loadInt21(pathInt21);	
	loadDangle(pathDangle);
	loadInt11(pathInt11);
	loadLoop(pathLoop);
	loadStack(pathStack);	
	loadTloop(pathTloop);
	loadTstackh(pathTstackh);
	loadTstacki(pathTstacki);
	
	//start Reading Input
	string choice;
	do
	{
		
		cout<<"\n>>ROOT: Run (run), keep (m)odifying, (e)xit, (l)oad, (s)ave, (u)ndo: ";
		getline(cin, choice);
		if(choice == "run")
		{
			computeFunction();
		}
		
		if(choice == "m" || choice == "M")
		{
			readCategory();
		}
		
		if(choice == "s")
		{
			saveModule();
		}
		
		if(choice == "l")
		{
			loadModule();
		}
		if(choice == "u")
		{
			undoModule();
		}
	}while(choice == "m" || choice == "M" || choice == "run" || choice == "s" || choice == "l" || choice == "u");
	
	exitFunction();
	
	return 0;
}
