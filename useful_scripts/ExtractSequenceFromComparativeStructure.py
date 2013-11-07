import sys

def MakeSequenceFromComparative(ComparativeFile, SequenceFile):
	with open(ComparativeFile, 'r') as fptr:
		comparativeFile = fptr.readlines()[5:]
	
	# getting the nucleotides from the file
	#
	print comparativeFile[10].split(' ',len(comparativeFile[10]))

	index = 5
	nucleotides = []
	for line in comparativeFile:
		if(line.split(' ',len(line))[index] == ''):
			index -= 1
		nucleotides.append(line.split(' ',len(line))[index])
	
	# write the nucleotides into sequence file
	#
	with open(SequenceFile, 'w') as fptr:
		for nucleotide in nucleotides:
			fptr.write(nucleotide)

def main():
	if(len(sys.argv) != 3):
		print ("Usage python ExtractSequenceFromComparativeStructure.py [ComparativeFile] [SequenceFile]")
		return
	ComparativeFile = sys.argv[1]
	SequenceFile = sys.argv[2]
	MakeSequenceFromComparative(ComparativeFile, SequenceFile)
	
	
if __name__ =="__main__":
	main();
