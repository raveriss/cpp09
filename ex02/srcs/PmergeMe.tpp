#include <iostream>
#include <vector>
#include <deque>
#include <iterator>

// Fonction pour imprimer le contenu d'un conteneur
template <typename Iterator>
void printContainer(Iterator begin, Iterator end) {
    for (Iterator it = begin; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template <typename ContainerType>
void merge(typename ContainerType::iterator iterBegin, typename ContainerType::iterator iterMid, typename ContainerType::iterator iterEnd) {
    typedef typename ContainerType::value_type ValueType;

    std::vector<ValueType> leftSubArray(iterBegin, iterMid + 1);
    std::vector<ValueType> rightSubArray(iterMid + 1, iterEnd + 1);

    typename std::vector<ValueType>::iterator iterLeft = leftSubArray.begin();
    typename std::vector<ValueType>::iterator iterRight = rightSubArray.begin();
    typename ContainerType::iterator iterMerge = iterBegin;

    std::cout << "Initial state:\n";
    std::cout << "leftSubArray: ";
    printContainer(leftSubArray.begin(), leftSubArray.end());
    std::cout << "rightSubArray: ";
    printContainer(rightSubArray.begin(), rightSubArray.end());
    std::cout << "iterMerge (original container): ";
    printContainer(iterBegin, iterEnd + 1);


    while (iterLeft != leftSubArray.end() && iterRight != rightSubArray.end()) {
        if (*iterLeft <= *iterRight) {
            *iterMerge = *iterLeft;
            ++iterLeft;
        } else {
            *iterMerge = *iterRight;
            ++iterRight;
        }
        ++iterMerge;

        std::cout << "\nDuring merge:\n";
        std::cout << "iterLeft: ";
        printContainer(iterLeft, leftSubArray.end());
        std::cout << "iterRight: ";
        printContainer(iterRight, rightSubArray.end());
        std::cout << "iterMerge (original container): ";
        printContainer(iterBegin, iterEnd + 1);
    }

    while (iterLeft != leftSubArray.end()) {
        *iterMerge = *iterLeft;
        ++iterLeft;
        ++iterMerge;
    }

    while (iterRight != rightSubArray.end()) {
        *iterMerge = *iterRight;
        ++iterRight;
        ++iterMerge;
    }

    std::cout << "After merge:\n";
    std::cout << "iterMerge (original container): ";
    printContainer(iterBegin, iterEnd + 1);
}

template <typename Container>
void insertionSort(typename Container::iterator begin, typename Container::iterator end) {
    typename Container::iterator current;

    for (current = begin + 1; current <= end; ++current) {
        typename Container::value_type currentValue = *current;
        typename Container::iterator previous = current;

        while (previous > begin && *(previous - 1) > currentValue) {
            *previous = *(previous - 1);
            --previous;
        }
        *previous = currentValue;
    }
}

template <typename T>
void mergeInsertSortHelper(T& container, typename T::iterator left, typename T::iterator right) {
    if (std::distance(left, right) <= 10) {
        insertionSort<T>(left, right);
        std::cout << "Insertion Sort: ";
        printContainer(left, right + 1);
    } else {
        typename T::iterator mid = left + std::distance(left, right) / 2;

        std::cout << std::endl;
        std::cout << "\nBefore Left Recursion: ";
        printContainer(left, mid + 1);

        std::cout << "Before Right Recursion: ";
        printContainer(mid + 1, right + 1);
        
        std::cout << std::endl;

        mergeInsertSortHelper(container, left, mid);
        mergeInsertSortHelper(container, mid + 1, right);

        std::cout << std::endl;

        merge<T>(left, mid, right);

        std::cout << "\nAfter Merge:\n";
        printContainer(left, right + 1);
        std::cout << std::endl;
    }
}

template <typename T>
void mergeInsertSort(T& container) {
    mergeInsertSortHelper(container, container.begin(), container.end() - 1);
}