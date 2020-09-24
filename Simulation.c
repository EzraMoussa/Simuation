#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#include"IntegerQueue.h"
#include"Job.h"

Job getJob(FILE* in){
   int a, d;
   fscanf(in, "%d %d\n", &a, &d);
   return newJob(a, d);
}

int main(int argc, char* argv[]){

    FILE* infile;      // handle for input file   
    FILE* testOut;    //for sample testing outputs                          
    FILE* traceFile;
    FILE* reportFIle;

    int numJobs;
    //int time =0;

    infile = fopen(argv[1], "r");
    if( infile==NULL ){
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char TraceFileName[100];
    char ReportFileName[100];
    strcpy(TraceFileName, argv[1]);
    strcat(TraceFileName, ".trc");

    strcpy(ReportFileName, argv[1]);
    strcat(ReportFileName, ".rpt");

    fscanf(infile, "%d\n", &numJobs);
    //read first line
    

    //create and open the outfile(in this case a tester out)
    testOut = fopen("testOut.out", "w");

    
    traceFile = fopen(TraceFileName, "w");
    reportFIle = fopen(ReportFileName, "w");
    
    int wasAction = 0;

    //initialize a backup Job array that holds the Jobs
    Job * backup = calloc(numJobs +1, sizeof(Job*));


    //read all jobs and place them in backup array
    int i =0;
    while (i<numJobs){
        backup[i] = getJob(infile);
        printJob(testOut, backup[i]);
        fprintf(testOut, "\n");
       // printf("something\n");
        i++;
    }

   // declare and initialize an array of m-1 processor Queues along with
   // any necessary storage queues - I'm making two storage queues, one for finished jobs and one for unstarted
    
    IntegerQueue Queue [numJobs+1];
    //printf("the num of jobs is %d\n", numJobs);
    
    //the storage queue for unstarted jobs
    Queue[0] = newIntegerQueue();


    //the storage queue for finished jobs
    Queue[1] = newIntegerQueue();

    //creating an integer Queue for each processor
    for(int k = 2; k <= numJobs; k++){
        Queue[k] = newIntegerQueue();
        
    }
    

    for(int p=0; p<numJobs; p++){
        enqueue(Queue[0], p);
    } 
  
    
    int j;
    fprintf(traceFile,"Trace file: %s.trc\n", argv[1]);
    fprintf(traceFile, "%d", numJobs);
    fprintf(traceFile, " Jobs:\n");

    char* currentJobS;
    currentJobS = IntegerQueueToString(Queue[0]);

    char* token; 
    char* rest = currentJobS; 
    while ((token = strtok_r(rest, " ", &rest))) {
        if (strlen(token) > 1) {
            int o =atoi(token);
            printJob(traceFile, backup[o]);
            //printf("int o =%d\n", o);
        }else if(strlen(token) == 1){
            int o = atoi(token);
            printJob(traceFile, backup[o]);
            //printf("int o =%d\n", o);
        }
        
    }

    fprintf(traceFile, "\n");
    fprintf(traceFile, "\n");
    fprintf(reportFIle,"Report file: %s.rpt\n", argv[1]);
    fprintf(reportFIle, "%d", numJobs);
    fprintf(reportFIle, " Jobs:\n");

    currentJobS = IntegerQueueToString(Queue[0]);

    char* token1; 
    char* rest1 = currentJobS; 
    int counter =0;
    while ((token1 = strtok_r(rest1, " ", &rest1)) && counter<numJobs) {
        if (strlen(token1) > 1) {
            int o =atoi(token1);
            printJob(reportFIle, backup[o]);
            //printf("int o =%d\n", o);
        }else if(strlen(token1) == 1){
            int o = atoi(token1);
            printJob(reportFIle, backup[o]);
            //printf("int o =%d\n", o);
        }
        counter++;
        
    }

    fprintf(reportFIle, "\n");
    fprintf(reportFIle, "\n");
    fprintf(reportFIle, "***********************************************************");

    //run the simulation the number of times there are processors(1-numJobs)
    for(j = 1; j<numJobs; j++){

        int time = 0;
        int maximumWait=0;
        int totalWaitTime=0;
        double averageWait = 0;
        
        fprintf(traceFile, "*****************************\n");
        //if there are is only processor
        if (j==1) {
            fprintf(traceFile, "%d", j);
            fprintf(traceFile, (" processor:\n"));
        }else {
            fprintf(traceFile, "%d", j);
            fprintf(traceFile, (" processors:\n"));
        }
        fprintf(traceFile, "*****************************\n");
        



        //keep running over and over until the correct number or jobs are completed
        while(length(Queue[1]) != numJobs){
            //printf("the length of the storage queue is: %d\n", length(Queue[0]));

            //loop through all of the processor queues in use
            for(int pq = 2; pq <= numJobs; pq++){
                
                //complete the finishing jobs
                if(length(Queue[pq]) != 0){
                    //printf("line117\n"); 
                    //if the finish time is now, enqueue and dequeue to the correct queues
                    if(length(Queue[pq]) != 0 && getFinish(backup[peek(Queue[pq])]) == time){ //while??
                        
                        //handling Wait Time
                        int currentWait = getWaitTime(backup[peek(Queue[pq])]); 
                        
                            if (currentWait > maximumWait) {
                                maximumWait = currentWait; 
                            }
                            totalWaitTime = totalWaitTime + currentWait;
                        

                        //printf("The Finish Time is: %d\n", getFinish(backup[peek(Queue[pq])]))
                        enqueue(Queue[1], peek(Queue[pq]));
                        dequeue(Queue[pq]);
                        wasAction = 1;
                        //printf("something\n");
                    
                    }
                }

            }
            //handle arriving jobs
            if(length(Queue[0]) != 0){
                while(length(Queue[0]) != 0 && time == getArrival(backup[peek(Queue[0])])){
                    
                    //find processor queue with least amount of jobs
                    int index = 2;
                    int s =2;
                    int lowestIndex = length(Queue[2]);
                    for( s=2; s<=j+1; s++){
                
                        if(length(Queue[s])<lowestIndex){
                        lowestIndex = length(Queue[s]);
                        index = s;
                        }   
                    }
                    
                    //enqueue and dequeue
                    enqueue(Queue[index], peek(Queue[0])); 
                    dequeue(Queue[0]);
                    wasAction =1;

                    //printf("lenght of queue is: %d\n", length(Queue[0]));

                        

                }
            }

            //if something made it to the front of the queue, compute it's finish time
            for(int pq = 2; pq <= numJobs; pq++){
                
                //complete the finishing jobs
                if(length(Queue[pq]) != 0 && getFinish(backup[peek(Queue[pq])]) == UNDEF){
                //if the finish time is now, enqueue and dequeue to the correct queues
                    
                    computeFinishTime(backup[peek(Queue[pq])],time);
                    
                }

            }

        if ((wasAction == 1) || (time == 0)) {

            fprintf(traceFile, "time=%d\n", time);
            fprintf(traceFile, "0: ");
            char* currentJobS;
            currentJobS = IntegerQueueToString(Queue[0]);
            char* token2; 
            char* rest2 = currentJobS; 
            while ((token2 = strtok_r(rest2, " ", &rest2))) {
                if (strlen(token2) > 1) {
                    int o =atoi(token2);
                    printJob(traceFile, backup[o]);
                    
                    //printf("%d\n", o);
                }else if(strlen(token2) == 1){
                    int o = atoi(token2);
                    printJob(traceFile, backup[o]);
            
                }
        
            }

            //prints jobs at 1:
            currentJobS = IntegerQueueToString(Queue[1]);
            char* token3; 
            char* rest3 = currentJobS; 
            while ((token3 = strtok_r(rest3, " ", &rest3))) {
                if (strlen(token3) > 1) {
                    int o =atoi(token3);
                    printJob(traceFile, backup[o]);
            
                }else if(strlen(token3) == 1){
                    int o = atoi(token3);
                    printJob(traceFile, backup[o]);
            
                }
        
            }
                    
            //prints rest of jobs
            for (int i=0; i < j; i++) {
                fprintf(traceFile, "\n");
                fprintf(traceFile, "%d", i+1);
                fprintf(traceFile, ": ");

                currentJobS = IntegerQueueToString(Queue[i+2]);
                for(int y =0; y<strlen(currentJobS); y++){
                    if(!isspace(currentJobS[y])){
                        int x = currentJobS[y] - '0';
                        printJob(traceFile, backup[x]);
                    }
                
                }
                
                //fprintf(traceFile, "\n");
            }
            fprintf(traceFile, "\n");
            fprintf(traceFile, "\n"); 

        }  
        //fprintf(traceFile, "\n");

        time++;
        wasAction = 0;
        }

        double newDoubleTotal;
        double newDoubleNumJobs;
        
        newDoubleTotal = totalWaitTime;
        newDoubleNumJobs = numJobs;

        averageWait = newDoubleTotal / newDoubleNumJobs;

       //fixing the case of the grammar error of **processor(s)**

       totalWaitTime = round( totalWaitTime * 1000.0 ) / 1000.0;
       averageWait = round( averageWait * 100.0 )/100.0;

        if (j == 1) {
            fprintf(reportFIle, "\n");
            fprintf(reportFIle, "1 processor: totalWait=%d", totalWaitTime);
            fprintf(reportFIle, ", maxWait=%d", maximumWait);
            fprintf(reportFIle, ", averageWait=%.2f\n", averageWait); 
        
        } else {
            fprintf(reportFIle, "%d ", j);
            fprintf(reportFIle, "processors: totalWait=%d", totalWaitTime);
            fprintf(reportFIle, ", maxWait=%d", maximumWait);
            fprintf(reportFIle, ", averageWait=%.2f\n", averageWait);
        }
  
    //reseting simulation
    for (int i = 0; i<=numJobs; i++) {
        dequeueAll(Queue[i]);
    }
    for(int p=0; p<numJobs; p++){
        enqueue(Queue[0], p);
    } 
    for(int i = 0; i<numJobs; i++){
        resetFinishTime(backup[i]);
    }
    
    }
    free(backup);
    free(currentJobS);
    free(token1);
    free(token);
    free(rest);
    free(rest1);
    return 0;
}