inputText = input("Text: ")
letters = countLetters(inputText)

def countLetters(inputText):
    letters = 0
    n = len(inputText)
    for i in range(n):
        letters += 1
    return letters