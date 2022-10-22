#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h> /* size_t */
#include "ilrd_uid.h" 
#include "pq.h"
#include "cstmdef.h"

typedef struct scheduler sched_t;
typedef enum ret_val sched_ret_val_t;
typedef sched_ret_val_t (*sched_operation_t)(void *); 
typedef void (*sched_clean_up_t)(void *param);


typedef enum sched_finish_state
{
    SCHEDULE_COMPLETE = 0,
    SCHEDULE_FAILURE = 1,
    TASK_FAILURE = 2
} sched_finish_state_t;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  *SchedCreate
 *  Description:  Creates a new scheduler.
 *   Parameters:  void
 *      Returns:  Pointer to the newly created scheduler.
 * =====================================================================================
 */
sched_t *SchedCreate(void);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  SchedDestroy
 *  Description:  Destroys target scheduler.
 *   Parameters:  sched - valid pointer to target scheduler.
 *      Returns:  void
 * =====================================================================================
 */
void SchedDestroy(sched_t *sched);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  SchedAddTask
 *  Description:  Adds a scheduled task to target scheduler.
 *   Parameters:  sched - valid pointer to target scheduler.
 *                task_func - valid function pointer to scheduled task.
 *                params - point to parameters to pass to the scheduled function
 *                interval_in_seconds - time, in seconds, after the schedulers initiation
 *                until the task's execution.
 *                repeating - boolean value representing whether the function is
 *                self-repeating
 *      Returns:  UID of the newly created task.
 * =====================================================================================
 */

ilrd_uid_t SchedAddTask(sched_t *sched, sched_operation_t task_func, void *params, time_t interval_in_seconds, sched_clean_up_t clean_up, void *clean_up_params);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  SchedRemoveTask
 *  Description:  Removes a task from target schedule, to be found by its UID.
 *   Parameters:  sched - valid pointer to target scheduler.
 *                task_uid - UID of the desired target task.
 *      Returns:  uid
 * =====================================================================================
 */
ilrd_uid_t SchedRemoveTask(sched_t *sched, ilrd_uid_t task_uid);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  SchedSize
 *  Description:  Calculates the amount of tasks in target scheduler.
 *   Parameters:  sched - valid pointer to target scheduler.
 *      Returns:  Number of tasks in the scheduler.
 * =====================================================================================
 */
size_t SchedSize(const sched_t *sched);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  SchedIsEmpty
 *  Description:  Checks whether the target scheduler is empty of tasks.
 *   Parameters:  sched - valid pointer to target scheduler.
 *      Returns:  1 if empty, 0 if not empty.
 * =====================================================================================
 */
int SchedIsEmpty(const sched_t *sched);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  SchedClear
 *  Description:  Empties target scheduler of its tasks.
 *   Parameters:  sched - valid pointer to target scheduler.
 *      Returns:  void
 * =====================================================================================
 */
void SchedClear(sched_t *sched);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  SchedRun
 *  Description:  Initiates execution of the target scheduler.
 *   Parameters:  sched - valid pointer to target scheduler.
 *      Returns:  Schedule finish exit state enum.
 * =====================================================================================
 */
sched_finish_state_t SchedRun(sched_t *sched);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  SchedStop
 *  Description:  Instructs target scheduler to cease all task execution.
 *   Parameters:  sched - valid pointer to target scheduler.
 *      Returns:  void
 * =====================================================================================
 */
void SchedStop(sched_t *sched);

#endif /* __SCHEDULER_H__ */
