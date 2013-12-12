#include "defs.h"
using namespace std;

default_random_engine generator(RANDOMSEED);
std::string capture_return;
float MYINFINITY = 10000000;

void log(char B1, char B2, char B11, char B22, char X1, char X2, char Y1, char Y2)
{
	//log info
	if(B1 != '0' && B2 != '0')
	{
		fprintf(stderr,"\nModifying -> Closing bp: [%c%c]; ",B1,B2);
	}
	if(B11 != '0' && B22 != '0')
	{
		fprintf(stderr, "Interior bp: [%c%c]; ",B11,B22);
	}
	if(X1 != '0' || X2 != '0' || Y1 != '0' || Y2 != '0')
		fprintf(stderr,"Unpaired bases: ");
	if(X1 != '0')
	{
		fprintf(stderr, "X1: [%c]; ",X1);
	}
	if(X2 != '0')
	{
		fprintf(stderr,"X2: [%c]; ",X2);
	}

	if(Y1 != '0')
	{
		fprintf(stderr, "Y1: [%c]; ",Y1);
	}
	if(Y2 != '0')
	{
		fprintf(stderr,"Y2: [%c]; ",Y2);
	}
	fprintf(stderr, "\n");
}

void log(int count)
{
	if(count == 0)
	fprintf(stderr, "\nModifying -> NO values modified\n");
}


float uniformDistributionNumberGenerator(float a, float b)
{
	uniform_real_distribution<float> dist(a, b);
	float retval = dist(generator);
	return retval;
}

float normalDistributionNumberGenerator(float mean, float stdev)
{
	if(mean > MYINFINITY)
	{
		return mean;
	}

	normal_distribution<float> dist(mean, stdev);
	float retval = dist(generator);
	return retval;
}

void lengthBasedModule()
{
	string logstr = "<length_module> ";
	char numBuff[20];
	string option;
	int len;
	float val;
	float mean, stdev, param1, param2;
	string valOption;
	cout << "\n>>Enter option for (i)nternal/(b)ulge/(h)airpin/(a)ll: ";
	cin >> option;
	logstr =logstr + "option = "+ option + " ";
	if(option == "i" || option == "b" || option == "h" || option == "a")
	{
		while(1)
		{
			cout<<"\nLen: ";
			cin >> len;
			sprintf(numBuff, "%d", len);
			logstr = logstr + "len: "+ numBuff;
			if(len == 0) break;
			cout<<"Val (a)bsolute, (d)isplacement, (n)ormal, (u)niform distribution: ";
			cin >> valOption;
			logstr = logstr + " valOption: "+valOption;
			if(valOption == "n")
			{
				cout<<"\n>>Enter mean (space) stdev: ";
				cin >>mean>>stdev;
				sprintf(numBuff, "%f %f",mean, stdev);
				logstr = logstr + " mean stdev: "+numBuff;
			}
			else if(valOption == "u")
			{
				cout<<"\n>>Enter upperbound (space) lowerbound: ";
				cin >> param1 >> param2;
				sprintf(numBuff,"%f %f",param1,param2);
				logstr = logstr + " upper lower:"+numBuff;
			}

			else if(valOption == "a" || valOption == "d")
			{
				cout<<"\n>>Val: ";
				cin >> val;
				sprintf(numBuff,"%f",val);
				logstr = logstr + " val:"+numBuff;
			}
			else
			{
				cout << "\n>>Invalid valOption";
				break;
			}

			if (len > 30)
			{
				cout<<"\n>>Len should be less than 30";
			}
			else
			{
				if(option == "i")
				{
					//keep backup for undo
					loop_ORIG[len-1][1] = loop[len-1][1];
					if(valOption == "a")
					loop[len - 1][1] = val;
					else if(valOption == "d")
					loop[len - 1][1] += val;
					else if(valOption == "n")
					loop[len - 1][1] = normalDistributionNumberGenerator(mean, stdev);
					else if(valOption == "u")
					loop[len-1][1] = uniformDistributionNumberGenerator(param1, param2);
				}
				if (option == "b")
				{
					//keep backup for undo
					loop_ORIG[len-1][2] = loop[len-1][2];
					if(valOption == "a")
					loop[len - 1][2] = val;
					else if(valOption == "d")
					loop[len - 1][2] += val;
					else if(valOption == "n")
					loop[len-1][2] = normalDistributionNumberGenerator(mean, stdev);
					else if(valOption == "u")
					loop[len -1][2] = uniformDistributionNumberGenerator(param1, param2);
				}
				if (option == "h")
				{
					//keep backup for undo
					loop_ORIG[len-1][3] = loop[len-1][3];
					if(valOption == "a")
					loop[len - 1][3] = val;
					else if(valOption == "d")
					loop[len - 1][3] += val;
					else if(valOption == "n")
					loop[len -1][3] = normalDistributionNumberGenerator(mean, stdev);
					else if(valOption == "u")
					loop[len-1][3] = uniformDistributionNumberGenerator(param1, param2);
				}
				if(option == "a")
				{
					//keep backup for undo
					loop_ORIG[len-1][1] = loop[len-1][1];
					loop_ORIG[len-1][2] = loop[len-1][2];
					loop_ORIG[len-1][3] = loop[len-1][3];
					if(valOption == "a"){
					loop[len - 1][1] = val;
					loop[len - 1][2] = val;
					loop[len - 1][3] = val;
					}
					else if(valOption == "d")
					{
						loop[len - 1][1] += val;
						loop[len - 1][2] += val;
						loop[len - 1][3] += val;
					}
					else if(valOption == "n")
					{
						loop[len -1][1] = normalDistributionNumberGenerator(mean, stdev);
						loop[len -1][2] = normalDistributionNumberGenerator(mean, stdev);
						loop[len -1][3] = normalDistributionNumberGenerator(mean, stdev);
					}
					else if(valOption == "u")
					{
						loop[len -1][1] = uniformDistributionNumberGenerator(param1, param2);
						loop[len -1][2] = uniformDistributionNumberGenerator(param1, param2);
						loop[len -1][3] = uniformDistributionNumberGenerator(param1, param2);
					}

				}

			}
			fileLog(logstr);	//log the query
			logstr = "<length_module> ";	//make logstr empty for next log cycle
		}
	}


	else
	{
		cout<<"\n>>Invalid Option";
	}
	//cout<<loop[4][1];
	//cout<<mean<<" "<<stdev<<" "<<normalDistributionNumberGenerator(mean,stdev);

	getline(cin, capture_return);
}

void dangleModule()
{
	HelperDangle darray[LINES_DANGLE][COLS_DANGLE];

	//creating array which contains information as to which element in the dangle array corresponds to which nucleotides
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<4; j++)
		{
			for (int x=0; x<4; x++)
			{
				if(i%4 == 0)
					darray[i][4*j + x].B1 = 'a';
				if(i%4 == 1)
					darray[i][4*j + x].B1 = 'c';
				if(i%4 == 2)
					darray[i][4*j + x].B1 = 'g';
				if(i%4 == 3)
					darray[i][4*j + x].B1 = 'u';
				if(j == 0)
					darray[i][4*j + x].B2 = 'a';
				if(j == 1)
					darray[i][4*j + x].B2 = 'c';
				if(j == 2)
					darray[i][4*j + x].B2 = 'g';
				if(j == 3)
					darray[i][4*j + x].B2 = 'u';
				if(i < 4)
				{
					darray[i][4*j + x].Y = '0';
					if(x == 0)
						darray[i][4*j + x].X = 'a';
					if(x == 1)
						darray[i][4*j + x].X = 'c';
					if(x == 2)
						darray[i][4*j + x].X = 'g';
					if(x == 3)
						darray[i][4*j + x].X = 'u';
				}
				if(i >= 4)
				{
					darray[i][4*j + x].X = '0';
					if(x == 0)
						darray[i][4*j + x].Y = 'a';
					if(x == 1)
						darray[i][4*j + x].Y = 'c';
					if(x == 2)
						darray[i][4*j + x].Y = 'g';
					if(x == 3)
						darray[i][4*j + x].Y = 'u';

				}
			}
		}
	}//end for
	string logstr;
	int modCount = 0;
	char B1, B2, X1, X2;	//for logging info
	string option;
	string queryBasePair;
	string queryXY;
	string closingBasePairOption="";
	string XYOption="";
	float val=0;
	float mean=0, stdev=0, param1=0, param2=0;
	string valOption;
	int basePairCount = 0;
	int XYCount = 0;
	//while(1)
	//{
		cout<<"\n>>(d)etailed query or (a)ll or (0) for root: ";
		cin >> option;
		if(option == "0")
		{getline(cin, capture_return);return;}
			
		if (option == "a")
		{
			//change all values
			cout<<"\n>>Val (a)bsolute, (d)isplacement, (n)ormal, (u)niform distribution: ";
			cin >> valOption;
			if(valOption == "n")
			{
				cout<<"\n>>Enter mean (space) stdev: ";
				cin>>mean>>stdev;
			}
			else if(valOption == "u")
			{
				cout<<"\n>>Enter upperbound (space) lowerbound: ";
				cin >> param1 >> param2;
			}

			else if (valOption == "a" || valOption == "d")
			{
				cout<<"\n>>Enter Val: ";
				cin >> val;
			}
			else
			{
				cout<<"\n>>Invalid Option";
				getline(cin, capture_return);
				return;
			}

			for(int i=0; i<LINES_DANGLE; i++)
			{
				for(int j=0; j<COLS_DANGLE; j++)
				{
					//backup for UNDO
					dangle_ORIG[i][j] = dangle[i][j];
					if(valOption == "a")
					dangle[i][j] = val;
					else if(valOption == "d")
					dangle[i][j] += val;
					else if(valOption == "n")
					dangle[i][j] = normalDistributionNumberGenerator(mean, stdev);
					else if(valOption == "u")
					dangle[i][j] = uniformDistributionNumberGenerator(param1, param2);
				}
			}
			cout<<"\n>>All values modified";
		}

		else if (option == "d")
		{
			//detailed query implementation

			cout<<"\n>>Any (c)ombination of closing base-pair or (s)pecify closing base-pair: ";
			cin >> closingBasePairOption;
			if(closingBasePairOption == "c")
			{
				cout<<"\n>>Enter closing base-pair in any order, (any) for all combinations: ";
				cin >> queryBasePair;
			}
			else if(closingBasePairOption == "s")
			{
				cout<<"\n>>Enter B1 B2 in order, (x) to not specify: ";
				cin >> queryBasePair;
			}
			else
			{
				cout<<"\n>>Invalid Option";
				getline(cin, capture_return);
				return;
			}
			cout<<"\n>>Any (c)ombination or (s)pecify X1 X2: ";
			cin >> XYOption;
			if(XYOption == "c")
			{
				cout <<"\n>>X1/X2 or (any):  ";
				cin >> queryXY;
			}
			else if(XYOption == "s")
			{
				cout<<"\n>>Enter X1 X2 in order (x) to not specify (Note: Atmost one nucleotide can be specified; other has to be 0): ";
				cin >>queryXY;
			}
			else
			{
				cout<<"\n>>Invalid Option";
				getline(cin, capture_return);
				return;
			}
			cout<<"\n>>Val (a)bsolute, (d)isplacement, (n)ormal, (u)niform distribution: ";
			cin >> valOption;
			if(valOption == "n")
			{
				cout<<"\n>>Enter mean (space) stdev: ";
				cin >> mean >> stdev;

			}
			else if(valOption == "u")
			{
				cout<<"\n>>Enter upperbound (space) lowerbound: ";
				cin >> param1 >> param2;
			}
			else if (valOption == "a" || valOption == "d")
			{
				cout<<"\n>>Enter Val: ";
				cin >> val;
			}
			else
			{
				cout<<"\n>>Invalid Option";
				getline(cin, capture_return);
				return;
			}

			modCount = 0;
			//start with the algorithm
			for(int i=0; i<LINES_DANGLE; i++)
			{

				for(int j = 0; j<COLS_DANGLE; j++)
				{
					//backup for UNDO
					dangle_ORIG[i][j] = dangle[i][j];
					B1 = darray[i][j].B1; B2 = darray[i][j].B2; X1 = darray[i][j].X; X2 = darray[i][j].Y;	//log
					basePairCount = 0;
					XYCount = 0;

					if(closingBasePairOption == "c")
					{
						if(queryBasePair == "any")
						{
							basePairCount = queryBasePair.length();	//match all
						}
						else
						{
							for(int p=0; p<queryBasePair.length(); p++)
							{
								//handle case for x
								if(queryBasePair.c_str()[p] == 'x')
									basePairCount += 1;
								else if(queryBasePair.c_str()[p] == darray[i][j].B1)
								{
									basePairCount += 1;
									//darray[i][j].B should not be used again
									darray[i][j].B1 = '1';
								}

								else if (queryBasePair.c_str()[p] == darray[i][j].B2)
								{
									basePairCount += 1;
									darray[i][j].B2 = '1';
								}

							}
						}
					}

					else if(closingBasePairOption == "s")
					{
						if(queryBasePair.c_str()[0] == 'x')
							basePairCount += 1;

						else if(queryBasePair.c_str()[0] == darray[i][j].B1)
							basePairCount += 1;

						if(queryBasePair.c_str()[1] == 'x')
							basePairCount += 1;

						else if(queryBasePair.c_str()[1] == darray[i][j].B2)
							basePairCount += 1;
					}

					if(XYOption == "c")
					{
						if( queryXY == "any")
						{
							XYCount = queryXY.length();

						}
						else
						{
							for(int p=0; p<queryXY.length(); p++)
							{
								//handle case for x
								if(queryXY.c_str()[p] == 'x')
									XYCount += 1;
								else if(queryXY.c_str()[p] == darray[i][j].X)
								{
									XYCount += 1;

								}
								else if (queryXY.c_str()[p] == darray[i][j].Y)
								{
									XYCount += 1;
								}
							}
						}
					}

					else if(XYOption == "s")
					{
						if(queryXY.c_str()[0] == 'x')
							XYCount += 1;
						else if(queryXY.c_str()[0] == darray[i][j].X)
							XYCount += 1;
						if(queryXY.c_str()[1] == 'x')
							XYCount += 1;
						else if(queryXY.c_str()[1] == darray[i][j].Y)
							XYCount += 1;
					}

					if((basePairCount >= queryBasePair.length()) && (XYCount >= queryXY.length()))
					{
						log(B1,B2,'0','0',X1,X2,'0','0');
						if(valOption == "a")
						dangle[i][j] = val;
						else if(valOption == "d")
						dangle[i][j] += val;
						else if(valOption == "n")
						dangle[i][j] = normalDistributionNumberGenerator(mean, stdev);
						else if(valOption == "u")
						dangle[i][j] = uniformDistributionNumberGenerator(param1, param2);
						modCount ++;
					}
				}//inner for
			}//outer for
			log(modCount);
		}


		else
		{
			cout <<"\n>>Invalid option";

		}
	//}
	getline(cin, capture_return);
	//fileLog the query
	fileLog("dangle_module",option,closingBasePairOption,"",XYOption,queryBasePair,"",queryXY,valOption,val,mean,stdev,param1,param2,modCount);
}

