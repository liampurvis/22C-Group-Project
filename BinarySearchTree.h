#ifndef Assignment_4_BinarySearchTree_h
#define Assignment_4_BinarySearchTree_h

#include "BinaryTree.h"
#include "BinaryNode.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    //*********** ADD A POINTER TO FUNCTION AS DESCRIBED ON THE ASSIGNMENT********
    //   I called it compare
    
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
    
public:
    //*********** ADD A CONSTRUCTOR AS DESCRIBED ON THE ASSIGNMENT********
    
    BinarySearchTree(int p(const ItemType&, const ItemType &))
    {compare = p;}
    
    
    //*********** ADD A COPY CONSTRUCTOR AS DESCRIBED ON THE ASSIGNMENT********
    
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
    // NOT IN THE Tree Code Files on Catalyst, use for HW#4:
    BinarySearchTree & operator=(const BinarySearchTree & sourceTree);
};




template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    BinaryTree<ItemType>::rootPtr = _insert(BinaryTree<ItemType>::rootPtr, newNodePtr);
    return true;
}




template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
    bool isSuccessful = false;
    BinaryTree<ItemType>::rootPtr = _remove(BinaryTree<ItemType>::rootPtr, target, isSuccessful);
    return isSuccessful;
}




template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
    // MUST INCLUDE CALLING THE PRIVATE findNode FUNCTION
    // Be sure to check if the findNode function actually finds anEntry
    // If it does, assign to the returnedItem parameter the item of the
    //     found node and return true
    // If it doesn't, return false
    
    if(findNode(BinaryTree<ItemType>::rootPtr, anEntry)==0)
        return false;
    else
        returnedItem = findNode(BinaryTree<ItemType>::rootPtr, anEntry)->getItem();
    return true;
        
    
    
}




//NOT IN THE Tree Code Files on Catalyst, use for HW#4:
template<class ItemType>
BinarySearchTree<ItemType> & BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType> & sourceTree)
{
    compare = sourceTree.compare; // assign to function pointer
    this->BinaryTree<ItemType>::operator=(sourceTree);
    return *this;
}



template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,BinaryNode<ItemType>* newNodePtr)
{
    if( nodePtr==0 )
        return newNodePtr;
    if( compare(newNodePtr->getItem(),  nodePtr->getItem()) < 0 ) //*****CHANGE THIS*****
        nodePtr->setLeftPtr(_insert( nodePtr->getLeftPtr(), newNodePtr ));
        else
            nodePtr->setRightPtr(_insert( nodePtr->getRightPtr(), newNodePtr ));
            return nodePtr; // must return
}

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


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const
{
    // ALGORITHM:
    //       IF nodePtr doesn't exist (is 0) THEN
    //            return 0
    //       ELSE IF nodePtr's item < target THEN (make sure you use the compare function)
    //                return what the recursive call to findNode, for the leftPtr, returns
    //       ELSE IF nodePtr's item > target THEN (make sure you use the compare function)
    //            return what the recursive call to findNode, for the rightPtr, returns
    //	ELSE
    
    if(nodePtr == 0)
        return 0;
    else if (compare(nodePtr->getItem(), target) < 0)
        return findNode(nodePtr->getLeftPtr(), target);
    else if (compare(nodePtr->getItem(), target) > 0)
        return findNode(nodePtr->getRightPtr(), target);
    else
        return nodePtr;
    
}

template<class ItemType>
void BinarySearchTree<ItemType>::print(BinaryNode<ItemType>* p, int indent = 0)
{
    if(p != NULL)
    {
        if(p->getLeftPtr())
        {
            print(p->getLeftPtr(), indent + 4);
        }
        if(p->getRightPtr())
        {
            print(p->getRightPtr(), indent + 4);
        }
        if(indent) //indent != 0
        {
            cout << setw(indent) << " ";
        }
        cout << p->getItem() << endl;
    }
}

#endif
