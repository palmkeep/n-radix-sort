#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <algorithm>

using std::cout;        using std::endl;
using std::cin;         using std::vector;


int ipow(int base, int exp)
{
    int res = 1;
    while(exp)
    {
        if (exp & 1) { res *= base; }

        exp >>= 1;
        base *= base;
    }
    return res;
}

vector<vector<int>> arrayToBuckets(int n_buckets, int iteration, vector<int> array)
{
    vector<vector<int>> arrayOfBuckets(n_buckets);
    for (int i = 0; i < array.size(); i++)
    {
        int pow = ipow(n_buckets, iteration);
        int digit = (array[i]/pow) % n_buckets;
        arrayOfBuckets[digit].push_back(array[i]);
    }
    return std::move(arrayOfBuckets);
}

// Deflates the ints from the list of vectors into a single ordered array
vector<int> bucketsToList(vector<vector<int>> bucket_array)
{
    vector<int> array;
    for (int i = 0; i < bucket_array.size(); i++)
    {
        for (int j = 0; j < bucket_array[i].size(); j++)
        {
            array.push_back(bucket_array[i][j]);
        }
    }
    return std::move(array);
}

vector<int> nRadixSort(int n, vector<int>& array, int arrayMaxVal)
{
    for (int i = 0; ipow(n,i) < arrayMaxVal; i++)
    {
        array = bucketsToList(arrayToBuckets(n, i, array));
    }
    return array;
}


// Performs radix sort on a random array of ints
// Compares with std::sort()
int main()
{
    int nRadix;
    cout << "Choose radix" << endl;
    cin >> nRadix;

    int numElements;
    cout << "Choose number of elements" << endl;
    cin >> numElements;

    int maxVal;
    cout << "Choose largest allowed integer value" << endl;
    cin >> maxVal;
    vector<int> randomizedArray1(numElements);
    vector<int> randomizedArray2(numElements);

    // Created a list of $numElements random integers < $maxVal
    srand(time(NULL)); // Seed rand()
    for (int i = 0; i < numElements; i++)
    {
        randomizedArray1[i] = rand() % maxVal;
    }
    for (int i = 0; i < numElements; i++)
    {
        randomizedArray2[i] = rand() % maxVal;
    }

    // Sort
    auto begin = std::chrono::high_resolution_clock::now();
    vector<int> sortedArray = nRadixSort(nRadix, randomizedArray1, maxVal);
    auto end = std::chrono::high_resolution_clock::now();

    cout << "n-radix-sort() | t=" << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << " [ns]"<< endl;

    begin = std::chrono::high_resolution_clock::now();
    std::sort ( randomizedArray2.begin(), randomizedArray2.end() );
    end = std::chrono::high_resolution_clock::now();
    cout << "std::sort()    | t=" << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << " [ns]" << endl;

    // Display
    char display_option;
    cout << "Display radix output? (y/N)" << endl;
    cin >> display_option;

    if (display_option == 'y' || display_option == 'Y')
    {
        cout << endl << "Printing result from radix-sort:" << endl;
        for (int i = 0; i < sortedArray.size(); i++)
        {
            cout << sortedArray[i] << endl;
        }
        cout << endl;
    }

    return 0;
}

