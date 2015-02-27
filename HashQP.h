
#include <cmath>
#include <vector>

using namespace std;

// ---------------------- HashQP Prototype --------------------------
template <class Object>
class HashQP // FIX HERE TO BE A DERIVED CLASS OF HashTable
{
protected:
   static const int INIT_TABLE_SIZE = 97;
   static const float INIT_MAX_LAMBDA;

			// ADD HERE: declare static variables

   enum ElementState { ACTIVE, EMPTY, DELETED };
   class HashEntry;

   vector<HashEntry> mArray;
   int mSize;
   int mLoadSize;
   int mTableSize;
   float mMaxLambda;

public:
   HashQP(int tableSize = INIT_TABLE_SIZE); // FIX HERE: need add'l parameters
   bool contains(const Object & x) const;
   void makeEmpty();
   bool insert(const Object & x);
   bool remove(const Object & x);
   static long nextPrime(long n);
   int size() const { return mSize; }
   bool setMaxLambda( float lm );
   void displayStatistics() const;
   bool getEntry(const Object & target, Object & returnedItem) const;

protected:
   void rehash();
   int myHash(const Object & x) const;
   int findPos( const Object & x ) const;
};

template <class Object>
const float HashQP<Object>::INIT_MAX_LAMBDA = 0.49F;

			// ADD HERE: initialize static variables

// definition of nested HashQP<Object>::HashEntry class ----------------
template <class Object>
class HashQP<Object>::HashEntry
{
public:
   Object data;
   ElementState state;
   HashEntry( const Object & d = Object(), ElementState st = EMPTY )
      : data(d), state(st)
   { }
};

// HashQP method definitions -------------------
template <class Object>	// FIX BELOW: add'l parameters, call base constructor
HashQP<Object>::HashQP(int tableSize) : mSize(0), mLoadSize(0)
{
   if (tableSize < INIT_TABLE_SIZE)
      mTableSize = INIT_TABLE_SIZE;
   else
      mTableSize = nextPrime(tableSize);
   mArray.resize(mTableSize);
   makeEmpty();
   mMaxLambda = INIT_MAX_LAMBDA;
}

template <class Object>
void HashQP<Object>::displayStatistics() const
{
	// FILL IN HERE TO DISPLAY AS SPEC. ON HW#5

}


template <class Object>
int HashQP<Object>::myHash(const Object & x) const
{
   int hashVal;

   hashVal = Hash(x) % mTableSize;//may need to do: this->Hash(x)
   if(hashVal < 0)
      hashVal += mTableSize;

   return hashVal;
}

template <class Object>
void HashQP<Object>::makeEmpty()
{
   int k, size = mArray.size();

   for(k = 0; k < size; k++)
      mArray[k].state = EMPTY;
   mSize = mLoadSize = 0;
}

template <class Object>
bool HashQP<Object>::contains(const Object & x) const
{
   return mArray[findPos(x)].state == ACTIVE;
}

template <class Object>
bool HashQP<Object>::getEntry(const Object & target, Object & returnedItem) const
{
	// FINISH THIS (should be like remove, but assign to returnedItem if found)


}

template <class Object>
bool HashQP<Object>::remove(const Object & x)
{
   int bucket = findPos(x);

   if ( mArray[bucket].state != ACTIVE )
      return false;

   mArray[bucket].state = DELETED;
   mSize--;      // mLoadSize not dec'd because it counts any non-EMP location
   return true;
}

template <class Object>
bool HashQP<Object>::insert(const Object & x)
{
   int bucket = findPos(x);

   if ( mArray[bucket].state == ACTIVE )
      return false;

   mArray[bucket].data = x;
   mArray[bucket].state = ACTIVE;
   mSize++;
   // check load factor
   if( ++mLoadSize > mMaxLambda * mTableSize )
      rehash();

   return true;
}
template <class Object>
int HashQP<Object>::findPos( const Object & x ) const
{
   int kthOddNum = 1;
   int index = myHash(x);

   while ( mArray[index].state != EMPTY
      && mArray[index].data != x )// CHANGE TO USE this->Compare function
   {
      index += kthOddNum;  // k squared = (k-1) squared + kth odd #
      kthOddNum += 2;   // compute next odd #
      if ( index >= mTableSize )
         index -= mTableSize;
 			// ADD HERE: use static variables

   }
			// ADD HERE: use static variables

   return index;
}

template <class Object>
void HashQP<Object>::rehash()
{
   vector<HashEntry> oldArray = mArray;
   int k, oldTableSize = mTableSize;

   mTableSize = nextPrime(2*oldTableSize);
   mArray.resize( mTableSize );
   for(k = 0; k < mTableSize; k++)
      mArray[k].state = EMPTY;

   mSize = mLoadSize = 0;
   for(k = 0; k < oldTableSize; k++)
      if (oldArray[k].state == ACTIVE)
         insert( oldArray[k].data );
}
template <class Object>
bool HashQP<Object>::setMaxLambda(float lam)
{
   if (lam < .1 || lam > .49)
      return false;
   mMaxLambda = lam;
   return true;
}

template <class Object>
long HashQP<Object>::nextPrime(long n)
{
   long k, candidate, loopLim;

   // loop doesn't work for 2 or 3
   if (n <= 2 )
      return 2;
   else if (n == 3)
      return 3;

   for (candidate = (n%2 == 0)? n+1 : n ; true ; candidate += 2)
   {
      // all primes > 3 are of the form 6k +/- 1
      loopLim = (long)( (sqrt((float)candidate) + 1)/6 );

      // we know it is odd.  check for divisibility by 3
      if (candidate%3 == 0)
         continue;

      // now we can check for divisibility of 6k +/- 1 up to sqrt
      for (k = 1; k <= loopLim; k++)
      {
         if (candidate % (6*k - 1) == 0)
            break;
         if (candidate % (6*k + 1) == 0)
            break;
      }
      if (k > loopLim)
         return candidate;
   }
}
