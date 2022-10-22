#include "task.h"
#include "tests.h"


task_ret_val_t CallBacFunc(void *params);

void TaskCreateDestoryTest(void);
void TaskIsEqualTest(void);
void TaskExecuteTest(void);
void TaskGetSetTest(void);
task_ret_val_t CallBackFunc(void *params);

int main()
{
	TaskCreateDestoryTest();
	TaskExecuteTest();
	TaskIsEqualTest();
	TaskGetSetTest();

	return 0;
}

task_ret_val_t CallBackFunc(void *params)
{
	printf("hello %s\n", (char *)params);
	return SUCCESS;	
}


void TaskCreateDestoryTest(void)
{
	char name[] = "Noy";
	task_t *new_task = TaskCreate(CallBackFunc, 30, (void *)name);
	TaskDestroy(new_task);
}

void TaskIsEqualTest(void)
{
	char name[] = "Noy";
	char another_name[] = "Yasmin";
	
	task_t *task_a = TaskCreate(CallBackFunc, 20, (void *)name);
	task_t *task_b = TaskCreate(CallBackFunc, 20, (void *)another_name);
	
	TEST("TaskIsEqual", TaskIsEqual(task_a, task_b), 0);
	 
	PASS;	
	TaskDestroy(task_a);
	TaskDestroy(task_b);
}

void TaskExecuteTest(void)
{
	char name[] = "Noy";
	task_t *task_a = TaskCreate(CallBackFunc, 20, (void *)name);
	TEST("TaskExecute test" , TaskExecute(task_a) , SUCCESS);
	PASS;
	TaskDestroy(task_a);
}

void TaskGetSetTest(void)
{
	char name[] = "Noy";
	task_t *task = TaskCreate(CallBackFunc, 20, (void *)name);
	TEST("TaskGetInterval test" , TaskGetInterval(task) , 20);
	TEST("TaskGetExecutionTime" , (int)TaskGetExecutionTime(task) , time(NULL) + (int)TaskGetInterval(task));
	TaskSetExecutionTime(task, 50);
	TEST("TaskGetExecutionTime" , (int)TaskGetExecutionTime(task) , time(NULL) + 50 - 20 + (int)TaskGetInterval(task));
	PASS;
	TaskDestroy(task);
}

