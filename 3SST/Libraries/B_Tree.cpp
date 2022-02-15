#include "B_Tree.hpp"
#include <algorithm>

// BTreeNode

BTreeNode::BTreeNode(int size)
    : amountKeysMax(size), size(0), isLeafNode(true) {}

BTreeNode::~BTreeNode() {}

void BTreeNode::operator=(const BTreeNode& b) {
    BTreeNode& a = *this;

    a.arrayChilds = b.arrayChilds;
    a.arrayKeys = b.arrayKeys;
    a.amountKeysMax = b.amountKeysMax;
    a.isLeafNode = b.isLeafNode;
    a.size = b.size;
}

int BTreeNode::getSize() const { return size; }

int BTreeNode::getKeysCapacity() const { return amountKeysMax; }

bool BTreeNode::isLeaf() const { return isLeafNode; }

std::vector<int> BTreeNode::getArrayKeys() const { return arrayKeys; }

std::vector<BTreeNode> BTreeNode::getArrayChilds() const { return arrayChilds; }

void BTreeNode::setArrayKeys(std::vector<int> arrayKeys) {
    this->arrayKeys = arrayKeys;
}
void BTreeNode::setArrayChilds(std::vector<BTreeNode> arrayChilds) {
    this->arrayChilds = arrayChilds;
}

// BTree

BTree::BTree(int t) : size(1), root(2 * t - 1), height(1) {}

BTree::~BTree() {}

void printRecursive(const BTreeNode& current, int width) {
    std::vector<int> keys = current.getArrayKeys();
    std::vector<BTreeNode> childs = current.getArrayChilds();
    int keysSize = keys.size();

    if (current.isLeaf())
        for (int i = 0; i < keysSize; ++i) {
            std::cout << std::string(width, ' ') << keys[i] << "\n";
        }
    else {
        for (int i = 0; i < keysSize; ++i) {
            printRecursive(childs[i], width - 2);
            std::cout << std::string(width, ' ') << keys[i] << "\n";
        }
        printRecursive(childs[keysSize], width - 2);
    }
}

void BTree::print() {
    int rootHeight = (height > 0) ? height * 2 - 2 : 0;
    printRecursive(root, rootHeight);
}

void BTree::insert(int data) {
    BTreeNode* current = &root;
    std::vector<int> keys = (*current).getArrayKeys();
    std::vector<BTreeNode> childs = (*current).getArrayChilds();
    int keysSize = keys.size();
    int capacity = (*current).getKeysCapacity();

    int i = 0;
    for (; i < keysSize; ++i) {
        if (data == keys[i])
            return;
        else if (data < keys[i])
            break;
    }

    if ((*current).isLeaf()) {
        keys.insert(keys.begin() + i, data);
        current->setArrayKeys(keys);

        if (keysSize == capacity) {
            int middle = capacity / 2;
            int middleData = keys[middle];

            BTreeNode left(capacity);
            BTreeNode right(capacity);

            std::vector<int> rightKeys(middle);

            keys.resize(middle);
            for (int i = middle; i < capacity; ++i) {
                rightKeys[i - middle] = keys[i];
            }
            left.setArrayKeys(keys);
            right.setArrayKeys(rightKeys);
            (*current).setArrayKeys({middleData});
            (*current).isLeafNode = false;
            (*current).arrayChilds.push_back(left);
            (*current).arrayChilds.push_back(right);
            size += 2;
            height += 1;
        }
    }
}

bool searchRecursive(const BTreeNode& current, int data) {
    std::vector<int> keys = current.getArrayKeys();
    std::vector<BTreeNode> childs = current.getArrayChilds();
    int keysSize = keys.size();

    if (current.isLeaf())
        for (int i = 0; i < keysSize; ++i) {
            if (data == keys[i])
                return true;
        }
    else {
        for (int i = 0; i < keysSize; ++i) {
            if (data == keys[i])
                return true;
            else if (data < keys[i]) {
                if (searchRecursive(childs[i], data))
                    return true;
            }
        }
        return searchRecursive(childs[keysSize], data);
    }

    return false;
}

bool BTree::search(int data) { return searchRecursive(root, data); }

void BTree::remove(int data) {
    BTreeNode* current = &root;
    std::vector<int> keys = (*current).getArrayKeys();
    std::vector<BTreeNode> childs = (*current).getArrayChilds();
    int keysSize = keys.size();
    // int capacity = (*current).getKeysCapacity();

    // int insertIndex = 0;
    for (int i = 0; i < keysSize; ++i) {
        if (data == keys[i]) {
            keys.erase(keys.begin() + i);
            current->setArrayKeys(keys);
            return;
        } // else if (data < keys[i] || i == keysSize - 1)
          // insertIndex = i;
    }
}

int BTree::getSize() const { return size; }
