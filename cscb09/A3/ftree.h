#ifndef _FTREE_H_
#define _FTREE_H_
#include <stdbool.h>
/* Function for copying a file tree rooted at src to dest
 * Returns < 0 on error. The magnitude of the return value
 * is the number of processes involved in the copy and is
 * at least 1.
 */
int copy_ftree(const char *src, const char *dest);

bool check_size(char *source, char *dest);

void copy(char *source, char *dest);

void make_dir(char *dest);

void copy_file(char *source, char *dest);

void copy_dir(char *source, char *dest); 


#endif // _FTREE_H_