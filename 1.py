# My First Data Miner Program
import math
import sys
import operator
'''
This program
a) performs data cleaning process to remove missing attribute values present in the database.
b) calculates probability of being breast cancer of an imaginary patient
   by evaluationg his/her sample results provided as command-line argument.
'''
input1 = (sys.argv[1])
i1list = input1.split(',')
for i in range(0,9):
    if i1list[i] == "?":
        pass
    else:
        i1list [i] = i1list[i].split(":")
ops = {"<":operator.lt,"<=":operator.le,">":operator.gt,">=":operator.ge,"!=":operator.ne,"=":operator.eq}
# Starter code that reads database named 'WBC.data' and loads it into a dictionary 'dataDic'

# Reads the datafile. Note: WBC.data should be located where this file belongs.
dataFile = open('WBC.data','r').read()

# Makes data file ready to use by assigning every record to a dictionary class name dataDic.
dataDic = {i.split(',')[0]: i.split(',')[1:]  for i in dataFile.split('\n')}
# Do not alter any upper lines so that you do not get trouble in loading data file
# Performs data cleaning process, design the content and arguments depending on your design
def funDataClean():
    totalnumbers = []
    totalaver = 0
    totalcount = 0
    for x in range(0, 9):
        bAppVal = []
        bKnVal = 0
        bcount = 0
        mAppVal = []
        mKnVal = 0
        mcount = 0
        for y in dataDic:
            if (dataDic[y])[9] == "malignant":
                if (dataDic[y])[x] == "?":
                    mAppVal.append(y)
                else:
                    mKnVal += int((dataDic[y])[x])
                    mcount += 1
            else:
                if (dataDic[y])[x] == "?":
                    bAppVal.append(y)
                else:
                    bKnVal += int((dataDic[y])[x])
                    bcount += 1
        mAver = mKnVal / mcount
        bAver = bKnVal / bcount
        for z in mAppVal:
            (dataDic[z])[x] = int(round(mAver))
            totalnumbers.append(int(round(mAver)))
            totalcount += 1
        for k in bAppVal:
            (dataDic[k])[x] = int(round(bAver))
            totalnumbers.append(int(round(bAver)))
            totalcount += 1
    for v in totalnumbers:
        totalaver += int(v)
    totalaver /= totalcount
    funDataClean.totalave = totalaver
    return dataDic
newdataDic =  funDataClean()



# Performas step-wise search in WBC database, design the content and arguments depending on your design
def performStepWiseSearch():
    legitdata = []
    malignantc = 0
    benignc = 0
    for y in newdataDic:
        legit = True
        for x in range(0,9):
            if i1list[x] == "?":
                pass
            else:
                if ops[(i1list[x])[0]](int((newdataDic[y])[x]),int((i1list[x])[1])) == True:
                    pass
                else:
                    legit = False
        if legit == True:
            legitdata.append(y)
    for z in legitdata:
        if (newdataDic[z])[9] == "malignant":
            malignantc += 1
        else:
            benignc += 1
    performStepWiseSearch.malignantc = malignantc
    performStepWiseSearch.benignc = benignc
    return malignantc / (malignantc + benignc)

performStepWiseSearch()
# 1st phase: Cleaning WBC Database

print ('The average of all missing values is  : ' + '{0:.4f}'.format(funDataClean.totalave))

# 2nd phase: Retrieving knowledge from WBC dataset

print('\nTest Results:\n'
      '----------------------------------------------'
      '\nPositive (malignant) cases            : ' + str(performStepWiseSearch.malignantc) +
      '\nNegative (benign) cases               : ' + str(performStepWiseSearch.benignc) +
      '\nThe probability of being positive     : ' + '{0:.4f}'.format(performStepWiseSearch()) +
      '\n----------------------------------------------')
	  
	  
# end of the 1.py file