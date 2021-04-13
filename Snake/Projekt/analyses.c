#include "global.h"
#include "graphic.h"
#include <sys/time.h>

long long current_timestamp_ms() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    //printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

void timer (int ms)
{
    long long start = current_timestamp_ms();
    while(current_timestamp_ms() - start < ms);
}

int sorting(float* numbers,int from,int to)
{
    float marker;
    int counter;
    int counterSum = 0;
    do
    {
        counter=0;
        for(int i=from; i<to-1; i++)
        {
            if(numbers[i]>numbers[i+1])
            {
                marker= numbers[i];
                numbers[i]=numbers[i+1];
                numbers[i+1]=marker;
                counter++;
                counterSum++;
            }
        }
    }
    while(counter!=0);
    return counterSum;
}

float average(float* numbers,int divisor)
{
    float sum = 0;
    for(int i=0; i<divisor; i++)
        sum = sum + numbers [i];
    return (sum/divisor);
}

float quantity(float* numbers,int elements)
{
    char* text = calloc(elements*10, sizeof(char));

    sorting(numbers,0,elements);

    int pos = 0;
    float* number = calloc(elements*10,sizeof(float));
    float* size = calloc(elements*10,sizeof(float));


    for(int i=0; (i < elements); i++)
    {

        if (i == 0)
        {
            size [0] = numbers [0];
            number [0] = 1;
        }
        else
        {
            if(numbers[i] == numbers[i-1])
                number [pos] = number [pos] + 1;
            else
            {
                pos++;
                number [pos]=1;
                size [pos]=numbers[i];
            }
        }
    }
    for(; pos >= 0; pos--)
    {
        sprintf(text,"%i x %.1f ",(int)(number [pos]),(float)(size [pos]));
        center(text,1);
    }

    return 0;
}
