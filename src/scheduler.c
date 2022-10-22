/*
* Programmer: Noy
* Project: scheduler
* Reviewd By: Haim
* Date: 14/09/22
*/

#include <assert.h> /*assert*/
#include <stdlib.h>/*malloc & free*/
#include <unistd.h> /*sleep*/

#include "scheduler.h"
#include "task.h"

#define IS_RUNNING 1
#define NOT_RUNNING 0

struct scheduler 
{
    pq_t *queue;
    task_t *current_task;
    int is_running;

};

static int PriorityFunc(const void *data1, const void *data2);
static int 	RemoveFunc(const void *data, const void *task_uid);

sched_t *SchedCreate(void)
{
	sched_t *sched = NULL;
	
	sched = (sched_t *)malloc(sizeof(sched_t));
	if(NULL == sched)
	{
		return NULL;
	}
	
	sched->current_task = NULL;
	sched->is_running = NOT_RUNNING;
	
	sched->queue = PQCreate(PriorityFunc);
	if(NULL == sched->queue)
	{
		free(sched);
		sched = NULL;
	}
	
	return sched;
}

static int PriorityFunc(const void *data1, const void *data2)
{
	assert(NULL != data1);
	assert(NULL != data2);

	return (TaskGetExecutionTime((task_t *)data1) - TaskGetExecutionTime((task_t *)data2));
}

void SchedDestroy(sched_t *sched)
{
	assert(NULL != sched);
	
	if(IS_RUNNING == sched->is_running)
	{
		sched->is_running = -1;
	}
	else
	{
		while (0 == SchedIsEmpty(sched))
        {
            TaskDestroy(PQDequeue(sched->queue));
        }
		
		PQDestroy(sched->queue);
		sched->queue = NULL;
		free(sched);
		sched = NULL;
	}
}

 
ilrd_uid_t SchedAddTask(sched_t *sched, sched_operation_t task_func, void *params, time_t interval_in_seconds, sched_clean_up_t clean_up, void *clean_up_params)
{
	task_t *new_task = NULL;

	assert(NULL != sched);
	assert(NULL != task_func);
	assert(NULL != params);
	
	new_task = TaskCreate(task_func, interval_in_seconds, params, clean_up, clean_up_params);
	if(FAILURE == PQEnqueue(sched->queue, new_task) || NULL == new_task)
	{
		return bad_uid;
	}
	
	return TaskGetUID(new_task);
}


size_t SchedSize(const sched_t *sched)
{
	assert(NULL != sched);

	return PQSize(sched->queue) + (sched->current_task != NULL);
}

int SchedIsEmpty(const sched_t *sched)
{
	assert(NULL != sched);
	
	return PQIsEmpty(sched->queue) && (sched->current_task == NULL);
}

void SchedClear(sched_t *sched)
{
	assert(NULL != sched);
	
	PQClear(sched->queue);
}

void SchedStop(sched_t *sched)
{
	assert(NULL != sched);
	
	sched->is_running = NOT_RUNNING;

}


ilrd_uid_t SchedRemoveTask(sched_t *sched, ilrd_uid_t task_uid)
{
	void *uid_task = NULL;
	
	assert(NULL != sched);
	
	uid_task = PQErase(sched->queue,RemoveFunc, (void *)&task_uid);
	if(NULL == uid_task)
	{
		return bad_uid;
	}
	TaskDestroy(uid_task);
	
	return task_uid;
}


static int RemoveFunc(const void *data, const void *task_uid)
{
    assert(NULL != data);
    
    return UIDIsSame(TaskGetUID((task_t *)data), *(ilrd_uid_t *)task_uid);
}

sched_finish_state_t SchedRun(sched_t *sched)
{
	task_ret_val_t task_exe = 0;
	time_t sleep_time = {0};
	
	assert(NULL != sched);
	
	sched->is_running = IS_RUNNING;
	
	while(IS_RUNNING == sched->is_running && !SchedIsEmpty(sched))
	{
		sched->current_task = PQDequeue(sched->queue);
		
		while(0 < (sleep_time = TaskGetExecutionTime(sched->current_task) - time(NULL)))
		{
			sleep(sleep_time);
		}
		
		task_exe = TaskExecute(sched->current_task);
		if(0 == task_exe)
		{
			TaskSetExecutionTime(sched->current_task, TaskGetInterval(sched->current_task));
			PQEnqueue(sched->queue, sched->current_task);
		}
		else
		{
			TaskDestroy(sched->current_task);
		}
		sched->current_task = NULL;
	}
	
	if(-1 == sched->is_running)
	{
		SchedDestroy(sched);
	}
	else
	{
		SchedStop(sched);
	}

	
	return SCHEDULE_COMPLETE;
	
}