void stackModule()
{
	HelperStack sarray[LINES_STACK][COLS_STACK];

	//creating array which contains information as to which element in the stack array corresponds to which nucleotides

	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			for(int y=0; y<4; y++)
			{
				for(int x=0; x<4; x++)
				{
					//fill B1
					if((4*i + x) <4)
					{
						sarray[4*i + x][4*j + y].B1 = 'a';
					}
					else if((4*i + x) < 8)
					{
						sarray[4*i + x][4*j + y].B1 = 'c';
					}
					else if((4*i + x) < 12)
					{
						sarray[4*i + x][4*j + y].B1 = 'g';
					}
					else if((4*i + x) < 16)
					{
						sarray[4*i + x][4*j + y].B1 = 'u';
					}

					//fill B2

					if((4*j + y) < 4)
					{
						sarray[4*i + x][4*j + y].B2 = 'a';
					}
					else if((4*j + y) < 8)
					{
						sarray[4*i + x][4*j + y].B2 = 'c';
					}
					else if((4*j + y) < 12)
					{
						sarray[4*i + x][4*j + y].B2 = 'g';
					}
					else if((4*j + y) < 16)
					{
						sarray[4*i + x][4*j + y].B2 = 'u';
					}

					//fill Y
					if(y == 0)
					{
						sarray[4*i + x][4*j + y].Y = 'a';
					}
					else if(y == 1)
					{
						sarray[4*i + x][4*j + y].Y = 'c';
					}
					else if(y == 2)
					{
						sarray[4*i + x][4*j + y].Y = 'g';
					}
					else if(y == 3)
					{
						sarray[4*i + x][4*j + y].Y = 'u';
					}
					//fill X
					if(x == 0)
					{
						sarray[4*i + x][4*j + y].X = 'a';
					}
					else if(x == 1)
					{
						sarray[4*i + x][4*j + y].X = 'c';
					}
					else if(x == 2)
					{
						sarray[4*i + x][4*j + y].X = 'g';
					}
					else if(x == 3)
					{
						sarray[4*i + x][4*j + y].X = 'u';
					}

				}//end for
			}//end for
		}//end for
	}//end for
	char B1, B2, B11, B22;	//for log
	int modCount = 0;
	string option;
	string closingBasePairOption;
	string XYOption;
	string queryBasePair;
	string queryXY;
	int basePairCount = 0;
	int XYCount = 0;
	float val;
	float mean, stdev, param1, param2;
	string valOption;
	cout<<"\n>>(d)etailed query or (a)ll or (0) for root: ";
	cin >> option;
	if (option == "d")
	{
		//detailed query implementation
		cout<<"\n>>Any (c)ombination of closing base-pair or (s)pecify closing base-pair: ";
		cin >> closingBasePairOption;
		if(closingBasePairOption == "c")
		{
			cout<<"\n>>Enter closing base-pair (any order), (any) for all combinations: ";
			cin >> queryBasePair;
		}
		else if(closingBasePairOption == "s")
		{
			cout<<"\n>>Enter B1 B2 in order, (x) to not specify: ";
			cin >> queryBasePair;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			getline(cin, capture_return);
			return;
		}
		cout<<"\n>>Any (c)ombination or (s)pecify interior bp: ";
		cin >> XYOption;
		if(XYOption == "c")
		{
			cout <<"\n>>Enter any combination of interior bp or (any) for all:  ";
			cin >> queryXY;
		}
		else if(XYOption == "s")
		{
			cout<<"\n>>Enter B11 B22 in order, (x) to not specify: ";
			cin >>queryXY;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			getline(cin, capture_return);
			return;
		}
		cout<<"\n>>Val (a)bsolute, (d)isplacement, (n)ormal, (u)niform distribution: ";
		cin >> valOption;
		if(valOption == "n")
		{
			cout<<"\n>>Enter mean (space) stdev: ";
			cin >> mean >> stdev;

		}
		else if(valOption == "u")
		{
			cout<<"\n>>Enter upperbound (space) lowerbound: ";
			cin >> param1 >> param2;
		}

		else if (valOption == "a" || valOption == "d")
		{
			cout<<"\n>>Enter Val: ";
			cin >> val;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			getline(cin, capture_return);
			return;
		}

		modCount = 0;
		//start with the algorithm
		for(int i=0; i<LINES_STACK; i++)
		{

			for(int j = 0; j<COLS_STACK; j++)
			{
				//backup for UNDO
				stack_ORIG[i][j] = stack[i][j];
				B1 = sarray[i][j].B1;B2 = sarray[i][j].B2;B11 = sarray[i][j].X;B22 = sarray[i][j].Y;
				basePairCount = 0;
				XYCount = 0;

				if(closingBasePairOption == "c")
				{
					if(queryBasePair == "any")
					{
						//match all
						basePairCount = queryBasePair.length();
					}
					else
					{
						for(int p=0; p<queryBasePair.length(); p++)
						{
							//handle x
							if(queryBasePair.c_str()[p] == 'x')
								basePairCount += 1;
							else if(queryBasePair.c_str()[p] == sarray[i][j].B1)
							{
								basePairCount += 1;
								//sarray[i][j].B1 should not be used again
								sarray[i][j].B1 = '1';
							}
							else if(queryBasePair.c_str()[p] == sarray[i][j].B2)
							{
								basePairCount += 1;
								sarray[i][j].B2 = '1';	//not be used again
							}
						}
					}
				}

				else if(closingBasePairOption == "s")
				{
					if(queryBasePair.c_str()[0] == 'x')
					{
						basePairCount += 1;
					}
					if(queryBasePair.c_str()[0] == sarray[i][j].B1)
					{
						basePairCount += 1;
					}
					if(queryBasePair.c_str()[1] == 'x')
					{
						basePairCount += 1;
					}
					if(queryBasePair.c_str()[1] == sarray[i][j].B2)
					{
						basePairCount += 1;
					}
				}

				if(XYOption == "c")
				{
					if( queryXY == "any")
					{
						XYCount = queryXY.length();

					}
					else
					{
						for(int p=0; p<queryXY.length(); p++)
						{
							//handle x
							if(queryXY.c_str()[p] == 'x')
								XYCount += 1;
							else if(queryXY.c_str()[p] == sarray[i][j].X)
							{
								XYCount += 1;
								sarray[i][j].X = '1';// not used again

							}
							else if (queryXY.c_str()[p] == sarray[i][j].Y)
							{
								XYCount += 1;
								sarray[i][j].Y = '1'; //not used again
							}
						}
					}
				}

				else if(XYOption == "s")
				{
					if(queryXY.c_str()[0] == 'x')
					{
						XYCount += 1;
					}
					if(queryXY.c_str()[0] == sarray[i][j].X)
					{
						XYCount += 1;
					}
					if(queryXY.c_str()[1] == 'x')
					{
						XYCount += 1;
					}
					if(queryXY.c_str()[1] == sarray[i][j].Y)
					{
						XYCount += 1;
					}
				}

				if((basePairCount >= queryBasePair.length()) && (XYCount >= queryXY.length()))
				{
					//matched then modify value
					//cout<<"\n>>Modifying "<<i<<" "<<j;
					log(B1,B2,B11,B22,'0','0','0','0');
					if(valOption == "a")
					stack[i][j] = val;
					else if(valOption == "d")
					stack[i][j] += val;
					else if(valOption == "n")
					stack[i][j] = normalDistributionNumberGenerator(mean, stdev);
					else if(valOption == "u")
					stack[i][j] = uniformDistributionNumberGenerator(param1, param2);
					modCount++;
				}
			}//inner for
		}//outer for
		log(modCount);
		}

	else if(option == "a")
	{
		modCount = 0;
		cout <<"\n>>Val (a)bsolute or (d)isplacement, (n)ormal, (u)niform distribution: ";
		cin >> valOption;
		if(valOption == "n")
		{
			cout<<"\n>>Enter mean (space) stdev: ";
			cin>>mean>>stdev;
		}
		else if(valOption == "u")
		{
			cout<<"\n>>Enter upperbound (space) lowerbound: ";
			cin >> param1 >> param2;
		}
		else if (valOption == "a" || valOption == "d")
		{
			cout<<"\n>>Enter Val: ";
			cin >> val;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			getline(cin, capture_return);
			return;
		}

		for(int i=0; i<LINES_STACK; i++)
		{
			for(int j=0; j<COLS_STACK; j++)
			{
				stack_ORIG[i][j] = stack[i][j];
				if(valOption == "a")
				stack[i][j] = val;
				else if(valOption == "d")
				stack[i][j] += val;
				else if(valOption == "n")
				stack[i][j] = normalDistributionNumberGenerator(mean, stdev);
				else if(valOption == "u")
				stack[i][j] = uniformDistributionNumberGenerator(param1, param2);
			}//end for
		}//end for
		cout<<"\n>>All values modified";
		modCount = LINES_STACK*COLS_STACK;
	}
	else if(option == "0")
	{
		getline(cin, capture_return);
		return;
	}
	fileLog("stack_module",option,closingBasePairOption,"",XYOption,queryBasePair,queryXY,"",valOption,val,mean,stdev,param1,param2,modCount);
	getline(cin, capture_return);
}


