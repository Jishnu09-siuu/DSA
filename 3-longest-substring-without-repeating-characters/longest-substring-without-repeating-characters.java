class Solution {
    public int lengthOfLongestSubstring(String s) {
        HashMap<Character,Integer> map = new HashMap<>();
        int left = 0;
        int maxLen = 0;
        for(int right=0 ; right < s.length() ; right++){
            char ch = s.charAt(right);
            while(map.containsKey(ch)){
                char leftchar = s.charAt(left);
                map.remove(leftchar);
                left++;
            }
            map.put(ch,1);
            maxLen = Math.max(maxLen, right - left + 1);
        }
        return maxLen;
        
    }
}