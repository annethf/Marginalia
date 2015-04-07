#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int Partition(vector<int> &vec, int low, int high)
{
    int pivot = vec.at(low);
    while(low < high)
    {
        while(low < high && vec.at(high) >= pivot)
            --high;
        if(low < high)
        {
            swap(vec.at(low), vec.at(high));
            low++;
        }
        while(low < high && vec.at(low) <= pivot)
            ++low;
        if(low < high)
        {
            swap(vec.at(low), vec.at(high));
            high--;
        }
    }
    return low;
}

void quickSort(vector<int> &vec, int low, int high)
{
    int pivotPos;
    if(low < high)
    {
        pivotPos = Partition(vec, low, high);
        quickSort(vec, low, pivotPos - 1);
        quickSort(vec, pivotPos + 1, high);
    }
}

int main()
{
    vector<int> vec;
    int number;
    ifstream in("input.txt");
    ofstream out("output.txt");
    while(in >> number)
        vec.push_back(number);
    vector<int> &p = vec;
    int low = 0;
    int high = vec.size() - 1;
    quickSort(p, low, high);
    vector<int>::iterator iter = vec.end() - 1;
    for(iter = vec.end() - 1; iter >= vec.begin(); iter--)
        out << *iter << " ";
    in.close();
    out.close();
    return 0;
}
