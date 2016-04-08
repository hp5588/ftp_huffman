//
// Created by brian on 3/30/16.
//

#include <list>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include "Huffman.h"
#include "TreeNode.h"


Huffman::Huffman(const string &inputFileName, const string &outputFileName, const string &treeFileName) {
    this->inputFileName = inputFileName;
    this->outputFileName = outputFileName;
    this->treeFileName = treeFileName;
}


int Huffman::encode() {
    this->clearVariables();

    fstream inFile,outFile,treeFile;


    /*open files*/
    inFile.open(inputFileName,fstream::binary | fstream::in );
    outFile.open(outputFileName,fstream::binary | fstream::in | fstream::out | fstream::trunc);
    treeFile.open(treeFileName, fstream::binary | fstream::in | fstream::out | fstream::trunc);

    if (inFile.fail()||outFile.fail()||treeFile.fail()){
        cout << "fail to open file" <<endl;
        return -1;
    }

    /*clean occurrence vector*/
    occurrenceVector.erase(occurrenceVector.begin(),occurrenceVector.end());

    /*generate occurrence vector*/
    while (!inFile.eof()){
        uint8_t buffer[1];
        buffer[0] = 0;

        /*read a byte*/
        inFile.read((char *) buffer, 1);
        if (inFile.eof()){
            break;
        }

        /*find in the occurrence vector*/
        bool found = false;
        for (int i = 0; i < occurrenceVector.size(); ++i) {
            Occurrence *oc = &occurrenceVector[i];
            if ((oc->originalValue ^ buffer[0])==0) {
                /*two value are the same*/
                oc->counts ++;
                found = true;
                break;
            }
        }

        /*add to vector if shown first time*/
        if (!found){
            /*init new Occurrence*/
            Occurrence oc;
            oc.counts = 1;
            oc.isRoot = false;
            oc.originalValue = buffer[0];
                TreeNode *leafNode = new TreeNode();
                leafNode->setChildL(0);
                leafNode->setChildR(0);
                leafNode->setOriginValue(oc.originalValue);
                leafNode->setParent(0);/*set parent in next section*/

            /*set tree leaf pointer for each occurrence*/
            oc.node = leafNode;

            occurrenceVector.push_back(oc);
            leafsVector.push_back(leafNode);
        }

    }




    while (occurrenceVector.size()>1){
        /*sort the occurrence in ascendant way*/
        sort(occurrenceVector.begin(),occurrenceVector.end(),this->compareOccurrence);

        /*take the smallest two in the occurrence list and combine into new root handle*/
        Occurrence oc1 = occurrenceVector.at(0);
        Occurrence oc2 = occurrenceVector.at(1);

        /*new HuffmanNode and oc*/
        TreeNode *rootNode = new TreeNode();
        Occurrence rootOc;

        /*get node pointer inside occurrence*/
        TreeNode *node1 = oc1.node;
        TreeNode *node2 = oc2.node;

        /*setup relationship*/
        rootNode->setParent(0);
        node1->setParent(rootNode);
        node2->setParent(rootNode);

        /*large value on the right*/
        if (oc1.originalValue < oc2.originalValue){
            rootNode->setChildR(node2);
            rootNode->setChildL(node1);
        } else{
            rootNode->setChildR(node1);
            rootNode->setChildL(node2);
        }

        /*replace two oc with new root oc*/
        uint32_t counts = oc1.counts + oc2.counts;
        rootOc.counts = counts;
        rootOc.isRoot = true;
        rootOc.originalValue = 0;
        rootOc.node = rootNode;

        /*update occurrence vector*/
        occurrenceVector.erase(occurrenceVector.begin(),occurrenceVector.begin()+2);
        occurrenceVector.insert(occurrenceVector.begin(),rootOc);


    }

    /*find out the path code for each leaf*/
    /*traceback to root to gain the path(encode)*/
    /*ex. (root) <-0010 1111 ->(leaf)*/
    for (TreeNode *leafNode : leafsVector) {
        TreeNode *currentNode = leafNode;
        TreeNode *parentNode = leafNode->getParent();
        uint32_t codePath = 0;
        uint32_t level= 0;

        while (parentNode) {
            /*find out which branch I belong to*/
            if (parentNode->getChildR() == currentNode) {
                /*I am on the right hand side, means I am equal to 1*/
                codePath = codePath | (RIGHT_BIT<<level);
//                codePath = codePath << 1
            } else if (parentNode->getChildL() == currentNode){
                /*I am on the left hand side, means I am equal to 0*/
//                codePath = codePath << 1;
            } else {
                cout << "structure error" <<endl;
                return -1;
            }

            /*get grand parents node*/
            currentNode = parentNode;
            parentNode = parentNode->getParent();
            level++;
        }

        leafNode ->setLevel(level);
        leafNode ->setCode(codePath);

    }

    /*encode file*/
    /*find length of file*/
    inFile.clear();
    inFile.seekg(0,inFile.end);
    long int sizeOfinputFile = inFile.tellg();
    if (sizeOfinputFile<0){
        cout << "can't get input file size" <<endl;
        return -1;
    }

//    bitset<sizeOfinputFile> outputBitSet;



    /*bool vector as bit*/
    vector<bool> outputData(sizeOfinputFile*8);/*at least as long as input*/
    uint64_t bitCount=0;

    /*loop through each byte and convert it to corresponding code*/
    inFile.seekp(0,ios::beg);
    while (!inFile.eof()){
        uint8_t buffer[1];
        buffer[0] = 0;

        inFile.read((char *) buffer, 1);

        if (inFile.eof()){
            break;
        }

        TreeNode *correspondingLeafNode = 0;
        /*find the data in leaf vector*/
        for (TreeNode *leafNode : leafsVector){
            if ((leafNode->getOriginValue()^buffer[0])==0){
                correspondingLeafNode = leafNode;
            }
        }

        if (correspondingLeafNode){
            uint32_t level = correspondingLeafNode->getLevel();
            /*check if output vector has enough space*/
            if ((bitCount+level) > outputData.size()){
                /*alloc more space assuming each encode length not more than 4 byte*/
                outputData.insert(outputData.end(),32,0);
            }

            for (int i = 0; i < level ; ++i) {
                outputData[bitCount++] = correspondingLeafNode->getCode()& (0x0001 <<(level-i-1));
            }
        } else{
            /*can't find in occurrence vector*/
            cout << "encode error: can't find corresponding byte to encode" <<endl;
            return  -1;
        }
    }



    /*save tree file in csv format*/
    for (TreeNode *leafNode : leafsVector) {
        string leafDataString =
                string(bitset<32>(leafNode->getCode()).to_string())
                .append(",")
                .append(string(bitset<8>(leafNode->getOriginValue()).to_string()))
                .append(",")
                    .append(to_string(leafNode->getLevel()))
                        .append("\n");

        treeFile.write(leafDataString.c_str(),leafDataString.size());
    }

    /*record data legth*/
    string lenghtString = to_string(sizeOfinputFile);
    treeFile.write(lenghtString.c_str(),lenghtString.size());


    /*save to output file*/
    /*convert vector<bit> to char */
    uint8_t outputBuffer[bitCount/8+1];
    /*clean buffer*/
    memset((char *) outputBuffer, 0 , sizeof(outputBuffer));
    for (int j = 0; j < bitCount; ++j) {
        bool bit = outputData.at(j);
        uint8_t pos = (uint8_t) (7-(j % 8));
        outputBuffer[j/8] |= (bit << pos);
    }
    uint8_t bytesLeft = bitCount%8;
    if (bytesLeft){
        outFile.write((const char *) outputBuffer, bitCount/8+1);
    }else{
        outFile.write((const char *) outputBuffer, bitCount/8);
    }

    cout << "compression rate: "<< to_string((bitCount/(sizeOfinputFile*8.0))*100.0) << " %" <<endl;


    /*close files*/
    inFile.close();
    outFile.close();
    treeFile.close();



    return true;
}

