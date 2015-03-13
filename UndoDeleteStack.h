// Undo Delete Stack
// Linked list implementation of stack ADT
// Vinitra Swamy


#ifndef _UNDO_DELETE_STACK
#define _UNDO_DELETE_STACK

#include "StackInterface.h"
#include "Node.h"

template<class ItemType>
class UndoDeleteStack : public StackInterface<ItemType>
{
private:
	Node<ItemType>* topPtr;

public:
	UndoDeleteStack() {topPtr = 0; }
	UndoDeleteStack(const UndoDeleteStack<ItemType>& aStack);
	virtual ~UndoDeleteStack() {while (topPtr!=0) {pop();} }

	bool isEmpty() const {return (topPtr == 0);}
	bool push(const ItemType& newItem);
	bool pop();
	ItemType peek() const {return topPtr->getItem();}
};

/////////////// add to this class so it's not an abstract class

template<class ItemType>
UndoDeleteStack<ItemType>::UndoDeleteStack(const UndoDeleteStack<ItemType>& aStack)
{
   Node<ItemType>* origChainPtr = aStack.topPtr;  // original chain is linked list to be copied

   if (origChainPtr == 0)
      topPtr = 0;
   else
   {
      topPtr = new Node<ItemType>();				// copy top item
      topPtr->setItem(origChainPtr->getItem());

      Node<ItemType>* newChainPtr = topPtr;			// new chain starts at top
      origChainPtr = origChainPtr->getNext();		// start with next item in original chain

      while (origChainPtr != 0)						// copy rest of list
      {
         ItemType nextItem = origChainPtr->getItem();
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);	// create new node
         newChainPtr->setNext(newNodePtr);							// add new node to list
         newChainPtr = newChainPtr->getNext();						// walk to next item
         origChainPtr = origChainPtr->getNext();
      }
      newChainPtr->setNext(0);						// set end of list
   }
}


template<class ItemType>
bool UndoDeleteStack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newItem);
	newNodePtr->setNext(topPtr);
	topPtr = newNodePtr;
	return true;
}


template<class ItemType>
bool UndoDeleteStack<ItemType>::pop()
{
	if (isEmpty())
		return false;

	Node<ItemType>* nodeToDeletePtr = topPtr;
	topPtr = topPtr->getNext();
	delete nodeToDeletePtr;
	return true;
}

template<class ItemType>
bool UndoDeleteStack<ItemType>::clear()
{
	
	while(topPtr != 0) //!isEmpty()
	{
		pop();
	}
	
	if(isEmpty())
		return true;
	
	return false;

}

#endif
