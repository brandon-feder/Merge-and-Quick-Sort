#include <iostream>
#include <list>
#include <chrono>
#include <forward_list>
#include <stdlib.h> // rand()

const int LENGTH = 1000000;

template<class iterType>
void printList(iterType start, iterType end)
{
    std::cout << "[ ";
    for(; start != end; ++start)
    {
        std::cout << *start << ", ";
    }
    std::cout << "]\n";
}

std::list<int> mergesort(std::list<int> listA)
{
    // If ListA's size > 1
    if(listA.size() > 1)
    {
        // The rounded middle of the two lists
        std::list<int>::iterator half = listA.begin();
        std::advance(half, listA.size()/2);

        // The second list being used
        std::list<int> listB;

        // Split ListA in half and transfer half the elements to listB
        listB.splice(listB.begin(), listA, listA.begin(), half);

        // Recursevly merge sort again
        listA = mergesort(listA);
        listB = mergesort(listB);

        // Merge
        listA.merge(listB);
    }

    return listA;
}

std::forward_list<int> mergesort(std::forward_list<int> listA, int size)
{
    // If ListA's size > 1
    if(size > 1)
    {
        // The rounded middle of the two lists
        std::forward_list<int>::iterator half = listA.begin();
        std::advance(half, size/2);

        // The second list being used
        std::forward_list<int> listB;

        // Split ListA in half and transfer half the elements to listB
        listB.splice_after(listB.before_begin(), listA, listA.before_begin(), half);

        // Recursevly merge sort again
        listA = mergesort(listA, size - size/2);
        listB = mergesort(listB, size/2);

        // Merge
        listA.merge(listB);
    }

    return listA;
}

int main()
{
    std::list<int> doubleList;
    std::forward_list<int> singleList;

    for(int i = 0; i < LENGTH; i++ )
    {
        int n = rand() % LENGTH;
        doubleList.push_front(n);
        singleList.push_front(n);
    }

    std::cout << "\nHere are the original lists: \n";

    std::cout << "\nSorting double linked list with merge sort\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    doubleList = mergesort(doubleList);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Total time to sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " nanoseconds\n";

    std::cout << "\nSorting single linked list with merge sort\n";
    begin = std::chrono::steady_clock::now();
    singleList = mergesort(singleList, LENGTH);
    end = std::chrono::steady_clock::now();
    std::cout << "Total time to sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " nanoseconds\n";
}
