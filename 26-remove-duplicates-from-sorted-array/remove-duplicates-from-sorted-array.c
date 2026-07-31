int removeDuplicates(int* nums, int numsSize) {
    if(numsSize==0){
        return 0;
    }
    int write = 0;
    for(int read = 1 ; read<numsSize;read++){
        if(nums[read]!=nums[write]){
            write++;
            nums[write]=nums[read];
        }
    }
    return write+1;
    
}