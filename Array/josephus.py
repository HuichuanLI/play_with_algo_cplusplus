class Solution:
    def josephus(self, n, m):
        peoples = [0] * n
        # 当前指针索引
        index = -1
        # 循环数0到m
        count = 0
        # 环中剩下的人数
        remainNum = n
        # 将所有的人数都淘汰出圈
        while remainNum > 0:
            # 索引 +1
            index += 1
            # 如果当前索引已经超过数组的长度，则需要将索引移动至数组的开头位置
            if index == n:
                # 索引移动至开头
                index = 0
            # 如果元素的值等于 -1，说明这个士兵已经被淘汰了，不计数，直接跳过
            if peoples[index] == -1:
                continue
            else:
                # 否则计数
                count += 1
                # 如果计数到m，说明该士兵需要被淘汰
                if count == m:
                    print(index, end=" ")
                    # 数值置为 -1
                    peoples[index] = -1
                    # 计数归 0
                    count = 0
                    # 圈内的人数减少 1
                    remainNum -= 1
        print("")
        return index


if __name__ == '__main__':
    solution = Solution()
    print("最后出圈的士兵:", solution.josephus(5, 3))
