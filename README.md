# Simuation
A data structures/algo exercise that simulates processor jobs

Given a batch of 𝑚 jobs, each with specific arrival times and
durations, determine (1) the total wait time (the total time spent by all 𝑚 jobs waiting in queues), (2) the maximum
wait time (the longest wait any of the 𝑚 jobs endured) and (3) the average wait time over all 𝑚 jobs. Furthermore,
determine these quantities for 𝑛 processors, where 𝑛 ranges from 1 to 𝑚 − 1

Each job has an arrival time, duration, and finish time

  finish_time = start_time + duration
  wait_time = finish_time – arrival_time – duration. 
  
The file job_list first contains the number of jobs to be processed follwed by each job with its arrival time and duration(in order of arrrival). The finish time
is yet to be calculated.

After making an executable, run by ./Simulation job_list

modify job_list as desired.

The program should output a report and trace file.

Report file should be as follows for the sample job list:

Report file: job_list.rpt
20 Jobs:
(1, 5, *) (2, 6, *) (3, 4, *) (4, 10, *) (5, 3, *) (6, 5, *) (7, 9, *) (8, 2, *) (9, 6, *) (10, 11, *) (11, 2, *) (12, 3, *) (13, 7, *) (14, 6, *) (15, 5, *) (16, 4, *) (17, 9, *) (18, 3, *) (19, 2, *) (20, 1, *) 

***********************************************************
1 processor: totalWait=876, maxWait=83, averageWait=43.80
2 processors: totalWait=326, maxWait=40, averageWait=16.30
3 processors: totalWait=133, maxWait=17, averageWait=6.65
4 processors: totalWait=72, maxWait=15, averageWait=3.60
5 processors: totalWait=14, maxWait=6, averageWait=0.70
6 processors: totalWait=4, maxWait=2, averageWait=0.20
7 processors: totalWait=1, maxWait=1, averageWait=0.05
8 processors: totalWait=0, maxWait=0, averageWait=0.00
9 processors: totalWait=0, maxWait=0, averageWait=0.00
10 processors: totalWait=0, maxWait=0, averageWait=0.00
11 processors: totalWait=0, maxWait=0, averageWait=0.00
12 processors: totalWait=0, maxWait=0, averageWait=0.00
13 processors: totalWait=0, maxWait=0, averageWait=0.00
14 processors: totalWait=0, maxWait=0, averageWait=0.00
15 processors: totalWait=0, maxWait=0, averageWait=0.00
16 processors: totalWait=0, maxWait=0, averageWait=0.00
17 processors: totalWait=0, maxWait=0, averageWait=0.00
18 processors: totalWait=0, maxWait=0, averageWait=0.00
19 processors: totalWait=0, maxWait=0, averageWait=0.00
