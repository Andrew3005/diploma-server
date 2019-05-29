#include<iostream>
using namespace std;
#include <stdint.h>
#include <vector>

#if defined(WIN32) || defined(_WIN32)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

extern "C" {
  EXPORT void LUdecomposition(float *arr, float *l, float *u, int rowSize, int columnSize) {

          int i = 0, j = 0, k = 0;

          for (i = 0; i < rowSize; i++) {

                for (j = 0; j < columnSize; j++) {
                  if (j < i){
                    l[j + rowSize*i] = 0;
                  } else {
                      l[j + rowSize*i] = arr[j + rowSize*i];
                      for (k = 0; k < i; k++) {
                        l[j + rowSize*i] = l[j + rowSize*i] - l[j + rowSize*i] * u[k + rowSize*i];
                      }
                  }
                };
                
                for (j = 0; j < columnSize; j++) {
                  if (j < i)
                      u[i + j * columnSize] = 0;
                  else if (j == i)
                      u[i + j * columnSize] = 1;
                  else {
                      u[i  + j * columnSize] = arr[i  + j * columnSize] / l[i + i * rowSize];
                      for (k = 0; k < i; k++) {
                        u[i  + j * columnSize] = u[i  + j * columnSize] - ((l[i + k * columnSize] * u[k + j * columnSize]) / l[i + i * rowSize]);
                      }
                  }
                }  
          } 
  }
}
