char* stoneGameIII(int* stoneValue, int stoneValueSize) {
    int n = stoneValueSize;

    int dp[n + 1];
    dp[n] = 0;

    for (int i = n - 1; i >= 0; i--) {
        dp[i] = -1000000000;
        int sum = 0;

        for (int k = 0; k < 3 && i + k < n; k++) {
            sum += stoneValue[i + k];

            int diff = sum - dp[i + k + 1];

            if (diff > dp[i])
                dp[i] = diff;
        }
    }

    if (dp[0] > 0)
        return "Alice";
    else if (dp[0] < 0)
        return "Bob";
    else
        return "Tie";
}