bool Huffman::decode() {

    /*clear varibles*/
    this->clearVariables();

    /*open input file*/
    fstream inFile,outFile,treeFile;


    /*open files*/
    inFile.open(inputFileName,fstream::binary | fstream::in );
    outFile.open(outputFileName,fstream::binary | fstream::in | fstream::out | fstream::trunc);
    treeFile.open(treeFileName, fstream::binary | fstream::in | fstream::out );

    if (inFile.fail()||outFile.fail()||treeFile.fail()){
        cout << "fail to open file" <<endl;
        return -1;
    }



    /*read file into leafs vector*/
    string aLine;
    getline(treeFile,aLine,'\n');
    int orgDataLength;

    while (!treeFile.eof()){
        stringstream ss;
        ss << aLine;

        string codeString;
        string orgValString;
        string levelString;

        getline(ss,codeString,',');
        getline(ss,orgValString,',');
        getline(ss,levelString);


        TreeNode *leafNode = new TreeNode();
        leafNode->setCode((uint32_t) bitset<32>(codeString).to_ulong());
        leafNode->setOriginValue((uint8_t) bitset<8>(orgValString).to_ulong());
        leafNode->setLevel((uint32_t) stoi(levelString));


        leafsVector.push_back(leafNode);

        getline(treeFile,aLine,'\n');
        if (treeFile.eof()){
            /*last line*/
            orgDataLength = stoi(aLine);
            break;
        }

    }

    /*find the highest level*/
    uint32_t highestLevel=0;
    for (TreeNode *leafNode : leafsVector){
        if (leafNode->getLevel()>highestLevel){
            highestLevel = leafNode->getLevel();
        }
    }

    /*for each layer traceback to root and reconstruct the relation*/
    /*start from layer 0 (leafs with highest level)*/
    vector<TreeNode*> currentLayer;
    vector<TreeNode*> upperLayer;

    for (int layer = 0; layer < highestLevel; ++layer) {
        uint32_t currentLevel = highestLevel-layer;
        /*find the leafs which are in this layer*/
        for (TreeNode *leafNode : leafsVector){
            if (leafNode->getLevel()==currentLevel){
                currentLayer.push_back(leafNode);
            }
        }

        /*sort according to code value*/
        sort(currentLayer.begin(),currentLayer.end(),compareNode);

        /*assume all node can pair up*/
        /*find sibling and combine into parents for upper layer*/
        for (int i = 0; i < currentLayer.size() / 2; ++i) {
            /*setup parents to be added*/
            TreeNode *parents = new TreeNode();
            TreeNode *node = currentLayer[i*2];
            TreeNode *nodeCmp = currentLayer[i*2+1];

            parents->setLevel(currentLevel-1);
            /*set path and children for upper layer's nodes*/
            parents->setCode(node->getCode()>>1);
            if (node->getCode() & 0x01){
                /*node is on the right hand side*/
                parents->setChildR(node);
                parents->setChildL(nodeCmp);
            }else {
                /*node is on the left hand side*/
                parents->setChildR(nodeCmp);
                parents->setChildL(node);
            }

            /*set parents for both node*/
            node->setParent(parents);
            nodeCmp->setParent(parents);

            /*put parent into upper layer*/
            upperLayer.push_back(parents);

        }

        /*move to upper layer*/
        currentLayer = upperLayer;
        upperLayer.clear();
    }

    /*level 0 (highest layer) is the root*/
    if (currentLayer.size()!=1){
        cout << "tree reconstruction error" <<endl;
        return -1;
    }
    TreeNode *rootNode = currentLayer.at(0);


    vector<bool> inputDataBitVector;
    while (!inFile.eof()){
        char buffer[100];
        memset(buffer,0,sizeof(buffer));
        inFile.read(buffer,sizeof(buffer));
        uint16_t byteRead = (uint16_t) inFile.gcount();

        for (int i = 0; i < byteRead; ++i) {
            uint8_t readChar = (uint8_t) buffer[i];
            for (int j = 0; j < 8; ++j) {
                inputDataBitVector.push_back((bool) ((readChar >> (7 - j)) & 0x01));
            }
        }
    }

    /*decoding*/
    /*for each bit*/
    vector<uint8_t > outputByteVector;
    TreeNode *currentNode = rootNode;
    for(bool bit : inputDataBitVector){
        /*follow path from root*/

        /*translate back as char when find child of current node is nil*/
        if (bit){
            /*go right*/
            currentNode = currentNode->getChildR();
        } else{
            /*go left*/
            currentNode = currentNode->getChildL();
        }
        if (!currentNode->getChildR()||!currentNode->getChildL()){
            /*value found*/
            outputByteVector.push_back(currentNode->getOriginValue());

            /*put node pointer back to root*/
            currentNode = rootNode;
        }

    }


    /*save buffer data into output file*/
    outFile.write((const char *) &outputByteVector[0], orgDataLength);


    /*close all file*/
    inFile.close();
    outFile.close();
    treeFile.close();

    return true;
}

bool Huffman::clearVariables() {
    leafsVector.clear();
    occurrenceVector.clear();
    currentRootNode = TreeNode();


    return true;
}















