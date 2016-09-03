#ifndef _SET_H_
#define _SET_H_

#include "common.h"

typedef struct _Set{
  int elem;
  struct _Set *next;
}Set;

/*--------- Memory Allocation -------------*/
void InsertSet(Set **S, int elem); /* It allocates a set. */
void DestroySet(Set **S); /* It deallocates a set. */

/*--------- Auxiliary Functions -------------*/
int RemoveSet(Set **S); /* It removes an element from the set. */
int GetSetSize(Set *S); /* It gets the size of the set. */
Set *CloneSet(Set *S); /* It makes a copy of the set. */

#endif