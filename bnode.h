/***********************************************************************
 * Module:
 *    PAIR
 * Author:
 *    Evan Harrison, Mark Mayeda, Edvaldo Melo, Michael Schmidt
 * Summary:
 *    This program will implement a pair: two values
 ************************************************************************/

#ifndef BNODE_H
#define BNODE_H

#include <iostream> 

template <class T>
class BNode {
  public:
    T data;
    BNode <T> * pLeft;
    BNode <T> * pRight;
    BNode <T> * pParent
    
    //Constructors
    BNode() : data(T()), pLeft(NULL), pRight(NULL), pParent(NULL) {}
    BNode(const T & t) : data(t), pLeft(NULL), pRight(NULL), pParent(NULL) {}
};

// Stand-alone functions

/************************************************************************
* ADDLEFT
************************************************************************/
template <class T>
void addLeft(BNode <T> * pNode, const T & t) throw(const char *) {
  BNode <T> * pAdd;
  try {
    pAdd = new BNode <T> (t);
  }
  catch(std::bad_alloc) {
    throw "ERROR: Unable to allocate a node";
  }
  pAdd->pParent = pNode;
  pNode->pLeft = pAdd;
}

template <class T>
void addLeft(BNode <T> * pNode, BNode <T> * pAdd) {
  if(pAdd != NULL) {
    pAdd->pParent = pNode;
  }
  pNode-pLeft = pAdd;
}

/************************************************************************
* ADDRIGHT
************************************************************************/
template <class T>
void addRight(BNode <T> * pNode, const T & t) throw(const char *) {
  BNode <T> * pAdd;
  try {
    pAdd = new BNode <T> (t);
  }
  catch(std::bad_alloc) {
    throw "ERROR: Unable to allocate a node";
  }
  pAdd->pParent = pNode;
  pNode->pRight = pAdd;
}

template <class T>
void addRight(BNode <T> * pNode, BNode <T> * pAdd) {
  if(pAdd != NULL) {
    pAdd->pParent = pNode;
  }
  pNode-pLeft = pAdd;
}

/************************************************************************
* COPYBTREE
************************************************************************/
template <class T>
void copyBTree(BNode <T> * source) {
  if(source = NULL) {
    return;
  }
  BNode <T> * destination;
  destination = new BNode(source->data);
  
  destination->pLeft = copyBTree(source->pLeft)
  if(destination->pLeft != NULL) {
    destination->pLeft->pParent = destination;
  }
  
  destination->pRight = copyBTree(source->pRight)
  if(destination->pRight != NULL) {
    destination->pRight->pParent = destination;
  }
  
  return destination;
}
  
/************************************************************************
* DELETETREE
************************************************************************/
template <class T>
void deleteBTree(BNode <T> * & node) {
  if(node = NULL) {
    return;
  }
  deleteBTree(node->pLeft);
  deleteBTree(node-pRight);
  delete node;
}
  
/************************************************************************
* INSERTION OPERATOR
************************************************************************/
template <class T>
std::ostream & operator  << (std::ostream & out, const BNode <T> * pHead) {
  if(pHead == NULL) {
  return;
  }
  operator << (out, pHead->pLeft);
  out << " " << pHead->data;
  operator << (out, pHead->pRight);
}

#endif