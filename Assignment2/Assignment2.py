import re
import time
inp=0;
def Prefix_fun(p):
	m=len(p);
	prefix_Arr=[-1]*(m)
	k=-1;# for 0 char match
	for i in range(1,m):
		while(k>-1 and (p[k+1] != p[i])) :
			k=prefix_Arr[k];
		if(p[k+1]==p[i]):
			k=k+1;
		prefix_Arr[i]=k;
	return prefix_Arr

def KMP_Matcher(t,p):
	n=len(t);
	m=len(p)
	occurence=[];
	x=time.time()
	prefix_Arr=Prefix_fun(p);
	y=time.time();
	if(inp==2):
		print("Preprocessing time in Seconds: ",y-x)	
	k=-1;
	x=time.time()
	for i in range(0,n):
		while(k>-1 and (t[i]!=p[k+1])):
			k=prefix_Arr[k];	
		if(p[k+1]==t[i]) :
			k=k+1;
		if(k+1==m):
			occurence.append(i-k);
			k=prefix_Arr[k];
	y=time.time()
	if(inp==2):
		print("Search time in Seconds: ",y-x)
	return occurence;
	

def rabin(t,p,d,q):
	n=len(t);
	m=len(p);
	i=1;
	h=1;
	occurence=[];
	while(i<m):
		h=h*d;
		i=i+1;	
	x=0;#text value
	y=0;#pattern value
	i=0;
	t1=time.time();
	while(i<m):
		x=(x*d+ord(t[i]))%q;
		y=(y*d+ord(p[i]))%q;
		i=i+1;
	t2=time.time();
	if(inp==2):
		print("Preprocessing time in Seconds: ",t2-t1)
	t1=time.time();
	for s in range(0,n-m+1)	:
		if(x==y):	
			j=0;
			while(j<m and (t[s+j]==p[j])):
				j=j+1;
			if(j==m):
				occurence.append(s);
											
		if(s < n-m):
			x=((x-ord(t[s])*h)*d+ord(t[s+m]))%q;
	t2=time.time();
	if(inp==2):
		print("Search time in Seconds: ",t2-t1)
	return occurence;

class Node(object):
    """
	This is a general node in the suffix tree
    	suffix_node -> the index of a node with a matching suffix, representing a suffix link.
        -1 indicates this node has no suffix link.
    """
    def __init__(self):
        self.suffix_node = -1   

class Edge(object):
    """
		An edge in the suffix tree.    
		first_char_index -> index of start of string part represented by this edge
		last_char_index -> index of end of string part represented by this edge
		source_node_index -> index of source node of edge
		dest_node_index -> index of destination node of edge
    """
    def __init__(self, first_char_index, last_char_index, source_node_index, dest_node_index):
        self.first_char_index = first_char_index
        self.last_char_index = last_char_index
        self.source_node_index = source_node_index
        self.dest_node_index = dest_node_index
        
    @property
    def length(self):
        return self.last_char_index - self.first_char_index


class Suffix(object):
    """
		Represents a suffix from first_char_index to last_char_index.    
		source_node_index -> index of node where this suffix starts
		first_char_index -> index of start of suffix in string
		last_char_index -> index of end of suffix in string
    """
    def __init__(self, source_node_index, first_char_index, last_char_index):
        self.source_node_index = source_node_index
        self.first_char_index = first_char_index
        self.last_char_index = last_char_index
        
    @property
    def length(self):
        return self.last_char_index - self.first_char_index
                
    def explicit(self):
        """
			A suffix is explicit if it ends on a node. first_char_index is set greater than last_char_index to indicate this.
        """
        return self.first_char_index > self.last_char_index
    
    def implicit(self):
        return self.last_char_index >= self.first_char_index

