#ifndef __ILRD_UID_H__
#define __ILRD_UID_H__

#include <time.h> /* time */
#include <sys/types.h> /*pid_t*/


typedef struct ilrd_uid 
{
    size_t serial;
    time_t time_stamp;
    pid_t pid;
}ilrd_uid_t;

extern const ilrd_uid_t bad_uid;  /* external variable representing invalid uid. {0, 0, 0}, to be defined by scheduler */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  UIDCreate
 *  Description:  Creates a new UID instance and fills it with appropriate, up-to-date
 *                data.
 *   Parameters:  void
 *      Returns:  The newly created UID instance.
 * =====================================================================================
 */
 ilrd_uid_t UIDCreate(void);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  UIDIsSame
 *  Description:  Checks whether two UID instances are identical.
 *   Parameters:  uid_lhs, uid_rhs - UID's to compare
 *      Returns:  1 if identical, 0 if non-identical.
 * =====================================================================================
 */
int UIDIsSame(ilrd_uid_t uid_lhs, ilrd_uid_t uid_rhs);

#endif /* __ILRD_UID_H__ */

