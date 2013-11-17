import sys
import os

dot1Values = []
dot2Values = []

def compareDotValues():
	print dot1Values
	print dot2Values

def postProcess(inputFile_1, inputFile_2):
	cmd = "cat "+ inputFile_1 + " | grep tr | grep -v legend | sed -e 's#<tr><td>.*</td><td>\(.*\)</td><td>\(.*\)</td></tr>#\\1 \\2#g' > dot_1.txt" 
	os.system(cmd)
	cmd = "cat "+ inputFile_2 + " | grep tr | grep -v legend | sed -e 's#<tr><td>.*</td><td>\(.*\)</td><td>\(.*\)</td></tr>#\\1 \\2#g' > dot_2.txt"
	os.system(cmd)

	#Read the two values into data structure
	with open("dot_1.txt", 'r') as fptr:
		dot_1 = fptr.readlines()[0:]
	with open("dot_2.txt",'r') as fptr:
		dot_2 = fptr.readlines()[0:]	

	dot1List = []
	dot2List = []

	for helix in dot_1:
		dot1List.append(helix.rstrip('\n').split(','))

	for listObj in dot1List:
		for elem in listObj:
			dot1Values.append(elem.split(' '))

	for helix in dot_2:
		dot2List.append(helix.rstrip('\n').split(','))
	
	for listObj in dot2List:
		for elem in listObj:
			dot2Values.append(elem.split(' '))

	compareDotValues()

def main():
	if(len(sys.argv) != 3):
		print ("Usage python PostProcessDot.py [InputFile1.dot] [InputFile2.dot]")
		return
	inputFile_1 = sys.argv[1]
	inputFile_2 = sys.argv[2]
	postProcess(inputFile_1, inputFile_2)

if __name__ =="__main__":
	main();
