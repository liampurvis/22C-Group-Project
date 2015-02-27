#pragma once
template <class Object>
class HashTable
{
protected:
   int (*Hash)(const Object&obj);
   int (*Compare)(const Object&left, const Object&right);
public:
   HashTable(int (*hashFcn)(const Object &obj),
		int (*comp)(const Object&left, const Object&right)){
			Hash = hashFcn; Compare = comp;}
   virtual ~HashTable(){}
   virtual bool contains(const Object & x) const =0;
   virtual void makeEmpty()=0;
   virtual bool insert(const Object & x) =0;
   virtual bool remove(const Object & x) =0;
   virtual int size() const =0;
   virtual void displayStatistics() const =0;
   virtual bool getEntry(const Object & target, Object & returnedItem) const=0;
};