class SuffixTree(object):
    """
		A suffix tree for string matching. Uses Ukkonen's algorithm for construction.
    """
    def __init__(self, string, case_insensitive=False):
        self.string = string
        self.case_insensitive = case_insensitive
        self.N = len(string) - 1
        self.nodes = [Node()]
        self.edges = {}
        self.active = Suffix(0, 0, -1)
        if self.case_insensitive:
            self.string = self.string.lower()
        for i in range(len(string)):
            self._add_prefix(i)
    

    def _add_prefix(self, last_char_index):
        """The construction method."""
        last_parent_node = -1
        while True:
            parent_node = self.active.source_node_index
            if self.active.explicit():
                if (self.active.source_node_index, self.string[last_char_index]) in self.edges:
                    # prefix is already in tree
                    break
            else:
                e = self.edges[self.active.source_node_index, self.string[self.active.first_char_index]]
                if self.string[e.first_char_index + self.active.length + 1] == self.string[last_char_index]:
                    # prefix is already in tree
                    break
                parent_node = self._split_edge(e, self.active)
        

            self.nodes.append(Node())
            e = Edge(last_char_index, self.N, parent_node, len(self.nodes) - 1)
            self._insert_edge(e)
            
            if last_parent_node > 0:
                self.nodes[last_parent_node].suffix_node = parent_node
            last_parent_node = parent_node
            
            if self.active.source_node_index == 0:
                self.active.first_char_index += 1
            else:
                self.active.source_node_index = self.nodes[self.active.source_node_index].suffix_node
            self._canonize_suffix(self.active)
        if last_parent_node > 0:
            self.nodes[last_parent_node].suffix_node = parent_node
        self.active.last_char_index += 1
        self._canonize_suffix(self.active)
        
    def _insert_edge(self, edge):
        self.edges[(edge.source_node_index, self.string[edge.first_char_index])] = edge
        
    def _remove_edge(self, edge):
        self.edges.pop((edge.source_node_index, self.string[edge.first_char_index]))
        
    def _split_edge(self, edge, suffix):
        self.nodes.append(Node())
        e = Edge(edge.first_char_index, edge.first_char_index + suffix.length, suffix.source_node_index, len(self.nodes) - 1)
        self._remove_edge(edge)
        self._insert_edge(e)
        self.nodes[e.dest_node_index].suffix_node = suffix.source_node_index  ### need to add node for each edge
        edge.first_char_index += suffix.length + 1
        edge.source_node_index = e.dest_node_index
        self._insert_edge(edge)
        return e.dest_node_index

    def _canonize_suffix(self, suffix):
        """
			This canonizes the suffix, walking along its suffix string until it is explicit or there are no more matched nodes.
        """
        if not suffix.explicit():
            e = self.edges[suffix.source_node_index, self.string[suffix.first_char_index]]
            if e.length <= suffix.length:
                suffix.first_char_index += e.length + 1
                suffix.source_node_index = e.dest_node_index
                self._canonize_suffix(suffix)
 

    # Public methods
    def find_substring(self, substring):
        """
			Returns the index of substring in string or -1 if it is not found.
        """
        if not substring:
            return -1
        if self.case_insensitive:
            substring = substring.lower()
        curr_node = 0
        i = 0
        while i < len(substring):
            edge = self.edges.get((curr_node, substring[i]))
            if not edge:
                return -1
            ln = min(edge.length + 1, len(substring) - i)
            if substring[i:i + ln] != self.string[edge.first_char_index:edge.first_char_index + ln]:
                return -1
            i += edge.length + 1
            curr_node = edge.dest_node_index
        return edge.first_char_index - len(substring) + ln
        
def patternSuffix(txt,pat,start,end):
	"""
		Checks if the pattern is a part of the input string
	"""
	length = len(pat)
	lcp = []
	s = start
	sumTime = 0
	x1 = time.time()
	sub = SuffixTree(txt)
	x2 = time.time()
	if(inp==2):
		print("Pre processing time in sec:",x2-x1)
	while(s <= end-length):
		search = txt[s:s+length]
		tree = SuffixTree(search)
		t1 = time.time()
		index = tree.find_substring(pat)
		t2 = time.time()
		if(index != -1):
			sumTime = sumTime +(t2-t1)
			lcp.append(index+s)
			s = s + length
		else:
			s = s + 1
	if(inp==2):
		print("Search time in seconds:",sumTime)	
	return lcp



def CrossIndex(y,algo):
	y=y.split("\n\n\n")
	t=y[0]
	y=y[1:]
	l=[]

	for i in y:
		a=i.split("\n\n",1)
		l.append(a);

	i=0;


	while(i<len(l)):
		n=len(l[i])
		if(n==1):
			l[i-1][1]=l[i-1][1]+l[i][0]
			l.remove(l[i]);
		i=i+1;


	for i in l:
		i[0]=i[0].replace("\n","");
		i[1]=i[1].replace("\n"," ");
		#i[1]=i[1].replace("\n\n"," ");
		i[1]=re.sub(" '"," ",i[1])
		i[1]=re.sub("' "," ",i[1])
		i[1]=re.sub(" +"," ",i[1])
		n=len(i[1])
		if(i[1][n-1]!=' '):
			i[1]=i[1]+" ";


	words=dict();
	for i in l:
		b=i[0]+i[1];
		a=b.split(" ");
		for k in a:

				if k not in words:
					words[k]=dict()
					words[k]['occur']=0;
				if i[0] not in words[k] :
					words[k][i[0]]=0;
					if(algo==1):			
						n=len(rabin(b,' '+k+' ',255,251));	
					elif(algo==2):
						n=len(KMP_Matcher(b,' '+k+' '))	
					elif(algo==3):
						n=len(patternSuffix(b,' '+k+' ',0,len(b)));	
					else:
						exit();			
					#n=len(KMP_Matcher(b,k+' '))
					words[k]['occur']=words[k]['occur']+n;
					words[k][i[0]]=words[k][i[0]]+n;

	for k in t.split(" "):
				if k not in words:
					words[k]=dict();
					words[k]['occur']=len(KMP_Matcher(b,k+' '));

	
	if '' in words:
		del words[''];

			
	for i in sorted(words):	
		print(i," 'Occururence' :",words[i]['occur'],words[i]);
		print()

