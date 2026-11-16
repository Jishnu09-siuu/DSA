class Solution {
    public int characterReplacement(String s, int k) {
        int n = s.length();
        int[] f = new int[256];
        int low = 0;
        int res = 0;
        for(int high = 0 ; high<n ; high++){
            f[s.charAt(high)]++;
            int len = high-low+1;
            int maxcount = find(f);
            int diff = len-maxcount;
            while(diff>k){
                f[s.charAt(low)]--;
                low++;
                maxcount = find(f);
                len = high-low+1;
                diff = len-maxcount;

            }
            len = high - low + 1;
            res = Math.max(res, len);



        }
        return res;
    }
    private int find (int[] f){
        int maxCount = 0;
        for (int i = 0; i < 256; i++) {
            maxCount = Math.max(maxCount, f[i]);
        }
        return maxCount;
    }

}
