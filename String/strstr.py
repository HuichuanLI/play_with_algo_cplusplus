class Solution:
    def isContain(self, source, pattern):
        i, j = 0, 0

        while i < len(source) and j < len(pattern):
            if source[i] == pattern[j]:
                i += 1
                j += 1
            else:
                i = i - j + 1
                j = 0
        if j == len(pattern):
            return True
        else:
            return False


if __name__ == '__main__':
    solution = Solution()
    print(solution.isContain("ABACDABABC", "BAB"))
