import sys
import os

def postProcess(inputFile, outputFile):
	cmd = "cat "+ inputFile + " | grep tr | grep -v legend | sed -e 's#<tr><td>.*</td><td>\(.*\)</td><td>\(.*\)</td></tr>#\\1 \\2#g' > " + outputFile
	print cmd
	os.system(cmd)

def main():
	if(len(sys.argv) != 3):
		print ("Usage python PostProcessDot.py [InputFile.dot] [OutputFile]")
		return
	inputFile = sys.argv[1]
	outputFile = sys.argv[2]
	postProcess(inputFile, outputFile)

if __name__ =="__main__":
	main();
