//
// Created by 李汇川 on 2022/3/27.
//

#include <iostream>
#include "LinkedListSet.h"
#include "FileOperation.h"

int main() {
  std::cout << "a-tale-of-two-cities.txt" << std::endl;
  vector<string> words;
  if (FileOps::readFile("/Users/hui/Desktop/c++/play_with_algo/DS/Set&Map/a-tale-of-two-cities.txt", words)) {
    std::cout << "Total words: " << words.size() << std::endl;
    LinkedListSet<string> *linkedListSet = new LinkedListSet<string>();
    for (string word: words) {
      linkedListSet->add(word);
    }
    std::cout << "Total different words: " << linkedListSet->getSize() << std::endl;
    linkedListSet = nullptr;
    delete linkedListSet;
  }

  std::cout << "a-tale-of-two-cities.txt" << std::endl;
  vector<string> words1;
  if (FileOps::readFile("/Users/hui/Desktop/c++/play_with_algo/DS/Set&Map/pride-and-prejudice.txt", words1)) {
    std::cout << "Total words: " << words1.size() << std::endl;
    LinkedListSet<string> *linkedListSet = new LinkedListSet<string>();
    for (string word: words1) {
      linkedListSet->add(word);
    }
    std::cout << "Total different words: " << linkedListSet->getSize() << std::endl;
    linkedListSet = nullptr;
    delete linkedListSet;
  }
  return 0;
}