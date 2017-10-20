import string as st
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

p = transition_function("http")
q = transition_function("ftp")
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
with open('aesopMod.txt', 'w') as myfile:
	for s in words:
		i = string_matching_FSA(s,p,4)
		j = string_matching_FSA(s,q,3)
		if(i == -1 and j == -1):
			myfile.write(s)
			myfile.write(" ")
		else:
			infected.append(s)
for j in infected:
	print(str(j)+"\n")