void helperTerminalModule(string callerOption)
{


	HelperStack sarray[LINES_TSTACKI][COLS_TSTACKI];	//TSTACKI and TSTACKH and STACK have the same number of LINES & COLS so can use either

	//creating array which contains information as to which element in the stack array corresponds to which nucleotides

	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			for(int y=0; y<4; y++)
			{
				for(int x=0; x<4; x++)
				{
					//fill B1
					if((4*i + x) <4)
					{
						sarray[4*i + x][4*j + y].B1 = 'a';
					}
					else if((4*i + x) < 8)
					{
						sarray[4*i + x][4*j + y].B1 = 'c';
					}
					else if((4*i + x) < 12)
					{
						sarray[4*i + x][4*j + y].B1 = 'g';
					}
					else if((4*i + x) < 16)
					{
						sarray[4*i + x][4*j + y].B1 = 'u';
					}

					//fill B2

					if((4*j + y) < 4)
					{
						sarray[4*i + x][4*j + y].B2 = 'a';
					}
					else if((4*j + y) < 8)
					{
						sarray[4*i + x][4*j + y].B2 = 'c';
					}
					else if((4*j + y) < 12)
					{
						sarray[4*i + x][4*j + y].B2 = 'g';
					}
					else if((4*j + y) < 16)
					{
						sarray[4*i + x][4*j + y].B2 = 'u';
					}

					//fill Y
					if(y == 0)
					{
						sarray[4*i + x][4*j + y].Y = 'a';
					}
					else if(y == 1)
					{
						sarray[4*i + x][4*j + y].Y = 'c';
					}
					else if(y == 2)
					{
						sarray[4*i + x][4*j + y].Y = 'g';
					}
					else if(y == 3)
					{
						sarray[4*i + x][4*j + y].Y = 'u';
					}
					//fill X
					if(x == 0)
					{
						sarray[4*i + x][4*j + y].X = 'a';
					}
					else if(x == 1)
					{
						sarray[4*i + x][4*j + y].X = 'c';
					}
					else if(x == 2)
					{
						sarray[4*i + x][4*j + y].X = 'g';
					}
					else if(x == 3)
					{
						sarray[4*i + x][4*j + y].X = 'u';
					}

				}//end for
			}//end for
		}//end for
	}//end for

	int modCount = 0;
	char B1,B2,X1,X2;	//log
	string option;
	string closingBasePairOption;
	string XYOption;
	string queryBasePair;
	string queryXY;
	int basePairCount = 0;
	int XYCount = 0;
	float val=0;
	float mean=0, stdev=0, param1=0, param2=0;
	string valOption;
	cout<<"\n>>(d)etailed query or (a)ll or (0) for root: ";
	cin >> option;
	if(option == "d")
	{
		//detailed query implementation
		cout<<"\n>>Any (c)ombination of closing base-pair or (s)pecify closing base-pair: ";
		cin >> closingBasePairOption;
		if(closingBasePairOption == "c")
		{
			cout<<"\n>>Enter closing base-pair (any order), (any) for all combinations: ";
			cin >> queryBasePair;
		}
		else if(closingBasePairOption == "s")
		{
			cout<<"\n>>Enter B1 B2 in order, (x) to not specify: ";
			cin >> queryBasePair;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			getline(cin, capture_return);
			return;
		}
		cout<<"\n>>Any (c)ombination or (s)pecify X1 X2: ";
		cin >> XYOption;
		if(XYOption == "c")
		{
			cout <<"\n>>Enter any combination of X1X2 or (any) for all:  ";
			cin >> queryXY;
		}
		else if(XYOption == "s")
		{
			cout<<"\n>>Enter X1X2 in order, (x) to not specify: ";
			cin >>queryXY;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			getline(cin, capture_return);
			return;
		}
		cout<<"\n>>Val (a)bsolute, (d)isplacement, (n)ormal, (u)niform distribution: ";
		cin >> valOption;
		if(valOption == "n")
		{
			cout<<"\n>>Enter mean (space) stdev: ";
			cin >> mean >> stdev;

		}
		else if(valOption == "u")
		{
			cout<<"\n>>Enter upperbound (space) lowerbound: ";
			cin >> param1 >> param2;
		}
		else if (valOption == "a" || valOption == "d")
		{
			cout<<"\n>>Enter Val: ";
			cin >> val;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			getline(cin, capture_return);
			return;
		}

		modCount = 0;
		//start with the algorithm
		for(int i=0; i<LINES_TSTACKH; i++)
		{

			for(int j = 0; j<COLS_TSTACKH; j++)
			{
				tstackh_ORIG[i][j] = tstackh[i][j];
				tstacki_ORIG[i][j] = tstacki[i][j];

				B1 = sarray[i][j].B1; B2 = sarray[i][j].B2; X1 = sarray[i][j].X; X2 = sarray[i][j].Y;
				basePairCount = 0;
				XYCount = 0;

				if(closingBasePairOption == "c")
				{
					if(queryBasePair == "any")
					{
						//match all
						basePairCount = queryBasePair.length();
					}
					else
					{
						for(int p=0; p<queryBasePair.length(); p++)
						{
							//handle x
							if(queryBasePair.c_str()[p] == 'x')
								basePairCount += 1;
							else if(queryBasePair.c_str()[p] == sarray[i][j].B1)
							{
								basePairCount += 1;
								//sarray[i][j].B1 should not be used again
								sarray[i][j].B1 = '1';
							}
							else if(queryBasePair.c_str()[p] == sarray[i][j].B2)
							{
								basePairCount += 1;
								sarray[i][j].B2 = '1';	//not be used again
							}
						}
					}
				}

				else if(closingBasePairOption == "s")
				{
					if(queryBasePair.c_str()[0] == 'x')
					{
						basePairCount += 1;
					}
					if(queryBasePair.c_str()[0] == sarray[i][j].B1)
					{
						basePairCount += 1;
					}
					if(queryBasePair.c_str()[1] == 'x')
					{
						basePairCount += 1;
					}
					if(queryBasePair.c_str()[1] == sarray[i][j].B2)
					{
						basePairCount += 1;
					}
				}

				if(XYOption == "c")
				{
					if( queryXY == "any")
					{
						XYCount = queryXY.length();

					}
					else
					{
						for(int p=0; p<queryXY.length(); p++)
						{
							if(queryXY.c_str()[p] == 'x')
								XYCount += 1;
							else if(queryXY.c_str()[p] == sarray[i][j].X)
							{
								XYCount += 1;
								sarray[i][j].X = '1';// not used again

							}
							else if (queryXY.c_str()[p] == sarray[i][j].Y)
							{
								XYCount += 1;
								sarray[i][j].Y = '1'; //not used again
							}
						}
					}
				}

				else if(XYOption == "s")
				{
					if(queryXY.c_str()[0] == 'x')
					{
						XYCount += 1;
					}
					if(queryXY.c_str()[0] == sarray[i][j].X)
					{
						XYCount += 1;
					}
					if(queryXY.c_str()[1] == 'x')
					{
						XYCount += 1;
					}
					if(queryXY.c_str()[1] == sarray[i][j].Y)
					{
						XYCount += 1;
					}
				}
				//end of algorithm, start to match
				if((basePairCount >= queryBasePair.length()) && (XYCount >= queryXY.length()))
				{
					log(B1,B2,'0','0',X1,X2,'0','0');
					//Match found then modify to val
					if(callerOption == "i")
					{
						//cout<<"\n>>Modifying "<<i<<" "<<j;
						if(valOption == "a")
						tstacki[i][j] = val;
						else if(valOption == "d")
						tstacki[i][j] += val;
						else if(valOption == "n")
						tstacki[i][j] = normalDistributionNumberGenerator(mean, stdev);
						else if(valOption == "u")
						tstacki[i][j] = uniformDistributionNumberGenerator(param1, param2);
					}
					else if(callerOption == "h")
					{
						//cout<<"\n>>Modifying "<<i<<" "<<j;
						if(valOption == "a")
						tstackh[i][j] = val;
						else if(valOption == "d")
						tstackh[i][j] += val;
						else if(valOption == "n")
						tstackh[i][j] = normalDistributionNumberGenerator(mean, stdev);
						else if(valOption == "u")
						tstackh[i][j] = uniformDistributionNumberGenerator(param1, param2);
					}
					modCount++;
				}
			}//inner for
		}//outer for
		log(modCount);
	}

	else if(option == "a")
	{
		modCount = 0;
		cout <<"\n>>Val (a)bsolute or (d)isplacement, (n)ormal, (u)niform distribution: ";
		cin >> valOption;
		if(valOption == "n")
		{
			cout<<"Enter mean (space) stdev: ";
			cin >> mean >> stdev;
		}
		else if(valOption == "u")
		{
			cout<<"\n>>Enter upperbound (space) lowerbound: ";
			cin >> param1 >> param2;
		}
		else if (valOption == "a" || valOption == "d")
		{
			cout<<"\n>>Enter Val: ";
			cin >> val;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			getline(cin, capture_return);
			return;
		}

		for(int i=0; i<LINES_STACK; i++)
		{
			for(int j=0; j<COLS_STACK; j++)
			{
				tstackh_ORIG[i][j] = tstackh[i][j];
				tstacki_ORIG[i][j] = tstacki[i][j];

				if(callerOption == "i")
				{
					if(valOption == "a")
					tstacki[i][j] = val;
					else if(valOption == "d")
					tstacki[i][j] += val;
					else if(valOption == "n")
					tstacki[i][j] = normalDistributionNumberGenerator(mean, stdev);
					else if(valOption == "u")
					tstacki[i][j] = uniformDistributionNumberGenerator(param1, param2);
				}
				else if(callerOption == "h")
				{
					if(valOption == "a")
					tstackh[i][j] = val;
					else if(valOption == "d")
					tstackh[i][j] += val;
					else if(valOption == "n")
					tstackh[i][j] = normalDistributionNumberGenerator(mean, stdev);
					else if(valOption == "u")
					tstackh[i][j] = uniformDistributionNumberGenerator(param1, param2);
				}
			}//end for
		}//end for
		modCount = LINES_TSTACKH*COLS_TSTACKH;
		cout<<"\n>>All values modified";
	}
	else if(option == "0")
	{
		getline(cin, capture_return);
		return;
	}
	if(callerOption == "h")
	fileLog("stack->tstackh",option,closingBasePairOption,"",XYOption,queryBasePair,"",queryXY,valOption,val,mean,stdev,param1,param2,modCount);
	else if(callerOption == "i")
	fileLog("stack->tstacki",option,closingBasePairOption,"",XYOption,queryBasePair,"",queryXY,valOption,val,mean,stdev,param1,param2,modCount);
	getline(cin, capture_return);
}

