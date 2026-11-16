#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <queue>
#include <vector>

struct TreeNode
{
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}

    int data;
    TreeNode *left;
    TreeNode *right;
};

class AVLTree
{
private:
    int height(TreeNode *node)
    {
        if (node == nullptr)
            return -1;
        else
        {
            int lheight = height(node->left);
            int rhieght = height(node->right);
            if (lheight > rhieght)
                return lheight + 1;
            else
                return rhieght + 1;
        }
    }

    void BFS(TreeNode *currentNode)
    {
        std::queue<TreeNode *> myQueue;

        myQueue.push(root);

        while (!myQueue.empty())
        {
            std::string currentLevel;
            int queueSize = myQueue.size();

            for (int i = 0; i < queueSize; i++)
            {
                TreeNode *currentNode = myQueue.front();
                currentLevel = currentLevel + std::to_string(currentNode->data) + " ";

                if (currentNode->left != nullptr)
                    myQueue.push(currentNode->left);
                if (currentNode->right != nullptr)
                    myQueue.push(currentNode->right);
                myQueue.pop();
            }
            std::cout << currentLevel << "\n";
        }
    }

    void leftToRightTrav(TreeNode *currentNode, int level, std::vector<int> &res)
    {
        if (currentNode == nullptr)
            return;

        if (level == 1)
        {
            res.push_back(currentNode->data);
        }
        else
        {
            leftToRightTrav(currentNode->left, level - 1, res);
            leftToRightTrav(currentNode->right, level - 1, res);
        }
    }

    void rightToLeftTrav(TreeNode *currentNode, int level, std::vector<int> &res)
    {
        if (currentNode == nullptr)
            return;

        if (level == 1)
        {
            res.push_back(currentNode->data);
        }
        else
        {
            rightToLeftTrav(currentNode->right, level - 1, res);
            rightToLeftTrav(currentNode->left, level - 1, res);
        }
    }

    std::vector<int> zigZagTraversal(TreeNode *currentNode)
    {
        std::vector<int> res;
        bool leftToRight = true;
        int h = height(currentNode);

        for (int i = 1; i <= h + 1; i++)
        {
            if (leftToRight)
                leftToRightTrav(currentNode, i, res);
            else
                rightToLeftTrav(currentNode, i, res);

            leftToRight = !leftToRight;
        }

        return res;
    }

    bool searchValue(int value, TreeNode *current)
    {
        if (current == nullptr)
            return false;
        else if (value == current->data)
            return true;
        else if (value < current->data)
            return searchValue(value, current->left);
        else
            return searchValue(value, current->right);
    }

    int getBalanceFactor(TreeNode *currentNode)
    {
        if (currentNode == nullptr)
            return -1;
        else
            return height(currentNode->left) - height(currentNode->right);
    }

    TreeNode *leftRotate(TreeNode *x)
    {
        TreeNode *y = x->right;
        TreeNode *T2 = y->left;

        y->left = x;
        x->right = T2;
        return y;
    }

    TreeNode *rightRotate(TreeNode *y)
    {
        TreeNode *x = y->left;
        TreeNode *T2 = x->right;

        x->right = y;
        y->left = T2;
        return x;
    }

    TreeNode *minValueNode(TreeNode *node)
    {
        TreeNode *currentNode = node;
        while (currentNode->left != nullptr)
            currentNode = currentNode->left;
        return currentNode;
    }

    TreeNode *insertNode(TreeNode *node, int &value)
    {
        if (node == nullptr)
        {
            return new TreeNode{value};
        }

        if (value < node->data)
        {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insertNode(node->right, value);
        }
        else
            return node;

        int bf = getBalanceFactor(node);

        if (bf > 1 && value < node->left->data)
            return rightRotate(node);
        if (bf < -1 && value > node->right->data)
            return leftRotate(node);
        if (bf > 1 && value > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (bf < -1 && value < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    TreeNode *deleteNode(TreeNode *node, int value)
    {
        if (node == nullptr)
            return node;
        else if (value < node->data)
            node->left = deleteNode(node->left, value);
        else if (value > node->data)
            node->right = deleteNode(node->right, value);
        else
        {
            if (node->left == nullptr)
            {
                TreeNode *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                TreeNode *temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                TreeNode *temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        int bf = getBalanceFactor(node);

        if (bf == 2 && getBalanceFactor(node->left) >= 0)
            return rightRotate(node);
        else if (bf == 2 && getBalanceFactor(node->left) == -1)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        else if (bf == -2 && getBalanceFactor(node->right) <= 0)
            return leftRotate(node);
        else if (bf == -2 && getBalanceFactor(node->right) == 1)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    TreeNode *root;

public:
    AVLTree() { root = nullptr; }

    bool find(int value)
    {
        return searchValue(value, root);
    }

    void insert(int value)
    {
        root = insertNode(root, value);
    }

    void deleteVal(int value)
    {
        root = deleteNode(root, value);
    }

    void BFSprint()
    {
        if (root == nullptr)
            std::cout << "\n";
        else
        {
            BFS(root);
        }
    }

    void zigZagPrint()
    {
        if (root == nullptr)
            std::cout << "\n";
        else
        {
            std::vector<int> res = zigZagTraversal(root);
            for (int i = 0; i < res.size(); i++)
                std::cout << res[i] << " ";
        }
        std::cout << "\n";
    }

    bool chkIfRootEmpty()
    {
        if (root == nullptr)
            return true;
        else
            return false;
    }
};
#endif