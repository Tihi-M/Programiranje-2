#include <iostream>
#include <limits>
int min_sum = INT_MAX;
int res_bus = 0;
int res_taxi = 0;
int taxi_fin = 0;
int bus_fin = 0;
int bus = 0;
int taxi= 0;

int zad4(int n,int a,int b,int sum){
    if(n == 0){
        if(sum < min_sum){
            min_sum = sum;
            bus_fin = bus;
            taxi_fin = taxi;
            res_bus = bus/50;
            res_taxi = taxi/4;
        }
        return 1;
    }
    if(n < 0)
        return 0;
    bus++;
    int sa_autobusom = zad4(n-1,a,b,sum+a);
    bus--;
    taxi++;
    int sa_taxijem = zad4(n-1,a,b,sum+b);
    taxi--;

    return sa_autobusom + sa_taxijem;
}

int main()
{
    int n,a,b;
    std::cin>> n >> a >> b;
    std::cout<<zad4(n,a,b,0)<<std::endl;

    std::cout<<res_bus << " "<< res_taxi;

    return 0;
}
