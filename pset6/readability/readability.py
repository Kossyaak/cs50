text = input("Text: ")
words = 0 
sentences = 0
letters = 0
l = len(text)
for i in range(l):
    ch = text[i]
    if(ch.isalpha()):
        letters += 1
    if(ch.isspace()):
        words += 1
    if(ch == '.' or ch == '!' or ch == '?'):
        sentences += 1
words += 1
L = (letters * 100.0) / words
S = (sentences *100.0) / words
index = int(round(0.0588 * L - 0.296 * S -15.8))
if(index < 1):
    print("Before Grade 1")
elif(index >= 16):
    print("Grade 16+")
else:
    print("Grade", index)
    
    
    
