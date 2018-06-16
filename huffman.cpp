/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include <cassert>         // for ASSERT
#include <string>          // for STRING: binary representation of codes
#include "bnode.h"         // for BINARY_NODE class definition
#include "list.h"
#include "pair.h"          // for PAIR container
#include "huffman.h"       // for HUFFMAN() prototype

using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::string;
using std::bad_alloc;
using namespace custom;

/*****************************************************************************
 * DISPLAY HUFFMAN
 * Displays the Huffman Codes for the leaf nodes of a completed Huffman Tree;
 * takes a list of the leaf nodes as a parameter
 * ***************************************************************************/
void displayHuffman(const list <BNode <Pair <string, float> > * > & leafNodes)
{
   string code;
   BNode <Pair <string, float> > * pNode;
   BNode <Pair <string, float> > * pPar;
   BNode <Pair <string, float> > * pLeaf;
 
   list <BNode <Pair <string, float> > * > :: iterator leafIt = leafNodes.begin();

   // loop through all leaf nodes in list
   while (leafIt != leafNodes.end())
   {
      pLeaf = *leafIt;
      pNode = pLeaf;

      // create Huffman code by moving from leaf to root
      while (pNode->pParent)
      {
         pPar = pNode->pParent;
         if (pNode == pPar->pLeft)
            code = '0' + code;
         else
            code = '1' + code;
         pNode = pNode->pParent;
      }

      cout << pLeaf->data.getFirst() << " = " << code << endl;

      code.clear();
            
      leafIt++;
   }
}

/*****************************************************************************
 * COMBINE TREES
 * Combines a list of individual leaf nodes into a complete Huffman tree with
 * a single root node; the list stores pointers to existing root nodes as the
 * trees are combined
 *****************************************************************************/
void combineTrees(list <BNode <Pair <string, float> > * > & treeList)
{
   bool begin;            // smallIt or nextIt == begin() iterator
   bool smallBeforeNext;  // smallIt comes before nextIt
   float frequency;      

   // pointer variables
   BNode <Pair <string, float> > * pLeft;
   BNode <Pair <string, float> > * pRight;
   BNode <Pair <string, float> > * pNew;

   // iterator variables
   list <BNode <Pair <string, float> > * > :: iterator smallIt;
   list <BNode <Pair <string, float> > * > :: iterator nextIt;
   list <BNode <Pair <string, float> > * > :: iterator insertIt;
   list <BNode <Pair <string, float> > * > :: iterator lastIt;
   list <BNode <Pair <string, float> > * > :: iterator endIt;
   list <BNode <Pair <string, float> > * > :: iterator testIt;

   // loop until there is only one root node remaining
   while (treeList.size() > 1)
   {
      // get iterators to the two smallest frequencies
      smallBeforeNext = findSmallest(treeList, smallIt, nextIt);

      // if the frequency values are the same, leftmost node connects
      // to left, righmost node connects to the right
      if ((*smallIt)->data == (*nextIt)->data && !smallBeforeNext)
      {
         pLeft = *nextIt;
         pRight = *smallIt;
      }
      // otherwise, the smallest value connects to the left
      else
      {
         pLeft = *smallIt;
         pRight = *nextIt;
      }

      // create a new node with combined frequency of child nodes
      frequency = pLeft->data.getSecond() + pRight->data.getSecond();
      Pair <string, float> dataPair("", frequency);
      pNew = new BNode <Pair <string, float> > (dataPair);

      // connect left and right nodes to new node
      addLeft(pNew, pLeft);
      addRight(pNew, pRight);

      // set begin to true if smallIt or nextIt is at begin() iterator
      if (smallIt == treeList.begin() || nextIt == treeList.begin())
         begin = true;
      else
         begin = false;

      // erase the nodes at smallIt and nextIt
      smallIt = treeList.erase(smallIt);
      nextIt = treeList.erase(nextIt);


      // insert new node in the original position of the leftmost child node
      // insert last list node in the original position of the rightmost node
      if (smallBeforeNext)
      {
         insertIt = smallIt;
         lastIt = nextIt;
      }
      else
      {
         insertIt = nextIt;
         lastIt = smallIt;
      }

      // push iterators one more to the right because the erase() method
      // pushed us to the left, except if the leftmost erased value was
      // at the beginning of the list
      if (!begin)
         ++insertIt;

      ++lastIt;

      // now we are ready to insert the new node
      treeList.insert(insertIt, pNew);


      // find the iterator to the last existing node in the list
      endIt = treeList.begin();
      testIt = treeList.begin();
      ++testIt;
      while (testIt != treeList.end())
      {
         ++testIt;
         ++endIt;
      }

      // finally, move the last node in the list
      treeList.insert(lastIt, *endIt);
      treeList.erase(endIt);
         
   }
   
}

/******************************************************************************
 * FIND SMALLEST
 * Finds the two smallest frequency values of the remaining root nodes in the
 * treeList; returns iterators by reference that point to these nodes; also
 * returns a bool value indicating if the smallest value comes before the
 * next smallest value in the list
 *
 * smallIt:  iterator to the smallest value in the list
 * nextIt:   iterator to the next smallest value in the list
 * smallPos: position of the smallest value
 * nextPos:  position of the next smallest value
 ******************************************************************************/
bool findSmallest(const list <BNode <Pair <string, float> > * > & treeList,
                  list <BNode <Pair <string, float> > * > :: iterator & smallIt,
                  list <BNode <Pair <string, float> > * > :: iterator & nextIt)
{
   int smallPos = 0;
   int numLoops = 0;

   smallIt = treeList.begin();
   list <BNode <Pair <string, float> > * > :: iterator findIt = smallIt;

   // loop through list to find smallest value
   while (findIt != treeList.end())
   {
      if ((*findIt)->data < (*smallIt)->data)
      {
         smallIt = findIt;
         smallPos = numLoops;
      }
      ++numLoops;
      ++findIt;
   }

   numLoops = 0;
   int nextPos = 0;
   nextIt = treeList.begin();

   // start loop at next iterator value if smallIt == begin()
   if (smallIt == nextIt)
      ++nextIt;
   findIt = nextIt;

   // loop through list again to find next smallest value
   while (findIt != treeList.end())
   {
      // skip smallIt this time around
      if (findIt != smallIt && (*findIt)->data < (*nextIt)->data)
      {
         nextIt = findIt;
         nextPos = numLoops;
      }
      ++numLoops;
      ++findIt;
   }            

   // return value for smallBeforeNext
   if (smallPos < nextPos)
      return true;
   else
      return false;
}

         

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string & fileName)
{
   Pair <string, float> dataPair;
   BNode <Pair <string, float> > * pLeaf;
   list <BNode <Pair <string, float> > * > treeList;
   
   ifstream fin(fileName.c_str());

   // read file data into list
   while (fin >> dataPair)
   {
      pLeaf = new BNode <Pair <string, float> > (dataPair);
      treeList.push_back(pLeaf);
   }

   fin.close();

   // preserve a copy of the leaf node list for the display function
   list <BNode <Pair <string, float> > * > leafNodes(treeList);

   combineTrees(treeList);

   displayHuffman(leafNodes);

   // free up memory from Huffman tree
   deleteBTree(*treeList.begin());
  
}
