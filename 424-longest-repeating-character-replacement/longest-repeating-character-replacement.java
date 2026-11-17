class Solution {
    public int characterReplacement(String s, int k) {
        int n = s.length();
        int []f = new int[256];
        int low = 0;
        int res = 0;
        for(int high = 0 ; high<n ; high++){
            f[s.charAt(high)]++;
            int maxCount = find(f);
            int len = high-low+1;
            int diff = len-maxCount;
            while(diff>k){
                f[s.charAt(low)]--;
                low++;
                len = high-low+1;
                maxCount = find(f);
                diff = len-maxCount;
            }
            len = high-low+1;
            res = Math.max(res,len);

        }
        return res;
    }
    private int find(int []f){
        int maxCount = 0;
        for(int i = 0 ; i<256 ; i++){
            maxCount = Math.max(maxCount , f[i]);
        }
        return maxCount;
    }

}

