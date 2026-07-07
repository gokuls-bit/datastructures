class Solution(object):
    def sumAndMultiply(self, n):
        """
        :type n: int
        :rtype: int
        """

        x = 0
        digit_sum = 0

        for ch in str(n):
            if ch != '0':
                d = int(ch)
                x = x * 10 + d
                digit_sum += d

        return x * digit_sum
