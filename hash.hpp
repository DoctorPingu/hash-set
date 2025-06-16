#ifndef HASH_HPP_
#define HASH_HPP_

#include <list>
#include <vector>

class HashSet {
 private:
  const std::vector<std::size_t> sizes {1ul, 13ul, 59ul, 127ul, 257ul, 541ul,
    1'109ul, 2'357ul, 5'087ul, 10'273ul, 20'753ul, 42'043ul,
    85'229ul, 172'933ul, 351'061ul, 712'697ul, 1'447'153ul, 2'938'679ul};

  std::list<int> linkedList;
  std::vector<std::list<int>::iterator> table;
  std::size_t numElements;
  float maxLoad;
  std::size_t sizeIndex;
  std::size_t hash(int key, std::size_t size) const;

 public:
  using Iterator = std::list<int>::iterator;

  HashSet();

  HashSet(const HashSet&);

  HashSet& operator=(HashSet);

  ~HashSet();

  void insert(int key);

  bool contains(int key) const;

  void erase(int key);

  void rehash(std::size_t newSize);

  Iterator find(int key);

  Iterator erase(Iterator it);

  std::size_t size() const;

  bool empty() const;

  std::size_t bucketCount() const;

  std::size_t bucketSize(std::size_t b) const;

  std::size_t bucket(int key) const;

  float loadFactor() const;

  float maxLoadFactor() const;

  void maxLoadFactor(float maxLoad);

  Iterator begin();

  Iterator end();
};

#endif      // HASH_HPP_
