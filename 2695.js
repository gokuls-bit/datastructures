/**
 * @param {number[]} nums
 */
var ArrayWrapper = function(nums) {
    this.nums = nums;
};

/**
 * Called when using +
 * @return {number}
 */
ArrayWrapper.prototype.valueOf = function() {
    let sum = 0;

    for (let num of this.nums) {
        sum += num;
    }

    return sum;
};

/**
 * Called when using String()
 * @return {string}
 */
ArrayWrapper.prototype.toString = function() {
    return "[" + this.nums.join(",") + "]";
};

/**
 * const obj1 = new ArrayWrapper([1,2]);
 * const obj2 = new ArrayWrapper([3,4]);
 * obj1 + obj2;        // 10
 * String(obj1);       // "[1,2]"
 */
