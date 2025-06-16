#include <utility>
#include <list>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>
#include "hash.hpp"

HashSet::Iterator HashSet::begin() {
  return linkedList.begin();
}

HashSet::Iterator HashSet::end() {
  return linkedList.end();
}

std::size_t HashSet::hash(int key, std::size_t size) const {
  return static_cast<std::size_t>(key < 0 ? -static_cast<long long>(key) : key) % size;
}

HashSet::HashSet() : numElements(0), maxLoad(1.0f), sizeIndex(0) {
  linkedList.clear();
  table = std::vector<std::list<int>::iterator>(sizes[sizeIndex], linkedList.end());
}

HashSet::HashSet(const HashSet& other)
  : linkedList(other.linkedList),
    table(),
    numElements(other.numElements),
    maxLoad(other.maxLoad),
    sizeIndex(other.sizeIndex) {
  rehash(sizes[sizeIndex]);
}

HashSet& HashSet::operator=(HashSet other) {
  std::swap(linkedList, other.linkedList);
  std::swap(numElements, other.numElements);
  std::swap(maxLoad, other.maxLoad);
  std::swap(sizeIndex, other.sizeIndex);
  
  table = std::vector<Iterator>(sizes[sizeIndex], linkedList.end());
  for (Iterator it = linkedList.begin(); it != linkedList.end(); ++it) {
    std::size_t idx = bucket(*it);
    if (table[idx] == linkedList.end()) {
      table[idx] = it;
    }
  }
  
  return *this;
}

HashSet::~HashSet() {
  linkedList.clear();
  table.clear();
  numElements = 0;
}

void HashSet::insert(int key) {
  if (contains(key)) return;

  float estimatedLoad = static_cast<float>(numElements + 1) / sizes[sizeIndex];
  if (estimatedLoad > maxLoad && sizeIndex + 1 < sizes.size()) {
    rehash(sizes[sizeIndex + 1]);
  }

  std::size_t idx = bucket(key);

  if (table[idx] == linkedList.end()) {
    linkedList.push_back(key);
    Iterator newNode = std::prev(linkedList.end());
    table[idx] = newNode;
  } else {
    Iterator bucketHead = table[idx];
    table[idx] = linkedList.insert(bucketHead, key);
  }

  ++numElements;
}

bool HashSet::contains(int key) const {
  std::size_t idx = bucket(key);
  Iterator it = table[idx];

  if (table[idx] == linkedList.end()) return false;

  while (it != linkedList.end() && bucket (*it) == idx) {
    if (*it == key) return true;
    ++it;
  }
  return false;
}

HashSet::Iterator HashSet::find(int key) {
  std::size_t idx = bucket(key);
  Iterator it = table[idx];

  while (it != linkedList.end() && bucket(*it) == idx) {
    if (*it == key) return it;
    ++it;
  }

  return linkedList.end();
}

void HashSet::erase(int key) {
  std::size_t idx = bucket(key);
  Iterator it = table[idx];

  while (it != linkedList.end() && bucket(*it) == idx) {
    if (*it == key) {
      erase(it);
      return;
    }
    ++it;
  }
}

HashSet::Iterator HashSet::erase(HashSet::Iterator it) {
  if (it == linkedList.end()) return it;

  std::size_t idx = bucket(*it);

  if (table[idx] == it) {
    Iterator next = std::next(it);
    while (next != linkedList.end() && bucket(*next) != idx) {
      table[idx] = next;
      break;
    }
    if (next == linkedList.end() || bucket(*next) != idx) {
      table[idx] = end();
    }

    table[idx] = (next != linkedList.end() && bucket(*next) == idx) ? next : end();
  }

  Iterator nextIt = std::next(it);
  linkedList.erase(it);
  --numElements;
  return nextIt;
}

void HashSet::rehash(std::size_t newSize) {
  std::size_t newIndex = sizeIndex;
  while (newIndex < sizes.size() && sizes[newIndex] < newSize) {
    ++newIndex;
  }

  if (newIndex >= sizes.size()) return;

  std::vector<Iterator> newTable(sizes[newIndex], linkedList.end());
  std::list<int> reordered;

  for (auto it = linkedList.begin(); it != linkedList.end(); ) {
    auto current = it++;
    int key = *current;

    std::size_t idx = hash(key, sizes[newIndex]);

    if (newTable[idx] == linkedList.end()) {
      reordered.splice(reordered.end(), linkedList, current);
      newTable[idx] = std::prev(reordered.end());
    } else {
      reordered.splice(newTable[idx], linkedList, current);
      newTable[idx] = current;
    }
  }

  linkedList = std::move(reordered);
  table = std::move(newTable);
  sizeIndex = newIndex;
}

std::size_t HashSet::size() const {
  return numElements;
}

bool HashSet::empty() const {
  return numElements == 0;
}

std::size_t HashSet::bucketCount() const {
  return table.size();
}

std::size_t HashSet::bucketSize(std::size_t b) const {
  if (b >= table.size() || table[b] == linkedList.end()) return 0;

  std::size_t count = 0;
  Iterator it = table[b];
  while (it != linkedList.end() && bucket(*it) == b) {
    ++count;
    ++it;
  }
  return count;
}

std::size_t HashSet::bucket(int key) const {
  return static_cast<std::size_t>(key < 0 ? -static_cast<long long>(key) : key) % sizes[sizeIndex];
}

float HashSet::loadFactor() const {
  return static_cast<float>(numElements) / static_cast<float>(table.size());
}

float HashSet::maxLoadFactor() const {
  return maxLoad;
}

void HashSet::maxLoadFactor(float maxLoad) {
  this->maxLoad = maxLoad;
  if (loadFactor() > maxLoad && sizeIndex + 1 < sizes.size()) {
    std::size_t requiredSize = static_cast<std::size_t>(numElements / maxLoad) + 1;
    rehash(requiredSize);
  }
}
