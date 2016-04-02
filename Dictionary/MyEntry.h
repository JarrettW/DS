#ifndef MYENTRY_H_
#define MYENTRY_H_
//词条模板类
template <typename K, typename V>
struct MyEntry{
  //关键码
  K key;
  //秩
  V value;
  //默认构造函数
  MyEntry(K k, V v):key(k), value(v) {}
  //拷贝构造函数
  MyEntry(const MyEntry<K, V> &e):key(e.key), value(e.value){ }
  bool operator<(const MyEntry<K, V> &e){
      return key < e.key;
  }
  bool operator>(const MyEntry<K, V> &e){
      return key > e.key;
  }
  bool operator==(const MyEntry<K, V> &e){
      return key == e.key;
  }
  bool operator!=(const MyEntry<K, V> &e){
      return key != e.key;
  }
};
#endif