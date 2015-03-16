//Binary Search Tree, derived from Binary Tree
//Vinitra Swamy

#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include "BinaryTree.h"
#include "BinaryNode.h"
#include <iostream>
#include <iomanip>

using namespace std;

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:

    // A pointer to function variable for compare function
     int (*compare)(const ItemType&, const ItemType&);

    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);

    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

    // search for target node
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;

    // internal print node: recursively prints entire tree with level numbers
    void _print(BinaryNode<ItemType>* p, int indent = 0, int level = 1);

public:

    //constructor
    BinarySearchTree(int p(const ItemType&, const ItemType &))
    {compare = p;}


    //copy constructor
    BinarySearchTree(const BinaryTree<ItemType> & tree)
    {
        compare = tree.compare;
        CopyTree(tree);
    }

    // insert a node at the correct location
    bool insert(const ItemType & newEntry);
    
    // remove a node if found
    bool remove(const ItemType & anEntry);
    
    // find a target node
    bool getEntry(const ItemType & target, ItemType & returnedItem) const;
    
    // overloading the "=" operator to copy sourceTree
    BinarySearchTree & operator=(const BinarySearchTree & sourceTree);

    //calls internal print function
    void print();

};

//**************************************************************
// Definition of function insert:
// This function is a public member insertion function that calls 
// the recursive internal _insert function
//**************************************************************

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    BinaryTree<ItemType>::rootPtr = _insert(BinaryTree<ItemType>::rootPtr, newNodePtr);
    return true;
}

//**************************************************************
// Definition of function remove:
// This function is a public member removal function that calls 
// the recursive internal  _remove function
//**************************************************************

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
    bool isSuccessful = false;
    BinaryTree<ItemType>::rootPtr = _remove(BinaryTree<ItemType>::rootPtr, target, isSuccessful);
    return isSuccessful;
}


//**************************************************************
// Definition of function getEntry:
// This function calls the findNode function to see whether node 
// exists, passes back foundNode's value in returnedItem, and
// returns a bool testing for the findNode's success
//**************************************************************

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{

    if(findNode(BinaryTree<ItemType>::rootPtr, anEntry) == 0)
        return false;
    else
        returnedItem = findNode(BinaryTree<ItemType>::rootPtr, anEntry)->getItem();
    return true;

}

//**************************************************************
// Definition of function operator=:
// This function overloads the "=" operator by assigning 
// sourceTree's contents to the BST
//**************************************************************

template<class ItemType>
BinarySearchTree<ItemType> & BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType> & sourceTree)
{
    compare = sourceTree.compare; // assign to function pointer
    this->BinaryTree<ItemType>::operator=(sourceTree);
    return *this;
}

//**************************************************************
// Definition of function _insert:
// This function is a private insert function called by the 
// public member insert function to insert new data into the BST
//**************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,BinaryNode<ItemType>* newNodePtr)
{
    if( nodePtr == 0 )
        return newNodePtr;
        
    if( compare(newNodePtr->getItem(),  nodePtr->getItem()) < 0 )
        nodePtr->setLeftPtr(_insert( nodePtr->getLeftPtr(), newNodePtr ));
        else
            nodePtr->setRightPtr(_insert( nodePtr->getRightPtr(), newNodePtr ));
            return nodePtr; // must return
}

//**************************************************************
// Definition of function _remove:
// This function is a private remove function called recursively 
// by the public member function remove to find and delete 
// data from the BST
//**************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target, bool & success)
{
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }
    if (compare(nodePtr->getItem(), target) > 0) //*****CHANGE THIS*****
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    else if (compare(nodePtr->getItem(), target) < 0) //*****CHANGE THIS*****
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    else	// found the node
    {
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}

//**************************************************************
// Definition of function deleteNode:
// This function is a private delete function called by another 
// function to delete the given node and returns the value of
// nodetoConnectPtr if nodePtr isn't a leaf or null
//**************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        ItemType newNodeValue;
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}

//**************************************************************
// Definition of function removeLeftMostNode:
// This function is a private remove function that calls the
// deleteNode function for the leftmost node on the given node's
// left subtree.
//**************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor = nodePtr->getItem();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }
}

//**************************************************************
// Definition of function findNode:
// This function is a private insert function which searches the 
// Binary Search Tree for a node given a target parameter value.
//**************************************************************

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const
{

    if(nodePtr == 0)
        return 0;
    else if (compare(nodePtr->getItem(), target) < 0)
        return findNode(nodePtr->getLeftPtr(), target);
    else if (compare(nodePtr->getItem(), target) > 0)
        return findNode(nodePtr->getRightPtr(), target);
    else
        return nodePtr;

}

//**************************************************************
// Definition of function _print:
// This function is a private print function which recursively 
// prints the Binary Search Tree in an indented format.
//**************************************************************

template<class ItemType>
void BinarySearchTree<ItemType>::_print(BinaryNode<ItemType>* p, int indent, int level)
{
    if(p != NULL)
    {

        if(p->getLeftPtr())
        {
            _print(p->getLeftPtr(), indent + 4, level + 1);
        }
        
        if(indent) //indent != 0
        {
            cout << setw(indent) << " ";
        }

        cout << level << ". ";
        p->getItem()->write(cout);
        cout << endl;

        if(p->getRightPtr())
        {
            _print(p->getRightPtr(), indent + 4, level + 1);
        }

    }
}
//**************************************************************
// Definition of function print:
// This public print function calls the private recursive print 
// function in the BST class.
//**************************************************************

template<class ItemType>
void BinarySearchTree<ItemType>::print()
{
    int indent = 0;
    int level = 1;
    _print(this->rootPtr, indent, level);
}

#endif // BINARYSEARCHTREE_H_INCLUDED
