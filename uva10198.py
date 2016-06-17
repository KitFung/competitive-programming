dp = [0, 2, 5, 13];

def dodp():
    for i in range(4, 1001):
        dp.append(dp[i-1]*2 + dp[i-2] + dp[i-3])

dodp()
while True:
    try:
        a = int(input())
        print(dp[a])
    except EOFError:
        break
