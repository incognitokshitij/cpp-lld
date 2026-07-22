#include <iostream>
#include <unordered_map>
using namespace std;

// ---------------- top-level interface ----------------
// calling code only ever depends on this
class ICache {
public:
  virtual int get(int key) = 0;
  virtual void put(int key, int value) = 0;
  virtual ~ICache() {}
};

// ---------------- LRUCache: owns storage AND ordering, no split
// ----------------
class LRUCache : public ICache {
  struct Node {
    int key, value;
    Node *prev;
    Node *next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
  };

  int capacity;
  unordered_map<int, Node *>
      nodeMap; // key -> node, node holds the value directly now
  Node *head;
  Node *tail;

  void unlink(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void pushFront(Node *node) {
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
  }

public:
  LRUCache(int cap) : capacity(cap) {
    head = new Node(-1, -1);
    tail = new Node(-1, -1);
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) override {
    if (nodeMap.find(key) == nodeMap.end())
      return -1;
    Node *node = nodeMap[key];
    unlink(node);
    pushFront(node);
    return node->value;
  }

  void put(int key, int value) override {
    if (nodeMap.find(key) != nodeMap.end()) {
      Node *node = nodeMap[key];
      node->value = value;
      unlink(node);
      pushFront(node);
      return;
    }

    if ((int)nodeMap.size() == capacity) {
      Node *lru = tail->prev;
      unlink(lru);
      nodeMap.erase(lru->key);
      delete lru;
    }

    Node *newNode = new Node(key, value);
    pushFront(newNode);
    nodeMap[key] = newNode;
  }

  ~LRUCache() {
    Node *curr = head;
    while (curr) {
      Node *next = curr->next;
      delete curr;
      curr = next;
    }
  }
};

// ---------------- LFUCache: owns storage AND ordering, no split
// ----------------
class LFUCache : public ICache {
  struct Node {
    int key, value, cnt;
    Node *prev;
    Node *next;
    Node(int k, int v)
        : key(k), value(v), cnt(1), prev(nullptr), next(nullptr) {}
  };

  struct DoublyLinkedList {
    int size;
    Node *head;
    Node *tail;

    DoublyLinkedList() {
      head = new Node(0, 0);
      tail = new Node(0, 0);
      head->next = tail;
      tail->prev = head;
      size = 0;
    }

    void addFront(Node *node) {
      Node *temp = head->next;
      node->next = temp;
      node->prev = head;
      head->next = node;
      temp->prev = node;
      size++;
    }

    void removeNode(Node *delnode) {
      Node *delprev = delnode->prev;
      Node *delnext = delnode->next;
      delprev->next = delnext;
      delnext->prev = delprev;
      size--;
    }

    ~DoublyLinkedList() {
      Node *curr = head;
      while (curr) {
        Node *next = curr->next;
        delete curr;
        curr = next;
      }
    }
  };

  int capacity;
  unordered_map<int, Node *> keyNode;
  unordered_map<int, DoublyLinkedList *> freqListMap;
  int minFreq = 0;

  void promote(Node *node) {
    freqListMap[node->cnt]->removeNode(node);
    if (node->cnt == minFreq && freqListMap[node->cnt]->size == 0) {
      minFreq++;
    }

    DoublyLinkedList *nextHigherFreqList;
    if (freqListMap.find(node->cnt + 1) != freqListMap.end()) {
      nextHigherFreqList = freqListMap[node->cnt + 1];
    } else {
      nextHigherFreqList = new DoublyLinkedList();
    }
    node->cnt += 1;
    nextHigherFreqList->addFront(node);
    freqListMap[node->cnt] = nextHigherFreqList;
  }

public:
  LFUCache(int cap) : capacity(cap) {}

  int get(int key) override {
    if (keyNode.find(key) == keyNode.end())
      return -1;
    Node *node = keyNode[key];
    int val = node->value;
    promote(node);
    return val;
  }

  void put(int key, int value) override {
    if (capacity == 0)
      return;

    if (keyNode.find(key) != keyNode.end()) {
      Node *node = keyNode[key];
      node->value = value;
      promote(node);
      return;
    }

    if ((int)keyNode.size() == capacity) {
      DoublyLinkedList *list = freqListMap[minFreq];
      Node *toEvict = list->tail->prev;
      keyNode.erase(toEvict->key);
      list->removeNode(toEvict);
      delete toEvict;
    }

    minFreq = 1;
    DoublyLinkedList *listFreq;
    if (freqListMap.find(minFreq) != freqListMap.end()) {
      listFreq = freqListMap[minFreq];
    } else {
      listFreq = new DoublyLinkedList();
    }

    Node *node = new Node(key, value);
    listFreq->addFront(node);
    keyNode[key] = node;
    freqListMap[minFreq] = listFreq;
  }
};

// ---------------- driver ----------------
int main() {
    
  cout << "=== LRUCache (matches the LeetCode example) ===" << endl;
  ICache *lruCache = new LRUCache(2);
  lruCache->put(1, 1);
  lruCache->put(2, 2);
  cout << lruCache->get(1) << endl; // 1
  lruCache->put(3, 3);              // evicts 2
  cout << lruCache->get(2) << endl; // -1
  lruCache->put(4, 4);              // evicts 1
  cout << lruCache->get(1) << endl; // -1
  cout << lruCache->get(3) << endl; // 3
  cout << lruCache->get(4) << endl; // 4
  delete lruCache;

  cout << "\n=== LFUCache, same ICache interface ===" << endl;
  ICache *lfuCache = new LFUCache(2);
  lfuCache->put(1, 1);
  lfuCache->put(2, 2);
  lfuCache->get(1);
  lfuCache->get(1);
  lfuCache->put(3, 3);              // evicts key 2, lowest frequency
  cout << lfuCache->get(1) << endl; // 1
  cout << lfuCache->get(2) << endl; // -1
  cout << lfuCache->get(3) << endl; // 3
  delete lfuCache;

  return 0;
}