import sys
wordstring = sys.argv[1]
wordlist = list(wordstring)
guessstring = sys.argv[2]
guesslist = guessstring.split(",")
secretword = ["-"]
leng = len(wordstring)
secretword = secretword * leng
mode = True
guess = 5
used = []
emp = ("--------------------------------------------")
print(" You have",guess,"guesses left")
print (secretword)
print(emp)
for x in guesslist:
    if x in used:
        found = 1
        mode = not mode
        guess -= 1
    else:
        if mode == True :
            if x in wordlist:
                used.append(x)
                for y in range(0,leng):
                    if x == wordstring[y]:
                        secretword[y] = x
                        found = 2
            else:
                found = 3
                mode = not mode
                guess -= 1
        else:
            if x in wordlist:
                found = 4
                guess -= 1
            else:
                found = 5
                mode = not mode
    if found == 1:
        print ("Guessed word:", x , "is used in IN mode. The game turned into OUT mode")
        print(" You have", guess, "guesses left")
        print (secretword)
        print (emp)
    elif found == 2:
        print("Guessed word:", x, "You are in IN mode")
        print(" You have", guess, "guesses left")
        print (secretword)
        print (emp)
    elif found == 3:
        print ("Guessed word:",x," The game turned into OUT mode")
        print(" You have",guess,"guesses left")
        print (secretword)
        print (emp)
    elif found == 4:
        print("Guessed word:", x , "You are in OUT mode")
        print(" You have", guess, "guesses left")
        print (secretword)
        print (emp)
    elif found == 5:
        print ("Guessed word:",x, " The game turned into IN mode")
        print(" You have", guess, "guesses left")
        print (secretword)
        print (emp)
if wordlist == secretword:
    print("You won the game")
else:
    print("You finished all letters\nYou lost the game")