//
// Created by brian on 3/30/16.
//

#ifndef FTPCLIENT_HUFFMANENCODER_H
#define FTPCLIENT_HUFFMANENCODER_H


#include <cstdint>
#include <fstream>
#include <map>
#include <vector>
#include "TreeNode.h"
#include <bitset>
#define  RIGHT_BIT 0x00000001
#define RIGHT_BIT_MASK (UINT32_MAX-1)


using  namespace std;

class Huffman {
public:
/*    struct HuffmanTreeNode{
        HuffmanTreeNode *nextR;*//*value 1*//*
        HuffmanTreeNode *nextL;*//*value 0*//*
        HuffmanTreeNode *parent;
//        bool isOne;
        uint32_t level;
//        uint8_t encodedValue;
        uint8_t originValue;
    };*/
    /*struct HuffmanTree{
        HuffmanTreeNode topNode;
        uint32_t depth;
    };*/

    struct Occurrence {
        uint32_t counts;
        uint8_t originalValue;
        bool isRoot;
        TreeNode *node;
    };


    Huffman(const string &inputFileName, const string &outputFileName, const string &treeFileName);




    /*function*/
    int encode();/*encoder*/
    bool decode();/*decode*/


    /*setter*/


    void setInputFileName(const string &inputFileName) {
        Huffman::inputFileName = inputFileName;
    }

    void setOutputFileName(const string &outputFileName) {
        Huffman::outputFileName = outputFileName;
    }

    void setTreeFileName(const string &treeFileName) {
        Huffman::treeFileName = treeFileName;
    }





private:
/*file name*/
    string inputFileName;
    string outputFileName;
    string treeFileName;

    vector<Occurrence> occurrenceVector;/* struct Occurrence  */
    vector<TreeNode*> leafsVector;
    TreeNode currentRootNode;

    bool clearVariables();



    /*compare function*//*ascendant*/
    static bool compareOccurrence(Occurrence a, Occurrence b){
        if (a.counts<b.counts){
            return true;
        } else{
            return false;
        }
    }

    static bool compareNode(TreeNode *a, TreeNode *b){
        if (a->getCode()<b->getCode()){
            return true;
        } else{
            return false;
        }
    }




};


/*Tree file
 *  leaf-->root   level
 * [  10110100  , 00001010 ,    5    ]
 * [   <path>   , <orgVal> , <level> ]
 *
 * <original file length(bytes)>
 * */


#endif
