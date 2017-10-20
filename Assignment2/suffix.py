from math import ceil
import math
def parse(txt):
	length = len(txt)
	start = []
	end = []
	titles = []
	count = 0
	title = 0
	string = ""
	for i in range(0,length):
		c = txt[i]
		if(title == 1 and c == '\n'):
			title = 0
			titles.append(string)
			string = ""		
		if(title == 1 and c != '\n'):
			string = string + c
		
		if(c == '\n'):
			count = count + 1
		else:
			count = 0
		if(count == 3):
			title = 1
			start.append(i+1)
	c = 1
	count = len(start)
	while(c < count):
		end.append(start[c])
		c = c + 1
	end.append(length-1)
	return (titles,start,end)
		
def suffixArray(txt):
	txt = txt + chr(0)
	N, tokens = len(txt), sorted(set(t for t in txt))

	equivalence = {t: i for i, t in enumerate(tokens)}

	c, r = [equivalence[t] for t in txt], [(0, 0, 0)]
	y = (int)(math.ceil(math.log(N,2)))+1	
	for i in range(1, y):
		n = 2 ** (i - 1)

		r = sorted([(c[j],  c[(j + n) % N], j) for j in range(N)])

		c[r[0][2]] = 0
		for j in range(1, N):
			c[r[j][2]] = c[r[j - 1][2]]
			if r[j][0:2] != r[j - 1][0:2]:
				c[r[j][2]] += 1

	return [result[2] for result in r][1:]        

import re
x=open("aesop.txt");
y=x.read();
y=y.replace("\n \n","\n\n")
y=y.replace("\n \n","\n\n")
y=y.replace("\n\n\n\n","\n\n\n");
y = re.sub('http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),#]|(?:%[0-9a-fA-F][0-9a-fA-F]))+'," ",y)
y = re.sub('ftp[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),#]|(?:%[0-9a-fA-F][0-9a-fA-F]))+'," ",y)
y=y.replace("?"," ")
y=y.replace('"'," ")
y=y.replace("."," ")
y=y.replace(","," ")
y=y.replace(";"," ")
y=y.replace(':'," ")
y=y.replace('!'," ")
y=y.replace(" '"," ")
y=y.replace("' "," ")
y=re.sub(" +"," ",y)

y=y.replace("(","")
y=y.replace(")","")
with open('aesop.txt', 'w') as myfile:
    myfile.write(y)
with open('aesop.txt', 'r') as myfile:
    string=myfile.read()
(titles,start,end) = parse(string)
length = (int)(input("Enter the length of the maximal palindrome:"))
string = string.replace("."," ")
string = string.replace(","," ")
string = string.replace(";"," ")
palin = []
palinIndex = []
palinTitle = []
count = 0
lentxt = len(string)
while(count < lentxt-length):
	s = ""
	x = count
	prev = ""
	next = ""
	space = 0
	for c in range(x,x+length):
		if(string[c] != ' '):
			s = s + string[c]
		else:
			space = 1
			break
	if(len(s.split()) <= 1 and space == 0):
		if(x != 0):
			prev = string[x-1]
		if(x+length < lentxt):
			next = string[x+length]
		s1 = s[::-1]
		sArray = suffixArray(s)
		sInvArray = suffixArray(s1)
		if(sArray == sInvArray and prev != next):
			pal = ""
			while(string[x] != ' ' and x >= 0):
				x = x - 1
			x = x + 1
			palinIndex.append(x)
			while(x < lentxt and string[x] != ' '):
				pal = pal + string[x]
				x = x + 1
			palin.append(pal)
	count = count + 1
for i in palinIndex:
	c = 0
	while(not(start[c]  <= i and end[c] >= i)):
		c = c + 1
	palinTitle.append(titles[c])
p = len(palin)
c = 0
print("Maximal Palindrome  ->   Title   ->   Index")   
for c in range(0,p):
	print("Maximal Palindrome:",palin[c])
	print("Story Title:",palinTitle[c])
	print("Index :",palinIndex[c])
	print("-------------------------------------------------------------------------")

