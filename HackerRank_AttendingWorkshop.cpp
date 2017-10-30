#include <iostream>
#include <algorithm>
using namespace std;

#include <vector>

struct Workshop
{
    Workshop() :
        startTime(0),
        duration(0),
        endTime(0)
    {}

    int startTime;
    int duration;
    int endTime;
};


struct Available_Workshops
{
    Available_Workshops(int count) :
        n(count)
    {
        workshopArray = new Workshop[n];
    }

    ~Available_Workshops() {
        delete[] workshopArray;
    }

    int         n;
    Workshop*   workshopArray;
};

Available_Workshops* initialize(int start_time[], int duration[], int n)
{
    Available_Workshops* result = new Available_Workshops(n);

    for ( int i = 0; i < n; ++i )
    {
        auto& item = result->workshopArray[i];
        item.startTime = start_time[i];
        item.duration = duration[i];
        item.endTime = start_time[i] + duration[i];
    }

    return result;
}


int CalculateMaxWorkshops(Available_Workshops* ptr)
{
    int result = 0;

    std::sort(ptr->workshopArray, ptr->workshopArray+ ptr->n,
        [](const Workshop& left, const Workshop& right)
    {
        return left.endTime < right.endTime;
    });
    
    int lastFinish = 0;
    for (int i = 0; i < ptr->n; ++i)
    {
        const auto& wrkShop = ptr->workshopArray[i];
        if (wrkShop.startTime >= lastFinish )
        {
            result++;
            lastFinish = wrkShop.endTime;
        }
    }

    return result;
}

/*int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> start_time[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time, duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}*/
