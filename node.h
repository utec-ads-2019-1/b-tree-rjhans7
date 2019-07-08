#ifndef NODE_H
#define NODE_H

#include "btree.h"
#include <vector>

using namespace std;

template <typename T>


class Node {
    unsigned int size;
    vector<unsigned int> keys;
    vector<Node<T>*> childs;
    bool isLeaf;

    public: 
        Node(unsigned int size, bool isLeaf = true) : size(size), isLeaf(isLeaf) {
            keys.resize(size - 1);
            childs.resize(size);
        }
        bool isLeaft(){
            return isLeaf;
        }
        unsigned int getDegree(){
            return size;
        }

        vector <unsigned int > getKeys(){
            return keys;
        }

        vector <Node <T>*> getChildren(){
            return childs;
        }

        bool search(Node * &pos , T value){
            int i = 0;
            while ((i <pos->getDegree() -1) && (value > pos->getKeys()[i]))
                i++;
            if (i < pos->getDegree()-1 && value == pos->getKeys()[i])
                return true;
            else if (pos->isLeaft())
                return false;
            else if(pos->getKeys()[i] > value)
                return pos->getChildren()[i]->search(pos, value);

            return pos->getChildren()[i+1]->search(pos, value);
        };

        bool splitChildren(Node * &pos, unsigned int childPos){
            auto child = pos->getChildren()[childPos];
            auto newChild = new Node <T> (pos->getDegree(), child->isLeaf());
            for(int i = pos->getDegree()/2; i < pos->getDegree()-1; i++)
                newChild->getKeys().push_back(pos->getKeys()[i]);
            if (!newChild->isLeaft()){
                for(int i = pos->getDegree()/2; i < pos->getDegree(); i++)
                    newChild->getChildren().push_back(pos->getChildren()[i]);
            }
            if(!newChild->isLeaft()){
                for(int i = pos->getDegree()/2; i < pos->getDegree(); i++)
                    newChild->getChildren().pop_back();
            }
            for(int i = pos->getDegree()/2; i < pos->getDegree()-1; i++)
                newChild->getKeys().pop_back();



        }

        bool insertNotFull(Node * &pos, unsigned int newKey){
            int i = pos->getDegree();
            if(pos->isLeaft()){
                pos->getKeys().push_back(newKey);
                sort(pos->getKeys().begin(), pos->getKeys().end());
            }
            while(i > 0 && newKey < pos->getKeys()[i])
                i--;
            i++;

        }


        //virtual bool isLeaf() = 0;

    friend class BTree;
};

#endif