import time
import random
import math
def DFT(coeff):
	v=[]
	for i in range(0,n):
		v.append([])
	k=360/n;
	l=0;
	for i in range(0,n):
		a=round(math.cos(math.radians(l)),2);
		b=round(math.sin(math.radians(l)),2)
		c=complex(a,b)
		l=l+k
		for j in range(0,n):
			v[i].append(pow(c,j));

	point=[]
	for i in range(0,n):
		s=0
		for j in range(0,n):
			s=s+v[i][j]*coeff[j]
		point.append(s)

	for i in range(0,n):
		a=round(point[i].real,2);
		b=round(point[i].imag,2);
		point[i]=complex(a,b)

	f=open("DFT_Output.txt",'w');

	f.write("Point Values \n");
	for i in point:
		f.write(str(i));
		f.write('\n');
	f.close();

def findpow(x):
	i=0;
	while(x!=1):
		x=x/2;
		i=i+1;
	return i

def bitreversal(x):
	l=[]
	#print("len",len(x))
	#p=round(math.sqrt(len(x)));
	p=findpow(len(x));
	for i in range(0,len(x)):
		a=bin(i)
		#print(a)
		a=a[2:]
		if(len(a)<p):
			m=p-len(a);
			a='0'*int(m)+a
			
		#print(a)
		a=a[::-1]
		#print("a",a)
		b=int(a,2)
		l.append(x[b])
	return l;

def Iterative(coeff):
	coeff=bitreversal(coeff)
	n=len(coeff)
	for i in range(1,int(math.log(n,2))+1):
		m=int(pow(2,i))
		p=360/m;
		a=round(math.cos(math.radians(p)),2);
		b=round(math.sin(math.radians(p)),2)
		wn=complex(a,b);
		#print(wn)
		for k in range(0,n,m):
			w=1
			x=int(m/2)
			for j in range(0,x):
				t=w*coeff[k+j+x]
				u=coeff[k+j]
				coeff[k+j]=u+t;
				coeff[k+j+x]=u-t;
				w=w*wn	
	return coeff

def FFT(coeff):
	coeff=Iterative(coeff)
	#print(coeff)
	for i in range(0,len(coeff)):
		a=round(coeff[i].real,2);
		b=round(coeff[i].imag,2);
		coeff[i]=complex(a,b)

	f=open("FFT_Output.txt",'w');
	'''
	print("point values")
	for i in coeff:
		print(i);
	'''
	f.write("Point Values \n");
	for i in coeff:
		f.write(str(i));
		f.write('\n');
	f.close();









n=int(input("Enter the Size of the vector : "))
f=open("input.txt",'w');
for i in range(0,n):
	f.write(str(random.randrange(-5,6)));
	f.write('\n');
f.close();
f=open("input.txt",'r')

coeff=f.read();
coeff=coeff.split('\n');
coeff.remove('')
for i in range(0,n):
	coeff[i]=int(coeff[i])

f.close()
x1=time.time();
DFT(coeff[:]);
x2=time.time();
y1=time.time();
FFT(coeff[:]);
y2=time.time();
print("Time taken by DFT in sec:",x2-x1);
print("Time taken by FFT in sec:",y2-y1);







