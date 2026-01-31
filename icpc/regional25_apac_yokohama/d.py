num = input()
length = len(num)

ans = 0
for pwr in range(0, length):
	small = 10 ** (pwr)
	big = int(num) - small
	cur = int(str(big) + str(small))
	ans = max(ans, cur)
print(ans)