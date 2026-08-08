#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();
        
        // right_match[j] stores the maximum starting index in word1 
        // from which the suffix word2[j:] can be perfectly matched.
        vector<int> right_match(m, -1);
        
        // 1. Backward pass: Populate the right_match array
        int i = n - 1;
        for (int j = m - 1; j >= 0; --j) {
            while (i >= 0 && word1[i] != word2[j]) {
                i--;
            }
            if (i >= 0) {
                right_match[j] = i;
                i--;
            }
        }
        
        vector<int> ans;
        int j = 0;
        bool mismatch_used = false;
        
        // 2. Forward pass: Greedily pick the earliest indices
        for (i = 0; i < n; ++i) {
            if (j == m) break;
            
            // If characters match, just take the index
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                j++;
            } 
            // If they don't match, see if we can use our one mismatch
            else if (!mismatch_used) {
                // We can use it if we are on the last character OR 
                // the remaining suffix can perfectly match in the remaining word1
                bool can_match_rest = (j + 1 == m) || (right_match[j + 1] > i);
                
                if (can_match_rest) {
                    mismatch_used = true;
                    ans.push_back(i);
                    j++;
                }
            }
        }
        
        // Return the sequence if we matched all characters of word2
        if (ans.size() == m) {
            return ans;
        }
        return {};
    }
};