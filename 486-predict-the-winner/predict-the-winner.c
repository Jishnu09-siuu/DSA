bool predictTheWinner(int* nums, int numsSize) {
    int dp[20][20];
    for(int i = 0;i<numsSize;i++){
        dp[i][i] = nums[i];
    }
    for(int len=2;len<=numsSize;len++){
        for(int i = 0;i<=numsSize-len;i++){
            int j = i+len-1;
            int left = nums[i]-dp[i+1][j];
            int right = nums[j]-dp[i][j-1];
            dp[i][j]= (left>right) ? left:right;
        }
    }
    return dp[0][numsSize-1]>=0;
    
}