def fsa():
	import string as st
	import os
	def string_matching_FSA(T, trans, m):
	    """
	    T: is the input sequence;
	    trans: is the transition function that define the pattern P we need to look for;
	    m: lenght of the pattern
	    """
	    s = 0
	    for i,c in enumerate(T):
	        s = trans[s][c]
	        if s == m:
	            return i-m+1
	
	    return -1
	
	def transition_function(P):
	    alphabet = st.ascii_letters+st.punctuation+st.digits+st.whitespace
	    m = len(P)
	    trans = [{c:0 for c in alphabet} for i in range(m)]
	    for s in range(m):
	        for c in alphabet:
	            k = min(m, s+1)
	            while (P[:s]+c)[-k:] != P[:k]:
	                k-=1
	
	            trans[s][c]=k

	    return trans
	t1 = time.time()
	p = transition_function(" http")
	q = transition_function(" ftp")
	t2 = time.time()
	print("Preprocessing time in seconds:",(t2-t1))
	infected = []
	with open('aesop.txt', 'r') as myfile:
	    string=myfile.read()

	string=string.replace("\n \n","\n")
	string=string.replace("\n \n","\n")
	string=string.replace("\n\n\n\n","\n")	
	string=string.replace("\n\n\n","\n")
	string=string.replace("\n\n","\n")
	string=string.replace("  "," ")
	string = string.replace(","," ")
	string = string.replace(";"," ")
	words = list(string.split())
	x1 = time.time()
	with open('aesopMod.txt', 'w') as myfile:
		for s in words:
			i = string_matching_FSA(s,p,4)
			j = string_matching_FSA(s,q,3)
			if(i == -1 and j == -1):
				myfile.write(s)
				myfile.write(" ")
			else:
				infected.append(s)
	x2 = time.time()
	print("Execution time in seconds:",(x2-x1))
	size_bef=os.path.getsize("./aesop.txt");
	size_af=os.path.getsize("./aesopMod.txt");
	print("File size Before :",size_bef);
	print("File size After :",size_af)

	return infected

def MaximalPalindrome(y):

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
	with open('aesopMod1.txt', 'w') as myfile:
    		myfile.write(y)
	with open('aesopMod1.txt', 'r') as myfile:
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
		




def Main():
	global inp;
	x=open("aesop.txt");
	t=x.read();
	t = t.replace("."," ")
	t = t.replace(","," ")
	t = t.replace(";"," ")
	t = t.replace("\n \n","\n\n")
	t = t.replace("\n \n","\n\n")
	t = t.replace("\n\n\n\n","\n\n\n")
	t = re.sub('http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),#]|(?:%[0-9a-fA-F][0-9a-fA-F]))+'," ",t)
	t = re.sub('ftp[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),#]|(?:%[0-9a-fA-F][0-9a-fA-F]))+'," ",t)
	t = t.replace("?"," ")
	t = t.replace('"'," ")
	t = t.replace("."," ")
	t = t.replace(","," ")
	t = t.replace(";"," ")
	t = t.replace(':'," ")
	t = t.replace('!'," ")
	t = t.replace(" '"," ")
	t = t.replace("' "," ")
	t = re.sub(" +"," ",t)
	t = t.replace("(","")
	t = t.replace(")","")
	inp=int(input("1.Find the length of the text with URL infection list \n2.Find Pattern\n3.Build cross Index\n4.Maximal Palindrome\n5:Exit\n"))
	while(inp != 5):
		if(inp==1):
			infected = fsa()
			print("URL infection list:")
			for i in infected:
				print(i)
		elif(inp==2):
			print("Enter the algorithm\n")
			algo=int(input("1.Rabin-Karp\n2.Knuth-Morris-Pratt\n3.Suffix Tree\n")) 
			b=int(input("Do you want the pattern search to be \n1.Between two strings \n2.Between two indices\n"));
			if(b==1):
				print("Enter the staring and ending string in which you want to find the pattern");
				s1=input("First String : ");
				s2=input("Second String : ");
				p=input("Enter The Pattern : ");
				m1=t.index(s1);
				m2=t.index(s2);
				m=m1+len(s1)
				l=t[m:m2]
			else:
				print("Enter the staring and ending index in which you want to find the pattern");
				m=int(input("First index : "));
				s2=int(input("Second index : "));
				p=input("Enter The Pattern : ");
				l=t[m:s2]

			if(algo==1):
				occur=(rabin(l,p,255,251));
			elif(algo==2):
				occur=(KMP_Matcher(l,p));
			else:
				occur=(patternSuffix(l,p,0,len(l)))
			n=len(occur)
			i=0;
		
			while(i<n):
				occur[i]=occur[i]+m
				i=i+1;
			print(occur)
		
			print("Number of times the pattern has occured : ",n)
		elif(inp==3):
			print("Enter the algorithm\n")
			algo=int(input("1.Rabin-Karp\n2.Knuth-Morris-Pratt\n3.Suffix Tree\n")) 
			CrossIndex(t,algo)
		elif(inp==4):
			MaximalPalindrome(t)
		inp=int(input("\n\n1.Find the length of the text with URL infection list\n2.Find Pattern\n3.Build cross Index\n4.Maximal Palindrome\n5:Exit\n"))			
Main();
		


			
		
