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
print(y)
#y=re.sub("[0-9]","",y);
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


'''
for i in l:
	print(i)
	print()
'''
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
	

def robin(t,p,d,q):
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
	while(i<m):
		x=(x*d+ord(t[i]))%q;
		y=(y*d+ord(p[i]))%q;
		i=i+1;
	for s in range(0,n-m+1)	:
		if(x==y):	
			j=0;
			while(j<m and (t[s+j]==p[j])):
				j=j+1;
			if(j==m):
				occurence.append(s);
											
		if(s < n-m):
			x=((x-ord(t[s])*h)*d+ord(t[s+m]))%q;
	return occurence;

'''
w=dict()
for i in l:
	if(i[0]=='The Wolf in Sheeps Clothing '):
		a=i[1].split(" ");
		for j in a:
			if j not in w:
				w[j]=0
				n=len(robin(i[1],j+" ",26,23))
				w[j]=w[j]+n	
print(w)
'''	

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
				n=len(robin(b,k+' ',255,251));						
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





			
		
