# BBM103 Introduction to Programming Lab 1 - Fall 2017 - Programming Assignment 3 Starter Code
import sys
import re
'''
This program will save the human race if done properly, 
so please do your best to get 100 from this assignment. 
You can do it! :)
'''

# Opening the input files

hurap_file = open(sys.argv[1], "r")

schuckscii_file = open(sys.argv[2], "r")

virus_codes_file = open(sys.argv[3], "r")

# Mission 00: Decrypting the HuRAP
def binaryCript(x):
    temp = list(x)
    temp.remove(temp[0])
    sum = 0
    for i in range(0,len(temp)):
        if temp[i]=="0":
            temp[i] = "1"
        else:
            temp[i] = "0"
    temp = temp[::-1]
    for k in range(0,len(temp)):
        if temp[k] == "1":
            sum += 2 ** k
    return sum
schuckscii_str = schuckscii_file.read()
schuckscii = {k.split("\t")[1]:k.split("\t")[0] for k in schuckscii_str.split("\n")}
reversesc = {n : m for m,n in schuckscii.items()}
virus_c = virus_codes_file.read()
virus = {k.split(":")[0]:k.split(":")[1] for k in virus_c.split("\n")}
binaryhex = {
    "0000": "0","0001":"1","0010":"2","0011":"3","0100":"4","0101":"5","0110":"6","0111":"7","1000":"8","1001":"9","1010":"A","1011":"B","1100":"C",
    "1101":"D","1110":"E","1111":"F"
}
reversebin = { c : o for o,c in binaryhex.items()}
hurapbin = hurap_file.read()
hbinLx = []
hextostr = []
hbinL = hurapbin.split("\n")
crytp = []
for i in hbinL:
    if i[0] == "0":
        pass
    elif i[0]== "1":
        pass
    else:
        shibin = i
        hbinL.remove(i)
for i in range(0,len(hbinL)):
    hbinLx.append(re.findall("....",hbinL[i]))
for x in range(0,len(hbinLx)):
    for y in range(0,len(hbinLx[x])):
        hbinLx[x][y] = binaryhex[hbinLx[x][y]]
for x in range(0,len(hbinLx)):
    hbinLx[x] = "".join(hbinLx[x])
for i in range(0,len(hbinLx)):
    hextostr.append(re.findall("..",hbinLx[i]))
for z in range(0,len(hextostr)):
    for t in range(0,len(hextostr[z])):
        hextostr[z][t] = schuckscii[hextostr[z][t]]
for x in range(0,len(hextostr)):
    hextostr[x] = "".join(hextostr[x])
cag = schuckscii.keys()
cag = sorted(list(cag))
cag = cag[::-1]
kut = schuckscii.values()
kut = sorted(kut)
kur = kut[::-1]
for i in range(0,len(hbinLx)):
    crytp.append(re.findall("..",hbinLx[i]))
for b in range(0,len(crytp)):
    for t in range(0,len(crytp[b])):
        l = 0
        l = cag.index(crytp[b][t])
        l = ((l + binaryCript(shibin) + 1) % len(cag))
        crytp[b][t] = cag[l]
for z in range(0,len(crytp)):
    for t in range(0,len(crytp[z])):
        crytp[z][t] = schuckscii[crytp[z][t]]
for x in range(0,len(crytp)):
    crytp[x] = "".join(crytp[x])
vcrytp = crytp
vcrytp = "\n".join(vcrytp)
for s,i in virus.items():
    vcrytp = vcrytp.replace(s,i)
dcrypt = (vcrytp.split("\n"))
for i in range(0,len(dcrypt)):
    dcrypt[i] = re.findall(".",dcrypt[i])

for b in range(0,len(dcrypt)):
    for t in range(0,len(dcrypt[b])):
        l = 0
        l = kut.index(dcrypt[b][t])
        l = ((l - binaryCript(shibin) - 1) % len(kut))
        dcrypt[b][t] = kut[l]
dtohex = dcrypt[:]
for i in range(0,len(dcrypt)):
    dcrypt[i] = "".join(dcrypt[i])
for i in range(0,len(dtohex)):
    dtohex[i] = list(dtohex[i])
    for a in range(0,len(dtohex[i])):
        dtohex[i][a] = reversesc[dtohex[i][a]]
    dtohex[i] = "".join(dtohex[i])
dtobin= dtohex[:]
for i in range(0,len(dtobin)):
    dtobin[i] = list(dtobin[i])
    for v in range(0,len(dtobin[i])):
        dtobin[i][v] = reversebin[dtobin[i][v]]
    dtobin[i] = "".join(dtobin[i])


print("""*********************
     Mission 00 
*********************""", end = "\n\n")

print("""--- hex of encrypted code ---
-----------------------------""", end="\n\n")
print(*hbinLx,sep="\n")
# Your code which calculates and prints out the hexadecimal representation
# of HuRAP goes here

print("""\n--- encrypted code ----
-----------------------""", end="\n\n")
print(*hextostr,sep="\n")
# Your code which calculates and prints the encrypted character
# representation of HuRAP goes here

print("""\n--- decrypted code ---
----------------------""", end="\n\n")
print(*crytp,sep = "\n")
# Your code which decrypts and prints the
# HuRAP goes here

# Mission 01: Coding the virus

print("""\n*********************
     Mission 01 
*********************""", end="\n\n")
print(vcrytp,)
# Your code which transforms the original HuRAP and prints
# the virus-infected HuRAP goes here
	  
	  
# Mission 10: Encrypting the virus-infected HuRAP

print("""\n*********************
     Mission 10 
*********************""", end="\n\n")

print("""--- encrypted code ---
----------------------""", end="\n\n")
print(*dcrypt,sep="\n")
# Your code which encrypts and prints the encrypted character
# representation of the virus-infected HuRAP goes here

print("""\n--- hex of encrypted code ---
-----------------------------""", end="\n\n")
print(*dtohex,sep="\n")
# Your code which calculates and prints out the hexadecimal representation
# of virus-infected and encrypted HuRAP goes here

print("""\n--- bin of encrypted code ---
-----------------------------""", end="\n\n")
print(*dtobin,sep="\n")
# Your code which calculates and prints out the binary representation
# of virus-infected and encrypted HuRAP goes here

# Closing the input files

hurap_file.close()
schuckscii_file.close()
virus_codes_file.close()