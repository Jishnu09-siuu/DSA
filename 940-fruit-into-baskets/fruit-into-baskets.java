class Solution {
    public int totalFruit(int[] fruits) {
        int n = fruits.length;
        int low = 0;
        int maxLen = 0 ;
        HashMap<Integer, Integer> map = new HashMap<>();
        for(int right = 0 ; right < n ; right++){
            //map.put(fruits[right],map.getOrDefault(fruits[right],0)+1)
            int fruit = fruits[right];
            int count = map.getOrDefault(fruit,0);
            map.put(fruit,count+1);
            while(map.size()>2){
                map.put(fruits[low], map.get(fruits[low]) - 1);
                if (map.get(fruits[low]) == 0) {
                    map.remove(fruits[low]);
                }
                low++;
            }
            maxLen = Math.max(maxLen, right - low + 1);
        }
        return maxLen;
    }
}