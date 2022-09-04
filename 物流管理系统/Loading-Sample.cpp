//
// Created by lhc456 on 2022/9/4.
//
#include<iostream>
#include<cstdlib>
#include<cstring>

using namespace std;

// 测试数据：
// 40 35 198 24 60
// 13 118 128 149 581

// 为了方便，用10厘米做单位进行换算。后面涉及到所有长度都按这个来
const int truck_length = 100;
const int truck_height = 30;

// 为了方便构造法初始化，高度全部取的30可以整除的那一个，所以50 * 80的和其他不一样
// 其他都是长边做高，50 * 80是长边做宽，不影响后面剩余包裹的处理
const int box_length[5] = {7, 8, 3, 2, 1};
const int box_height[5] = {10, 5, 5, 3, 1};

// 记录包裹的位置和横竖的结构体
struct BoxPosition {
    // 分别记录横纵坐标位置，横/竖，以及放在第几辆卡车
    int x, y, orientation, truck_id;
};

int main() {
    cin.tie(NULL);
    cout.tie(NULL);

    // 输入部分，读入5种规格的包裹数目
    int count[5];
    int n = 0;

    for (int i = 0; i < 5; i++) {
        cin >> count[i];
        n += count[i];
    }

    // 记录卡车数，每个包裹放在了哪辆卡车的哪个位置，以及已经放了包裹的每辆卡车的剩余空间
    int truck_count = 1;
    BoxPosition box_pos[5][n];
    int box_loaded[5];
    int truck_used_len[n];

    // 数组初始化
    memset(box_loaded, 0, sizeof(box_loaded));
    memset(truck_used_len, 255, sizeof(truck_used_len));

    // 构造法初始化，对于每种规格的包裹，只要剩余包裹还够拼成高度为30的一竖排
    // 就一直拼下去。
    // 这里每次会从当前所有卡车中挑选剩余空间最少的那一辆放进去（前提是能放下）
    // 如果当前所有卡车剩余空间都不够放了，就新加一辆卡车
    for (int i = 0; i < 5; i++) {
        // 只要当前规格剩余包裹数目足够拼成一满列，就继续
        while (count[i] - box_loaded[i] >= truck_height / box_height[i]) {
            // 寻找能放下当前列的，剩余长度最小的卡车
            int put_truck = -1;
            for (int j = 0; j < truck_count; j++) {
                int remain_len = truck_length - truck_used_len[j] - 1;
                if (remain_len >= box_length[i] &&
                    (put_truck == -1 || remain_len < truck_length - truck_used_len[put_truck] - 1))
                    put_truck = j;
            }
            // 如果找不到对应卡车，就新开一辆
            if (put_truck == -1)
                put_truck = truck_count++;
            // 将每个包裹的位置信息记录一下
            for (int j = 0; j < truck_height / box_height[i]; j++) {
                BoxPosition pos;
                pos.x = truck_used_len[put_truck] + 1;
                pos.y = box_height[i] * j;
                // 0表示竖放，1表示横放
                // 只有规格1(50 * 80)的包裹需要横着放，其他都是竖着
                pos.orientation = (i == 1) ? 1 : 0;
                pos.truck_id = put_truck;
                box_pos[i][box_loaded[i]++] = pos;
            }
            // 更新卡车的已使用空间
            truck_used_len[put_truck] += box_length[i];
        }
    }

    // 构造法主体部分
    // 当前最后一辆未被放满的车辆假设它剩余的长度为lenx，那么问题就转化为如何
    // 尽可能将剩余包裹放入长为lenx，高为30的矩形空间里
    int lenx = truck_used_len[truck_count - 1] + 1;
    bool remain_truck_space[101][31];
    memset(remain_truck_space, 0, sizeof(remain_truck_space));
    for (int i = 0; i < 5; i++)
        while (count[i] - box_loaded[i] > 0) {
            // 记录当前包裹是否能够放入最后一辆车里，以及放的位置和方向
            bool canPut;
            int px = 0, py = 0, po = 0;

            int boxl = box_length[i];
            int boxh = box_height[i];
            // 先竖着放再横着放
            for (int ori = 0; ori < 2; ori++) {
                // 横竖转换，保证长短边和当前横竖设置符合
                if (ori == 0 && boxl > boxh || ori == 1 && boxl < boxh)
                    swap(boxl, boxh);
                // 找到最左下角的可以放当前包裹的空间
                for (int x = lenx; x < truck_length - boxl; x++) {
                    for (int y = 0; y < truck_height - boxh; y++) {
                        canPut = true;
                        // 这里使用最朴素的方法，就是循环判断这个空间的每个坐标
                        // 看看是否被别的包裹占用
                        for (int ti = 0; ti < boxl; ti++) {
                            for (int tj = 0; tj < boxh; tj++)
                                if (remain_truck_space[x + ti][y + tj]) {
                                    canPut = false;
                                    break;
                                }
                            if (!canPut) break;
                        }
                        // 如果没有被占用，就可以放入当前包裹
                        if (canPut) {
                            px = x;
                            py = y;
                            po = ori;
                            break;
                        }
                    }
                    if (canPut)
                        break;
                }
                if (canPut)
                    break;
            }

            // 如果当前包裹横竖都放不了，就重新开一辆车，包裹换回竖放状态
            if (!canPut) {
                truck_count++;
                lenx = 0;
                memset(remain_truck_space, 0, sizeof(remain_truck_space));
                if (boxl > boxh)
                    swap(boxl, boxh);
                po = 0;
            }

            // 更新当前车辆空间占用情况，以及放入包裹的位置信息
            for (int ti = 0; ti < boxl; ti++)
                for (int tj = 0; tj < boxh; tj++)
                    remain_truck_space[px + ti][py + tj] = true;
            BoxPosition pos;
            pos.x = px;
            pos.y = py;
            pos.orientation = po;
            pos.truck_id = truck_count - 1;
            box_pos[i][box_loaded[i]++] = pos;
        }

    // 输出
    // 第一行，需要的运输车辆总数
    cout << truck_count << endl;
    // 每个包裹一行，格式为"[包裹规格], [包裹横坐标], [包裹纵坐标], [包裹横竖], [包裹装车编号]"
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < count[i]; j++)
            cout << i + 1 << ", " << box_pos[i][j].x << ", " << box_pos[i][j].y
                 << ", " << box_pos[i][j].orientation << ", " << box_pos[i][j].truck_id + 1 << endl;
    return 0;
}

