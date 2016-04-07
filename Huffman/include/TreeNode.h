//
// Created by brian on 2016/4/2.
//

#ifndef FTPCLIENT_TREENODE_H
#define FTPCLIENT_TREENODE_H


#include <cstdint>

class TreeNode {
public:



    void setOriginValue(uint8_t originValue) {
        TreeNode::originValue = originValue;
    }

    void setChildR(TreeNode *nextR) {
        TreeNode::childR = nextR;
    }

    void setChildL(TreeNode *nextL) {
        TreeNode::childL = nextL;
    }

    void setParent(TreeNode *parent) {
        TreeNode::parent = parent;
    }

    void setLevel(uint32_t level) {
        TreeNode::level = level;
    }


    uint32_t getLevel() const {
        return level;
    }

    TreeNode *getParent() const {
        return parent;
    }

    TreeNode *getChildR() const {
        return childR;
    }

    TreeNode *getChildL() const {
        return childL;
    }

    uint8_t getOriginValue() const {
        return originValue;
    }

    uint32_t getCode() const {
        return code;
    }

    void setCode(uint32_t code) {
        TreeNode::code = code;
    }
private:
    TreeNode *childR;/*value 1*/
    TreeNode *childL;
    TreeNode *parent;

    uint32_t code;

    uint32_t level;
    uint8_t originValue;
};


#endif //FTPCLIENT_TREENODE_H
