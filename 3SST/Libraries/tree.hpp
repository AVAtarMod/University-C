#ifndef TREE_LIB
#define TREE_LIB

template <class T>
class NodeData
{
private:
    T /* data */

public:
    NodeData(T /* args */);
};


template <class T>
class TreeNode
{
private:
    NodeData<T> data;

public:
    TreeNode(T /* args */);
};

template <class T> class Tree {
  private:
    TreeNode<T> root;
  public:
    Tree();
    ~Tree();
};
#endif // TREE_LIB
