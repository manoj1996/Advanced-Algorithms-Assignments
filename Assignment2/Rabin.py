
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


	
def Find_string():
	x=open("aesop.txt");
	#x=open("sample.txt");
	t=x.read();
	b=int(input("Do you want the pattern search to be \n 1.Between Two strings 2.Between two indices \nEnter 1 or 2 : "));
	if(b==1):
		print("Enter the starting and ending string between which you want to find the pattern");
		s1=input("First String : ");
		s2=input("Second String : ");
		p=input("Enter The Pattern : ");
		m1=t.index(s1);
		m2=t.index(s2);
		m=m1+len(s1)
		l=t[m:m2]
	else:
		print("Enter the starting and ending index between which you want to find the pattern");
		m=int(input("First index : "));
		s2=int(input("Second index : "));
		p=input("Enter The Pattern : ");
		l=t[m:s2]

	#print(l);
	occur=(robin(l,p,255,251));
	n=len(occur)
	i=0;
	while(i<n):
		occur[i]=occur[i]+m
		i=i+1;
	print(occur)
	#print(t.index(p));
	#print(t[occur[1]])

Find_string();
#Find_string();			
#t=input("Enter the Text : ");
'''
p=input("Enter The Pattern : ");
x=open("AESOP_TALES.txt");
t=x.read();
print(t.index(p));
print(robin(t,p,26,23));	
'''		 
