#ifndef _HASH_H_
#define _HASH_H_

#ifndef HASH_SIZE
  #define HASH_SIZE 8
#endif  // HASH_SIZE

// Hash manipulation helper functions
extern void show_hash(char *hash, long block_size);

extern void hash(char *hash_val, char *file); 

extern bool compare_hash(char *hash1, char *hash2);

#endif // _HASH_H_