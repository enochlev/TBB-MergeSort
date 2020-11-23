// Parallel merge sort from Introduction to Algorithms, 3rd edition
// by Cormen, Leiserson, Rivest, and Stein
// chapter 27

// The algorithms from the book expect arrays that start at 1,
// so we use pointer math to make arrays that start at 1

#ifndef TBB_MERGESORT_SORT_H
#define TBB_MERGESORT_SORT_H

#include <tbb/task_group.h>

template<typename item>
int BinarySearch(item x, item T[], int p, int r) {
	int low = p;
	int high = std::max(p, r + 1);
	while (low < high) {
		int mid = (low + high) / 2;
		if (x <= T[mid]) {
			high = mid;
		} else {
			low = mid + 1;
		}
	}
	return high;
}

// Merge the sorted arrays T[p1..r1] and T[p2..r2] into a new sorted array stored starting at A[p3]
template<typename item>
void PMerge(item T[], int p1, int r1, int p2, int r2, item A[], int p3) {
	int n1 = r1 - p1 + 1;
	int n2 = r2 - p2 + 1;
	if (n1 < n2) {
		std::swap(p1, p2);
		std::swap(r1, r2);
		std::swap(n1, n2);
	}
	if (n1 == 0) {
		return;
	} else {
		int q1 = (p1 + r1) / 2;
		int q2 = BinarySearch(T[q1], T, p2, r2);
		int q3 = p3 + (q1 - p1) + (q2 - p2);
		A[q3] = T[q1];
		tbb::task_group tg;
		tg.run([=] { PMerge(T, p1, q1 - 1, p2, q2 - 1, A, p3); });
		tg.run([=] { PMerge(T, q1 + 1, r1, q2, r2, A, q3 + 1); });
		tg.wait();
	}
}

// "PMergeSort(A, p, r, B, s) sorts the elements in A[p..r] and stores them in B[s..s+r-p]"
template<typename item>
void PMergeSort(item A[], int p, int r, item B[], int s) {
	int n = r - p + 1;
	if (n == 1) {
		B[s] = A[p];
	} else {
		item *T = new item[n];
		T--;
		int q = (p + r) / 2;
		int qp = q - p + 1;
		tbb::task_group tg;
		tg.run([=] { PMergeSort(A, p, q, T, 1); });
		tg.run([=] { PMergeSort(A, q + 1, r, T, qp + 1); });
		tg.wait();
		PMerge(T, 1, qp, qp + 1, n, B, s);
		T++;
		delete[] T;
	}
}

// Sorts the contents of `in` and stores the result in `out`
// `n` is the length of the arrays
template<typename item>
void MergeSort(item in[], item out[], int n) {
	PMergeSort(in - 1, 1, n, out - 1, 1);
}

#endif //TBB_MERGESORT_SORT_H
