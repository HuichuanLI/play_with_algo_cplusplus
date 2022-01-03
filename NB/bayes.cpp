//
// Created by 李汇川 on 2021/11/23.
//

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <numeric>

typedef struct {
  int count;
  int totalWords;
  std::vector<int> wordsNum;
  double pci;
  std::vector<double> pfci;
} TRAINING_T;

typedef std::pair<std::vector<std::string>, std::string> EXAMPLE_T;
typedef std::map<std::string, TRAINING_T> TRAINING_RESULT;

std::vector<EXAMPLE_T> examples =
    {
        {{"周六", "公司", "庆祝", "聚餐", "时间", "订餐"}, "普通邮件"},
        {{"喜欢", "概率论", "考试", "研究", "及格", "补考", "失败"}, "普通邮件"},
        {{"贝叶斯", "理论", "算法", "公式", "困难"}, "普通邮件"},
        {{"上海", "晴朗", "郊游", "青草", "蓝天", "帐篷", "停车场", "拥堵"}, "普通邮件"},
        {{"代码", "走查", "错误", "反馈", "修改", "入库", "编译"}, "普通邮件"},
        {{"公司", "单元测试", "覆盖率", "时间", "用例", "失败", "成功"}, "普通邮件"},
        {{"优惠", "打折", "促销", "返利", "金融", "理财"}, "垃圾邮件"},
        {{"公司", "发票", "税点", "优惠", "增值税", "返利"}, "垃圾邮件"},
        {{"抽奖", "中奖", "点击", "恭喜", "申请", "资格"}, "垃圾邮件"},
        {{"爆款", "秒杀", "打折", "抵用券", "特惠"}, "垃圾邮件"},
        {{"招聘", "兼职", "日薪", "信用", "合作"}, "垃圾邮件"},
        {{"贷款", "资金", "担保", "抵押", "小额", "利息"}, "垃圾邮件"},
        {{"正规", "发票", "税务局", "验证", "咨询", "打折"}, "垃圾邮件"},
        {{"诚意", "合作", "特价", "机票", "欢迎", "咨询"}, "垃圾邮件"}
    };

std::vector<std::string> MakeAllWordsList(const std::vector<EXAMPLE_T> &examples) {
  std::set<std::string> wordsSet;
  for (auto &e: examples) {
    wordsSet.insert(e.first.begin(), e.first.end());
  }

  std::vector<std::string> wordsList;
  std::copy(wordsSet.begin(), wordsSet.end(), std::back_inserter(wordsList));
  return std::move(wordsList);
}

int main() {
  std::vector<std::string> allWords = MakeAllWordsList(examples);
  std::for_each(allWords.begin(), allWords.end(), [](std::string a) -> void {
    std::cout << a << std::endl;
  });
  //  TRAINING_RESULT tr = TrainingExample(allWords, examples);
//
//
//  //std::vector<std::string> testWords = { "公司", "讨论", "单元测试", "覆盖率", "错误", "成功" };
//  std::vector<std::string> testWords = { "公司", "保险", "讨论", "喜欢", "周六", "郊游", "蓝天" };
//  std::string classification = ClassifyResult(tr, allWords, testWords);
//  std::cout << "[";
//  std::copy(testWords.begin(), testWords.end(), std::ostream_iterator<std::string>(std::cout, " "));
//  std::cout << "] 被分类为： " << classification << std::endl << std::endl;
//
//  std::vector<std::string> testWords2 = { "公司", "优惠", "打折", "秒杀", "喜欢", "合作" };
//  std::string classification2 = ClassifyResult(tr, allWords, testWords2);
//  std::cout << "[";
//  std::copy(testWords2.begin(), testWords2.end(), std::ostream_iterator<std::string>(std::cout, " "));
//  std::cout << "] 被分类为： " << classification2 << std::endl << std::endl;

  return 0;
}
