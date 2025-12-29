# import sys
def cal(L, R):
	ans = R // 3 - (L-1) // 3
	if L <= 3 <= R:
		ans -= 1
	for l in range(1, 18+1):
		if l % 2 == 1:
			num = int("6" + "9"*l)
			if L <= num <= R:
				ans -= 1
			num = int("9"*l)
			if L <= num <= R:
				ans -= 1
		else:
			num = int("3" + "9"*l)
			if L <= num <= R:
				ans -= 1
	return ans

q = int(input())
for _ in range(q):
	L, R = map(int, input().split())
	print(cal(L, R))