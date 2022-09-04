#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>

using namespace std;

const int minutes_of_day = 1440;

// 记录问题提供的图，起点，终点，出发时间，路线类型，预算的变量
int N, M, start_point, end_point, start_time, path_type = 1;
double budget;

// 记录每条边的信息的结构体
struct Edge {
    int from_point, to_point;
    int length, speed_limit;
    int pass_start_time, pass_end_time;
    int toll;
};

// 保存整个路线图的二维向量，模拟邻接表。另外保存一个反向图方便预处理
vector<vector<Edge>> graph, reverse_graph;
// 记录节点相对于终点层数的哈希表
map<int, int> point_level;

// 辅助计算当前时间对于一条路径，从路径起点出发到达终点的时间
// 注意：这里考虑了路径可能有通行时间限制，如果不能通行，则顺延到第二天
int getNextArrivalTime(int arrival_time, Edge edge) {
    int pass_time = ceil((edge.length + 0.0) / edge.speed_limit);
    if (arrival_time % minutes_of_day > edge.pass_end_time)
        return (arrival_time / minutes_of_day + 1) * minutes_of_day
               + edge.pass_start_time + pass_time;
    return arrival_time + pass_time;
}

// 记录路径节点信息的结构体
struct PathNode {
    int point, arrival_time, distance, prev;
    int cost, heuristic_cost;
    int heuristic_time, heuristic_distance;

    // 计算启发函数值，根据path_type不同，计算方法也不同
    void calcHeuristic() {
        switch (path_type) {
            case 1:
                calcHeuristicTime();
                break;
            case 2:
                calcHeuristicDistance();
                break;
            case 3:
                calcHeuristicCost();
                calcHeuristicTime();
                break;
            case 4:
                calcHeuristicTime();
                break;
            default:
                break;
        }
    }

    // 计算以时间作为启发函数值的情况，这里使用了一个贪心过程，每次在层数-1且有道路
    // 连接的点中选择最早到达道路另一端的来走
    void calcHeuristicTime() {
        int t = arrival_time;
        int current_point = point;
        while (current_point != end_point) {
            int next_point = -1;
            int next_point_t = INT_MAX;
            for (Edge edge: graph[current_point])
                if (point_level[current_point] - point_level[edge.to_point] == 1) {
                    int next_arrival_time = getNextArrivalTime(arrival_time, edge);
                    if (next_point == -1 || next_arrival_time < next_point_t) {
                        next_point = edge.to_point;
                        next_point_t = next_arrival_time;
                    }
                }
            current_point = next_point;
            t = next_point_t;
        }
        heuristic_time = t;
    }

    // 计算以距离作为启发函数值的情况
    void calcHeuristicDistance() {
        int dis = distance;
        int current_point = point;
        while (current_point != end_point) {
            int next_point = -1;
            int next_point_dis = INT_MAX;
            for (Edge edge: graph[current_point])
                if (point_level[current_point] - point_level[edge.to_point] == 1) {
                    int next_distance = dis + edge.length;
                    if (next_point == -1 || next_distance < next_point_dis) {
                        next_point = edge.to_point;
                        next_point_dis = next_distance;
                    }
                }
            current_point = next_point;
            dis = next_point_dis;
        }
        heuristic_distance = dis;
    }

    // 计算以花费作为启发函数值的情况
    void calcHeuristicCost() {
        int current_cost = cost;
        int current_point = point;
        while (current_point != end_point) {
            int next_point = -1;
            int next_point_cost = INT_MAX;
            for (Edge edge: graph[current_point])
                if (point_level[current_point] - point_level[edge.to_point] == 1) {
                    int next_cost = current_cost + edge.toll;
                    if (next_point == -1 || next_cost < next_point_cost) {
                        next_point = edge.to_point;
                        next_point_cost = next_cost;
                    }
                }
            current_point = next_point;
            current_cost = next_point_cost;
        }
        heuristic_cost = current_cost;
    }

    // 重载<符号，用于优先队列的比较，根据path_type不同，比较方法也不同
    bool operator<(const PathNode &pn) const {
        switch (path_type) {
            case 1:
                return heuristic_time > pn.heuristic_time;
                break;
            case 2:
                return heuristic_distance > pn.heuristic_distance;
                break;
            case 3:
                if (heuristic_cost > pn.heuristic_cost)
                    return true;
                if (heuristic_cost == pn.heuristic_cost
                    && heuristic_time > pn.heuristic_time)
                    return true;
                return false;
                break;
            case 4:
                return heuristic_time > pn.heuristic_time;
                break;
            default:
                break;
        }
        return false;
    }
};

// 将HH:mm转化为分钟
int toMinute(string time) {
    return ((time[0] - '0') * 10 + time[1] - '0') * 60
           + (time[3] - '0') * 10 + time[4] - '0';
}

// 将分钟转化为"HH:mm"
string toHourAndMinute(int time) {
    int hour = time / 60;
    int minute = time % 60;
    return ((hour < 10) ? "0" : "") + to_string(hour) + ":"
           + ((minute < 10) ? "0" : "") + to_string(minute);
}

// 根据路线类型返回需要比较的属性
int getAttribute(PathNode current, Edge edge) {
    switch (path_type) {
        case 1:
            return getNextArrivalTime(current.arrival_time, edge);
            break;
        case 2:
            return current.distance + edge.length;
            break;
        case 3:
            return current.cost + edge.toll;
            break;
        case 4:
            return getNextArrivalTime(current.arrival_time, edge);
            break;
        default:
            break;
    }
    return -1;
}

