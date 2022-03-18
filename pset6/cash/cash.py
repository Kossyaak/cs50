from cs50 import get_float

while True:
    doll = get_float("Сдача которую нужно выдать: ")
    if doll >= 0:
        break
cent = round(doll * 100)
res25 = cent / 25
res10 = cent % 25
res5 = res10 % 10
res1 = res5 % 5
total = int(res25) + int(res10 / 10) + int(res5 / 5) + res1
print(total)