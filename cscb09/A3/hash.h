#ifndef _HASH_H_
#define _HASH_H_

// Hash manipulation helper functions
extern void show_hash(char *hash, long block_size);

extern void hash(char *hash_val, char *file); 

extern bool compare_hash(char *hash1, char *hash2);

#endif // _HASH_H_