void terminalModule()
{
	string option;
	while(1)
	{
		cout<<"\n>>Select terminal mismatch energies for (i)nternal loop or (h)airpin, (0) for ROOT: ";
		cin >> option;
		if(option == "0")
			break;
		if(option == "i" || option == "h")
			helperTerminalModule(option);
		else
			cout<<"\n>>Invalid Option";
	}
	getline(cin, capture_return);
}


void miscModule()
{
	string option;
	string logstr;
	string tetraloop;
	int i;
	float val;
	float mean, stdev, param1, param2;
	string valOption;
	cout<< "\n>>Select (t)etraloop: ";
	cin >> option;
	if(option == "t")
	{
		while(1){
			cout<<"\n>>Specify tetraloop or (a)ll, (0) for ROOT: ";
			cin >> tetraloop;
			if(tetraloop == "0")
				break;

			if(tetraloop == "a")
			{
				cout<<"\n>>Val (a)bsolute (d)isplacement, (n)ormal, (u)niform distribution: ";
				cin >> valOption;
				if(valOption == "n")
				{
					cout<<"\n>>Enter mean (space) stdev: ";
					cin >> mean >> stdev;
					logstr = to_string(mean) + " " + to_string(stdev);
				}
				else if(valOption == "u")
				{
					cout<<"\n>>Enter upperbound (space) lowerbound: ";
					cin >> param1 >> param2;
					logstr = to_string(param1) + " "+ to_string(param2);
				}

				else if(valOption == "a" || valOption == "d")
				{
					cout<<">>Enter Val: ";
					cin >> val;
					logstr = to_string(val);
				}
				else
				{
					cout << "\n>>Invalid Option";
					break;
				}
				for(i=0; i<LINES_TLOOP; i++)
				{
					tloop_ORIG[i] = tloop[i];

					if(valOption == "a")
					tloop[i] = val;
					else if(valOption == "d")
					tloop[i] += val;
					else if(valOption == "n")
					tloop[i] = normalDistributionNumberGenerator(mean, stdev);
					else if(valOption == "u")
					tloop[i] = uniformDistributionNumberGenerator(param1, param2);
				}

				cout<<"\n>>All values modified";
			}

			else
			{
				for(i=0; i<LINES_TLOOP; i++)
				{
					if(tetraloop == stringTloop[i])
				{
					tloop_ORIG[i] = tloop[i];

					cout<<"\n>>Val (a)bsolute, (d)isplacement, (n)ormal, (u)niform distribution: ";
					cin >> valOption;
					if(valOption == "n")
					{
						cout<<"\n>>Enter mean (space) stdev: ";
						cin >> mean >> stdev;

					}
					else if(valOption == "u")
					{
						cout<<"\n>>Enter upperbound (space) lowerbound: ";
						cin >> param1 >> param2;
					}

					else if (valOption == "a" || valOption == "d")
					{
						cout<<"\n>>Enter Val: ";
						cin >> val;
					}
					else
					{
						cout<<"\n>>Invalid Option";
						break;
					}

					if(valOption == "a")
					tloop[i] = val;
					else if(valOption == "d")
					tloop[i] += val;
					else if(valOption == "n")
					tloop[i] = normalDistributionNumberGenerator(mean, stdev);
					else if(valOption == "u")
					tloop[i] = uniformDistributionNumberGenerator(param1, param2);
					break;
				}
			}
			if(i >= LINES_TLOOP)
			{
				cout<<"\n>>Invalid Tetraloop";
			}
			}
		//do while closing brace
		string tempstr = "misc->tetraloop";
		tempstr = tempstr + " tetraloop:"+ tetraloop + " valOption:"+ valOption + " vals:"+ logstr;
		//string tempstr = "misc->tetraloop"+ " tetraloop:";
		fileLog(tempstr);
		}

	}

	else
	{
		cout<<"\n>>Invalid option";
		getline(cin, capture_return);
		return;
	}

	getline(cin, capture_return);
}

void internalModule()
{
	string option;
	while(1)
	{
		cout<<"\n>>Choose type of internal loop (1)1x1 (2)2x1 (3)2x2, (0) for root: ";
		cin >> option;
		if(option == "0")
			break;
		else if(option == "1")
			module1x1();
		else if(option == "2")
			module2x1();
		else if(option == "3")
			module2x2();
	}
	getline(cin, capture_return);
}

