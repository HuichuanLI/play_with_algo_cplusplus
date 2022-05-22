class Solution:

    def reverse(self, str, start, end):
        while start < end:
            temp = str[start]
            str[start] = str[end]
            str[end] = temp
            start += 1
            end -= 1

    def reverseSentence(self, sentence):
        str = list(sentence)
        size = len(str)
        # 翻转整个句子
        self.reverse(str, 0, size - 1)
        flag = False
        index = 0
        for i in range(0, size):
            if str[i] != ' ':
                # 开始新的单词
                if flag == False:
                    flag = True
                    index = i
                # 如果是最后一个字符
                if i == size - 1:
                    self.reverse(str, index, i)
            elif flag:
                flag = False
                self.reverse(str, index, i - 1)
        return self.removeSpaces(str)

    def removeSpaces(self, str):
        res = ''
        flag = False
        for i in range(0, len(str)):
            if str[i] != ' ':
                res += str[i]
                flag = False
            else:
                if flag:
                    continue
                else:
                    res += str[i]
                    flag = True
        return res


if __name__ == '__main__':
    solution = Solution()
    str = "I love coding every  day"
    print(solution.reverseSentence(str))
