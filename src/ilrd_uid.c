#include <unistd.h> /* getpid() */	
#include "ilrd_uid.h"

const ilrd_uid_t bad_uid= {0 ,0 ,0};

ilrd_uid_t UIDCreate(void)
{
	static size_t serial_id = 1;
	ilrd_uid_t uid = {0};
	
	uid.serial = serial_id;
	++serial_id;
	uid.time_stamp = time(NULL);
	uid.pid = getpid();
	
	return uid;
}

int UIDIsSame(ilrd_uid_t uid_lhs, ilrd_uid_t uid_rhs)
{
	return ((uid_lhs.serial == uid_rhs.serial) && (uid_lhs.time_stamp == uid_rhs.time_stamp) && (uid_lhs.pid == uid_rhs.pid));
}