void module1x1()
{
	//implement algorithm for 1x1 internal loops
	//cout<<"\n>>In 1x1 Module";
	Helper1x1 iarray[LINES_INT11][COLS_INT11];
	//fill in the helper array
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<6; j++)
		{
			for(int x=0; x<4; x++)
			{
				for(int y=0; y<4; y++)
				{
					if(4*i + x < 4)
					{
						iarray[4*i + x][4*j + y].B1 = 'a';
						iarray[4*i + x][4*j + y].B2 = 'u';
					}
					else if(4*i + x < 8)
					{
						iarray[4*i + x][4*j + y].B1 = 'c';
						iarray[4*i + x][4*j + y].B2 = 'g';
					}
					else if(4*i + x < 12)
					{
						iarray[4*i + x][4*j + y].B1 = 'g';
						iarray[4*i + x][4*j + y].B2 = 'c';
					}
					else if(4*i+x < 16)
					{
						iarray[4*i + x][4*j + y].B1 = 'u';
						iarray[4*i + x][4*j + y].B2 = 'a';
					}
					else if(4*i+x < 20)
					{
						iarray[4*i + x][4*j + y].B1 = 'g';
						iarray[4*i + x][4*j + y].B2 = 'u';
					}
					else if(4*i+x <24)
					{
						iarray[4*i + x][4*j + y].B1 = 'u';
						iarray[4*i + x][4*j + y].B2 = 'g';
					}
					//fill B11 B22
					if(4*j+y <4)
					{
						iarray[4*i + x][4*j + y].B11 = 'a';
						iarray[4*i + x][4*j + y].B22 = 'u';
					}

					else if(4*j+y < 8)
					{
						iarray[4*i + x][4*j + y].B11 = 'c';
						iarray[4*i + x][4*j + y].B22 = 'g';
					}
					else if(4*j+y < 12)
					{
						iarray[4*i + x][4*j + y].B11 = 'g';
						iarray[4*i + x][4*j + y].B22 = 'c';
					}
					else if(4*j+y < 16)
					{
						iarray[4*i + x][4*j + y].B11 = 'u';
						iarray[4*i + x][4*j + y].B22 = 'a';
					}
					else if(4*j+y < 20)
					{
						iarray[4*i + x][4*j + y].B11 = 'g';
						iarray[4*i + x][4*j + y].B22 = 'u';
					}
					else if(4*j+y < 24)
					{
						iarray[4*i + x][4*j + y].B11 = 'u';
						iarray[4*i + x][4*j + y].B22 = 'g';
					}
					//Fill X
					if(x == 0)iarray[4*i + x][4*j + y].X = 'a';
					else if(x == 1)iarray[4*i + x][4*j + y].X = 'c';
					else if(x == 2)iarray[4*i + x][4*j + y].X = 'g';
					else if(x == 3)iarray[4*i + x][4*j + y].X = 'u';
					//Fill Y
					if(0 == y)iarray[4*i + x][4*j + y].Y = 'a';
					else if (1 == y)iarray[4*i + x][4*j + y].Y = 'c';
					else if (2 == y)iarray[4*i + x][4*j + y].Y = 'g';
					else if (3 == y)iarray[4*i + x][4*j + y].Y = 'u';


				}//end for
			}//end for
		}//end for
	}//end for
	int modCount = 0;
	char B1,B2,B11,B22,X1,X2;	//log
	string option;
	string closingBasePair;
	string interiorBasePair;
	string XY;
	string closingBasePairOption;
	string interiorBasePairOption;
	string XYOption;
	int closingBasePairCount = 0;
	int interiorBasePairCount = 0;
	int XYCount = 0;
	float val;
	float mean, stdev, param1, param2;
	string valOption;
	cout<<"\n>>Enter (d)etailed query, (a)ll or (0)back: ";
	cin >> option;
	if(option == "d")
	{
		//detailed query

		cout<<"\n>>Any (c)ombination of closing base-pair or (s)pecify closing base-pair: ";
		cin >> closingBasePairOption;
		if(closingBasePairOption == "c")
		{
			cout<<"\n>>Enter closing base-pair (any order), (any) for all combinations: ";
			cin >> closingBasePair;
		}
		else if(closingBasePairOption == "s")
		{
			cout<<"\n>>Enter B1 B2 in order, (x) to not specify: ";
			cin >> closingBasePair;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}
		cout<<"\n>>Any (c)ombination of interior bp or (s)pecify interior bp: ";
		cin >> interiorBasePairOption;
		if(interiorBasePairOption == "c")
		{
			cout <<"\n>>Enter interior bp (any order), (any) for all combinations: ";
			cin >> interiorBasePair;
		}
		else if(interiorBasePairOption == "s")
		{
			cout<<"\n>>Enter B11 B22, (x) to not specify: ";
			cin >>interiorBasePair;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}
		cout<<"\n>>Any (c)ombination of unpaired bases or (s)pecify: ";
		cin >> XYOption;
		if(XYOption == "c")
		{
			cout<<"\n>>Enter X1 X2 in any combination, (any) for all combinations: ";
			cin >> XY;

		}
		else if(XYOption== "s")
		{
			cout<<"\n>>Enter X1 X2, (x) to not specify: ";
			cin >> XY;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}
		cout<<"\n>>Val (a)bsolute, (d)isplacement, (n)ormal, (u)niform distribution: ";
		cin >> valOption;
		if(valOption == "n")
		{
			cout<<"\n>>Enter mean (space) stdev: ";
			cin >> mean >> stdev;

		}
		else if(valOption == "u")
		{
			cout<<"\n>>Enter upperbound (space) lowerbound: ";
			cin >> param1 >> param2;
		}
		else if (valOption == "a" || valOption == "d")
		{
			cout<<"\n>>Enter Val: ";
			cin >> val;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}

		modCount = 0;
		for(int i=0; i<LINES_INT11; i++)
		{
			for(int j=0; j<COLS_INT11; j++)
			{
				//backup for undo
				int11_ORIG[i][j] = int11[i][j];

				//logging
				B1 = iarray[i][j].B1; B2 = iarray[i][j].B2; B11 = iarray[i][j].B11; B22 = iarray[i][j].B22; X1 = iarray[i][j].X; X2 = iarray[i][j].Y;
				closingBasePairCount = 0;
				interiorBasePairCount = 0;
				XYCount = 0;

				if(closingBasePairOption == "c")
				{
					if(closingBasePair == "any")
					{
						closingBasePairCount = closingBasePair.length();
					}
					else
					{
						for(int p=0; p<closingBasePair.length(); p++)
						{
							//handle x
							if(closingBasePair.c_str()[p] == 'x')
								closingBasePairCount += 1;
							else if(closingBasePair.c_str()[p] == iarray[i][j].B1)
							{
								closingBasePairCount += 1;
								//not matches again
								iarray[i][j].B1 = '1';
							}
							else if(closingBasePair.c_str()[p] == iarray[i][j].B2)
							{
								closingBasePairCount += 1;
								//not matches again
								iarray[i][j].B2 = '1';
							}
						}
					}
				}

				if(closingBasePairOption == "s")
				{
					if(closingBasePair.c_str()[0] == 'x')
						closingBasePairCount += 1;
					if(closingBasePair.c_str()[0] == iarray[i][j].B1)
						closingBasePairCount += 1;
					if(closingBasePair.c_str()[1] == 'x')
						closingBasePairCount += 1;
					if(closingBasePair.c_str()[1] == iarray[i][j].B2)
						closingBasePairCount += 1;
				}

				if(interiorBasePairOption == "c")
				{
					if(interiorBasePair == "any")
					{
						interiorBasePairCount = interiorBasePair.length();
					}
					else
					{
						for(int p=0; p<interiorBasePair.length(); p++)
						{
							//handle x
							if(interiorBasePair.c_str()[p] == 'x')
								interiorBasePairCount += 1;
							else if(interiorBasePair.c_str()[p] == iarray[i][j].B11)
							{
								interiorBasePairCount += 1;
								iarray[i][j].B11 = '1';
							}
							else if(interiorBasePair.c_str()[p] == iarray[i][j].B22)
							{
								interiorBasePairCount += 1;
								iarray[i][j].B22 = '1';
							}
						}
					}
				}

				if(interiorBasePairOption == "s")
				{
					if(interiorBasePair.c_str()[0] == 'x')
						interiorBasePairCount += 1;
					if(interiorBasePair.c_str()[0] == iarray[i][j].B11)
						interiorBasePairCount += 1;
					if(interiorBasePair.c_str()[1] == 'x')
						interiorBasePairCount += 1;
					if(interiorBasePair.c_str()[1] == iarray[i][j].B22)
						interiorBasePairCount += 1;
				}

				if(XYOption == "c")
				{
					if(XY == "any")
					{
						XYCount = XY.length();
					}
					else
					{
						for(int p=0; p<XY.length(); p++)
						{
							//handle x
							if(XY.c_str()[p] == 'x')
								XYCount += 1;
							else if(XY.c_str()[p] == iarray[i][j].X)
							{
								XYCount += 1;
								iarray[i][j].X = '1';
							}
							else if(XY.c_str()[p] == iarray[i][j].Y)
							{
								XYCount += 1;
								iarray[i][j].Y = '1';
							}
						}
					}
				}

				if(XYOption == "s")
				{
					if(XY.c_str()[0] == 'x')
						XYCount += 1;
					if(XY.c_str()[0] == iarray[i][j].X)
						XYCount += 1;
					if(XY.c_str()[1] == 'x')
						XYCount += 1;
					if(XY.c_str()[1] == iarray[i][j].Y)
						XYCount += 1;
				}

				//match
				if(closingBasePairCount >= closingBasePair.length() && interiorBasePairCount >= interiorBasePair.length() && XYCount >= XY.length())
				{
					//cout<<"\n>>Modifying "<<i<<" "<<j;
					log(B1,B2,B11,B22,X1,X2,'0','0');
					if(valOption == "a")
					int11[i][j] = val;
					else if(valOption == "d")
					int11[i][j] += val;
					else if(valOption == "n")
					int11[i][j] = normalDistributionNumberGenerator(mean, stdev);
					else if(valOption == "u")
					int11[i][j] = uniformDistributionNumberGenerator(param1, param2);
					modCount++;
				}
			}//inner for
		}//outer for
	}

	else if(option == "a")
	{
		//algo to modify all
		cout<<"\n>>Val (a)bsolute (d)isplacement, (n)ormal, (u)niform distribution: ";
		cin >> valOption;
		if(valOption == "n")
		{
			cout<<"\n>>Enter mean (space) stdev: ";
			cin >> mean >> stdev;

		}
		else if(valOption == "u")
		{
			cout<<"\n>>Enter upperbound (space) lowerbound: ";
			cin >> param1 >> param2;
		}
		else if (valOption == "a" || valOption == "d")
		{
			cout<<"\n>>Enter Val: ";
			cin >> val;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}

		for(int i=0; i<LINES_INT11; i++)
		{
			for(int j=0; j<COLS_INT11; j++)
			{
				int11_ORIG[i][j] = int11[i][j];

				if(valOption == "a")
				int11[i][j] = val;
				else if(valOption == "d")
				int11[i][j] += val;
				else if(valOption == "n")
				int11[i][j] = normalDistributionNumberGenerator(mean, stdev);
				else if(valOption == "u")
				int11[i][j] = uniformDistributionNumberGenerator(param1, param2);
			}
		}
		modCount = LINES_INT11*COLS_INT11;
		cout<<"\nAll values modified";
	}
	else if(option == "0")
	{
		return;
	}
	else
	{
		cout<<"\n>>Invalid Option";
	}

	fileLog("internal->1x1",option,closingBasePairOption,interiorBasePairOption,XYOption,closingBasePair,interiorBasePair,XY,valOption,val,mean,stdev,param1,param2,modCount);

}

