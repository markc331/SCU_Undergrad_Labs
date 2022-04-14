#include <limits>
#include <algorithm>    
using namespace std;

int dpcc(int N, int d[], int m)
{
    int ans[N+1];
    ans[0] = 0;

    for(int i = 1; i<= N; ++i)
    {
        ans[i] = 0;
        for(int j = 1; j<= m; ++j)
        {
            if(i >= d[j])
                ans[i] = std::min(ans[i], 1+ans[i - d[j]]);
        }
        return ans[N];
    }
}

int main()
{
    int N = 22;
    int d[] = {6,10,25};
    int m = 2;
    return dpcc(N, d, m);
}