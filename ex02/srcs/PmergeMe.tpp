/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:32:22 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/26 17:33:22 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

#include <algorithm>
#include <vector>
#include <deque>

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
 * @brief Fusionne deux moitiés d'un conteneur
 * 
 * @param left L'itérateur pointant sur le début de la première moitié
 * @param mid L'itérateur pointant sur la fin de la première moitié
 * @param right L'itérateur pointant sur la fin de la seconde moitié
 * 
 * Cette fonction fusionne deux moitiés d'un conteneur, triées 
 * individuellement, en un seul conteneur trié. Elle utilise des vecteurs 
 * pour stocker temporairement les éléments des deux moitiés à fusionner 
 * et les compare pour réinsérer les éléments dans le conteneur d'origine 
 * dans l'ordre croissant.
 * 
 * Pourquoi fusionner deux moitiés triées ?
 * 
 * L'algorithme de tri fusion est un algorithme de tri efficace qui 
 * divise un conteneur en moitiés jusqu'à ce qu'il obtienne des sous-ensembles 
 * de taille un, puis les fusionne progressivement pour reformer le conteneur 
 * trié. Fusionner deux moitiés triées est essentiel pour reconstruire le 
 * conteneur final trié.
 * 
 * Pourquoi utiliser des vecteurs temporaires ?
 * 
 * Les vecteurs temporaires sont utilisés pour stocker les éléments des 
 * moitiés à fusionner car cela permet de gérer les éléments de manière 
 * isolée et d'éviter les interférences avec les éléments restants du 
 * conteneur original pendant la fusion.
 * 
 * @return void
 * 
 * @graphe_de_flux:
 *   Début
 *     |
 *     v
 *   Initialiser les vecteurs leftHalf et rightHalf
 *     |
 *     v
 *   Initialiser les itérateurs i, j, k
 *     |
 *     v
 *   Tant que i != leftHalf.end() et j != rightHalf.end()
 *  /        \
 * VRAI      FAUX
 *  |         |
 *  v         |
 * Si *i <= *j ?      Copier le reste de rightHalf dans le conteneur
 *  /        \
 * VRAI      FAUX
 *  |         |
 *  v         v
 * Copier *i dans le conteneur   Copier *j dans le conteneur
 * Incrémenter i      Incrémenter j
 *  |         |
 *  v         v
 * Incrémenter k      Incrémenter k
 *  |         |
 *  v         v
 * Répéter    Répéter
 *  |         |
 *  v         v
 * Copier le reste de leftHalf dans le conteneur
 *     |
 *     v
 * Fin
 * 
 * @exemple_utilisation:
 * std::vector<int> vec = {1, 3, 5, 2, 4, 6};
 * merge<std::vector<int>>(vec.begin(), vec.begin() + 2, vec.end() - 1);
 * 
 * @dépendances:
 * La fonction dépend de la bibliothèque <vector> pour utiliser les 
 * vecteurs temporaires leftHalf et rightHalf.
 */
template <typename ContainerType>
void merge(typename ContainerType::iterator iterBegin, typename ContainerType::iterator iterMid, typename ContainerType::iterator iterEnd)
{
	/* Declare the container type */
    typedef typename ContainerType::value_type ValueType;

	/* Création des sous-tableaux pour la fusion */
    std::vector<ValueType> leftSubArray(iterBegin, iterMid + 1);
    std::vector<ValueType> rightSubArray(iterMid + 1, iterEnd + 1);

	/* Initialisation des itérateurs pour la fusion */
    typename std::vector<ValueType>::iterator iterLeft = leftSubArray.begin();
    typename std::vector<ValueType>::iterator iterRight = rightSubArray.begin();
    typename ContainerType::iterator iterMerge = iterBegin;

    std::cout << "Initial state: ";
    printContainer(iterBegin, iterEnd + 1);

    /* Fusionner les deux moitiés */
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

        std::cout << "Merging: ";
        printContainer(iterBegin, iterEnd + 1);		
		
    }

    /* Copier les éléments restants de leftSubArray */
    while (iterLeft != leftSubArray.end())
    {
        *iterMerge = *iterLeft;
        ++iterLeft;
        ++iterMerge;
    }

    /* Copier les éléments restants de rightSubArray */
    while (iterRight != rightSubArray.end())
    {
        *iterMerge = *iterRight;
        ++iterRight;
        ++iterMerge;

        std::cout << "Copying Right: ";
        printContainer(iterBegin, iterEnd + 1);
		
    }
}



