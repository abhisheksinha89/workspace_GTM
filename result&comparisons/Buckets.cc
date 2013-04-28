#include<iostream>
#include<cstdlib>
#include<fstream>
#include<stdio.h>
#include<string>
#include<stdlib.h>
using namespace std;

float compare (const void *a, const void *b)
{
	return (*(float *)a - *(float *)b);
}

int getLines(FILE *fp)
{
	int count=0;
	char temp[100];
	while(fgets(temp,100,fp) != NULL)
	{
		count++;
	}
	return count;
}

void mySort(float *A, int n)
{
	float temp;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n-1; j++)
		{
			if(A[j] > A[j+1])
			{
				temp = A[j];
				A[j] = A[j+1];
				A[j+1] = temp;
			}
		}
	}
}

int main(int argc, char **argv)
{
	FILE *fp;
	float offset = atof(argv[2]);
	fp = fopen(argv[1], "r");
	int n = getLines(fp);
	float list[n];
	rewind(fp);
	for(int i=0; i<n; i++)
	{
		fscanf(fp,"%f",&list[i]);
	}
	fclose(fp);
	//call to sort
	mySort(list, n);
	cout<<list[0]<<" "<<list[n-1]<< " " <<offset <<"\n";
	float numOfBuckets= (list[n-1] - list[0])/offset;
	cout << numOfBuckets<< "\n"<<"------"<<"\n";
	
	int *result = (int *)calloc(numOfBuckets+1, sizeof(int));
	int index=0;
	for(int i=0; i<n; i++)
	{
		index = (list[i]-list[0])/offset;
		result[index] += 1;
	}
	for(int i=0; i<numOfBuckets+1; i++)
	{
		cout<<(offset*i + list[0])<<"\t";
		cout<<result[i]<<"\n";
	}
	return 0;
}
