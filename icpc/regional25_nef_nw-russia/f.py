s, c = input().split()
lenS = len(s)
lenC = len(c)
c = int(c)

found = False
for lenA in range(1, lenS):
    lenB = lenS - lenA
    if abs(lenA - (lenB + lenC)) <= 2:
        a = s[:lenA]
        b = s[lenA:]
        if b[0] == "0":
            continue
        a = int(a)
        b = int(b)
        if b * c == a:
            print(a, b)
            found = True
    if found:
        break
