t = int(input())
for _ in range(1, t+1):
	n = int(input())
	a = list(map(int, input().split()))
	ans = 0
	for i in range(0, n-1):
		ans = max(ans, abs(a[i+1]-a[i]))
	print("Case #{}: {}".format(_, ans))