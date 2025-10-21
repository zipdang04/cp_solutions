t = int(input())
for _ in range(1, t + 1):
	n, a, b = map(int, input().split())
	ans = [1] * (2*n-1) + [b]
	print("Case #{}:".format(_), end = ' ')
	print(*ans)