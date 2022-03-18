while True:
    h = input("Введите высоту пирамиды от 1 до 8: ")
    if h.isdigit():
        if int(h) >= 1 and int(h) <= 8:
             l = int(h)
             break
for i in range(l):
    print((l - 1 - i) * " ", end = "")
    print((i + 1) * "#", end = "  ")
    print((i + 1) * "#")

