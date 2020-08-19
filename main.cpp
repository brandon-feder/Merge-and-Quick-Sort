#include <iostream>
#include <list>
#include <chrono>
#include <forward_list>
#include <stdlib.h> // rand()

const int LENGTH = 10000;

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

// Pivot function for the quick sort algorythm
std::list<int>::iterator pivot(std::list<int>::iterator start, std::list<int>::iterator end)
{
    // Setting up pivot, and two markers
    std::list<int>::iterator pivot = end;
    --pivot;

    std::list<int>::iterator i = start;
    --i;

    std::list<int>::iterator j = start;

    // for every j from 0 to pivot
    for(; j != pivot; ++j)
    {
        // If the value j references < then that of the pivot
        if(*j < *pivot)
        {
            ++i; //increment i
            std::iter_swap( i, j ); // swap i and j
        }
    }

    ++i;
    std::iter_swap( i, pivot );

    return i;
}


// Pivot function for the quick sort algorythm
std::forward_list<int>::iterator pivot(std::forward_list<int>::iterator pre_start, std::forward_list<int>::iterator pre_end)
{
    // Setting up pivot, and two markers
    std::forward_list<int>::iterator pivot = pre_end;

    std::forward_list<int>::iterator i = pre_start;

    std::forward_list<int>::iterator j = pre_start;
    j++;

    // for every j from 0 to pivot
    for(; std::distance(j, pivot) > 0; ++j)
    {
        // If the value j references < then that of the pivot
        if(*j < *pivot)
        {
            ++i; //increment i
            std::iter_swap( i, j ); // swap i and j
        }
    }

    std::forward_list<int>::iterator pre_i = i;

    ++i;
    std::iter_swap( i, pivot );

    return pre_i;
}

void quicksort(std::list<int>::iterator start, std::list<int>::iterator end)
{
    if(std::distance(start, end) > 1)
    {
        // Get the pivot
        std::list<int>::iterator pi = pivot(start, end);

        // Get the start and end of the first part
        std::list<int>::iterator listA_start = start;
        std::list<int>::iterator listA_end = pi;

        // Start and end of second part
        std::list<int>::iterator listB_start = pi;
        std::list<int>::iterator listB_end = end;

        // In order to prevent the splitting of a list into something lie [], and [3, 3, 3] which causes an infiniute loop
        if(listA_start == listA_end)
        {
            ++listA_end;
            ++listB_start;
        }

        // Quick Sort again
        quicksort(listA_start, listA_end);
        quicksort(listB_start, listB_end);


    }

}

void quicksort(std::forward_list<int>::iterator pre_start, std::forward_list<int>::iterator pre_end)
{
    if(std::distance(pre_start, pre_end) > 1)
    {
        // Get the pivot
        std::forward_list<int>::iterator pre_pi = pivot(pre_start, pre_end);

        // // Get the start and end of the first part
        std::forward_list<int>::iterator listA_start = pre_start;
        std::forward_list<int>::iterator listA_end = pre_pi;
        //
        // // Start and end of second part
        std::forward_list<int>::iterator listB_start = pre_pi;
        std::forward_list<int>::iterator listB_end = pre_end;
        //
        // // In order to prevent the splitting of a list into something lie [], and [3, 3, 3] which causes an infiniute loop
        if(listA_start == listA_end)
        {
            ++listA_end;
            ++listB_start;
        }

        //
        // Quick Sort again
        quicksort(listA_start, listA_end);
        quicksort(listB_start, listB_end);


    }

}

int main()
{
    srand(time(0));

    std::list<int> doubleList_merge;
    std::forward_list<int> singleList_merge;

    std::list<int> doubleList_quick;
    std::forward_list<int> singleList_quick;

    for(int i = 0; i < LENGTH; i++ )
    {
        int n = rand() % LENGTH;
        doubleList_merge.push_front(n);
        singleList_merge.push_front(n);
        doubleList_quick.push_front(n);
        singleList_quick.push_front(n);
    }

    std::cout << "\nHere are the original lists: \n";

    // =======================================================
    std::cout << "\nSorting double linked list with merge sort\n";

    // Get the start time
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    doubleList_merge = mergesort(doubleList_merge);

    // Get the end time
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // Print the elapsed time
    std::cout << "Total time to sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " nanoseconds\n";

    // =======================================================

    std::cout << "\nSorting single linked list with merge sort\n";

    // Get the start time
    begin = std::chrono::steady_clock::now();

    singleList_merge = mergesort(singleList_merge, LENGTH);

    // Get the end time
    end = std::chrono::steady_clock::now();

    // Print the elapsed time
    std::cout << "Total time to sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " nanoseconds\n";

    // =======================================================

    std::cout << "\nSorting double linked list with quick sort\n";

    // Get the start time
    begin = std::chrono::steady_clock::now();

    quicksort(doubleList_quick.begin(), doubleList_quick.end());

    // Get the end time
    end = std::chrono::steady_clock::now();

    // Print the elapsed time
    std::cout << "Total time to sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " nanoseconds\n";

    // =======================================================

    std::cout << "\nSorting single linked list with quick sort\n";

    // Get the start time
    begin = std::chrono::steady_clock::now();

    std::forward_list<int>::iterator end_iterator = singleList_quick.before_begin();
    std::advance(end_iterator, LENGTH);


    quicksort(singleList_quick.before_begin(), end_iterator);

    // Get the end time
    end = std::chrono::steady_clock::now();

    // Print the elapsed time
    std::cout << "Total time to sort: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " nanoseconds\n";



}
