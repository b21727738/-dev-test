import sys



inputfile = (open(sys.argv[1],"r",encoding='utf8')).read()
outputfile = open(sys.argv[2],"w")
inputlist = (inputfile.split("\n"))
inputlist = [inputlist[i].split("\t") for i in range(0,len(inputlist))]
inputlist = sorted(sorted(inputlist,key=lambda x: int(x[1])),key=lambda x: int(x[0]))
k = 1
x = 0
c = ""
print (inputlist)
for i in range(0,len(inputlist)):
    inputlist[i] = " ".join(inputlist[i])
while x < len(inputlist):
    cag = inputlist[x].index(" ")
    if c == inputlist[x][0:cag]:
        print (inputlist[x],file = outputfile)
        x += 1
    else:
        print ("Message", k,file = outputfile)
        print (inputlist[x],file = outputfile)
        cag = inputlist[x].index(" ")
        c = inputlist[x][0:cag]
        k += 1
        x += 1
outputfile.close()