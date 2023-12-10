input = open("C:/Users/Eek/hobby/Calende_2023/Day4/input.txt")
#input = open("C:/Users/Eek/hobby/Calende_2023/Day4/exampleinput.txt")


def splitAndSkit(str):
    #get the game nr
    str = str.strip()
    gameRoundStr = str.split(":")
    gameNr = gameRoundStr[0].replace("Card ","")
    #get all the rounds in a list
    winNrandGottenNr = gameRoundStr[1].split("|")
    winNr = winNrandGottenNr[0].split(" ")
    winNr = [ x for x in winNr if x.isdigit() ]
    
    gottenNr = winNrandGottenNr[1].split(" ")
    gottenNr = [ x for x in gottenNr if x.isdigit() ]
    return int(gameNr), winNr, gottenNr

def getWinners(winNr,gottenNr):
    value = 0
    for number in winNr:
        if(gottenNr.__contains__(number)):
                value += 1
    return value

resultingPoints = 0
numberOfTickets = [1]*220
for str in input:

    gameNr,winNr,gottenNr = splitAndSkit(str)

    resultingPoints = getWinners(winNr,gottenNr)
    print(resultingPoints)
    for i in range(resultingPoints):
     if(int(gameNr)+i < len(numberOfTickets)):
        numberOfTickets[gameNr+i] += 1*numberOfTickets[gameNr-1]
    print(numberOfTickets)

alltickets = 0
for tickets in numberOfTickets:
    alltickets += tickets
print(alltickets)
