//Amose Ho

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <limits.h>
#include <math.h>

using namespace std;

template <typename T> class SA;
template <typename T> ostream& operator<< (ostream& os, const SA<T>& s);

template <typename T>
class SA
{
  private:
    int low, high;
    T* p;

  public:
    SA();
    SA(int);
    SA(int,int);
    SA(const SA&);
    ~SA();

    T& operator[](int);
    SA & operator=(const SA &);
    operator T*();

    friend ostream& operator<< <T>(ostream& os, const SA<T>& s);
};

template <typename T>
class SM
{
  private:
    SA< SA<T> > safeMatrix;

  public:
    SM();
    SM(int,int);
    SM(int,int,int,int);

    SA<T>& operator[](int);
    operator SA<T>*();
};

template <typename T>
class VNT : public SM<T>
{
    private:
        SM<T> vntMatrix;
        int rlow, rhigh;
        int clow, chigh;
        int min;

    public:
        // Constructors
        VNT ();
        VNT(int,int);
        VNT(int,int,int,int);

        void init();
        void add(int);
        T getMin();
        bool find(T);
        void memberSort();
        void sort(T A[], int);
        void print();

        SA<T>& operator[](int);
        operator SA<T>*();
};

int main(){

/*
First Fill a VNT a approximately halfway
using the a.add() function and using a sequence
of neither ascending or descending numbers
(i.e. some numbers should be greater than the number added
to the VNT before them and some should be less than the number
added to the VNT before them)
Then print the VNT a
then remove a number using a.getmin();
then remove another number using a.getmin();
then print out the VNT a again
*/

  VNT<int> a(5,6);
  int addedNumber = 0;
  for(int i = 0; i <= 15; i++){
    addedNumber = (i*31)%50;
    a.add(addedNumber);
    cout<<addedNumber<<endl;
  }


//use whatever method you want to print the VNT
//it can be a member function or you can just loop
//through or however else you want to print it
//this is just an example of what it could look like
//it doesn't have to look like this
  a.print();


  //remove 2 numbers (if you removed a different number that's also okay)
  a.getMin();
  a.getMin();
  //now print it again
  a.print();


/*
now use find on some numbers that are and are not in the VNT
print out which one's you're using find on and whether find returns
true or false
*/

  int firstSearched = 100;
  int secondSearched = 0;
  int thirdSearched = 31;

  //the following statements will print something like:
  //"100 is in VNT is: false"
  cout<< firstSearched << " is in VNT is: " << a.find(firstSearched) << endl;
  cout<< secondSearched << " is in VNT is: " << a.find(secondSearched) << endl;
  cout<< thirdSearched << " is in VNT is: " << a.find(thirdSearched) << endl;



  /*
  Now create a 1d int array with 50 integers in neither ascending or
  descending order as explained earlier and print out the unsorted version
  */
  int arraySize = 50;
  VNT<int> testSort(1, arraySize);
  int* k = new int[arraySize];
  cout<<"The array initially is:"<< endl;
  for(int i = 0; i < arraySize; i++){
    addedNumber = (i*31)%50;
    k[i] = addedNumber;
    cout<< addedNumber << " ";
  }
  cout<<endl<<endl;

  /*
  Now use the sort method from the VNT class to
  sort the array k. It doesn't have to look like how I wrote it
  you can create a VNT instance and use that or you can call the function
  statically from the VNT class
  */

  testSort.sort(k, arraySize);

  //now reprint the now sorted array k

  cout<<"The array, now sorted by VNT, is:"<<endl;
  for(int i = 0; i < arraySize; i++){
    cout<< k[i] << " ";
  }
  cout<<endl;

  //You're done

}
//default constructor
template<typename T>
SA<T>::SA()
{
    low = 0;
    high = -1;
    p = NULL;
}
//2 input constructor
template<typename T>
SA<T>::SA(int low, int high)
{
    if((high-low+1) <= 0)
    {
        cout<< "constructor error in bounds definition" << endl;
        exit(1);
    }

    this->low = low;
    this->high = high;
    p = new T[high-low+1];
}

template<typename T>
SA<T>::SA(int i)
{
    low = 0;
    high = i-1;
    p = new T[i];
}

template<typename T>
SA<T>::SA(const SA& s)
{
    p = new T[s.high - s.low + 1];

    for(int i = 0; i < s.high - s.low + 1; i++)
        p[i] = s.p[i];
    low = s.low;
    high = s.high;
}

template<typename T>
SA<T>::~SA()
{
    delete [] p;
}

template<typename T>
T& SA<T>::operator[](int i)
{
    if(i < low || i > high)
    {
        cout << "index "<< i <<" out of range" << endl;
        exit(1);
    }
    return p[i - low];
}

template<typename T>
SA<T>& SA<T>::operator=(const SA & s)
{
    if(this == &s)
        return *this;

    delete [] p;
    p = new T[s.high - s.low + 1];

    for(int i = 0; i < s.high - s.low + 1; i++)
        p[i] = s.p[i];

    low = s.low;
    high = s.high;

    return *this;
}

