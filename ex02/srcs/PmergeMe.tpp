/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:08:49 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/30 13:53:53 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Include the standard library for std::cout */
#include <iostream>

/* Include the standard library for std::vector */
#include <vector>

/* Include the standard library for std::deque */
#include <deque>

/* Include the standard library for std::iterator */
#include <iterator>

/**
 * @brief Print the content of a container
 */
template <typename Iterator>
void printContainer(Iterator begin, Iterator end)
{
    for (Iterator it = begin; it != end; ++it)
	{
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Merge two halves of a container
 */
template <typename ContainerType>
void merge(typename ContainerType::iterator iterBegin, typename ContainerType::iterator iterMid, typename ContainerType::iterator iterEnd)
{
    typedef typename ContainerType::value_type ValueType;

    std::vector<ValueType> leftSubArray(iterBegin, iterMid + 1);
    std::vector<ValueType> rightSubArray(iterMid + 1, iterEnd + 1);

    typename std::vector<ValueType>::iterator iterLeft = leftSubArray.begin();
    typename std::vector<ValueType>::iterator iterRight = rightSubArray.begin();
    typename ContainerType::iterator iterMerge = iterBegin;

    while (iterLeft != leftSubArray.end() && iterRight != rightSubArray.end())
	{
        if (*iterLeft <= *iterRight)
		{
            *iterMerge = *iterLeft;
            ++iterLeft;
        }
		else
		{
            *iterMerge = *iterRight;
            ++iterRight;
        }
        ++iterMerge;
    }

    while (iterLeft != leftSubArray.end())
	{
        *iterMerge = *iterLeft;
        ++iterLeft;
        ++iterMerge;
    }

    while (iterRight != rightSubArray.end())
	{
        *iterMerge = *iterRight;
        ++iterRight;
        ++iterMerge;
    }
}

/**
 * @brief Insertion sort
 */
template <typename Container>
void insertionSort(typename Container::iterator begin, typename Container::iterator end)
{
    typename Container::iterator current;

    for (current = begin + 1; current <= end; ++current)
	{
        typename Container::value_type currentValue = *current;
        typename Container::iterator previous = current;

        while (previous > begin && *(previous - 1) > currentValue)
		{
            *previous = *(previous - 1);
            --previous;
        }
        *previous = currentValue;
    }
}

/**
 * @brief Merge Insertion Sort Helper
 */
template <typename T>
void mergeInsertSortHelper(T& container, typename T::iterator left, typename T::iterator right)
{
    if (std::distance(left, right) <= 10)
	{
        insertionSort<T>(left, right);
    }
	else
	{
        typename T::iterator mid = left + std::distance(left, right) / 2;

        mergeInsertSortHelper(container, left, mid);
        mergeInsertSortHelper(container, mid + 1, right);

        merge<T>(left, mid, right);
    }
}

/**
 * @brief Merge Insertion Sort
 */
template <typename T>
void mergeInsertSort(T& container)
{
    mergeInsertSortHelper(container, container.begin(), container.end() - 1);
}

/* PMERGEME_TPP */