def main():
    inputText = input("Text: ")
    letters = countLetters(inputText)
    words = countWords(inputText)
    sentences = countSentences(inputText)

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
    n = len(inputText)
    for i in range(0, n):
        if inputText[i].isspace():
            words += 1
    return words
    
def countSentences(inputText):
    sentences = 0
    n = len(inputText)
    for i in range(0, n):
        if inputText[i] == "." or inputText[i] == "!" or inputText[i] == "?":
            sentences += 1
    return sentences




main()