def main():
    inputText = input("Text: ")
    letters = countLetters(inputText)
    words = countWords(inputText)
    sentences = countSentences(inputText)
    colemanLiauIndex(letters, words, sentences)

# Function to count letters
def countLetters(inputText):
    letters = 0
    n = len(inputText)
    for i in range(0, n):
        if inputText[i].isalnum():
            letters += 1
    return letters

# Function to count words
def countWords(inputText):
    words = 0
    if str(inputText[:1]).isalnum():
        words = 1
    n = len(inputText)
    for i in range(0, n):
        if inputText[i].isspace():
            words += 1
    return words

# Function to count sentences
def countSentences(inputText):
    sentences = 0
    n = len(inputText)
    for i in range(0, n):
        if inputText[i] == "." or inputText[i] == "!" or inputText[i] == "?":
            sentences += 1
    return sentences

# Function to analyze grade of input text
def colemanLiauIndex(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Special Cases
    # (1) Grade 16+
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")

main()