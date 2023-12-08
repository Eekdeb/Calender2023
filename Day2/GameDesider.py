maxBlue = 14
maxRed = 12
maxGreen = 13

def checkImposableGame(str):
    #get the game nr
    gameRoundStr = str.split(":")
    gameNr = gameRoundStr[0].replace("Game ","")
    #get all the rounds in a list
    rounds = gameRoundStr[1].split(";")
    #foreach round check if the max color is reached
    imposableGame = False
    for round in rounds:
        colors = round.split(",")
        for color in colors:
            colorNr = color.split(" ")
            if("green" in colorNr[2] and int(colorNr[1]) > maxGreen):
                imposableGame = True
            if("blue" in colorNr[2] and int(colorNr[1]) > maxBlue):
                imposableGame = True
            if("red" in colorNr[2] and int(colorNr[1]) > maxRed):
                imposableGame = True
    if imposableGame:
        return 0
    return gameNr

test = "Game 11: 7 green, 11 red, 12 blue; 3 blue, 6 green, 6 red; 10 blue, 13 green; 1 red, 13 green, 9 blue; 2 blue, 2 red, 13 green; 2 red, 3 blue, 15 green"
#print("This!!" + str(checkImposableGame(test)))
input = open("C:/Users/A483349/Advent/Calender2023/Day2/input.txt")
#read next line
sum = 0
for str in input:
    gameNr = int(checkImposableGame(str))
    sum = sum + gameNr
print(sum)

2354
2696