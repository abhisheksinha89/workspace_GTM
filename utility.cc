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

string findRunPath(string command)
{
	char *val;
	if(command == "gtmfe")
		val = getenv("GTMODIFYRUNPATH");
	if(command == "RNAprofile")
		val = getenv("RNAPROFILERUNPATH");
	string retval = "";
	if(val != NULL)
		retval = val;
	return retval;
}

string getPartBeforeFileName(string gtfoldCommand)
{
	unsigned pos = gtfoldCommand.find_last_of(' ');
	return gtfoldCommand.substr(0, pos);

}

string getFileName(string gtfoldCommand)
{
	unsigned pos = gtfoldCommand.find_last_of(' ');
	return gtfoldCommand.substr(pos+1);
}

string getRunBinary(string gtfoldCommand)
{
	unsigned pos = gtfoldCommand.find_first_of(' ');
	return gtfoldCommand.substr(0, pos);
}

void computeFunction()
{
	string retval;
	// Call gtfold with parameters and link to GTModify
	//
	char line[200];
	string gtfoldCommand;
	cout<<"Enter GTFold or profiling command (-p and -paramDir is set automatically): ";
	getline(cin, gtfoldCommand);

	//implement integration with gtfold & Profiling code
	//
	if(getRunBinary(gtfoldCommand) == "RNAprofile")
	{
		retval = findRunPath("RNAprofile");
		if(retval == "")
		{
			cout<<"\n>>Environment variable RNAPROFILERUNPATH not set";
			return;
		}
	}
	
	else if(getRunBinary(gtfoldCommand) == "gtmfe" || getRunBinary(gtfoldCommand) == "gtboltzmann")
	{
		retval = findRunPath("gtmfe");	
		if(retval == "")
		{
			cout<<"\n>>Environment variable GTMODIFYRUNPATH not set";
			return;
		}
	}

	else
	{
		cout<<"\n>>Command not recognized....supported commands are [gtmfe] [gtboltzmann] & [RNAprofile]";
		return;
	}

	//saving arrays to default temp dir which will be used to feed parameter values to gtfold
	saveArraysToPath(CURRENT_WORKING_DIR+"/temp");	 

	
	// creating the RUNPATH
	//
	if(getRunBinary(gtfoldCommand) == "gtmfe" || getRunBinary(gtfoldCommand) == "gtboltzmann")
	{
		RUNPATH = retval + "/" + getPartBeforeFileName(gtfoldCommand) +" -p "+ CURRENT_WORKING_DIR + "/temp " + "./" + getFileName(gtfoldCommand);
		//cout<<"\n------"<<RUNPATH<<endl;
		system(RUNPATH.c_str());
	}
	else if(getRunBinary(gtfoldCommand) == "RNAprofile")
	{
		RUNPATH = retval + "/" + getPartBeforeFileName(gtfoldCommand) + " --paramdir "+ CURRENT_WORKING_DIR + "/temp " + "./" + getFileName(gtfoldCommand);
		cout<<RUNPATH<<"\n";
		system(RUNPATH.c_str());
	}
	return;
}

void readCategory()
{
	cout<< ">>Categories:\n>>(length) : modify hairpin/bulge/internal energies based on length of loop\n>>(misc) : modify tetraloop and other miscellaneous energies\n>>(internal) : modify 1x1 2x1 2x2 internal loop energies\n>>(stack) : modify stack energies\n>>(terminal) : modify terminal mismatch energies for hairpin and internal loops\n>>(dangle) : modify dangling energies\n>>(value): modify value based params (To Implement)\n>>(all): modify all Turner99 parameters\n\n";
	cout<<">>Enter category to Modify: ";
	getline(cin, category);
	
	if (category == "length")
	{
		lengthBasedModule();
		
	}
	
	else if (category == "value")
	{
		valueModule();
		
	}
	
	else if (category == "misc")
	{
		miscModule();
		
	}
	
	else if (category == "dangle")
	{
		dangleModule();
		
	}
	
	else if(category == "stack")
	{
		stackModule();
		
	}
	
	else if(category == "terminal")
	{
		terminalModule();
		
	}
	
	else if(category == "internal")
	{
		internalModule();
		
	}
	
	else if (category == "exit")
	{
		exitFunction();
	}
	
	else if(category == "all")
	{
		allValuesModule();
	}

	else
	{
		printf("\n>>Wrong Format");
		return;
	}
	
}

void saveModule()
{
	string savePath;
	cout<<"\n>>Enter Full Path where you wish to save: ";
	getline(cin, savePath);
	
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
			fprintf(fp, "\t%.2f",int22[i][j]);
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
			fprintf(fp, "%.2f\t",int21[i][j]);
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
			fprintf(fp,"%.2f \t",dangle[i][j]);
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
			fprintf(fp, "%.2f\t",int11[i][j]);
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
			fprintf(fp, "%.2f\t",loop[i][j]);
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
			fprintf(fp, "%.2f\t",stack[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	
	//save tloop has string values as well
	fileSavePath = savePath + "/tloop.DAT";
	fp = fopen(fileSavePath.c_str(), "w");
	for(int i=0; i<LINES_TLOOP; i++)
	{
		fprintf(fp,"%s\t%.2f",stringTloop[i].c_str(), tloop[i]);
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
			fprintf(fp, "%.2f\t",tstackh[i][j]);
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
			fprintf(fp, "%.2f\t",tstacki[i][j]);
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
	getline(cin, loadPath);
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
