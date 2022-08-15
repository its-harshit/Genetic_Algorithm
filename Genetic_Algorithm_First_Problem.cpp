//Implementing GA to solve the problem: What the maximum sum of a bitstring is (a string consisting of only 1s and 0s) of length N?

// The trivial answer to the problem is N.



#include <bits/stdc++.h>
#include <array>
#include <stdlib.h>
#include <utility>
using namespace std;

#define LENGTH_OF_A_BITSTRING 100
#define POPULATION_SIZE 100
// Initialising a DD-array (population_size * (length_of_bitstring +1) )
// Each row represents a individual
// First element of each row will represent the fitness of the individual
int mat[POPULATION_SIZE][(LENGTH_OF_A_BITSTRING + 1)];

// Function to generate random numbers in given range
int random_num(int start, int end)
{
    int range = (end - start) + 1;
    int random_int = start + (rand() % range);
    return random_int;
}

// Function to perform mating between parents and generate a offspring
int *mating(int *parent1, int *parent2)
{
    int *child = (int *)malloc((LENGTH_OF_A_BITSTRING + 1) * sizeof(int));

    for (int i = 1; i < (LENGTH_OF_A_BITSTRING + 1); i++)
    {
        // random probability
        float p = random_num(0, POPULATION_SIZE) / 100;
        // if prob is less than 0.45, insert gene from parent 1
        if (p < 0.45)
            child[i] = parent1[i];

        // if prob is between 0.45 and 0.90, insert gene from parent 2

        else if (p < 0.90)
            child[i] = parent2[i];
        // otherwise insert random gene(mutate), for maintaining diversity
        else
            child[i] = abs(rand()) % 2;
    }
    // calculating the fitness of the offspring
    int sum = 0;
    for (int i = 1; i < (LENGTH_OF_A_BITSTRING + 1); i++)
    {
        sum += child[i];
    }
    child[0] = sum;

    return child;
}
// Function to sort the individuals according to their fitness
void sort_fitness()
{
    int swap, position, i, j, l, m;
    int arr[(LENGTH_OF_A_BITSTRING + 1)];
    for (i = 0; i < 99; i++)
    {
        position = i;
        for (j = i + 1; j < POPULATION_SIZE; j++)
        {
            if (mat[position][0] < mat[j][0])
                position = j;
        }

        if (position != i)
        {
            for (l = 0; l < (LENGTH_OF_A_BITSTRING + 1); l++)
                arr[l] = mat[i][l];
            for (l = 0; l < (LENGTH_OF_A_BITSTRING + 1); l++)
                mat[i][l] = mat[position][l];
            for (l = 0; l < (LENGTH_OF_A_BITSTRING + 1); l++)
                mat[position][l] = arr[l];
        }
    }
}

int main()
{
    int i, j, ran, flag = 0, sum;
    int generation = 0;

    // Generating first population consisting of totally random bits
    for (i = 0; i < POPULATION_SIZE; i++)
    {
        for (j = 0; j < (LENGTH_OF_A_BITSTRING + 1); j++)
        {
            ran = rand();
            mat[i][j] = ran % 2;
        }
    }

    for (i = 0; i < POPULATION_SIZE; i++)
    {
        sum = 0;
        for (j = 1; j < (LENGTH_OF_A_BITSTRING + 1); j++)
        {
            sum += mat[i][j];
        }
        mat[i][0] = sum;
    }
    // Performing the process of Genetic Algorithm
    while (!flag)
    {
        sort_fitness();
        // Continue performing the process till we get a bitstring which has all elements '1' and therfore fitness = Length of the bitstring
        if (mat[0][0] == LENGTH_OF_A_BITSTRING)
        {
            flag = 1;
            break;
        }
        // Otherwise generate the successor population
        int newm[POPULATION_SIZE][(LENGTH_OF_A_BITSTRING + 1)];
        // Perform Elitism, that mean 10% of fittest population goes to the next generation
        for (i = 0; i < 0.1 * POPULATION_SIZE; i++)
        {
            for (j = 0; j < (LENGTH_OF_A_BITSTRING + 1); j++)
            {
                newm[i][j] = mat[i][j];
            }
        }
        // From 50% of fittest population, Individuals will mate to produce offspring for the rest 90% of the next generation
        for (i = (0.1 * POPULATION_SIZE); i < POPULATION_SIZE; i++)
        {
            int r = random_num(0, 0.5 * POPULATION_SIZE);
            int parent1[(LENGTH_OF_A_BITSTRING + 1)];
            for (j = 0; j < (LENGTH_OF_A_BITSTRING + 1); j++)
            {
                parent1[j] = mat[r][j];
            }
            r = random_num(0, 0.5 * POPULATION_SIZE);
            int parent2[(LENGTH_OF_A_BITSTRING + 1)];
            for (j = 0; j < (LENGTH_OF_A_BITSTRING + 1); j++)
            {
                parent2[j] = mat[r][j];
            }
            int *offspring = mating(parent1, parent2);
            for (j = 0; j < (LENGTH_OF_A_BITSTRING + 1); j++)
            {
                newm[i][j] = offspring[j];
            }
            free(offspring);
        }

        for (i = 0; i < POPULATION_SIZE; i++)
        {
            for (j = 0; j < (LENGTH_OF_A_BITSTRING + 1); j++)
            {
                mat[i][j] = newm[i][j];
            }
        }
        cout << "Generation: " << generation << "\t";
        cout << "Fitness of fittest individual: " << mat[0][0] << "\n";
        generation++;
    }
    cout << "Generation: " << generation << "\t";
    cout << "Fitness of fittest individual: " << mat[0][0] << "\n";

    // Display the fittest generation
    //         for(i=0;i<POPULATION_SIZE;i++)
    // {
    //     for(j=0;j<LENGTH_OF_A_BITSTRING +1;j++)
    //     {
    //         printf("%d  ",mat[i][j]);
    //     }printf("\n");
    // }
}