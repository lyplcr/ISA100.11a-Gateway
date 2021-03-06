#!/usr/bin/python
# open file
import string;
import re;
import sys;

def parseStringByPattern(line=[], pattern=""):
	print "pattern =%s" %(pattern)
	p = re.compile(pattern);
	print "line =%s" %(line);
	result = p.findall(line);
	print "result=%s" %(result)	
	return result;
	
def parseLine(file, line=[]):
	#pattern = '[a-fA-F0-9]{0,}[(][a-fA-F0-9]{0,}\([,]*[a-fA-F0-9]{0,}\)\1{0,}[)]';
	pattern = '[a-fA-Z0-9]{0,}[(][\,a-fA-Z0-9]{0,}[)]';
	result = parseStringByPattern(line, pattern);
	pattern = 'GraphID=[\s]*[0-9]*:[\s]*'
	graphIds = parseStringByPattern(line, pattern);		
	if(len(graphIds) > 0):
		pattern = '\d+'
		graphId = parseStringByPattern(graphIds[0], pattern);
		file.write('\nsubgraph cluster%d { \n' %(int(graphId[0])));	
		file.write("clusterrank=local\n  ");

		
		print "result=%s" %(result);
		for iter in result:
			pattern = '[a-fA-Z0-9]{1,3}';
			p = re.compile(pattern);
			nodes = parseStringByPattern(iter, pattern);	
			print nodes;
			file.write( '_%s_%d -> _%s_%d [color=red]\n' %(nodes[0],(int(graphId[0])), nodes[1], (int(graphId[0]))));
			for i in range(len(nodes) - 2):
				if (nodes[i+2] != "U0"):
					file.write( '_%s_%d -> _%s_%d \n' %(nodes[0], (int(graphId[0])), nodes[i+2], (int(graphId[0]))));
				
		file.write("}");
	
def main():
	line = sys.stdin.readline();
	pattern='[0-9]{2}[:][0-9]{2}[:][0-9]{2}[,][0-9]{3}';
	timestamp = parseStringByPattern(line, pattern);	
	filename = "networkNopology_timestamp.dot";
	file = open(filename , "w");
	file.write("digraph netWorkTopology {");
	while line:
		parseLine(file, line);
		line = sys.stdin.readline();
	file.write("}");	


if __name__ == "__main__":
    main()