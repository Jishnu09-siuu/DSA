/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMissingElements(int* nums, int numsSize, int* returnSize) {
    int min = nums[0] , max = nums[0];
    for(int i = 0;i<numsSize;i++){
        if(nums[i]<min){
            min = nums[i];
        }
        if(nums[i]>max){
            max = nums[i];
        }
    }
    int present[101] = {0};
    for(int i = 0;i<numsSize;i++){
        present[nums[i]] = 1;
    }
    int *ans = (int *)malloc((max-min+1)*sizeof(int));
    int k = 0;
    for(int i = min ;i<=max ; i++){
        if(!present[i]){
            ans[k++] = i;
        }
    }
    *returnSize = k;
    return ans;
    
}