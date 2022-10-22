

#include <assert.h>
#include <stdlib.h>

#include "task.h"

struct task 
{
    task_func_t callback;
    void *params;
    size_t execution_interval;
    time_t execution_time;
    ilrd_uid_t uid;
    clean_up_t clean_up;
    void *clean_up_params;
};

task_t *TaskCreate(task_func_t callback, time_t interval_in_seconds, void *params, clean_up_t clean_up, void *clean_up_params)
{
	task_t *task = NULL;
	
	assert(NULL != callback);
	assert(NULL != params);
	
	task = (task_t *)malloc(sizeof(task_t));
	if(NULL == task)
	{
		return NULL;
	}
	
	task->callback = callback;
	task->params = params;
	task->execution_interval = interval_in_seconds;
	task->execution_time = time(NULL) + interval_in_seconds;
	task->uid = UIDCreate();
	task->clean_up_params = clean_up_params;
	task->clean_up = clean_up;
	
	return task;
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	TaskExecuteCleanup(task);
	
	free(task);
	task = NULL;
}

int TaskIsEqual(const task_t *lhs, const task_t *rhs)
{
	assert(NULL != lhs);
	assert(NULL != rhs);
	
	return UIDIsSame(lhs->uid, rhs->uid);
}

ilrd_uid_t TaskGetUID(task_t *task)
{
	assert(NULL != task);

	return task->uid;
}

size_t TaskGetInterval(task_t *task)
{
	assert(NULL != task);

	return task->execution_interval;
}

time_t TaskGetExecutionTime(task_t *task)
{
	assert(NULL != task);	
	
	return task->execution_time;
}

void TaskSetExecutionTime(task_t *task, time_t execution_time)
{
	assert(NULL != task);
	
	task->execution_time = time(NULL) + execution_time;
}

task_ret_val_t TaskExecute(task_t *task)
{
	assert(NULL != task);
	
	return task->callback(task->params);
}

void TaskExecuteCleanup(task_t *task)
{
	if(NULL != task && NULL != task->clean_up_params)
	{
		task->clean_up(task->clean_up_params);
	}
}
