#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper functions for min and max
static inline int max_int(int a, int b) { return a > b ? a : b; }
static inline int min_int(int a, int b) { return a < b ? a : b; }

char* smallestNumber(char* num, long long t) {
    long long temp = t;
    int req2 = 0, req3 = 0, req5 = 0, req7 = 0;
    
    // Step 1: Factorize t
    while (temp % 2 == 0) { req2++; temp /= 2; }
    while (temp % 3 == 0) { req3++; temp /= 3; }
    while (temp % 5 == 0) { req5++; temp /= 5; }
    while (temp % 7 == 0) { req7++; temp /= 7; }
    
    // If t has prime factors other than 2, 3, 5, 7, it's impossible.
    if (temp > 1) {
        char* no_ans = (char*)malloc(3 * sizeof(char));
        strcpy(no_ans, "-1");
        return no_ans;
    }
    
    // Step 2: DP for min digits needed for remaining factors of 2 and 3
    int MAX2 = 50, MAX3 = 30; // Max powers for 10^14: 2^46 > 10^14, 3^29 > 10^14
    int dp[50][30];
    
    for (int i = 0; i < MAX2; i++) {
        for (int j = 0; j < MAX3; j++) {
            dp[i][j] = 1e9; // representing infinity
        }
    }
    dp[0][0] = 0;
    
    for (int i = 0; i < MAX2; i++) {
        for (int j = 0; j < MAX3; j++) {
            if (i == 0 && j == 0) continue;
            int res = 1e9;
            res = min_int(res, 1 + dp[max_int(0, i - 1)][j]);               // using 2
            res = min_int(res, 1 + dp[i][max_int(0, j - 1)]);               // using 3
            res = min_int(res, 1 + dp[max_int(0, i - 2)][j]);               // using 4
            res = min_int(res, 1 + dp[max_int(0, i - 1)][max_int(0, j - 1)]); // using 6
            res = min_int(res, 1 + dp[max_int(0, i - 3)][j]);               // using 8
            res = min_int(res, 1 + dp[i][max_int(0, j - 2)]);               // using 9
            dp[i][j] = res;
        }
    }
    
    // Predefined factor counts for digits 1-9
    int f2_map[10] = {0, 0, 1, 0, 2, 0, 1, 0, 3, 0};
    int f3_map[10] = {0, 0, 0, 1, 0, 0, 1, 0, 0, 2};
    int f5_map[10] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    int f7_map[10] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
    
    int L = strlen(num);
    
    // Use dynamically allocated arrays due to potentially large L (up to 2*10^5)
    int* pref2 = (int*)calloc(L + 1, sizeof(int));
    int* pref3 = (int*)calloc(L + 1, sizeof(int));
    int* pref5 = (int*)calloc(L + 1, sizeof(int));
    int* pref7 = (int*)calloc(L + 1, sizeof(int));
    
    int z_idx = L;
    
    for (int i = 0; i < L; i++) {
        int d = num[i] - '0';
        if (d == 0) {
            if (i < z_idx) z_idx = i;
            pref2[i + 1] = pref2[i];
            pref3[i + 1] = pref3[i];
            pref5[i + 1] = pref5[i];
            pref7[i + 1] = pref7[i];
        } else {
            pref2[i + 1] = pref2[i] + f2_map[d];
            pref3[i + 1] = pref3[i] + f3_map[d];
            pref5[i + 1] = pref5[i] + f5_map[d];
            pref7[i + 1] = pref7[i] + f7_map[d];
        }
    }
    
    // Check if num itself perfectly works
    if (z_idx == L && pref2[L] >= req2 && pref3[L] >= req3 && pref5[L] >= req5 && pref7[L] >= req7) {
        free(pref2); free(pref3); free(pref5); free(pref7);
        char* ans = (char*)malloc((L + 1) * sizeof(char));
        strcpy(ans, num);
        return ans;
    }
    
    // Step 3: Try modifying a character in num at index i
    int start_i = min_int(L - 1, z_idx);
    for (int i = start_i; i >= 0; i--) {
        int rem2 = max_int(0, req2 - pref2[i]);
        int rem3 = max_int(0, req3 - pref3[i]);
        int rem5 = max_int(0, req5 - pref5[i]);
        int rem7 = max_int(0, req7 - pref7[i]);
        
        int start_d = (num[i] - '0') + 1;
        for (int d = start_d; d <= 9; d++) {
            int nr2 = max_int(0, rem2 - f2_map[d]);
            int nr3 = max_int(0, rem3 - f3_map[d]);
            int nr5 = max_int(0, rem5 - f5_map[d]);
            int nr7 = max_int(0, rem7 - f7_map[d]);
            
            int rem_len = L - 1 - i;
            if (nr5 + nr7 + dp[nr2][nr3] <= rem_len) {
                // Construct greedy minimal remaining suffix
                char* ans = (char*)malloc((L + 1) * sizeof(char));
                for(int j = 0; j < i; j++) ans[j] = num[j];
                ans[i] = d + '0';
                
                int curr2 = nr2, curr3 = nr3, curr5 = nr5, curr7 = nr7;
                for (int pos = i + 1; pos < L; pos++) {
                    for (int nxt_d = 1; nxt_d <= 9; nxt_d++) {
                        int nnr2 = max_int(0, curr2 - f2_map[nxt_d]);
                        int nnr3 = max_int(0, curr3 - f3_map[nxt_d]);
                        int nnr5 = max_int(0, curr5 - f5_map[nxt_d]);
                        int nnr7 = max_int(0, curr7 - f7_map[nxt_d]);
                        
                        if (nnr5 + nnr7 + dp[nnr2][nnr3] <= L - 1 - pos) {
                            ans[pos] = nxt_d + '0';
                            curr2 = nnr2; curr3 = nnr3; curr5 = nnr5; curr7 = nnr7;
                            break;
                        }
                    }
                }
                ans[L] = '\0';
                free(pref2); free(pref3); free(pref5); free(pref7);
                return ans;
            }
        }
    }
    
    // Step 4: Fallback - pick minimal length string strictly greater than len(num)
    int min_needed_len = req5 + req7 + dp[req2][req3];
    int target_L = max_int(L + 1, min_needed_len);
    
    char* ans = (char*)malloc((target_L + 1) * sizeof(char));
    int curr2 = req2, curr3 = req3, curr5 = req5, curr7 = req7;
    
    for (int pos = 0; pos < target_L; pos++) {
        for (int d = 1; d <= 9; d++) {
            int nr2 = max_int(0, curr2 - f2_map[d]);
            int nr3 = max_int(0, curr3 - f3_map[d]);
            int nr5 = max_int(0, curr5 - f5_map[d]);
            int nr7 = max_int(0, curr7 - f7_map[d]);
            
            if (nr5 + nr7 + dp[nr2][nr3] <= target_L - 1 - pos) {
                ans[pos] = d + '0';
                curr2 = nr2; curr3 = nr3; curr5 = nr5; curr7 = nr7;
                break;
            }
        }
    }
    ans[target_L] = '\0';
    
    free(pref2); free(pref3); free(pref5); free(pref7);
    return ans;
}