import sys

def compareStruct(fileP, fileN):
	tp = 0
	fp = 0
	fn = 0
	
	#reading the input file
	fptr = open(fileP,"r")
	pList = fptr.readlines()
	fptr.close()
	fptr = open(fileN,"r")
	nList = fptr.readlines()
	fptr.close()
	if(len(pList) != (len(nList)+1)):
		print "Sequence lengths do not match"
		return

	temp = []
	predicted = []
	native = []
	
	i=0
	for val in pList:
		i += 1
		if(i== 1):
			continue
		val = val.strip()
		predicted.append([x for x in val.split()])
	
	for val in nList:
		val = val.strip()
		native.append([x for x in val.split()])
	
	print native[0]
	print predicted[0]
	
	for i in range(len(native)):
		if(native[i][1] != predicted[i][1]):
			print "Nucleotide mismatch at sequence #["+str(i+1)+"]"
		if(native[i][2] == predicted[i][4] and native[i][2] != '0'):
			tp += 1
		if(predicted[i][4] != '0' and native[i][2] != predicted[i][4]):
			fp += 1
		if(native[i][2] != '0' and native[i][2] != predicted[i][4]):
			fn += 1
	print "\n"
	print "#tp #fp #fn: "+str(tp)+"  "+str(fp)+"  "+str(fn)
	ppv = tp/float(tp+fp)
	sens = tp/float(tp+fn)
	fmeasure = 2*ppv*sens/(ppv+sens)
	print "PPV Sens F-measure: "+ str(ppv) +"  "+ str(sens) + "  " +str(fmeasure)
	return

def main():
	
	if(len(sys.argv) != 3):
		print "Usage compare.py [predicted_file] [native_file]"
		return

	fileP = sys.argv[1]
	fileN = sys.argv[2]
	compareStruct(fileP, fileN)	

if __name__ =="__main__":
	main();
