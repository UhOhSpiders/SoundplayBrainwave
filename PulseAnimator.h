#pragma once

class PulseAnimator
{
private:
// should this be the button objects?
    bool held[2];
    int minPulseLength;
    int colorIndexes[2];
    int leftToRightArray[300];
    int rightToLeftArray[300];
    int renderArray[300];

public:
    PulseAnimator(int pixels);
    void createBlankRenderArray();
    void animateArray(int arr[300]);
    void checkPulseLength(int arr[300]);
    int arr[300] getRenderArray();
    int arr[300] flipArray();
    int arr[300] overlayArrays();
    void printRenderArray();
    void update();

    // [[colorIndex, brightness],[colorIndex, brightness],[colorIndex, brightness],[colorIndex, brightness]]
    // tailBrightnessValues = [100, 100, 80, 70, 50, 20]
    // 
    // ---------------( for leftToRight and rightToLeft arrays )------------------
    //   push everything along --------->
    // for( int i = 0; i < 300; i++)
    //     arr[i + 1] = arr[i]
    // --------------------------------------------------------------------------
    // decide on starting pixel
    // arr[0] = held[vector] ? [colorIndexes[vector],100] : tailIndex[vector] < sizeOf(tailBrightnessValues) ? drawFadingTail(vector) : [0,0];
    // ---------------------------------------------------------------------------
    // drawFadingTail(vector)
    // tailIndex[vector]++
    // return [colorIndexes[vector], tailBrightnessValues[tailIndex[vector]]]
    // ---------------------------------------------------------------------------
    // int[300] flipArray();
    // ---------------------------------------------------------------------------
    // getCollisions
    // return new array by adding values of rTL and lTR by index
    // collisionArray[i] = leftToRightArray[i] + rightToLeftArray[i]
    // [0,0,0,1,1,1,1,1,1,0,0,0,0,0]
    // +
    // [0,0,0,0,0,0,2,2,2,2,2,2,0,0]
    // =
    // [0,0,0,1,1,1,3,3,3,2,2,2,0,0]
    // this can be used to render the actual led strip
};