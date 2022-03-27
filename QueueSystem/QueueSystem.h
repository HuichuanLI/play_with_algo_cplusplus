//
// Created by 李汇川 on 2022/3/26.
//

//
//  QueueSystem.hpp
//  QueueSystem
//

#ifndef QueueSystem_hpp
#define QueueSystem_hpp

#include "Event.h"
#include "Queue.h"
#include "ServiceWindow.h"

class QueueSystem {

 public:
  // 初始化队列系统
  QueueSystem(int total_service_time, int window_num) :
      total_service_time(total_service_time),
      window_num(window_num),
      total_customer_stay_time(0),
      total_customer_num(0) {
    // 创建服务窗口
    this->windows = new ServiceWindow[window_num];
  }
  ~QueueSystem() {
    delete[] windows;
  }
  void simulate(int simulate_num) {
    double sum = 0;
    for (int i = 0; i != simulate_num; ++i) {
      sum += run();
    }
    avg_stay_time = (double) sum / simulate_num;
    avg_customers = (double) total_customer_num / (total_service_time * simulate_num);
  }

  inline double getAvgStayTime() const {
    return avg_stay_time;
  }
  inline double getAvgCustomers() const {
    return avg_customers;
  }

 private:
  // 让队列系统运行一次
  double run() {
    this->init();
    while (current_event) {
      // 判断当前事件类型
      if (current_event->event_type == -1) {
        customerArrived();
      } else {
        customerDeparture();
      }
      delete current_event;
      // 获得新的事件
      current_event = event_list.dequeue();
    };
    this->end();
    // 返回顾客的平均逗留时间
    return (double) total_customer_stay_time / total_customer_num;
  }

  // 系统开启运行, 初始化事件链表, 部署第一个事件
  void init() {
    // 第一个事件肯定是到达事件, 使用默认构造
    Event *event = new Event;
    current_event = event;
  }

  // 清空各种参数
  void end() {
    // 设置所有窗口空闲
    for (int i = 0; i != window_num; ++i) {
      windows[i].setIdle();
    }
    // 顾客队列清空
    customer_list.clearQueue();

    // 事件列表清空
    event_list.clearQueue();

  }

  // 获得空闲窗口索引
  int getIdleServiceWindow() {
    for (int i = 0; i != window_num; ++i) {
      if (windows[i].isIdle()) {
        return i;
      }
    }
    return -1;
  }

  // 处理顾客到达事件
  void customerArrived() {

    total_customer_num++;

    // 生成下一个顾客的到达事件

    int intertime = Random::getRandom(POISSON, 0.5);  // 下一个顾客到达的时间间隔，我们假设100分钟内一定会出现一个顾客
    // 下一个顾客的到达时间 = 当前事件的发生时间 + 下一个顾客到达的时间间隔
    int time = current_event->occur_time + intertime;
    Event temp_event(time);
    // 如果下一个顾客的到达时间小于服务的总时间，就把这个事件插入到事件列表中
    // 同时将这个顾客加入到 customer_list 进行排队
    if (time < total_service_time) {
      event_list.orderEnqueue(temp_event);
    } // 否则不列入事件表，且不加入 cusomer_list


    // 处理当前事件中到达的顾客
    Customer *customer = new Customer(current_event->occur_time);
    if (!customer) {
      exit(-1);
    }
    customer_list.enqueue(*customer);

    // 如果当前窗口有空闲窗口，那么直接将这个顾客送入服务窗口
    int idleIndex = getIdleServiceWindow();
    if (idleIndex >= 0) {
      customer = customer_list.dequeue();
      windows[idleIndex].serveCustomer(*customer);
      windows[idleIndex].setBusy();

      // 顾客到窗口开始服务时，就需要插入这个顾客的一个离开事件到 event_list 中
      // 离开事件的发生时间 = 当前时间事件的发生时间 + 服务时间
      Event temp_event(current_event->occur_time + customer->duration, idleIndex);
      event_list.orderEnqueue(temp_event);
    }
    delete customer;
  }

  // 处理用户离开事件
  void customerDeparture() {
    // 如果离开事件的发生时间比中服务时间大，我们就不需要做任何处理
    if (current_event->occur_time < total_service_time) {
      // 顾客逗留时间 = 当前顾客离开时间 - 顾客的到达时间
      total_customer_stay_time +=
          current_event->occur_time - windows[current_event->event_type].getCustomerArriveTime();
      // 如果队列中有人等待，则立即服务等待的顾客
      if (customer_list.length()) {
        Customer *customer;
        customer = customer_list.dequeue();
        windows[current_event->event_type].serveCustomer(*customer);

        // 离开事件
        Event temp_event(
            current_event->occur_time + customer->duration,
            current_event->event_type
        );
        event_list.orderEnqueue(temp_event);

        delete customer;
      } else {
        // 如果队列没有人，且当前窗口的顾客离开了，则这个窗口是空闲的
        windows[current_event->event_type].setIdle();
      }

    }
  }
  // 服务窗口的总数
  int window_num;

  // 总的营业时间
  int total_service_time;

  // 顾客的逗留总时间
  int total_customer_stay_time;

  // 总顾客数
  int total_customer_num;

  // 核心成员
  ServiceWindow *windows;
  Queue<Customer> customer_list;
  Queue<Event> event_list;
  Event *current_event;

  // 给外部调用的结果
  double avg_customers;
  double avg_stay_time;

};

#endif /* QueueSystem_hpp */