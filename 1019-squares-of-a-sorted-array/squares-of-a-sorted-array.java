class Solution {
    public int[] sortedSquares(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];
        int left = 0;
        int right = n-1;
        int index = n-1;
        while(left<=right){
            int leftsquare = nums[left]*nums[left];
            int rightsquare = nums[right]*nums[right];
            if(leftsquare>rightsquare){
                result[index] = leftsquare;
                left++;
            }
            else{
                result[index] = rightsquare;
                right--;
            }
            index--;

        }
        return result;        
    }
}