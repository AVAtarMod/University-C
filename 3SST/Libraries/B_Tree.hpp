#ifndef B_TREE_LIB
#define B_TREE_LIB

#include <iomanip>
#include <iostream>
#include <vector>

class BTreeNode {
  private:
    int amountKeysMax;
    int size;
    bool isLeafNode;
    std::vector<int> arrayKeys;
    std::vector<BTreeNode> arrayChilds;

    friend class BTree;
  public:
    BTreeNode(int size);
    ~BTreeNode();

    void operator=(const BTreeNode& b);

    int getSize() const;
    int getKeysCapacity() const;
    bool isLeaf() const;
    std::vector<int> getArrayKeys() const;
    std::vector<BTreeNode> getArrayChilds() const;

    void setArrayKeys(std::vector<int> arrayKeys);
    void setArrayChilds(std::vector<BTreeNode> arrayChilds);
};

class BTree {
  private:
    int size;
    BTreeNode root;
    int height;

    void update();
    void insertRecursiveUp(BTreeNode* current,
                                int data);
    void insertRecursiveDown(BTreeNode* parent, BTreeNode& current,
                                int data);
  public:
    BTree(int nodeSize);
    ~BTree();

    void print();
    void insert(int data);
    bool search(int data);
    void remove(int data);

    int getSize() const;
};

#endif // B_TREE_LIB
