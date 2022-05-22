import functools


class Solution:
    def compare(self, x, y):
        a, b = x + y, y + x
        if a > b:
            return 1
        elif a < b:
            return -1
        else:
            return 0

    def minNumber(self, nums):
        strs = [str(num) for num in nums]
        strs.sort(key=functools.cmp_to_key(self.compare))
        res = ""
        for i in range(0, len(strs)):
            res += str(strs[i])
        return res


if __name__ == '__main__':
    solution = Solution()
    nums = [3, 32, 321]
    print(solution.minNumber(nums))