void module2x1()
{
	//implement algo for 2x1 internal loops
	Helper2x1 iarray[LINES_INT21][COLS_INT21];
	int ri=0, ci=0; //row indices and column indices for helper array
	//fill in the helper arrays
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<6; j++)
		{
			for(int y1=0; y1<4; y1++)
			{
				for(int x=0; x<4; x++)
				{
					for(int y=0; y<4; y++)
					{
						//start filling the helper array
						ri = (16*i + 4*y1 + x);
						ci = (4*j + y);
						if(i == 0){iarray[ri][ci].B1 = 'a'; iarray[ri][ci].B2 = 'u';}
						else if(i == 1){iarray[ri][ci].B1 = 'c'; iarray[ri][ci].B2 = 'g';}
						else if(i == 2){iarray[ri][ci].B1 = 'g'; iarray[ri][ci].B2 = 'c';}
						else if(i == 3){iarray[ri][ci].B1 = 'u'; iarray[ri][ci].B2 = 'a';}
						else if(i == 4){iarray[ri][ci].B1 = 'g'; iarray[ri][ci].B2 = 'u';}
						else if(i == 5){iarray[ri][ci].B1 = 'u'; iarray[ri][ci].B2 = 'g';}

						if(j == 0){iarray[ri][ci].B11 = 'a'; iarray[ri][ci].B22 = 'u';}
						else if(1 == j){iarray[ri][ci].B11 = 'c'; iarray[ri][ci].B22 = 'g';}
						else if(2 == j){iarray[ri][ci].B11 = 'g'; iarray[ri][ci].B22 = 'c';}
						else if(3 == j){iarray[ri][ci].B11 = 'u'; iarray[ri][ci].B22 = 'a';}
						else if(4 == j){iarray[ri][ci].B11 = 'g'; iarray[ri][ci].B22 = 'u';}
						else if(5 == j){iarray[ri][ci].B11 = 'u'; iarray[ri][ci].B22 = 'g';}

						if(0 == y1){iarray[ri][ci].Y1 = 'a';}
						else if(1 == y1){iarray[ri][ci].Y1 = 'c';}
						else if(2 == y1){iarray[ri][ci].Y1 = 'g';}
						else if(3 == y1){iarray[ri][ci].Y1 = 'u';}

						if(0 == x){iarray[ri][ci].X = 'a';}
						else if(1 == x){iarray[ri][ci].X = 'c';}
						else if(2 == x){iarray[ri][ci].X = 'g';}
						else if(3 == x){iarray[ri][ci].X = 'u';}

						if(0 == y){iarray[ri][ci].Y = 'a';}
						else if(1 == y){iarray[ri][ci].Y = 'c';}
						else if(2 == y){iarray[ri][ci].Y = 'g';}
						else if(3 == y){iarray[ri][ci].Y = 'u';}
					}
				}
			}
		}
	}//end filling helper array

	int modCount = 0;
	char B1,B2,B11,B22,X1,X2,Y2;	//log
	string option;
	string closingBasePair;
	string interiorBasePair;
	string XYY1;
	string closingBasePairOption;
	string interiorBasePairOption;
	string XYY1Option;
	float val;
	float mean, stdev, param1, param2;
	string valOption;
	int closingBasePairCount = 0;
	int interiorBasePairCount = 0;
	int XYY1Count = 0;

	cout<<"\n>>Enter (d)etailed query, (a)ll or (0) to go back: ";
	//if we have varied options for each of the closingBasePair, interiorBasePair, etc implement a single code block which update counts based on the
	//option selected
	cin >> option;
	if(option == "d")
	{
		//detailed query


		cout<<"\n>>Any (c)ombination of closing base-pair or (s)pecify closing base-pair: ";
		cin >> closingBasePairOption;
		if(closingBasePairOption == "c")
		{
			cout<<"\n>>Enter closing base-pair (any order), (any) for all combinations: ";
			cin >> closingBasePair;
		}
		else if(closingBasePairOption == "s")
		{
			cout<<"\n>>Enter B1 B2 in order, (x) to not specify: ";
			cin >> closingBasePair;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}
		cout<<"\n>>Any (c)ombination of interior bp or (s)pecify interior bp: ";
		cin >> interiorBasePairOption;
		if(interiorBasePairOption == "c")
		{
			cout <<"\n>>Enter interior bp (any order), (any) for all combinations: ";
			cin >> interiorBasePair;
		}
		else if(interiorBasePairOption == "s")
		{
			cout<<"\n>>Enter B11 B22, (x) to not specify: ";
			cin >>interiorBasePair;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}
		cout<<"\n>>Any (c)ombination of unpaired bases or (s)pecify: ";
		cin >> XYY1Option;
		if(XYY1Option == "c")
		{
			cout<<"\n>>Enter X1 X2 Y2 any order, (any) for all combinations: ";
			cin >> XYY1;

		}
		else if(XYY1Option== "s")
		{
			cout<<"\n>>Enter X1 X2 Y2, (x) to not specify: ";
			cin >> XYY1;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}
		cout<<"\n>>Val (a)bsolute, (d)isplacement, (n)ormal, (u)niform distribution: ";
		cin >> valOption;
		if(valOption == "n")
		{
			cout<<"\n>>Enter mean (space) stdev: ";
			cin >> mean >> stdev;

		}
		else if(valOption == "u")
		{
			cout<<"\n>>Enter upperbound (space) lowerbound: ";
			cin >> param1 >> param2;
		}
		else if (valOption == "a" || valOption == "d")
		{
			cout<<"\n>>Enter Val: ";
			cin >> val;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}

		modCount = 0;
		//start with the algorithm
		for(int i=0; i<LINES_INT21; i++)
		{
			for(int j=0; j<COLS_INT21; j++)
			{
				int21_ORIG[i][j] = int21[i][j];

				//log info
				B1 = iarray[i][j].B1; B2 = iarray[i][j].B2; B11 = iarray[i][j].B11; B22 = iarray[i][j].B22; X1 = iarray[i][j].X; X2 = iarray[i][j].Y; Y2 = iarray[i][j].Y1;
				closingBasePairCount= 0;
				interiorBasePairCount = 0;
				XYY1Count = 0;
				//start from here
				if(closingBasePairOption == "c")
				{
					if(closingBasePair == "any")
					{
					closingBasePairCount = closingBasePair.length();
					}
					else
					{
						for(int p=0; p<closingBasePair.length(); p++)
						{
							//handle x
							if(closingBasePair.c_str()[p] == 'x')
								closingBasePairCount += 1;
							else if(closingBasePair.c_str()[p] == iarray[i][j].B1)
							{
								closingBasePairCount += 1;
								//not matches again
								iarray[i][j].B1 = '1';
							}
							else if(closingBasePair.c_str()[p] == iarray[i][j].B2)
							{
								closingBasePairCount += 1;
								//not matches again
								iarray[i][j].B2 = '1';
							}
						}
					}


				}
				else if(closingBasePairOption == "s")
				{
					if(closingBasePair.c_str()[0] == 'x')
						closingBasePairCount += 1;
					else if(closingBasePair.c_str()[0] == iarray[i][j].B1)
						closingBasePairCount += 1;
					if(closingBasePair.c_str()[1] == 'x')
						closingBasePairCount += 1;
					else if(closingBasePair.c_str()[1] == iarray[i][j].B2)
						closingBasePairCount += 1;
				}
				//done with closing bp
				//start with interior base pair
				if(interiorBasePairOption == "c")
				{
					if(interiorBasePair == "any")
					{
						interiorBasePairCount = interiorBasePair.length();
					}
					else
					{
						for(int p=0; p<interiorBasePair.length(); p++)
						{
							if(interiorBasePair.c_str()[p] == 'x')
								interiorBasePairCount += 1;
							else if(interiorBasePair.c_str()[p] == iarray[i][j].B11)
							{
								interiorBasePairCount += 1;
								iarray[i][j].B11 = '1';
							}
							else if(interiorBasePair.c_str()[p] == iarray[i][j].B22)
							{
								interiorBasePairCount += 1;
								iarray[i][j].B22 = '1';
							}
						}
					}

				}
				else if(interiorBasePairOption == "s")
				{
					if(interiorBasePair.c_str()[0] == 'x')
						interiorBasePairCount += 1;
					else if(interiorBasePair.c_str()[0] == iarray[i][j].B11)
						interiorBasePairCount += 1;
					if(interiorBasePair.c_str()[1] == 'x')
						interiorBasePairCount += 1;
					else if(interiorBasePair.c_str()[1] == iarray[i][j].B22)
						interiorBasePairCount += 1;

				}
				//interior base pair done
				//start with XYY1
				if(XYY1Option == "c")
				{
					if(XYY1 == "any")
					{
						XYY1Count = XYY1.length();
					}
					else
					{
						for(int p=0 ; p<XYY1.length(); p++)
						{
							//handle x
							if(XYY1.c_str()[p] == 'x')
								XYY1Count += 1;
							else if(XYY1.c_str()[p] == iarray[i][j].X)
							{
								XYY1Count += 1;
								iarray[i][j].X = '1';
							}
							else if(XYY1.c_str()[p] == iarray[i][j].Y)
							{
								XYY1Count += 1;
								iarray[i][j].Y = '1';
							}
							else if(XYY1.c_str()[p] == iarray[i][j].Y1)
							{
								XYY1Count += 1;
								iarray[i][j].Y1 = '1';
							}
						}
					}
				}
				else if(XYY1Option == "s")
				{
					if(XYY1.c_str()[0] == 'x')
						XYY1Count += 1;
					else if(XYY1.c_str()[0] == iarray[i][j].X)
						XYY1Count += 1;
					if(XYY1.c_str()[1] == 'x')
						XYY1Count += 1;
					else if(XYY1.c_str()[1] == iarray[i][j].Y)
						XYY1Count += 1;
					if(XYY1.c_str()[2] == 'x')
						XYY1Count += 1;
					else if(XYY1.c_str()[2] == iarray[i][j].Y1)
						XYY1Count += 1;
				}

				if(closingBasePairCount >= closingBasePair.length() && interiorBasePairCount >= interiorBasePair.length() && XYY1Count >= XYY1.length())
				{
					//match then update val
					//cout<<"\n>>Modifying "<<i<<" "<<j;
					log(B1,B2,B11,B22,X1,X2,'0',Y2);
					if(valOption == "a")
					int21[i][j] = val;
					else if(valOption == "d")
					int21[i][j] += val;
					else if(valOption == "n")
					int21[i][j] = normalDistributionNumberGenerator(mean, stdev);
					else if(valOption == "u")
					int21[i][j] = uniformDistributionNumberGenerator(param1, param2);
					modCount++;
				}
			}
		}
		log(modCount);

	}

	else if(option == "a")
	{
		modCount = 0;
		//modify all values
		cout<<"\n>>Val (a)bsolute, (d)isplacement, (n)ormal, (u)niform distribution: ";
		cin >> valOption;
		if(valOption == "n")
		{
			cout<<"\n>>Enter mean (space) stdev: ";
			cin >> mean >> stdev;

		}
		else if(valOption == "u")
		{
			cout<<"\n>>Enter upperbound (space) lowerbound: ";
			cin >> param1 >> param2;
		}
		else if (valOption == "a" || valOption == "d")
		{
			cout<<"\n>>Enter Val: ";
			cin >> val;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}

		for(int i = 0; i<LINES_INT21; i++)
		{
			for(int j = 0; j<COLS_INT21; j++)
			{
				int21_ORIG[i][j] = int21[i][j];

				if(valOption == "a")
				int21[i][j] = val;
				else if(valOption == "d")
				int21[i][j] += val;
				else if(valOption == "n")
				int21[i][j] = normalDistributionNumberGenerator(mean, stdev);
				else if(valOption == "u")
				int21[i][j] = uniformDistributionNumberGenerator(param1, param2);
			}
		}
		cout<<"\n>>Modified all values";
		modCount = LINES_INT21*COLS_INT21;
		//fileLog("internal->2x1",option,"","","","","",valOption,val,mean,stdev,param1,param2,LINES_INT21*COLS_INT21);
	}

	else if(option == "0")
	{
		return;
	}

	else
	{
		cout<<"\n>>Invalid Option";
		return;
	}
	fileLog("internal->2x1",option,closingBasePairOption,interiorBasePairOption,XYY1Option,closingBasePair,interiorBasePair,XYY1,valOption,val,mean,stdev,param1,param2,modCount);
}