// 预处理，计算终点反向出发到达每个节点所用的最少路径数目（不是长度）
// 这个数目作为这个节点的"层数"，在后面用贪心法计算启发函数值的时候会用到
// 这个预处理本质上是一个简单的BFS遍历，时间复杂度很低
void getLevelOfPoints() {
    queue<int> queue;
    queue.push(end_point);
    point_level[end_point] = 0;
    while (!queue.empty()) {
        int t = queue.front();
        queue.pop();
        for (Edge edge: reverse_graph[t])
            if (point_level.find(edge.from_point) == point_level.end()) {
                point_level[edge.from_point] = point_level[t] + 1;
                queue.push(edge.from_point);
            }
    }
}

// 初始化，读入数据并建图
void init() {
    cin >> N >> M >> start_point >> end_point >> path_type >> budget;
    // 预算单位转化为分
    budget *= 100;
    string time;
    cin >> time;
    start_time = toMinute(time);

    for (int i = 0; i < N; i++) {
        vector<Edge> tmp;
        graph.push_back(tmp);
        reverse_graph.push_back(tmp);
    }
    for (int i = 0; i < M; i++) {
        Edge newPath;
        // 每条边输入数据的形式为：
        // 起点，终点，长度，限速，收费，通行起始时间~通行结束时间
        // 注：通行时间如果是00:00~24:00就意味着没有限制，可以随意通行
        cin >> newPath.from_point >> newPath.to_point >> newPath.length >> newPath.speed_limit;
        // 将费用转化为用"分"存储，这样就可以使用整数类型
        double t;
        cin >> t;
        newPath.toll = t * 100;
        cin >> time;
        // 此处time的形式应该是" HH:mm~HH:mm"
        newPath.pass_start_time = toMinute(time.substr(1, 5));
        newPath.pass_end_time = toMinute(time.substr(7, 5));
        graph[newPath.from_point].push_back(newPath);
        // 反向图也保存同一条边，只是保存在终点对应的vector下
        reverse_graph[newPath.to_point].push_back(newPath);
    }

    // 预处理计算每个节点是从终点开始的第几层
    getLevelOfPoints();
}

// 输出最终的路径信息
void printPath(vector<PathNode> &archived_states) {
    int state_size = archived_states.size();
    PathNode last_point = archived_states[state_size - 1];
    cout << toHourAndMinute(last_point.arrival_time) << " ";
    cout << last_point.distance << " ";
    cout << (last_point.cost + 0.0) / 100 << endl;

    // 用一个临时变量path存储经过的所有点
    vector<PathNode> path;
    path.push_back(last_point);
    // 从终点开始根据prev逆向推回去，找到路径经过的每个点
    while (last_point.prev != -1) {
        last_point = archived_states[last_point.prev];
        path.push_back(last_point);
    }
    // 将路径经过的点从起点到终点输出，因为path是逆向保存的，所以需要反向输出
    cout << path.size() << endl;
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i].point << " " << toHourAndMinute(path[i].arrival_time) << endl;
}

void aStar() {
    // 记录比较属性的哈希表，历史记录队列（输出结果用）和A*的主优先队列
    map<int, int> hash_state;
    vector<PathNode> archived_states;
    priority_queue<PathNode, vector<PathNode>> state_queue;

    // 初始化，将起点状态加入优先队列
    PathNode init_state;
    init_state.arrival_time = start_time;
    init_state.point = start_point;
    init_state.cost = 0;
    init_state.distance = 0;
    // prev = -1表示不存在前一个节点，即起点
    init_state.prev = -1;
    init_state.calcHeuristic();
    state_queue.push(init_state);

    // A*主过程
    while (!state_queue.empty()) {
        PathNode current = state_queue.top();
        state_queue.pop();
        archived_states.push_back(current);

        // 如果取出的状态是终点状态，则找到了解，输出并返回
        if (current.point == end_point) {
            printPath(archived_states);
            return;
        }

        // 遍历从当前点出发的每一条边，如果对于当前的path_type来说，经过这条边到达
        // 下一个点更优（跟hash_state比较），则生成新状态并计算估价函数，然后加入优先队列
        for (Edge edge: graph[current.point]) {
            // 根据path_type不同，比较的属性也不同，所以用attribute来统一代表
            int attribute = getAttribute(current, edge);
            if (hash_state.find(edge.to_point) == hash_state.end()
                || hash_state[edge.to_point] > attribute) {
                PathNode next;
                next.point = edge.to_point;
                next.arrival_time = getNextArrivalTime(current.arrival_time, edge);
                next.distance = current.distance + edge.length;
                next.cost = current.cost + edge.toll;
                // 特殊判断：对于最后一种类型，如果cost已经超过budget上限
                // 则说明这条路不符合要求，新状态直接丢掉
                if (path_type == 4 && next.cost > budget)
                    continue;
                // 新状态的上一个状态应该是历史记录队列里的最后一个（即“当前状态”）
                next.prev = archived_states.size() - 1;
                next.calcHeuristic();
                state_queue.push(next);
                hash_state[next.point] = attribute;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // 初始化
    init();

    // A*算法主过程
    aStar();

    return 0;
}