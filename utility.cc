#include "defs.h"
using namespace std;

std::string category;
std::string RUNPATH;

std::string currentDateTime()
{
	time_t now = time(0);
	struct tm  tstruct;
    	char buf[80];
    	tstruct = *localtime(&now);
    	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    	return buf;
	
}

//modulename, option, cbp, ibp, char XY, valOption ,val mean stdev param1 param2
void fileLog(std::string moduleName, std::string opt,std::string cbp_opt, std::string ibp_opt, std::string xy_opt, std::string cbp, std::string ibp, std::string xy,std::string valOption,float val,float mean,float stdev,float param1,float param2,int mc)
{
	logfile << "[" << currentDateTime() << "]" << ": " << "<"<<moduleName<<"> " << "Options:"<<opt<<" "<< cbp_opt <<" "<< ibp_opt << " " << xy_opt <<" cbp:"<<cbp<<"  ibp:"<< ibp <<"  xy:"<<xy<<"  valOption:"<<valOption<<"  val:"<<val<<"  mean:"<<mean<<"  stdev:"<<stdev<<"  ub:"<<param1<<"  lb:"<<param2<<"   #mod="<< mc <<"\n";
	
}

void fileLog(std::string query)
{
	logfile << "[" << currentDateTime() << "]" << ": " << query <<"\n";  	

}

void undoModule()
{
	//int21
	for(int i=0; i<LINES_INT21; i++)
	{
		for(int j=0; j<COLS_INT21; j++)
		{
			int21[i][j] = int21_ORIG[i][j];
		}
	}
	//int22
	for(int i=0; i<LINES_INT22; i++)
	{
		for(int j=0; j<COLS_INT22; j++)
		{
			int22[i][j] = int22_ORIG[i][j];
		}
	}
	//dangle
	for(int i=0; i<LINES_DANGLE; i++)
	{
		for(int j=0; j<COLS_DANGLE; j++)
		{
			dangle[i][j] = dangle_ORIG[i][j];
		}
	}
	//int21
	for(int i=0; i<LINES_INT11; i++)
	{
		for(int j=0; j<COLS_INT11; j++)
		{
			int11[i][j] = int11_ORIG[i][j];
		}
	}
	//loop
	for(int i=0; i<LINES_LOOP; i++)
	{
		for(int j=0; j<COLS_LOOP; j++)
		{
			loop[i][j] = loop_ORIG[i][j];
		}
	}	
	//stack
	for(int i=0; i<LINES_STACK; i++)
	{
		for(int j=0; j<COLS_STACK; j++)
		{
			stack[i][j] = stack_ORIG[i][j];
		}
	}
	//tloop
	for(int i=0; i<LINES_TLOOP; i++)
	{
		tloop[i] = tloop_ORIG[i];
	}
	//tstackh
	for(int i=0; i<LINES_TSTACKH; i++)
	{
		for(int j=0; j<COLS_TSTACKH; j++)
		{
			tstackh[i][j] = tstackh_ORIG[i][j];
		}
	}
	//tstacki
	for(int i=0; i<LINES_TSTACKI; i++)
	{
		for(int j=0; j<COLS_TSTACKI; j++)
		{
			tstacki[i][j] = tstacki_ORIG[i][j];
		}
	}
	fileLog("UNDO OPERATION");
	cout<<"\n>>Latest Query Undone!";
	return;
}

string getCurrentWorkingDir()
{
	char cwd[1000];
	string retval="";
	if(getcwd(cwd, sizeof(cwd)) == NULL)
		return retval;
	else
		retval = cwd;
	
	return retval;
}

string findRunPath()
{
	char *val;
	val = getenv("GTMODIFYRUNPATH");
	string retval = "";
	if(val != NULL)
		retval = val;
	return retval;
}

