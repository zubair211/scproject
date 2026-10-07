#include<iostream>
#include<chrono>
#include<fstream>
#include<ctime>
using namespace std;
using namespace chrono;

void selectionsortw(int array[], int n)
{
    for (int i = 0; i <= n - 2; i++)
    {
        for (int j = i + 1; j <= n - 1; j++)
        {
            if (array[i] > array[j])
            {
                std::swap(array[i], array[j]);
            }
        }
    }
}

void selectionsortc(int array[], int n)
{
    for (int i = 0; i <= n - 2; i++) 
    {
        int min = i;
        for (int j = i + 1; j <= n - 1; j++)
        {
            if (array[j] < array[min])
            {
                min = j;
            }
        }
        if (i != min)
        {
            std::swap(array[i], array[min]);
        }
    }
}

void insertionsort(int array[], int n)
{
    for (int i = 1; i <= n - 1; i++)
    {
        int pivot = array[i];
        int j = i;
        while (j > 0 && pivot < array[j - 1])
        {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = pivot;
    }
}

void bubblesort(int array[], int n)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) 
        {
            break;
        }
    }
}

void randomarray(int arr[], int size)
{
    for (int i = 0; i < size; i++) 
    {
        arr[i] = rand() % 50;
    }
}

void asscendingarray(int arr[], int size)
{
    for (int i = 0; i < size; i++) 
    {
        arr[i] = i;
    }
}

void descendingarray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = size - i;
    }
}

int main(int argv, char* argc[])
{
    if (argv < 3)
    {
        std::cout << "Use of command line argument \nfilename.exe , array size  , csv filename  Thank you ";
        return 1;
    }

    int size = atoi(argc[1]);
    int* array = new int[size];
    const char* file = argc[2];
    std::ofstream fileobj(file);

    if (fileobj)
    {
        fileobj << "file type ,sorting type ,Time taken " << std::endl;
    }
    else
    {
        std::cout << "  File not created give permission thank you  " << std::endl;
            return 1;
    }

    std::string arrayType;
    for (int pick = 1; pick <= 3; pick++)
    {
        switch (pick)
        {
        case 1:
            randomarray(array, size);
            arrayType = "Random";
            break;
        case 2:
            asscendingarray(array, size);
            arrayType = "Ascending";
            break;
        case 3:
            descendingarray(array, size);
            arrayType = "Descending";
            break;
        }

        int* sortingarray = new int[size];
        for (int i = 0; i < size; i++)
        {
            sortingarray[i] = array[i];
        }
        std::cout << "\nBefore sorting elements " << std::endl;
        for (int i = 0; i < size; i++)
        {
            std::cout << " " << sortingarray[i];
        }
        auto start = std::chrono::high_resolution_clock::now();
        selectionsortw(sortingarray, size);
        auto end = std::chrono::high_resolution_clock::now();
        fileobj << arrayType << ",Wrong Selection Sort," << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

        std::cout << "\nAfter sorting elements by using wrong selection sort " << std::endl;
        for (int i = 0; i < size; i++)
        {
            std::cout << " " << sortingarray[i];
        }

        delete[] sortingarray;
        sortingarray = new int[size];
        for (int i = 0; i < size; i++) 
        {
            sortingarray[i] = array[i];
        }
        std::cout << "\nBefore sorting elements " << std::endl;
        for (int i = 0; i < size; i++)
        {
            std::cout << " " << sortingarray[i];
        }
        start = std::chrono::high_resolution_clock::now();
        selectionsortc(sortingarray, size);
        end = std::chrono::high_resolution_clock::now();
        fileobj << arrayType << ",Correct Selection Sort," << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

        std::cout << "\nAfter sorting elements by using correct selection sort " << std::endl;
        for (int i = 0; i < size; i++) 
        {
            std::cout << " " << sortingarray[i];
        }

        delete[] sortingarray;
        sortingarray = new int[size];
        for (int i = 0; i < size; i++)
        {
            sortingarray[i] = array[i];
        }
        std::cout << "\nBefore sorting elements " << std::endl;
        for (int i = 0; i < size; i++)
        {
            std::cout << " " << sortingarray[i];
        }
        start = std::chrono::high_resolution_clock::now();
        insertionsort(sortingarray, size);
        end = std::chrono::high_resolution_clock::now();
        fileobj << arrayType << ",Insertion Sort," << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

        std::cout << "\nAfter sorting elements by using Insertion sort " << std::endl;
        for (int i = 0; i < size; i++)
        {
            std::cout << " " << sortingarray[i];
        }

        delete[] sortingarray;
        sortingarray = new int[size];
        for (int i = 0; i < size; i++)
        {
            sortingarray[i] = array[i];
        }
        std::cout << "\nBefore sorting elements " << std::endl;
        for (int i = 0; i < size; i++)
        {
            std::cout << " " << sortingarray[i];
        }
        start = std::chrono::high_resolution_clock::now();
        bubblesort(sortingarray, size);
        end = std::chrono::high_resolution_clock::now();
        fileobj << arrayType << ",Bubble Sort," << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;

        std::cout << "\nAfter sorting elements by using Bubble sorting  " << std::endl;
        for (int i = 0; i < size; i++)
        {
            std::cout << " " << sortingarray[i];
        }

        delete[] sortingarray;
    }

    delete[] array;
    return 0;
}