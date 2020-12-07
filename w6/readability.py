def main():
    inputText = input("Text: ")
    letters = countLetters(inputText)
    words = countWords(inputText)

def countLetters(inputText):
    letters = 0
    n = len(inputText)
    for i in range(n):
        letters += 1
    return letters

def countWords(inputText):
    words = 0
    if str(inputText[:1]).isalnum():
        words = 1
    # n = len(inputText)
    # for i in range(n):
    #     if

# main()