void computeFunction()
{
	//implement integration with gtfold
	string retval = findRunPath();	
	if(retval == "")
	{
		cout<<"\n>>Environment variable GTMODIFYRUNPATH not set";
		return;
	}
	
	//saving arrays to default temp dir which will be used to feed parameter values to gtfold
	saveArraysToPath(CURRENT_WORKING_DIR+"/temp");	 
	
	//making the runpath and integrating with gtfold
	string gtfoldFileName;
	cout<<"\n>>Enter File Name: ";
	cin >> gtfoldFileName;
	RUNPATH = retval+"/gtmfe "+"-p "+ CURRENT_WORKING_DIR +"/temp " +"./"+gtfoldFileName;
	//cout<<"\n------"<<RUNPATH;
	system(RUNPATH.c_str());
	
	return;
}

void readCategory()
{
	cout<< ">>Categories:\n>>(length) : modify hairpin/bulge/internal energies based on length of loop\n>>(misc) : modify tetraloop and other miscellaneous energies\n>>(internal) : modify 1x1 2x1 2x2 internal loop energies\n>>(stack) : modify stack energies\n>>(terminal) : modify terminal mismatch energies for hairpin and internal loops\n>>(dangle) : modify dangling energies\n\n";
	cout<<">>Enter category to Modify: ";
	cin >> category;
	
	if (category == "length")
	{
		lengthBasedModule();
		return;
	}
	
	else if (category == "misc")
	{
		miscModule();
		return;
	}
	
	else if (category == "dangle")
	{
		dangleModule();
		return;
	}
	
	else if(category == "stack")
	{
		stackModule();
		return;
	}
	
	else if(category == "terminal")
	{
		terminalModule();
		return;
	}
	
	if(category == "internal")
	{
		internalModule();
		return;
	}
	
	else if (category == "exit")
	{
		exitFunction();
	}
	
	else
	{
		cout<<">>Wrong Input Format\n";
		return;
	}
		
}

void saveModule()
{
	string savePath;
	cout<<"\n>>Enter Full Path where you wish to save: ";
	cin >> savePath;
	
	if(savePath == "0")
		return;
		
	if(saveArraysToPath(savePath))
	{
		cout << ">>Files saved to :" << savePath << "\n";
		fileLog("SAVE OPERATION to : "+savePath);
	}
	else
		cout << "ERROR Saving to :" << savePath << "\n";
	
}

