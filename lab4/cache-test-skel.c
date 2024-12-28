/*
 * CSE 351 Lab 4 (Caches and Cache-Friendly Code)
 * Part 1 - Inferring Mystery Cache Geometries
 *
 * Name(s):  Zifeng Wang
 * NetID(s): zifenw
 *
 * NOTES:
 * 1. When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 *
 * 2. Do NOT change the provided main function, especially the print statement.
 * If you do so, the autograder may fail to grade your code even if it produces
 * the correct result.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "support/mystery-cache.h"

//C=S*E*K
/* Returns the size (in B) of each block in the cache. */
int get_block_size(void) {     //K
  /* YOUR CODE GOES HERE */
	int offset = 1;	// A test address
	flush_cache(); 		// clear the cache to start fresh
	access_cache(0);
	//Access the first address to ensure the cache block is loaded
	while(access_cache(offset)){
		offset++; 	//increase offset and test next address
	}

  return offset;
}


//Returns the size (in B) of the cache. 
int get_cache_size(int block_size) {       //C
  flush_cache();
  int set = 0;
  while(! access_cache(set*block_size) && access_cache(0)) {
      for(int i =0; i< set; ++i){
        access_cache(i * block_size);
      }
      set++;
  }
  return set * block_size;
}



/*	int cache_size = 0;		//not work at 1,1,1
  	int check = block_size;
  	flush_cache();
  	access_cache(0);
  	while (access_cache(0)) {
    		cache_size = block_size;
    		while (cache_size <= check) {
      			cache_size += block_size;
      			access_cache(cache_size);
    		}
    		check += block_size;
  	}
  return cache_size;
}
*this one can only fit for associativity = 1; if check others, it will become infinity loop
int get_cache_size(int block_size) {
    int cache_size = 0;

    // Flush the cache and access the initial address
    flush_cache();
    access_cache(0);

    // Use exponential growth to minimize the number of iterations
    while (access_cache(0)) {
    	cache_size += block_size;  // Increment cache size by block size
        access_cache(cache_size);  // Access the memory block at cache_size
    }
    return cache_size;  // The determined cache size
}
	*/




/* Returns the associativity of the cache. */
int get_cache_assoc(int cache_size) {      //E
  /* YOUR CODE GOES HERE */
 	//int cache_size = 0;
       	int size_temp;
	int check = cache_size;
        int assoc = 0;
	flush_cache();
        access_cache(0);
        while (access_cache(0)) {
                size_temp = cache_size;
		assoc = 0;
		while (size_temp <= check) {
                        assoc++;
			size_temp += cache_size;
                        access_cache(size_temp);  //access_cache(assoc*chache_size); also work
		}
                check += cache_size;
        }
  return assoc;

}


/* Run the functions above on a given cache and print the results. */
int main(int argc, char* argv[]) {
  int size;
  int assoc;
  int block_size;
  char do_block_size, do_size, do_assoc;
  do_block_size = do_size = do_assoc = 0;
  if (argc == 1) {
    do_block_size = do_size = do_assoc = 1;
  } else {
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "block_size") == 0) {
        do_block_size = 1;
        continue;
      }
      if (strcmp(argv[i], "size") == 0) {
        do_size = 1;
        continue;
      }
      if (strcmp(argv[i], "assoc") == 0) {
        do_assoc = 1;
      }
    }
  }

  if (!do_block_size && !do_size && !do_assoc) {
    printf("No function requested!\n");
    printf("Usage: ./cache-test\n");
    printf("Usage: ./cache-test {block_size/size/assoc}\n");
    printf("\tyou may specify multiple functions\n");
    return EXIT_FAILURE;
  }

  cache_init(0, 0);

  block_size = size = assoc = -1;
  if (do_block_size) {
    block_size = get_block_size(); 				//use the get_block_size()
    printf("Cache block size: %d bytes\n", block_size);
  }
  if (do_size) {
    if (block_size == -1) block_size = get_block_size(); 	//use the get_block_size()
    size = get_cache_size(block_size);				//use the get_cache_size(int block_size)
    printf("Cache size: %d bytes\n", size);
  }
  if (do_assoc) {
    if (block_size == -1) block_size = get_block_size();	//use the get_block_size()
    if (size == -1) size = get_cache_size(block_size);		//use the get_cache_size(int block_size)
    assoc = get_cache_assoc(size);				//use the get_cache_assoc(int cache_size)
    printf("Cache associativity: %d\n", assoc);
  }
}
