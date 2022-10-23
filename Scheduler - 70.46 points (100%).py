MOD = 1000000000 + 7

inp = input().split()
n = int(inp[0])
m = int(inp[1])

x = [int(i) for i in input().split()]

if (m == 1):
    sm = 0
    for i in x:
        sm += pow(2, i, MOD)
        sm %= MOD
    print(sm)
else:
    print(pow(2, max(x), MOD))
