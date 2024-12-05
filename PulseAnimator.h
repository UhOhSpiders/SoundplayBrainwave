#pragma once

class PulseAnimator
{
private:
    bool held[2];
    int tailBrightnessValues[6];
    int colorIndexes[2];
    int tailIndex[2];
    int leftToRightArray[30][2];
    int rightToLeftArray[30][2];
    int renderArray[30][2];

public:
    PulseAnimator();
    void toggleHeld(int vector);
    void init();
    void createBlankArray(int arr[30][2]);
    void animateArray(int arr[30][2], int vector);
    int* getRenderArray();
    void flipArray(int arr[30][2]);
    int* overlayArrays(int arr1[30][2],int arr2[30][2]);
    void printRenderArray();
    int getFadedTailValue(int vector);
    void resetTailIndex(int vector);
    void update();
};