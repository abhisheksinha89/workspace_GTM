import sys

def main():
	fp = open(sys.argv[1])
	offset = float(sys.argv[2])
	readList = fp.readlines()
	fp.close()
	vals = []
	for x in readList:
		vals.append([float(z) for z in x.split()])

	numBuckets = int((max(vals)[0]-min(vals)[0])/offset) + 1	
	print numBuckets
	bucket = [0] * numBuckets
	for x in vals:
		index = int((x[0] - min(vals)[0])/offset)
		bucket[index] += 1
	print "offset: "+ str(offset)
	print "min: "+ str(min(vals)[0])
	for x in range(len(bucket)):
		print	str(bucket[x])

	m = 0.6
	print int((m-min(vals)[0])/offset)
	r = int((m - min(vals)[0])/offset)
	print r

if __name__ == "__main__":
	main();