void module2x2()
{
	//implement algo for 2x2 internal loops
	Helper2x2 iarray[LINES_INT22][COLS_INT22];
	//fill the Helper array
	int ri=0, ci=0;	//row index and column index
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<6; j++)
		{
			for(int x=0; x< 16; x++)
			{
				for(int y=0; y<16; y++)
				{
					ri = (96*i + 16*j + x);
					ci = y;
					if(i == 0){iarray[ri][ci].B1 = 'a'; iarray[ri][ci].B2 = 'u';}
					else if(i == 1){iarray[ri][ci].B1 = 'c'; iarray[ri][ci].B2 = 'g';}
					else if(i == 2){iarray[ri][ci].B1 = 'g'; iarray[ri][ci].B2 = 'c';}
					else if(i == 3){iarray[ri][ci].B1 = 'u'; iarray[ri][ci].B2 = 'a';}
					else if(i == 4){iarray[ri][ci].B1 = 'g'; iarray[ri][ci].B2 = 'u';}
					else if(i == 5){iarray[ri][ci].B1 = 'u'; iarray[ri][ci].B2 = 'g';}

					if(j == 0){iarray[ri][ci].B11 = 'a'; iarray[ri][ci].B22 = 'u';}
					else if(j == 1){iarray[ri][ci].B11 = 'c'; iarray[ri][ci].B22 = 'g';}
					else if(j == 2){iarray[ri][ci].B11 = 'g'; iarray[ri][ci].B22 = 'c';}
					else if(j == 3){iarray[ri][ci].B11 = 'u'; iarray[ri][ci].B22 = 'a';}
					else if(j == 4){iarray[ri][ci].B11 = 'g'; iarray[ri][ci].B22 = 'u';}
					else if(j == 5){iarray[ri][ci].B11 = 'u'; iarray[ri][ci].B22 = 'g';}

					if(x == 0){iarray[ri][ci].X1 = 'a'; iarray[ri][ci].X2 = 'a';}
					else if(x == 1){iarray[ri][ci].X1 = 'a'; iarray[ri][ci].X2 = 'c';}
					else if(x == 2){iarray[ri][ci].X1 = 'a'; iarray[ri][ci].X2 = 'g';}
					else if(x == 3){iarray[ri][ci].X1 = 'a'; iarray[ri][ci].X2 = 'u';}
					else if(x == 4){iarray[ri][ci].X1 = 'c'; iarray[ri][ci].X2 = 'a';}
					else if(5 == x){iarray[ri][ci].X1 = 'c'; iarray[ri][ci].X2 = 'c';}
					else if(6 == x){iarray[ri][ci].X1 = 'c'; iarray[ri][ci].X2 = 'g';}
					else if(7 == x){iarray[ri][ci].X1 = 'c'; iarray[ri][ci].X2 = 'u';}
					else if(8 == x){iarray[ri][ci].X1 = 'g'; iarray[ri][ci].X2 = 'a';}
					else if(9 == x){iarray[ri][ci].X1 = 'g'; iarray[ri][ci].X2 = 'c';}
					else if(10 == x){iarray[ri][ci].X1 = 'g'; iarray[ri][ci].X2 = 'g';}
					else if(11 == x){iarray[ri][ci].X1 = 'g'; iarray[ri][ci].X2 = 'u';}
					else if(12 == x){iarray[ri][ci].X1 = 'u'; iarray[ri][ci].X2 = 'a';}
					else if(13 == x){iarray[ri][ci].X1 = 'u'; iarray[ri][ci].X2 = 'c';}
					else if(14 == x){iarray[ri][ci].X1 = 'u'; iarray[ri][ci].X2 = 'g';}
					else if(15 == x){iarray[ri][ci].X1 = 'u'; iarray[ri][ci].X2 = 'u';}

					if(0 == y){iarray[ri][ci].Y1 = 'a'; iarray[ri][ci].Y2 = 'a';}
					else if(y == 1){iarray[ri][ci].Y1 = 'a'; iarray[ri][ci].Y2 = 'c';}
					else if(y == 2){iarray[ri][ci].Y1 = 'a'; iarray[ri][ci].Y2 = 'g';}
					else if(y == 3){iarray[ri][ci].Y1 = 'a'; iarray[ri][ci].Y2 = 'u';}
					else if(y == 4){iarray[ri][ci].Y1 = 'c'; iarray[ri][ci].Y2 = 'a';}
					else if(5 == y){iarray[ri][ci].Y1 = 'c'; iarray[ri][ci].Y2 = 'c';}
					else if(6 == y){iarray[ri][ci].Y1 = 'c'; iarray[ri][ci].Y2 = 'g';}
					else if(7 == y){iarray[ri][ci].Y1 = 'c'; iarray[ri][ci].Y2 = 'u';}
					else if(8 == y){iarray[ri][ci].Y1 = 'g'; iarray[ri][ci].Y2 = 'a';}
					else if(9 == y){iarray[ri][ci].Y1 = 'g'; iarray[ri][ci].Y2 = 'c';}
					else if(10 == y){iarray[ri][ci].Y1 = 'g'; iarray[ri][ci].Y2 = 'g';}
					else if(11 == y){iarray[ri][ci].Y1 = 'g'; iarray[ri][ci].Y2 = 'u';}
					else if(12 == y){iarray[ri][ci].Y1 = 'u'; iarray[ri][ci].Y2 = 'a';}
					else if(13 == y){iarray[ri][ci].Y1 = 'u'; iarray[ri][ci].Y2 = 'c';}
					else if(14 == y){iarray[ri][ci].Y1 = 'u'; iarray[ri][ci].Y2 = 'g';}
					else if(15 == y){iarray[ri][ci].Y1 = 'u'; iarray[ri][ci].Y2 = 'u';}
				}
			}
		}
	}//end filling the helper array
	//start with the algorithm
	//cout<<"------: "<<iarray[0][1].B1<<iarray[0][1].B2<<iarray[0][1].X1<<iarray[0][1].X2<<iarray[0][1].Y1<<iarray[0][1].Y2<<"-----------\n";
	int modCount = 0;
	//log info
	char B1,B2,B11,B22,X1,X2,Y1,Y2;
	string option;
	string closingBasePair;
	string interiorBasePair;
	string XY;
	string closingBasePairOption;
	string interiorBasePairOption;
	string XYOption;
	string valOption;
	float val;
	float mean, stdev, param1, param2;
	int closingBasePairCount = 0;
	int interiorBasePairCount = 0;
	int XYCount = 0;

	cout<<"\n>>Enter (d)etailed query, (a)ll or (0) to go back: ";
	//if we have varied options for each of the closingBasePair, interiorBasePair, etc implement a single code block which update counts based on the
	//option selected
	cin >> option;
	if(option == "d")
	{
		//detailed query


		cout<<"\n>>Any (c)ombination of closing base-pair or (s)pecify closing base-pair: ";
		cin >> closingBasePairOption;
		if(closingBasePairOption == "c")
		{
			cout<<"\n>>Enter closing base-pair (any order), (any) for all combinations: ";
			cin >> closingBasePair;
		}
		else if(closingBasePairOption == "s")
		{
			cout<<"\n>>Enter B1 B2 in order, (x) to not specify: ";
			cin >> closingBasePair;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}
		cout<<"\n>>Any (c)ombination of interior bp or (s)pecify interior bp: ";
		cin >> interiorBasePairOption;
		if(interiorBasePairOption == "c")
		{
			cout <<"\n>>Enter interior bp (any order), (any) for all combinations: ";
			cin >> interiorBasePair;
		}
		else if(interiorBasePairOption == "s")
		{
			cout<<"\n>>Enter B11 B22, (x) to not specify: ";
			cin >>interiorBasePair;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}
		cout<<"\n>>Any (c)ombination of unpaired bases or (s)pecify: ";
		cin >> XYOption;
		if(XYOption == "c")
		{
			cout<<"\n>>Enter unpaired bases in any order, (any) for all combinations: ";
			cin >> XY;

		}
		else if(XYOption == "s")
		{
			cout<<"\n>>Enter unpaired bases in order X1X2Y1Y2, (x) to not specify: ";
			cin >> XY;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}
		cout<<"\n>>Val (a)bsolute, (d)isplacement, (n)ormal, (u)niform distribution: ";
		cin >> valOption;
		if(valOption == "n")
		{
			cout<<"\n>>Enter mean (space) stdev: ";
			cin >> mean >> stdev;

		}
		else if(valOption == "u")
		{
			cout<<"\n>>Enter upperbound (space) lowerbound: ";
			cin >> param1 >> param2;
		}
		else if (valOption == "a" || valOption == "d")
		{
			cout<<"\n>>Enter Val: ";
			cin >> val;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}

		modCount = 0;
		//start with the algorithm
		for(int i=0; i<LINES_INT22; i++)
		{
			for(int j=0; j<COLS_INT22; j++)
			{
				int22_ORIG[i][j] = int22[i][j];

				//log info
				B1 = iarray[i][j].B1; B2 = iarray[i][j].B2; B11 = iarray[i][j].B11; B22 = iarray[i][j].B22; X1 = iarray[i][j].X1; X2 = iarray[i][j].X2; Y1 = iarray[i][j].Y1; Y2 = iarray[i][j].Y2;
				closingBasePairCount= 0;
				interiorBasePairCount = 0;
				XYCount = 0;
				//start from here
				if(closingBasePairOption == "c")
				{
					if(closingBasePair == "any")
					{
					closingBasePairCount = closingBasePair.length();
					}
					else
					{
						for(int p=0; p<closingBasePair.length(); p++)
						{
							if(closingBasePair.c_str()[p] == 'x')
								closingBasePairCount += 1;
							else if(closingBasePair.c_str()[p] == iarray[i][j].B1)
							{
								closingBasePairCount += 1;
								//not matches again
								iarray[i][j].B1 = '1';
							}
							else if(closingBasePair.c_str()[p] == iarray[i][j].B2)
							{
								closingBasePairCount += 1;
								//not matches again
								iarray[i][j].B2 = '1';
							}
						}
					}


				}
				else if(closingBasePairOption == "s")
				{
					if(closingBasePair.c_str()[0] == 'x')
						closingBasePairCount += 1;
					else if(closingBasePair.c_str()[0] == iarray[i][j].B1)
						closingBasePairCount += 1;
					if(closingBasePair.c_str()[1] == 'x')
						closingBasePairCount += 1;
					else if(closingBasePair.c_str()[1] == iarray[i][j].B2)
						closingBasePairCount += 1;
				}
				//done with closing bp
				//start with interior base pair
				if(interiorBasePairOption == "c")
				{
					if(interiorBasePair == "any")
					{
						interiorBasePairCount = interiorBasePair.length();
					}
					else
					{
						for(int p=0; p<interiorBasePair.length(); p++)
						{
							//handle x
							if(interiorBasePair.c_str()[p] == 'x')
								interiorBasePairCount += 1;
							else if(interiorBasePair.c_str()[p] == iarray[i][j].B11)
							{
								interiorBasePairCount += 1;
								iarray[i][j].B11 = '1';
							}
							else if(interiorBasePair.c_str()[p] == iarray[i][j].B22)
							{
								interiorBasePairCount += 1;
								iarray[i][j].B22 = '1';
							}
						}
					}

				}
				else if(interiorBasePairOption == "s")
				{
					if(interiorBasePair.c_str()[0] == 'x')
						interiorBasePairCount += 1;
					else if(interiorBasePair.c_str()[0] == iarray[i][j].B11)
						interiorBasePairCount += 1;
					if(interiorBasePair.c_str()[1] == 'x')
						interiorBasePairCount += 1;
					else if(interiorBasePair.c_str()[1] == iarray[i][j].B22)
						interiorBasePairCount += 1;

				}
				//interior base pair done
				//start with XYY1
				if(XYOption == "c")
				{
					if(XY == "any")
					{
						XYCount = XY.length();
					}
					else
					{
						for(int p=0 ; p<XY.length(); p++)
						{
							if(XY.c_str()[p] == 'x')
								XYCount += 1;
							else if(XY.c_str()[p] == iarray[i][j].X1)
							{
								XYCount += 1;
								iarray[i][j].X1 = '1';
							}
							else if(XY.c_str()[p] == iarray[i][j].X2)
							{
								XYCount += 1;
								iarray[i][j].X2 = '1';
							}
							else if(XY.c_str()[p] == iarray[i][j].Y1)
							{
								XYCount += 1;
								iarray[i][j].Y1 = '1';
							}
							else if(XY.c_str()[p] == iarray[i][j].Y2)
							{
								XYCount += 1;
								iarray[i][j].Y2 = '1';
							}
						}
					}
				}
				else if(XYOption == "s")
				{
					if(XY.c_str()[0] == 'x')
						XYCount += 1;
					else if(XY.c_str()[0] == iarray[i][j].X1)
						XYCount += 1;
					if(XY.c_str()[1] == 'x')
						XYCount += 1;
					else if(XY.c_str()[1] == iarray[i][j].X2)
						XYCount += 1;
					if(XY.c_str()[2] == 'x')
						XYCount += 1;
					else if(XY.c_str()[2] == iarray[i][j].Y1)
						XYCount += 1;
					if(XY.c_str()[3] == 'x')
						XYCount += 1;
					else if(XY.c_str()[3] == iarray[i][j].Y2)
						XYCount += 1;
				}

				if(closingBasePairCount >= closingBasePair.length() && interiorBasePairCount >= interiorBasePair.length() && XYCount >= XY.length())
				{
					//match then update val
					//cout<<"\n>>Modifying "<<i<<" "<<j;
					log(B1,B2,B11,B22,X1,X2,Y1,Y2);
					if(valOption == "a")
					int22[i][j] = val;
					else if(valOption == "d")
					int22[i][j] += val;
					else if(valOption == "n")
					int22[i][j] = normalDistributionNumberGenerator(mean, stdev);
					else if(valOption == "u")
					int22[i][j] = uniformDistributionNumberGenerator(param1, param2);
					modCount++;
				}
			}

		}
		log(modCount);

	}
	else if(option == "a")
	{
		cout<<"\n>>Val (a)bsolute, (d)isplacement, (n)ormal, (u)niform distribution: ";
		cin >> valOption;
		if(valOption == "n")
		{
			cout<<"\n>>Enter mean (space) stdev: ";
			cin >> mean >> stdev;

		}
		else if(valOption == "u")
		{
			cout<<"\n>>Enter upperbound (space) lowerbound: ";
			cin >> param1 >> param2;
		}
		else if (valOption == "a" || valOption == "d")
		{
			cout<<"\n>>Enter Val: ";
			cin >> val;
		}
		else
		{
			cout<<"\n>>Invalid Option";
			return;
		}

		for(int i=0; i<LINES_INT22; i++)
		{
			for(int j=0; j<COLS_INT22; j++)
			{
				int22_ORIG[i][j] = int22[i][j];

				if(valOption == "a")
				int22[i][j] = val;
				else if(valOption == "d")
				int22[i][j] += val;
				else if(valOption == "n")
				int22[i][j] = normalDistributionNumberGenerator(mean, stdev);
				else if(valOption == "u")
				int22[i][j] = uniformDistributionNumberGenerator(param1, param2);
			}
		}
		modCount = LINES_INT22*COLS_INT22;
		cout<<"\n>>All values modified";
		//fileLog("internal->2x2",option,"","","","","",valOption,val,mean,stdev,param1,param2,LINES_INT22*COLS_INT22);
	}
	else if(option == "0")
	{
		return;
	}
	else
	{
		cout<<"\n>>Invalid Option";
		return;
	}
	fileLog("internal->2x2",option,closingBasePairOption,interiorBasePairOption,XYOption,closingBasePair,interiorBasePair,XY,valOption,val,mean,stdev,param1,param2,modCount);
	//cout <<"\n---------------------" <<iarray[0][0].X1 << iarray[0][0].X2<<iarray[0][0].Y1<<iarray[0][0].Y2<<"-------------\n";

}

