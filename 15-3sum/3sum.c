/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int compare(const void*a , const void *b){
    int x = *(const int*)a;
    int y = *(const int*)b;
    if(x>y){
        return 1;
    }
    else if(x<y){
        return -1;
    }
    else{
        return 0;
    }
}
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    qsort(nums,numsSize,sizeof(int),compare);
    int capacity = numsSize*numsSize;
    int **result = (int**)malloc(capacity * sizeof(int *));
    *returnColumnSizes = (int*)malloc(capacity*sizeof(int));
    *returnSize = 0;
    for(int i = 0 ; i<numsSize -2 ; i++){
        int left = i+1;
        int right = numsSize-1;
        while(left<right){
            int sum = nums[i]+nums[left]+nums[right];
            if(sum == 0){
                int duplicate = 0;
                for(int j = 0 ; j<*returnSize ; j++){
                    if(result[j][0]==nums[i]&&
                       result[j][1]==nums[left]&&
                       result[j][2]==nums[right]){
                        duplicate = 1;
                        break;
                       }

                    }
                if (!duplicate)
                {
                    result[*returnSize] = (int *)malloc(3 * sizeof(int));

                    result[*returnSize][0] = nums[i];
                    result[*returnSize][1] = nums[left];
                    result[*returnSize][2] = nums[right];

                    (*returnColumnSizes)[*returnSize] = 3;
                    (*returnSize)++;
                }
                left++;
                right--;
                
            }
            else if(sum<0){
                left++;
            }
            else{
                right--;
            }
        }
    } 
    return result;   
}