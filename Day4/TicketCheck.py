#input = open("C:/Users/Eek/hobby/Calende_2023/Day4/input.txt")
input = open("C:/Users/Eek/hobby/Calende_2023/Day4/exampleinput.txt")


def splitAndSkit(str):
    #get the game nr
    str = str.strip()
    gameRoundStr = str.split(":")
    gameNr = gameRoundStr[0].replace("Game ","")
    #get all the rounds in a list
    winNrandGottenNr = gameRoundStr[1].split("|")
    winNr = winNrandGottenNr[0].split(" ")
    winNr = [ x for x in winNr if x.isdigit() ]
    
    gottenNr = winNrandGottenNr[1].split(" ")
    gottenNr = [ x for x in gottenNr if x.isdigit() ]
    return gameNr, winNr, gottenNr

def getWinners(winNr,gottenNr):
    value = 0
    for number in winNr:
        if(gottenNr.__contains__(number)):
            if value == 0:
                value = 1
            else:
                value = value*2
    return value

resultingPoints = 0
for str in input:

    gameNr,winNr,gottenNr = splitAndSkit(str)

    resultingPoints += getWinners(winNr,gottenNr)

print(resultingPoints)
