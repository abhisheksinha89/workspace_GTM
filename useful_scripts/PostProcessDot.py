import sys
import os

dot1Values = []
dot2Values = []

def enclosed(helix1_orig, helix2_orig):
	
	helix1 = map(int, helix1_orig)
	helix2 = map(int, helix2_orig)

	if(helix1[0] > helix2[0] and helix1[1] < helix2[1]):
		#test for enclosing
		i = helix2[2]
		for x in range(i):
			if(helix1[0]-i == helix2[0] and helix1[1]+i == helix2[1]):
				return True
	if(helix2[0] > helix1[0] and helix2[1] < helix1[1]):
		i = helix1[2]
		for x in range(i):
			if(helix2[0]-i == helix1[0] and helix2[1]+i == helix1[1]):
				return True
	return False


def compareDotValues():
	result_strict = 0.0
	result_moderate = 0.0

	for helix1 in dot1Values:
		for helix2 in dot2Values:
			if(helix1[0] == helix2[0] and helix1[1] == helix2[1] and helix1[2] == helix2[2]):
				result_strict += 1
				result_moderate += 1
				print helix1
				print helix2
				print ("+1\n")
				break
			elif(enclosed(helix1, helix2)):
				result_moderate += 0.5
				print helix1
				print helix2
				print ("+0.5\n")
				break
				
	print ("\n")
	print (">>Strict Score: %f" %(result_strict/len(dot1Values)))
	print (">>Mod Score: %f" %(result_moderate/len(dot1Values)))

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
	os.system("rm dot_1.txt")
	os.system("rm dot_2.txt")

if __name__ =="__main__":
	main();
