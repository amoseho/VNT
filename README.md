VNT
This project implements a VNT class short for Very Neat Table. It handles an m x n matrix such that the entries of each row are in sorted order from left to right and the entries of each column are in sorted order from top to bottom. Some of the entries of a VNT maybe INT_MAX, which we treat as nonexistent elements.

The class will perform the following actions:

If A is a VNT object, then A is empty if and only if A[0][0] = INT_MAX.

VNT(int m, int n) will create an m x n VNT object.

A.add(25) will add 25 to a non-full VNT.

A.getMin() will extract the smallest element for A and leave A a VNT.

A.sort(int k[], int size) will sort the 1D array using the VNT.

A.find(int i) will return true if i is in A and false otherwise.
