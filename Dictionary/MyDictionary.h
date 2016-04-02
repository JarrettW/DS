#ifndef MYDICTIONARY_H_
#define MYDICTIONARY_H_
//词典结构的操作接口规范
template <typename K, typename V>
struct MyDictionary{
  //当前的词条总数
  virtual int size()const = 0;
  //插入词条(禁止雷同词条出现时失败)
  virtual bool put(K, V) = 0;
  //读取词条
  virtual T* get(K k);
  //删除词条
  virtual bool remove(K k) = 0;
};
#endif