int saveArraysToPath(string savePath)
{
	
	//try to make dir if not exists
	string makeTheDir = "mkdir "+ savePath;
	system(makeTheDir.c_str());
	
	string fileSavePath;
	FILE *fp;

	//save int22
	fileSavePath = savePath+"/int22.DAT";
	fp = fopen(fileSavePath.c_str(),"w");
	for(int i=0; i<LINES_INT22; i++)
	{
		for(int j=0; j<COLS_INT22; j++)
		{	
			fprintf(fp, "%f  ",int22[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	
	//save int21
	fileSavePath = savePath+"/int21.DAT";
	fp = fopen(fileSavePath.c_str(), "w");
	for(int i=0; i<LINES_INT21; i++)
	{
		for(int j=0; j<COLS_INT21; j++)
		{
			fprintf(fp, "%f\t",int21[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	//save dangle
	fileSavePath = savePath +"/dangle.DAT";
	fp = fopen(fileSavePath.c_str(), "w");
	for(int i=0; i<LINES_DANGLE; i++)
	{
		for(int j=0; j<COLS_DANGLE; j++)
		{
			fprintf(fp,"%f \t",dangle[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);

	//save int11
	fileSavePath = savePath +"/int11.DAT";
	fp = fopen(fileSavePath.c_str(), "w");
	for(int i=0; i<LINES_INT11; i++)
	{
		for(int j=0; j<COLS_INT11; j++)
		{
			fprintf(fp, "%f\t",int11[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	
	//save loop
	fileSavePath = savePath +"/loop.DAT";
	fp = fopen(fileSavePath.c_str(), "w");
	for(int i=0; i<LINES_LOOP; i++)
	{
		for(int j=0; j<COLS_LOOP; j++)
		{
			if(j == 0)
			fprintf(fp, "%d\t", (i+1));
			else
			//cout<<"---------------- "<<loop[i][j]<<"\n";
			fprintf(fp, "%f\t",loop[i][j]);
			//fprintf(fp, "Hello\t");
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	
	//save stack
	fileSavePath = savePath +"/stack.DAT";
	fp = fopen(fileSavePath.c_str(), "w");
	for(int i=0; i<LINES_STACK; i++)
	{
		for(int j=0; j<COLS_STACK; j++)
		{
			fprintf(fp, "%f\t",stack[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	
	//save tloop has string values as well
	fileSavePath = savePath + "/tloop.DAT";
	fp = fopen(fileSavePath.c_str(), "w");
	for(int i=0; i<LINES_TLOOP; i++)
	{
		fprintf(fp,"%s\t%f",stringTloop[i].c_str(), tloop[i]);
		fprintf(fp, "\n");
	}
	fclose(fp);

	//save tstackh
	fileSavePath = savePath +"/tstackh.DAT";
	fp = fopen(fileSavePath.c_str(), "w");
	for(int i=0; i<LINES_TSTACKH; i++)
	{
		for(int j=0; j<COLS_TSTACKH; j++)
		{
			fprintf(fp, "%f\t",tstackh[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);


	//save tstacki
	fileSavePath = savePath +"/tstacki.DAT";
	fp = fopen(fileSavePath.c_str(), "w");
	for(int i=0; i<LINES_TSTACKI; i++)
	{
		for(int j=0; j<COLS_TSTACKI; j++)
		{
			fprintf(fp, "%f\t",tstacki[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	
	//copy miscloop.DAT, tstacke.DAT and tstackm.DAT to savePath
	string copyCommand;

	//copy miscloop.DAT
	copyCommand = "cp miscloop.DAT "+savePath; 
	system(copyCommand.c_str());

	//copy tstacke.DAT
	copyCommand = "cp tstacke.DAT "+savePath; 
	system(copyCommand.c_str());

	//copy tstackm.DAT
	copyCommand = "cp tstackm.DAT "+savePath; 
	system(copyCommand.c_str());

	return 1;
}

void loadModule()
{
	string loadPath;
	cout<<"\n>>Enter the full Path to Load Data files: ";
	cin >> loadPath;
	if(loadPath == "0")
		return;
	if(loadArraysFromPath(loadPath))
	{
		cout<< ">>Files loaded from : "<< loadPath <<"\n";
		fileLog("LOAD OPERATION to : "+loadPath);
	}
	else
		cout << "ERROR Loading from : "<< loadPath <<"\n";
}

int loadArraysFromPath(string loadPath)
{
	//implement function here
	
	string pathInt22 = loadPath+"/int22.DAT";
	string pathInt21 = loadPath+"/int21.DAT";
	string pathDangle = loadPath+"/dangle.DAT";
	string pathInt11 = loadPath+"/int11.DAT";
	string pathLoop = loadPath+"/loop.DAT";
	string pathStack = loadPath+"/stack.DAT";
	string pathTloop = loadPath+"/tloop.DAT";
	string pathTstackh = loadPath+"/tstackh.DAT";
	string pathTstacki = loadPath+"/tstacki.DAT";

	loadInt22(pathInt22);
	loadInt21(pathInt21);	
	loadDangle(pathDangle);
	loadInt11(pathInt11);
	loadLoop(pathLoop);
	loadStack(pathStack);	
	loadTloop(pathTloop);
	loadTstackh(pathTstackh);
	loadTstacki(pathTstacki);

	return 1;
}

void exitFunction()
{
	logfile << "\n-------------------- SESSION END ---------------------\n";
	logfile.close();	
	exit(0);
}
