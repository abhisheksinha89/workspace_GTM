import sys
import os
import math

# global Data Structures
#
file1List = []
file2List = []
file1Helices = []
file2Helices = []
file1Frequency = []
file2Frequency = []

def foundAndProcessIn(theFile, helixInSet):
	if(theFile == 'File1'):
		for helix in file1List:
			if(helix.rsplit(' ',1)[0] == helixInSet):
				file1Frequency.append(float(helix.rsplit(' ',1)[1]))
				return
		file1Frequency.append(1.0)
	elif (theFile == 'File2'):
		for helix in file2List:
			if(helix.rsplit(' ',1)[0] == helixInSet):
				file2Frequency.append(float(helix.rsplit(' ',1)[1]))
				return
		file2Frequency.append(1.0)


def getDivergence():
	setOfHelices = set(file1Helices + file2Helices)

	for helix in setOfHelices:
		foundAndProcessIn('File1', helix)
		foundAndProcessIn('File2', helix)

	sumFrequency1 = 0.0
	sumFrequency2 = 0.0

	for frequency in file1Frequency:
		sumFrequency1 += frequency
	for frequency in file2Frequency:
		sumFrequency2 += frequency
	
	divergence_12 = 0.0
	divergence_21 = 0.0

	# convert frequencies into probabilities
	for i in range(len(setOfHelices)):
		file1Frequency[i] = float(file1Frequency[i])/sumFrequency1
		file2Frequency[i] = float(file2Frequency[i])/sumFrequency2

	for i in range(len(setOfHelices)):
		divergence_12 += (math.log(file1Frequency[i]/file2Frequency[i]))*file1Frequency[i]
		divergence_21 += (math.log(file2Frequency[i]/file1Frequency[i]))*file2Frequency[i] 

	print divergence_12, divergence_21


def kulbackLeiblerDivergenceWrapper():
	
	#Read the two files into data structure
	with open("temp1.txt", 'r') as fptr:
		file1 = fptr.readlines()[0:]
	with open("temp2.txt",'r') as fptr:
		file2 = fptr.readlines()[0:]

	# Some more parsing 
	#	
	for helix in file1:
		file1List.append(helix.rstrip('\n'))
	for helix in file2:
		file2List.append(helix.rstrip('\n'))
	for helix in file1List:
		file1Helices.append(helix.rsplit(' ',1)[0])
	for helix in file2List:
		file2Helices.append(helix.rsplit(' ',1)[0])

	getDivergence()

def parseInputFiles(file1, file2):
	cmd = "cat "+ file1 + " | grep Helix | sed -e ' s/.* is \(.*\) (.*) with freq \(\d*\)/\\1 \\2/' > temp1.txt"
	os.system(cmd)
	cmd = "cat "+ file2 + " | grep Helix | sed -e ' s/.* is \(.*\) (.*) with freq \(\d*\)/\\1 \\2/' > temp2.txt"
	os.system(cmd)
	kulbackLeiblerDivergenceWrapper()

def main():
	if(len(sys.argv) != 3):
		print ("Usage python Kulback-Leibler-Divergence.py [InputFile1] [InputFile2]")
		return
	file1 = sys.argv[1]
	file2 = sys.argv[2]
	parseInputFiles(file1, file2)
	# remove temporary parsed files
	#
	os.system("rm temp1.txt")
	os.system("rm temp2.txt")

if __name__ =="__main__":
	main();