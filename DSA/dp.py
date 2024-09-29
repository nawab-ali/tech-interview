# Common dynamic programming problems

# Find the minimum number of operations required to reach a number N starting from 0, using the allowed operations
# of either:
#	1.	Add 1:  x -> x + 1 
#	2.	Multiply by 2:  x -> x * 2
# O(n)
def min_ops_to_N(N: int) -> int:
    if N == 0:
        return 0
    
    # dp[i] is the minimum number of operations required to reach the number i from 0
    dp = [float('inf')] * (N + 1)
    dp[0] = 0

    for i in range(1, N + 1):
        dp[i] = dp[i - 1] + 1
        if i % 2 == 0:
            dp[i] = min(dp[i], dp[i // 2] + 1)

    return dp[N]

# Given a set of coin denominations and an amount, find the minimum number of coins required to make that amount.
def coin_change(coins: list, amount: int) -> int:
    # dp[i] represents the minimum number of coins needed to make the amount i
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0

    for coin in coins:
        for i in range(coin, amount + 1):
            dp[i] = min(dp[i], dp[i - coin] + 1)
    
    return dp[amount] if dp[amount] != float('inf') else -1

# The problem of finding the Longest Common Substring between two strings involves identifying the longest contiguous
# sequence of characters that appears in both strings.
def longest_common_substring(s1: str, s2: str) -> int:
    n = len(s1)
    m = len(s2)
    max_len = 0

    # dp[i][j] represents the length of the longest common substring ending at s1[i-1] and s2[j-1]
    dp = [[0] * (m + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if s1[i - 1] == s2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
                max_len = max(max_len, dp[i][j])
    
    return max_len

# In the Edit Distance problem, the goal is to determine the minimum number of operations required to convert one
# string into another.
def edit_distance(s1: str, s2: str) -> int:
    n = len(s1)
    m = len(s2)

    # dp[i][j] represents the minimum edit distance between the first i characters of the first string and the first
    # j characters of the second string.
    dp = [[0] * (m + 1) for _ in range(n + 1)]

    # Initialize the table    
    for i in range(n + 1):
        dp[i][0] = i # Deleting all characters to match an empty string
    
    for j in range(m + 1):
        dp[0][j] = j # Inserting all characters to match an empty string
        
    # Fill the DP table
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if s1[i - 1] == s2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                dp[i][j] = min(dp[i][j - 1], # Insertion
                               dp[i - 1][j], # Deletion
                               dp[i - 1][j - 1]) + 1  # Substitution
    
    return dp[n][m]

if __name__ == "__main__":
    print(min_ops_to_N(10))  # Output: 5
    print(min_ops_to_N(12))  # Output: 5
    print(coin_change([1, 2, 5], 11))
    print(longest_common_substring("abcdef", "zcdemf"))
    print(edit_distance("kitten", "sitting"))
