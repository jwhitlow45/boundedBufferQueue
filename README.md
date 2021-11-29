# Build and Run

#### Open a terminal and clone the git repository:
```console
git clone https://github.com/jwhitlow45/boundedBufferQueue
```
#### Navigate to the repository:
```console
cd boundedBufferQueue
```
#### Finally, build and run the code (g++11 is recommended):
```console
g++ src/main.cpp src/BoundedBufferQueue.cpp -o src/main -I include/ -std=c++11 -pthread && ./src/main -tc=10000 -tp=10000 -qs=25
```
* The values for tp, tc, and qs can be changed freely. Producer sleep range and consumer sleep range values must be provided (milliseconds), but queue size defaults to 25 if a value is not provided.