template<typename T>
SA<T>::operator T*()
{
    return p;
}

template <typename T>
ostream& operator<<(ostream& os, const SA<T>& s)
{
    int size = s.high - s.low + 1;

    for(int i = 0; i < size; i++)
    {
        os << s.p[i];
    }
    return os;
}

template<typename T>
SM<T>::SM()
{
}

template<typename T>
SM<T>::SM(int row, int col)
{
    safeMatrix = SA< SA<T> >(0, row-1);

    for(int i = 0; i < row; i++)
    {
        safeMatrix[i] = SA<T>(0, col-1);
    }
}

template<typename T>
SM<T>::SM(int rlow, int rhigh, int clow, int chigh)
{
    safeMatrix = SA< SA<T> >(rlow, rhigh-1);

    for(int i = rlow; i < rhigh; i++)
    {
        safeMatrix[i] = SA<T>(clow, chigh-1);
    }
}

template<typename T>
SA<T>& SM<T>::operator[](int r)
{
    return safeMatrix[r];
}

template<typename T>
SM<T>::operator SA<T>*()
{ // conversion function
    return safeMatrix;
}

template<typename T>
VNT<T>::VNT(int rlow, int rhigh, int clow, int chigh) : SM<T>(rlow,rhigh,clow,chigh)
{
    vntMatrix = SM<T>(rlow,rhigh,clow,chigh);

    rlow = rlow;
    rhigh = rhigh;
    clow = clow;
    chigh = chigh;
    init();
}

template<typename T>
VNT<T>::VNT()
{
}

template<typename T>
VNT<T>::VNT(int row, int col) : SM<T>(row,col)
{
    vntMatrix = SM<T>(row,col);

    rlow = 0;
    rhigh = row;
    clow = 0;
    chigh = col;
    init();
}

template<typename T>
void VNT<T>::add(int element)
{
    for(int i = rlow; i < rhigh; i++)
    {
        for(int j = clow; j < chigh; j++)
        {
            if(vntMatrix[i][j] == INT_MAX)
            {
                vntMatrix[i][j] = element;
                memberSort();
                return;
            }
        }
    }
}

template<typename T>
void VNT<T>::init()
{
    min = INT_MAX;
    for(int i = rlow; i < rhigh; i++)
    {
        for(int j = clow; j < chigh; j++)
        {
            vntMatrix[i][j] = INT_MAX;
        }
    }
}

template<typename T>
SA<T>& VNT<T>::operator[](int r) {
    return vntMatrix[r];
}

template<typename T>
VNT<T>::operator SA<T>*() {
    return vntMatrix;
}

//take minimum value and removes it from vntMatrix and sorts it again after removal
template<typename T>
T VNT<T>::getMin() {
    min = vntMatrix[0][0];
    vntMatrix[0][0] = INT_MAX;
    memberSort();
    return min;
}

//returns 1 if element is found and 0 if element is not in array
template<typename T>
bool VNT<T>::find(T element) {

    for(int i = rlow; i < rhigh; i++)
    {
        for(int j = clow; j < chigh; j++)
        {
            if(element == vntMatrix[i][j])
            {
                return true;
            }
        }
    }
        return false;
}

template<typename T>
void VNT<T>::memberSort()
{
    // Represents the 2D Array (vntMatrix) as a 1D Array
    int rowSize = rhigh - rlow;
    int colSize = chigh - clow;

    T* tempArray = new T[rowSize * colSize];
    int index = 0;

    for(int i = rlow; i < rhigh; i++)
    {
        for(int j = clow; j < chigh; j++)
        {
            tempArray[index++] = vntMatrix[i][j];
        }
    }


    // Sorting the 1D Array in Ascending Order
    int tempInt;
    for(int i = 0; i < (rowSize * colSize)-1; i++)
    {
        for(int j = i+1; j < (rowSize * colSize); j++)
        {
            if(tempArray[i] > tempArray[j])
            {
                tempInt = tempArray[i];
                tempArray[i] = tempArray[j];
                tempArray[j] = tempInt;
            }
        }
    }

    index = 0;
    for(int i = rlow; i < rhigh; i++)
    {
        for(int j = clow; j < chigh; j++)
        {
            vntMatrix[i][j] = tempArray[index++];
        }
    }


    delete [] tempArray;
}

//VNT sort for array given array and size of array
template<typename T>
void VNT<T>::sort(T A[], int size)
{
    int index = 0;
    vntMatrix = SM<T>(1,size);
    init();

    while(index < size)
    {
        add(A[index]);
        index++;
    }

    index = 0;
    while(index < size)
    {
        A[index] = getMin();
        index++;
    }
}

//print function for VNT
template<typename T>
void VNT<T>::print()
{
    for(int i = rlow; i < rhigh; i++)
    {
        for(int j = clow; j < chigh; j++)
        {
            cout << vntMatrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
