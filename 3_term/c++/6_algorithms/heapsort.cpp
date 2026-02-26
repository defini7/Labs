#include <iostream>
#include <array>

// We can represent a full binary tree
// where 0'th element is a root and for i != 0
// i'th element is a root and 2*i+1 is the left child node
// and 2*i+2 is the right child node, also parent of every
// node is located at (i - 1) / 2

// Heap is a full binary tree where each node has a value greater than
// any of the children ones, or each node can have a value less than any of the children ones

template <class T>
void heapify(T& data, size_t length, size_t root = 0)
{
    // For every element we must be sure that it's on the right place,
    // i.e. the heap is constructed correctly, so let's push the root value
    // forward until it's on the right position

    size_t largest = root;
    size_t left = 2 * root + 1;
    size_t right = 2 * root + 2;

    // Every time we need to be sure that we stand within the bounds,
    // i.e. left < length & right < length

    // Now let's pick largest element among the root and its children

    if (left < length && data[left] > data[largest])
        largest = left;

    if (right < length && data[right] > data[largest])
        largest = right;

    if (largest != root)
    {
        std::swap(data[root], data[largest]);

        // Now we heapify a sub-tree which
        // root is the largest element of the current sub-tree
        heapify(data, length, largest);
    }
}

template <class T>
void make_heap(T& data, size_t length)
{
    // Going from the bottom to the top of the tree heapifying
    // each sub-tree under the root element

    for (ptrdiff_t i = length / 2 - 1; i >= 0; i--)
        heapify(data, length, i);
}

template <class T>
void sort_heap(T& data, size_t length)
{
    for (ptrdiff_t i = length - 1; i >= 0; i--)
    {
        // Swapping the root with the largest element in the container
        // so the root now is the largest one
        std::swap(data[i], data[0]);

        // Heapifying our data again so the largest element is again at data[i]
        heapify(data, i);
    }
}

int main()
{
    std::array<int, 10> a = { 5, 4, 6, 2, 10, 13, 3, 1, -10, -2 };

    make_heap(a, a.size());
    sort_heap(a, a.size());

    for (int n : a)
        std::cout << n << ' ';

    std::cout << std::endl;
}
