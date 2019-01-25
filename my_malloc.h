/**
 * Implementing malloc and free using sbrk() - C wrapper on brk() syscall
 * Maintain a free list - doubly linked list which tracks free blocks
 *
 */

#include <unistd.h>

// create a doubly LL node struct to track free list
struct _blk_t {
  size_t size; // bytes
  struct _blk_t * next;
  struct _blk_t * prev;
} typedef blk_t;

// todo: check correctness of casting & pointer arithmetic below
#define BLKHD_SIZE sizeof(blk_t)
#define BLK_P(us_p) ((blk_t)((void *)us_p + BLKHD_SIZE))
#define US_P(blk_p) ((void *)blk_p - BLKHD_SIZE)

// First fit malloc/free
void * ff_malloc(size_t size);
void ff_free(void * ptr);

// Best fit malloc/free
void * bf_malloc(size_t size);
void bf_free(void * ptr);

unsigned long get_data_segment_size(); // in bytes
unsigned long get_data_segment_free_space_size(); // in bytes

// Inserts a freed block back into the LinkedList
void insert_free(blk_t * blk_ptr);

// search for block ff and bf allocation policies
blk_t * ff_search(size_t size); // Searches for first usable block
blk_t * bf_search(size_t size); // searches for best fit block to allocate - min diff b/w sizes

// function takes blk_t pointer and size of bock to malloc and splits if there
// is more space
void spilt(blk_t * start_ptr, size_t size);
