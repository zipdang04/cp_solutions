t = int(input())
for _ in range(t):
	p, q = map(int, input().split())
	k = 3*p-2*q
	if k >= 0 and k <= p and k < q:
		print("Bob")
		continue
	print("Alice")
