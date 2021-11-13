# Description

Using multithreading, condition variables, and lock statements, the above program inserts and removes items to and from a bounded buffer queue in a thread safe manner. The size of this queue is provided by the user through the command to run the program. This bounded buffer queue is manipulated by two different types of threads: consumers and producers. Consumers remove items from the queue while producers add items to the queue. At the start of the program 10 producer threads and 10 consumer threads are created. Consumers will only remove items from the queue if the queue is not empty while producers will only add items to the queue if the queue is not full. To prevent two items from being inserted/removed at the same time, a mutex is used. In the event a given thread X tries to insert/remove when thread Y has the a lock on the mutex, thread X will wait until the lock is released by thread Y.

Before every produce/consume operation, a thread will generate its own random wait time from 0 to T, where T is a sleep range provided by the user. Two sleep ranges are provided by the user through the command to run the program: one for producers and one for consumers. The consumer thread sleep range remains constant for the duration of the program, however the producer sleep range is dynamic. If the queue capacity is less than 25%, the producers are sped up by gradually reducing their sleep range as capcity approaches 0%, down to half the intial sleep range (2x speed). The opposite is done when capcity exceeds 75%, slowing down producers by gradually increasing their sleep range as capacity approaches 100%, up to double the initial sleep range (1/2x speed).

Benchmarks were performed on this program which measured the number of items produced and consumed, as well as the number of times a producer/consumer had to halt due to the queue being full/empty (referred to as a producer halt or a consumer halt). The results and analysis of these benchmarks can be found below in the Data Analysis section. 

# Demonstration

Here is a [demonstration video](https://gfycat.com/likelyenragedauk.gif) of the project running.

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
g++ src/main.cpp src/BoundedBufferQueue.cpp -o src/main -I include/ && ./src/main -tp=10000 -tc=10000 -qs=25
```
* The values for tp, tc, and qs can be changed freely. Producer sleep range and consumer sleep range values must be provided (milliseconds), but queue size defaults to 25 if a value is not provided.

# Testing Methodology

The following data was gathered using a [python script](https://github.com/jwhitlow45/boundedBufferQueue/blob/main/benchmarks.py) to build and run the bounded buffer queue program with g++11. Results were stored in a .csv file, using different parameters for producer sleep range, consumer sleep range, and queue size, and then imported to Google Sheets for interpretation and graphing. The producer/consumer sleep ranges tested were 25, 50, 100, 250, and 1000 ms while queue sizes were 25, 50, and 100. Every combination of these parameters were tested for a total of 75 tests ran over roughly 15 minutes. These tests were run on a Surface Pro 6 with an i5-8250U (4 core/8 thread @ 3.4 GHz) and 8 GB of RAM running Ubuntu 21.10. During these tests the only open application was VSCode and no user was interacting with the machine.

# Data Analysis

All of the following charts and data can be found in this [Google Sheet](https://docs.google.com/spreadsheets/d/1tFKspgmAZmG4oimnjpJ3H8YAZPHxBgIeonOy--TpXgM/).

Of the following graphs, 3 show the producer halt rate (`producer halts / item produced`) vs. sleep range differential (`producer sleep range - consumer sleep range`) with varying queue sizes and 3 show the consumer halt rate (`consumer halts / item produced`) vs. sleep range differential (`producer sleep range - consumer sleep range`) with varying queue sizes.

### Preference for Producer Threads

During testing, it became obvious that the thread scheduler for Linux was giving preference to the producer threads over the consumer threads. Across all queue sizes, sleep range differentials of 0 (equivalent sleep ranges) led to producer halt rates anywhere from 12% to 25% and consumer halt rates of 0%. This preference for producers becomes even more apparent when looking at Figures 4-6. The consumer halt rate does not rise above 0% until the producer sleep range is 100 ms greater than the consumer sleep range. This initially appeared to be because the first generated thread was a producer (threads are created in an alternating pattern of producer then consumer), however rerunning the tests with consumers as the first threads in the pattern did not show any statistically significant difference in results.

### Producer/Consumer Halt Rate Increases with more negative/positive Sleep Range Differential

As sleep range differential is calculated by producer sleep range - consumer sleep range, a positive sleep range differential means producer sleep range > consumer sleep range and a negative sleep range differential means consumer sleep range < producer sleep range. Since a larger sleep range leads to, on average, more sleep time for threads of a given type, it can be concluded that a larger sleep differential in favor of a given thread type (negative for consumers, positive for producers) will lead to a decrease in that thread type’s halt rate, and an increase in the other thread type’s halt rate. This is because the more active thread type will have to wait on the slower thread type to add/remove items to/from the queue. In simpler terms, a more negative sleep range differential should lead to a greater producer halt rate, but lesser consumer halt rate. Conversely, a more positive sleep range differential should lead to a greater consumer halt rate, but lesser producer halt rate.

### Halt Rate Reduces as Queue Size Increases

By increasing the size of the bounded buffer queue, the rate at which halts occur is meaningfully reduced. At a queue size of 25, the average halt rate of producers and consumers is 40.21% and 3.54% respectively. When the queue size is increased to 50, the average halt rate of producers and consumers decreases to 38.38% and 1.13%, and at a queue size of 100 they decrease even further to 35.71% and 0.28%. This trend can also be seen on all figures as the halt rates shrink at the left side when comparing Figures 1, 2, and 3, and right end when comparing Figures 4, 5, and 6. This is also a logical conclusion to come to, as the greater queue size allows for more “room” for the queue to grow and shrink, leading to less producer and consumer halts.

### Figures
<div align="center" display="flex">
  <img title="Figure 1" width="300px" src="https://github.com/jwhitlow45/boundedBufferQueue/blob/main/media/graphs/Producer%20Halt%20Rate%20vs.%20Sleep%20Range%20Differential%20(Queue%20Size%2025).png">
  <img title="Figure 2" width="300px" src="https://github.com/jwhitlow45/boundedBufferQueue/blob/main/media/graphs/Producer%20Halt%20Rate%20vs.%20Sleep%20Range%20Differential%20(Queue%20Size%2050).png">
  <img title="Figure 3" width="300px" src="https://github.com/jwhitlow45/boundedBufferQueue/blob/main/media/graphs/Producer%20Halt%20Rate%20vs.%20Sleep%20Range%20Differential%20(Queue%20Size%20100).png">
  <img title="Figure 4" width="300px" src="https://github.com/jwhitlow45/boundedBufferQueue/blob/main/media/graphs/Consumer%20Halt%20Rate%20vs.%20Sleep%20Range%20Differential%20(Queue%20Size%2025).png">
  <img title="Figure 5" width="300px" src="https://github.com/jwhitlow45/boundedBufferQueue/blob/main/media/graphs/Consumer%20Halt%20Rate%20vs.%20Sleep%20Range%20Differential%20(Queue%20Size%2050).png">
  <img title="Figure 6" width="300px" src="https://github.com/jwhitlow45/boundedBufferQueue/blob/main/media/graphs/Consumer%20Halt%20Rate%20vs.%20Sleep%20Range%20Differential%20(Queue%20Size%20100).png">
</div>