void valueModuleHelper(string fileOption, float upper, float lower, float val)
{
	int lines = 0, cols = 0, modCount = 0;
	if(fileOption == "1x1")
	{
		lines = LINES_INT11; cols = COLS_INT11;
	}
	else if(fileOption == "1x2")
	{
		lines = LINES_INT21; cols = COLS_INT21;
	}
	else if (fileOption == "2x2")
	{
		 lines = LINES_INT22; cols = COLS_INT22;
	}

	for (int i = 0; i<lines; i++)
	{
		for(int j = 0; j<cols; j++)
		{
			if(fileOption == "1x1")
			{
				if(int11[i][j] >= lower && int11[i][j] <= upper)
				{
					int11[i][j] = val;
					modCount++;
				}
			}
			else if(fileOption == "1x2")
			{
				if(int21[i][j] >= lower && int21[i][j] <= upper)
				{
					int21[i][j] = val;
					modCount++;
				}

			}
			else if(fileOption == "2x2")
			{
				if(int22[i][j] >= lower && int22[i][j] <= upper)
				{
					int22[i][j] = val;
					modCount++;
				}

			}
		}
	}
	cout<<">>Vals Modified: "<<modCount<<"\n";
}

void valueModule()
{
	string fileOption;
	cout<< ">>Enter 1x1 or 1x2 or 2x2: ";
	cin >> fileOption;
	float upper = 0, lower = 0, val=0;
	int proceed = 1;
	while (proceed)
	{
		cout << ">>Upper (space) Lower (space) newValue: ";
		cin >> upper >> lower >> val;
		if(fileOption == "1x1")
			valueModuleHelper("1x1",upper, lower, val);
		else if(fileOption == "1x2")
			valueModuleHelper("1x2",upper, lower, val);
		else if(fileOption == "2x2")
			valueModuleHelper("2x2",upper, lower, val);
		else
		{
			cout<<">>Invalid Option\n";
			return;
		}
		cout<<">>Continue? (0 or 1): ";
		cin >> proceed;
	}
}

void allValuesModule()
{
	// This module modifies all Turner 99 parameters on the same 4 modify options
	//
	string stopper;
	int modCount = 0;
	string valOption;
	float mean, stdev, param1, param2;
	float val;

	cout<<"Val (a)bsolute, (d)isplacement, (n)ormal, (u)niform distribution: ";
	cin >> valOption;
	if(valOption == "n")
	{
		cout<<"\n>>Enter stdev as fraction (like 0.2 implies 20% of original value): ";
		cin >> stdev;
	}
	else if(valOption == "u")
	{
		cout<<"\n>>Enter upperbound (space) lowerbound: ";
		cin >> param1 >> param2;
	}
	else if (valOption == "a" || valOption == "d")
	{
		cout<<"\n>>Enter Val: ";
		cin >> val;
	}
	else
	{
		cout<<"\n>>Invalid Option";
		return;
	}

	// int 22
	//
	for(int i=0; i<LINES_INT22; i++)
		{
			for(int j=0; j<COLS_INT22; j++)
			{
				int22_ORIG[i][j] = int22[i][j];

				if(valOption == "a")
				int22[i][j] = val;
				else if(valOption == "d")
				int22[i][j] += val;
				else if(valOption == "n")
				int22[i][j] = normalDistributionNumberGenerator(int22[i][j], stdev*int22[i][j]);
				else if(valOption == "u")
				int22[i][j] = uniformDistributionNumberGenerator(param1, param2);
			}
		}
		modCount = LINES_INT22*COLS_INT22;

	// int 21
	//
	for(int i = 0; i<LINES_INT21; i++)
		{
			for(int j = 0; j<COLS_INT21; j++)
			{
				int21_ORIG[i][j] = int21[i][j];

				if(valOption == "a")
				int21[i][j] = val;
				else if(valOption == "d")
				int21[i][j] += val;
				else if(valOption == "n")
				int21[i][j] = normalDistributionNumberGenerator(int21[i][j], stdev*int21[i][j]);
				else if(valOption == "u")
				int21[i][j] = uniformDistributionNumberGenerator(param1, param2);
			}
		}
		
		modCount += LINES_INT21*COLS_INT21;

	// dangle
	//
	for(int i=0; i<LINES_DANGLE; i++)
			{
				for(int j=0; j<COLS_DANGLE; j++)
				{
					//backup for UNDO
					dangle_ORIG[i][j] = dangle[i][j];
					if(valOption == "a")
					dangle[i][j] = val;
					else if(valOption == "d")
					dangle[i][j] += val;
					else if(valOption == "n")
					dangle[i][j] = normalDistributionNumberGenerator(dangle[i][j], stdev*dangle[i][j]);
					else if(valOption == "u")
					dangle[i][j] = uniformDistributionNumberGenerator(param1, param2);
				}
			}
			modCount += LINES_DANGLE*COLS_DANGLE;

	// int 11
	//
	for(int i=0; i<LINES_INT11; i++)
		{
			for(int j=0; j<COLS_INT11; j++)
			{
				int11_ORIG[i][j] = int11[i][j];

				if(valOption == "a")
				int11[i][j] = val;
				else if(valOption == "d")
				int11[i][j] += val;
				else if(valOption == "n")
				int11[i][j] = normalDistributionNumberGenerator(int11[i][j], stdev*int11[i][j]);
				else if(valOption == "u")
				int11[i][j] = uniformDistributionNumberGenerator(param1, param2);
			}
		}
		modCount += LINES_INT11*COLS_INT11;

	// loop
	//
	for(int len = 1; len <= 30; len++)
	{
		loop_ORIG[len-1][1] = loop[len-1][1];
		loop_ORIG[len-1][2] = loop[len-1][2];
		loop_ORIG[len-1][3] = loop[len-1][3];
		if(valOption == "a"){
			loop[len - 1][1] = val;
			loop[len - 1][2] = val;
			loop[len - 1][3] = val;
			}
		else if(valOption == "d")
		{
		loop[len - 1][1] += val;
		loop[len - 1][2] += val;
		loop[len - 1][3] += val;
		}
		else if(valOption == "n")
		{
		loop[len -1][1] = normalDistributionNumberGenerator(loop[len-1][1], stdev*loop[len-1][1]);
		loop[len -1][2] = normalDistributionNumberGenerator(loop[len -1][2], stdev*loop[len -1][2]);
		loop[len -1][3] = normalDistributionNumberGenerator(loop[len -1][3], stdev*loop[len -1][3]);
		}
		else if(valOption == "u")
		{
		loop[len -1][1] = uniformDistributionNumberGenerator(param1, param2);
		loop[len -1][2] = uniformDistributionNumberGenerator(param1, param2);
		loop[len -1][3] = uniformDistributionNumberGenerator(param1, param2);
		}
	}
	modCount += 90;

	// stack
	//
	for(int i=0; i<LINES_STACK; i++)
		{
			for(int j=0; j<COLS_STACK; j++)
			{
				stack_ORIG[i][j] = stack[i][j];
				if(valOption == "a")
				stack[i][j] = val;
				else if(valOption == "d")
				stack[i][j] += val;
				else if(valOption == "n")
				stack[i][j] = normalDistributionNumberGenerator(stack[i][j], stdev*stack[i][j]);
				else if(valOption == "u")
				stack[i][j] = uniformDistributionNumberGenerator(param1, param2);
			}//end for
		}//end for

	modCount += LINES_STACK*COLS_STACK;

	// tloop
	//
	for(int i=0; i<LINES_TLOOP; i++)
	{
		tloop_ORIG[i] = tloop[i];
		if(valOption == "a")
			tloop[i] = val;
		else if(valOption == "d")
			tloop[i] += val;
		else if(valOption == "n")
			tloop[i] = normalDistributionNumberGenerator(tloop[i], stdev*tloop[i]);
		else if(valOption == "u")
			tloop[i] = uniformDistributionNumberGenerator(param1, param2);
	}
	modCount += LINES_TLOOP;

	// tstackh
	//

	// tstacki
	//
	for(int i=0; i<LINES_STACK; i++)
		{
			for(int j=0; j<COLS_STACK; j++)
			{
				tstackh_ORIG[i][j] = tstackh[i][j];
				tstacki_ORIG[i][j] = tstacki[i][j];

					if(valOption == "a")
					tstacki[i][j] = val;
					else if(valOption == "d")
					tstacki[i][j] += val;
					else if(valOption == "n")
					tstacki[i][j] = normalDistributionNumberGenerator(tstacki[i][j], stdev*tstacki[i][j]);
					else if(valOption == "u")
					tstacki[i][j] = uniformDistributionNumberGenerator(param1, param2);
				
					if(valOption == "a")
					tstackh[i][j] = val;
					else if(valOption == "d")
					tstackh[i][j] += val;
					else if(valOption == "n")
					tstackh[i][j] = normalDistributionNumberGenerator(tstackh[i][j], stdev*tstackh[i][j]);
					else if(valOption == "u")
					tstackh[i][j] = uniformDistributionNumberGenerator(param1, param2);
				
			}//end for
		}//end for

	cout<<">>All values modified\n";
	getline(cin, stopper);
}


