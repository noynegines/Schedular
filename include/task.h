#ifndef __TASK_H__
#define __TASK_H__

#include <stddef.h> /* size_t */
#include "cstmdef.h"
#include "ilrd_uid.h"

typedef struct task task_t;

typedef enum ret_val task_ret_val_t;

typedef task_ret_val_t (*task_func_t)(void *params);
typedef void (*clean_up_t)(void *param);



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TaskCreate
 *  Description:  Creates a new task, with user defined parameters.
 *   Parameters:  callback - valid function pointer to the callback operation
 *                interval_in_seconds - Time after schedule execution is started when
 *                the task is executed.
 *                is_repeating - Boolean flag representing whether the task is repeating
 *                regularly at interval_in_seconds intervals.
 *      Returns:  Pointer to the newly created task.
 * =====================================================================================
 */
task_t *TaskCreate(task_func_t callback, time_t interval_in_seconds, void *params, clean_up_t clean_up, void *clean_up_params);
 
  /* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TaskDestroy
 *  Description:  Destroys target task.
 *   Parameters:  task - valid pointer to target task.
 *      Returns:  void
 * =====================================================================================
 */
void TaskDestroy(task_t *task);
 
 /* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TaskIsEqual
 *  Description:  Checks whether two task pointers point to the same task.
 *   Parameters:  lhs, rhs - valid pointers to the two tasks to compare.
 *      Returns:  1 if matched, 0 if not matched.
 * =====================================================================================
 */
int TaskIsEqual(const task_t *lhs, const task_t *rhs);

 /* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TaskExecute
 *  Description:  Executes target test.
 *   Parameters:  task - valid pointer to target test.
 *      Returns:  0/SUCCESS and 1/FAILURE as defined by the task's callback function.
 * =====================================================================================
 */
task_ret_val_t TaskExecute(task_t *task);
 
 /* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TaskGetUID
 *  Description:  Returns the UID of target test.
 *   Parameters:  task - valid pointer to target test.
 *      Returns:  UID of target test.
 * =====================================================================================
 */
ilrd_uid_t TaskGetUID(task_t *task);
 
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TaskGetInterval
 *  Description:  Returns the execution time interval of target test.
 *   Parameters:  task - valid pointer to target test.
 *      Returns:  Execution time interval of target test.
 * =====================================================================================
 */
size_t TaskGetInterval(task_t *task);
 
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TaskGetExecutionTime
 *  Description:  Returns the absolute time of the task's next scheduled execution.
 *   Parameters:  task - valid pointer to target test.
 *      Returns:  Absolute time of the task's next scheduled execution.
 * =====================================================================================
 */
time_t TaskGetExecutionTime(task_t *task);
 
 /* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TaskSetExecutionTime
 *  Description:  Sets the absolute time of the task's next scheduled execution.
 *   Parameters:  task - valid pointer to target test.
 *                execution_time - set time for the task's next scheduled execution.
 *      Returns:  void
 * =====================================================================================
 */
void TaskSetExecutionTime(task_t *task, time_t execution_time);
 
 /* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TaskExecuteCleanup
 *  Description:  Executes the cleanup function associated with the target task..
 *   Parameters:  task - valid pointer to target task.
 *      Returns:  void.
 * =====================================================================================
 */
void TaskExecuteCleanup(task_t *task);


#endif /* __TASK_H__ */
 
