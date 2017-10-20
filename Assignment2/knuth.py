import re 
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
	prefix_Arr=Prefix_fun(p);
	k=-1;
	for i in range(0,n):
		while(k>-1 and (t[i]!=p[k+1])):
			k=prefix_Arr[k];	
		if(p[k+1]==t[i]) :
			k=k+1;
		if(k+1==m):
			occurence.append(i-k);
			k=prefix_Arr[k];
	return occurence;
	
def Find_string():
	x=open("aesop.txt");
	#x=open("sample.txt");
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
	b=int(input("Do you want the pattern search to be \n 1.Between Two strings 2.Between two indices Enter 1 or 2 : "));
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

	#print(l);
	occur=(KMP_Matcher(l,p));
	n=len(occur)
	i=0;
	while(i<n):
		occur[i]=occur[i]+m
		i=i+1;
	print(occur)
	print(t.index(p));
	
'''
#t=input("Enter the Text : ");
x=open("AESOP_TALES.txt");
p=input("Enter The Pattern : ");
t=x.read();
t.index(p);
print(KMP_Matcher(t,p));
print(t.index(p));
'''
Find_string();
#Find_string();			
