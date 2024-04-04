#include<iostream>
#include<vector>

using namespace std;

using ll = long long;

int a, b;

unsigned int cur = 0;           // беззнаковое 32-битное число
unsigned int nextRand24() {
    cur = cur * a + b;          // вычисляется с переполнениями
    return cur >> 8;            // число от 0  до 2^24-1.
}

// merge two sorted subarrays `arr[low … mid]` and `arr[mid+1 … high]`
ll merge(vector<ll>& arr, vector<ll>& aux, ll low, ll mid, ll high)
{
    ll k = low, i = low, j = mid + 1;
    ll inversionCount = 0;

    // while there are elements in the left and right runs
    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j]) {
            aux[k++] = arr[i++];
        }
        else {
            aux[k++] = arr[j++];
            inversionCount += (mid - i + 1);    // NOTE
        }
    }

    // copy remaining elements
    while (i <= mid) {
        aux[k++] = arr[i++];
    }

    /* no need to copy the second half (since the remaining items
       are already in their correct position in the temporary array) */

       // copy back to the original array to reflect sorted order
    for (ll i = low; i <= high; i++) {
        arr[i] = aux[i];
    }

    return inversionCount;
}

// Sort array `arr[low…high]` using auxiliary array `aux`
ll mergeSort(vector<ll>& arr, vector<ll>& aux, ll low, ll high)
{
    // base case
    if (high <= low) {        // if run size <= 1
        return 0;
    }

    // find midpoint
    ll mid = (low + ((high - low) >> 1));
    ll inversionCount = 0;

    // recursively split runs into two halves until run size <= 1,
    // then merges them and return up the call chain

    // split/merge left half
    inversionCount += mergeSort(arr, aux, low, mid);

    // split/merge right half
    inversionCount += mergeSort(arr, aux, mid + 1, high);

    // merge the two half runs
    inversionCount += merge(arr, aux, low, mid, high);

    return inversionCount;
}

int main()
{
    ll n, m;
    cin >> n >> m;
    cin >> a >> b;
    vector<ll> arr(n);

    for (auto& a : arr) {
        a = nextRand24() % m;
    }

    vector<ll> aux(arr);

    // get the inversion count by performing merge sort on arr
    cout <<  mergeSort(arr, aux, 0, n - 1);

    return 0;
}