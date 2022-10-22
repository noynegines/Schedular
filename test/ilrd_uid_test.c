#include <time.h> 		/* time */
#include <unistd.h>		/* getpid() */

#include "tests.h"
#include "ilrd_uid.h"


int main()
{
	ilrd_uid_t new_uid1 = {0, 0, 0};
	ilrd_uid_t new_uid2 = {0, 0, 0};
	
	new_uid1 = UIDCreate();
	new_uid2 = UIDCreate();
	
	TEST("Serial 1 Failed", new_uid1.serial, 1);
	TEST("Serial 2 Failed", new_uid2.serial, 2);
	
	TEST("Time Stamp 1 Failed", new_uid1.time_stamp, new_uid2.time_stamp);
	TEST("Time Stamp 2 Failed", new_uid2.time_stamp, new_uid1.time_stamp);
	
	TEST("PID 1 Failed", new_uid1.pid, getpid());
	TEST("PID 2 Failed", new_uid2.pid, getpid());
	
	TEST("Is Same Failed", UIDIsSame(new_uid1, new_uid2), 0);
	TEST("Is Same Failed", UIDIsSame(new_uid1, new_uid1), 1);
	
	PASS;
	
	return 0;
}

