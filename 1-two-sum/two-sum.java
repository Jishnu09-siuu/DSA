class Solution {
    public int[] twoSum(int[] nums, int target) {
        int left = 0;
        int right = nums.length-1;
        int[][] arr = new int[nums.length][2];
        for (int i = 0; i < nums.length; i++) {
            arr[i][0] = nums[i];
            arr[i][1] = i;
        }

        Arrays.sort(arr, (a, b) -> a[0] - b[0]);
        Arrays.sort(nums);
        while(left<right){
            int sum = nums[left]+nums[right];
            if(sum==target){
                return new int[]{
                    arr[left][1],
                    arr[right][1]
                };
            }
            else if(sum<target){
                left++;
            }
            else{
                right--;
            }
        }
        return new int[]{};
    }
}