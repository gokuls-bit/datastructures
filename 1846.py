class Solution(object):
    def maximumElementAfterDecrementingAndRearranging(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        # Step 1: Sort the array to easily handle the rearranging condition
        arr.sort()
        
        # Step 2: Enforce the first rule (the first element must be 1)
        arr[0] = 1
        
        # Step 3: Iterate through the array and enforce the adjacent difference rule
        for i in range(1, len(arr)):
            # The current element can be at most 1 greater than the previous element.
            # We use min() because we can only decrease elements, never increase them.
            arr[i] = min(arr[i], arr[i - 1] + 1)
            
        # Step 4: The last element will be the maximum possible value
        return arr[-1]
