#ifndef __TREENODE_H__
#define __TREENODE_H__

class TreeNode {
  public:
    TreeNode();
    TreeNode(int data);

    void setData(int data);
    void setLeft(TreeNode *left);
    void setRight(TreeNode *right);

    int getData();
    TreeNode *getLeft();
    TreeNode *getRight();

  private:
    int data;
    TreeNode *left;
    TreeNode *right;
};

#endif
