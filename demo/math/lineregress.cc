#include <iostream>
#include <vector>

#include <mgl2/mgl.h>

int main()
{
    float samples[4][2] = {{26, 42}, {2, 53}, {96, 35}, {74, 10}}; 

    float xr = 0, yr = 0;
    for (int i = 0; i < 4; i++)
    {
        xr += samples[i][0];
        yr += samples[i][1];
    }
    xr /= 4;
    yr /= 4;
    
    float molecule = 0;
    float denominator = 0;
    for (int i = 0; i < 4; i++)
    {
        molecule += (samples[i][0] - xr) * (samples[i][1] - yr);
        denominator += (samples[i][0] - xr) * (samples[i][0] - xr);
    }

    float a = molecule / denominator;
    float b = yr - (a * xr);

    printf("y = %fx+%f\n", a, b);

    return 0;
}