/**
 * @brief Trie une section du conteneur
 * 
 * @param left L'itérateur pointant sur le début de la section à trier
 * @param right L'itérateur pointant sur la fin de la section à trier
 * 
 * Cette fonction trie une section du conteneur en utilisant l'algorithme 
 * de tri par insertion. L'algorithme de tri par insertion est un algorithme 
 * de tri simple et efficace qui trie les éléments un par un en les insérant 
 * à leur place correcte dans le sous-conteneur trié.
 * 
 * Pourquoi utiliser le tri par insertion pour les petites sections ?
 * 
 * Le tri par insertion est efficace pour les petites sections car il a une 
 * complexité temporelle de O(n^2) dans le pire des cas, ce qui le rend plus 
 * rapide que d'autres algorithmes de tri pour les petites sections. Il est 
 * également stable, ce qui signifie qu'il conserve l'ordre relatif des 
 * éléments égaux.
 * 
 * @return void
 * 
 * @graphe_de_flux:
 *   Début
 *     |
 *     v
 *   Pour chaque élément i de left + 1 à right
 *     |
 *     v
 *   Initialiser key à *i
 *     |
 *     v
 *   Initialiser j à i - 1
 *     |
 *     v
 *   Tant que j >= left et *j > key
 *  /        \
 * VRAI      FAUX
 *  |         |
 *  v         |
 * Copier *j dans *(j + 1)   Décrémenter j
 *  |         |
 *  v         |
 * Si j == left ?      Sortir de la boucle
 *  /        \
 * VRAI      FAUX
 *  |         |
 *  v         v
 * Décrémenter j      Répéter
 *     |
 *     v
 * Copier key dans *(j + 1)
 *     |
 *     v
 * Répéter
 * 
 * @exemple_utilisation:
 * std::vector<int> vec = {1, 3, 5, 2, 4, 6};
 * insertionSort<std::vector<int>>(vec.begin(), vec.end() - 1);
 */
template <typename Container>
void insertionSort(typename Container::iterator begin, typename Container::iterator end)
{
	/* Declare the current iterator */
	typename Container::iterator current;

	
	current = begin + 1;
	for (; current <= end; ++current)
	{
		typename Container::value_type currentValue = *current;
		typename Container::iterator previous = current - 1;

		while (previous >= begin && *previous > currentValue)
		{
			*(previous + 1) = *previous;
			if (previous == begin)
			{
				/* Exit the loop */
				--previous;
				break;
			}
			--previous;
		}
		*(previous + 1) = currentValue;


	}
}


/** 
 * @brief Trie un conteneur en utilisant l'algorithme de tri fusion-insertion
 * 
 * @param container Le conteneur à trier
 * 
 * Cet algorithme trie un conteneur en utilisant l'algorithme de tri fusion-insertion. 
 * L'algorithme de tri fusion-insertion est une combinaison des algorithmes de tri 
 * fusion et de tri par insertion. Il divise le conteneur en sous-conteneurs de 
 * taille fixe (10 éléments) et utilise le tri par insertion pour trier les sous-conteneurs. 
 * Ensuite, il fusionne les sous-conteneurs triés en un seul conteneur trié en utilisant 
 * l'algorithme de tri fusion.
 * 
 * Pourquoi utiliser le tri fusion-insertion ?
 * 
 * Le tri fusion-insertion combine les avantages du tri fusion et du tri par insertion. 
 * Il est efficace pour les conteneurs de petite taille car il utilise le tri par insertion 
 * pour trier les sous-conteneurs de taille fixe. Cela permet de réduire le nombre de 
 * comparaisons et de déplacements d'éléments, ce qui améliore les performances du tri.
 * 
 * @return void
 * 
 * @graphe_de_flux:
 *   Début
 *     |
 *     v
 *   Si la taille du conteneur est inférieure ou égale à 10
 *  /        \
 * VRAI      FAUX
 *  |         |
 *  v         |
 * Trier le conteneur avec le tri par insertion
 *     |
 *     v
 * Diviser le conteneur en deux moitiés
 *     |
 *     v
 * Trier récursivement la première moitié
 *     |
 *     v
 * Trier récursivement la seconde moitié
 *     |
 *     v
 * Fusionner les deux moitiés triées
 *     |
 *     v
 * Fin
 * 
 * @exemple_utilisation:
 * std::vector<int> vec = {1, 3, 5, 2, 4, 6};
 * mergeInsertSort<std::vector<int>>(vec);
 */
template <typename T>
void mergeInsertSortHelper(T& container, typename T::iterator left, typename T::iterator right)
{
	if (std::distance(left, right) <= 10)
	{
		/* Explicitly specify the template argument */
		insertionSort<T>(left, right);
	}
	else
	{
		typename T::iterator mid = left + std::distance(left, right) / 2;
		mergeInsertSortHelper(container, left, mid);
		mergeInsertSortHelper(container, mid + 1, right);
		
		/* Explicitly specify the template argument */
		merge<T>(left, mid, right); 
	}
}

template <typename T>
void mergeInsertSort(T& container)
{
	mergeInsertSortHelper(container, container.begin(), container.end() - 1);
}

/* PmergeMe.tpp */
