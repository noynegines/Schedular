#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ilrd_uid.h"
#include "scheduler.h"
#include "tests.h"
#include "cstmdef.h"

size_t TestSchedCreateAndDestroy()
{
    sched_t *sched = SchedCreate();
    SchedDestroy(sched);
    return 0;
}

static enum ret_val operation1(void *param)
{
    (void)(param);
    printf("Operation 1\n");
    system("xeyes &");
    printf("\n");
    return FAILURE;
}

static enum ret_val operation2(void *param)
{
    (void)(param);
    printf("Operation 2\n");
    system("firefox https://www.youtube.com/watch?v=LOZuxwVk7TU");
    return FAILURE;
}

static enum ret_val operation3(void *param)
{
    static int counter = 1;
    (void)(param);
    printf("Operation 3\n");
    alarm(0);

    if(counter > 5)
    {
        return FAILURE;
    }

    ++counter;

    return SUCCESS;
}

static enum ret_val operation4(void *param)
{
    (void)(param);
    printf("Operation 4\n");
    return FAILURE;
}

static enum ret_val operation5(void *param)
{
    (void)(param);
    printf("Operation 5\n");
    return FAILURE;
}

static enum ret_val operation6(void *param)
{
    (void)(param);
    printf("Size - should be 2 - %ld\n", SchedSize(param));
    return FAILURE;
}

static enum ret_val operation7(void *param)
{
    (void)(param);
    printf("IsEmpty - should be 0 - %d\n", SchedIsEmpty(param));
    return FAILURE;
}

static enum ret_val destroyHelper(void *param)
{
    (void)(param);
    SchedDestroy(param);
    return FAILURE;
}

static enum ret_val stoptask(void *param)
{
    (void)(param);
    SchedStop(param);
    return FAILURE;
}


size_t TestAddSizeIsEmpty()
{
    int x = 0;
    sched_t *sched = SchedCreate();
    printf("\nTesting TestAddSizeIsEmpty:\n");

    TEST("Testing IsEmpty", SchedIsEmpty(sched), 1);
    TEST("Testing Size", SchedSize(sched), 0);
    SchedAddTask(sched, operation1, &x, 10, NULL, NULL);
    TEST("Testing IsEmpty", SchedIsEmpty(sched), 0);
    TEST("Testing Size", SchedSize(sched), 1);
    SchedDestroy(sched);
    PASS;
    return 0;
}

size_t TestRunSimple()
{
    int x = 0;
    sched_t *sched = SchedCreate();
    printf("\nTesting TestRunSimple:\n");

    SchedAddTask(sched, operation1, &x, 10, NULL, NULL);
    SchedAddTask(sched, operation2, &x, 5, NULL, NULL);

    SchedRun(sched);

    SchedDestroy(sched);

    return 0;
}

size_t TestRunDeleteTask()
{
    int x = 4;
    sched_t *sched = SchedCreate();
    ilrd_uid_t uid;
    printf("\nTesting TestRunDeleteTask:\n");
    printf("you shouldn't see here operation 1...\n");

    uid = SchedAddTask(sched, operation1, &x, 10, NULL, NULL);


    SchedAddTask(sched, operation2, &x, 5, NULL, NULL);
    SchedRemoveTask(sched, uid);

    SchedRun(sched);

    SchedDestroy(sched);

    return 0;
}

size_t TestRunRep()
{
    sched_t *sched = SchedCreate();
    printf("\nTesting TestRunRep:\n");


    SchedAddTask(sched, operation3, sched, 2, NULL, NULL);

    SchedRun(sched);

    SchedDestroy(sched);

    return 0;
}

size_t TestTaskThatDestroySched()
{
    sched_t *sched = SchedCreate();
    printf("\nTesting TestDestroySched:\n");

    
    printf("you should only see operations 1 and 2\n");

    SchedAddTask(sched, operation1, sched, 2, NULL, NULL);
    SchedAddTask(sched, operation2, sched, 3, NULL, NULL);
    SchedAddTask(sched, destroyHelper, sched, 4, NULL, NULL);
    SchedAddTask(sched, operation4, sched, 5, NULL, NULL);
    SchedAddTask(sched, operation5, sched, 6, NULL, NULL);

    SchedRun(sched);

    return 0;
}

size_t TestTaskThatIsSizeAndIsEmpty()
{
    sched_t *sched = SchedCreate();
    printf("\nTesting TestTaskThatIsSizeAndIsEmpty:\n");

    SchedAddTask(sched, operation6, sched, 2, NULL, NULL);
    SchedAddTask(sched, operation7, sched, 3, NULL, NULL);

    SchedRun(sched);

    SchedDestroy(sched);

    return 0;
}

size_t TestTaskThatStops()
{
    sched_t *sched = SchedCreate();
    printf("\nTesting TestDestroySched:\n");

    
    printf("you should only see operations 1 and 2\n");

    SchedAddTask(sched, operation1, sched, 2, NULL, NULL);
    SchedAddTask(sched, operation2, sched, 3, NULL, NULL);
    SchedAddTask(sched, stoptask, sched, 4, NULL, NULL);
    SchedAddTask(sched, operation4, sched, 5, NULL, NULL);
    SchedAddTask(sched, operation5, sched, 6, NULL, NULL);

    SchedRun(sched);

    SchedDestroy(sched);

    return 0;
}



int main()
{
    TestSchedCreateAndDestroy();
    TestAddSizeIsEmpty();
    TestRunSimple();
    TestRunRep();
    TestRunDeleteTask();
    TestTaskThatDestroySched();
    TestTaskThatIsSizeAndIsEmpty();
    TestTaskThatStops();
    return 0;
}

