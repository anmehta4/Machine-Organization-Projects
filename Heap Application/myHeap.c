////////////////////////////////////////////////////////////////////////////////
// Main File:        myHeap.c
// This File:        myHeap.c
// Other Files:      None
// Semester:         CS 354 Spring 2021
// Instructor:       deppeler
// 
// Author:           Arnav Mehta
// Email:            anmehta4@wisc.edu
// CS Login:         amehta
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None
//
// Online sources:   None
//////////////////////////// 80 columns wide ///////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020-2021 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission Fall 2020, CS354-deppeler
//
///////////////////////////////////////////////////////////////////////////////

// DEB'S PARTIAL SOLUTION FOR SPRING 2021 DO NOT SHARE
 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "myHeap.h"
 
/*
 * This structure serves as the header for each allocated and free block.
 * It also serves as the footer for each free block but only containing size.
 */
typedef struct blockHeader {           

    int size_status;
    /*
     * Size of the block is always a multiple of 8.
     * Size is stored in all block headers and in free block footers.
     *
     * Status is stored only in headers using the two least significant bits.
     *   Bit0 => least significant bit, last bit
     *   Bit0 == 0 => free block
     *   Bit0 == 1 => allocated block
     *
     *   Bit1 => second last bit 
     *   Bit1 == 0 => previous block is free
     *   Bit1 == 1 => previous block is allocated
     * 
     * End Mark: 
     *  The end of the available memory is indicated using a size_status of 1.
     * 
     * Examples:
     * 
     * 1. Allocated block of size 24 bytes:
     *    Allocated Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 25
     *      If the previous block is allocated p-bit=1 size_status would be 27
     * 
     * 2. Free block of size 24 bytes:
     *    Free Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 24
     *      If the previous block is allocated p-bit=1 size_status would be 26
     *    Free Block Footer:
     *      size_status should be 24
     */
} blockHeader;         

/* Global variable - DO NOT CHANGE. It should always point to the first block,
 * i.e., the block at the lowest address.
 */
blockHeader *heapStart = NULL;     

/* Size of heap allocation padded to round to nearest page size.
 */
int allocsize;

/*
 * Additional global variables may be added as needed below
 */

 
/* 
 * Function for allocating 'size' bytes of heap memory.
 * Argument size: requested size for the payload
 * Returns address of allocated block (payload) on success.
 * Returns NULL on failure.
 *
 * This function must:
 * - Check size - Return NULL if not positive or if larger than heap space.
 * - Determine block size rounding up to a multiple of 8 
 *   and possibly adding padding as a result.
 *
 * - Use BEST-FIT PLACEMENT POLICY to chose a free block
 *
 * - If the BEST-FIT block that is found is exact size match
 *   - 1. Update all heap blocks as needed for any affected blocks
 *   - 2. Return the address of the allocated block payload
 *
 * - If the BEST-FIT block that is found is large enough to split 
 *   - 1. SPLIT the free block into two valid heap blocks:
 *         1. an allocated block
 *         2. a free block
 *         NOTE: both blocks must meet heap block requirements 
 *       - Update all heap block header(s) and footer(s) 
 *              as needed for any affected blocks.
 *   - 2. Return the address of the allocated block payload
 *
 * - If a BEST-FIT block found is NOT found, return NULL
 *   Return NULL unable to find and allocate block for desired size
 *
 * Note: payload address that is returned is NOT the address of the
 *       block header.  It is the address of the start of the 
 *       available memory for the requesterr.
 *
 * Tips: Be careful with pointer arithmetic and scale factors.
 */
void* myAlloc(int size) {     
    //TODO: Your code goes in here.
    
    if (size <= 0 || size>allocsize ) {
       // fprintf(stderr, "Error:mem.c: Requested block size is not positive or greater than allocated memory\n");
        return NULL;
    }	
	
    int pagesize = 8;   // page size
    int padsize = 0;    // size of padding when heap size not a multiple of page size
    int allocatesize; // final size to be allocated

    padsize = (size+4) % pagesize; // add size + 4(for header)
    if(padsize%pagesize!=0){ // if padsize is mulitple of 8 do nothing else add the difference 
    	padsize = pagesize - padsize;
    }
    allocatesize = size + 4 + padsize;
    blockHeader *current = heapStart; // initialize first blockHeader

    int t_bits;
    int t_size;
    int maxsize = allocsize+1; // maxSize to check for the bestFit
    blockHeader *bestfit;// stores the bestFit header
    blockHeader *split;// stores the header if there is a split
    
    int found=0; // flag variable if size has been allocated with perfect match

    while (current->size_status != 1) { // until end block
        t_size = current->size_status;
	t_bits = current->size_status%pagesize;

	if (t_size & 1) {
            // LSB = 1 => used block
	    current = (blockHeader*)((char*)current + t_size-t_bits);
	    continue;
	}
	else {
	         if((t_size-t_bits)==allocatesize){ // perfect match
			current->size_status += 1; // update a bit of current block
			blockHeader* next = (blockHeader*)((char*)current + t_size - t_bits);
			if(next->size_status!=1){
				next->size_status += 2; // update p bit of next block if not the ned block
			}
			found=1; // update found to 1
			return (void*)((char*)current + 4);// return pointer to payload
		 }
		 else if((t_size-t_bits)>allocatesize && (t_size-t_bits)<maxsize){ // if not exact size but smaller than maxSize
			bestfit = current; // update bestFit pointer and maxSize
			maxsize = t_size-t_bits;
			current = (blockHeader*)((char*)current + t_size - t_bits); // update current pointer
		 }
		 else{
			current = (blockHeader*)((char*)current + t_size - t_bits); // update current pointer
		 }
	}
    }		
	if(found==0){
		if(maxsize==allocsize+1){ // if maxSize not updated no match found
			return NULL;
		}
		else{
			int remainingsize = maxsize - allocatesize;// size remianing 
			bestfit->size_status= bestfit->size_status - remainingsize+1; // updating the status of the allocated block
			
			if(remainingsize>0){
				split = (blockHeader*)((char*)bestfit + allocatesize); // blockHeader to the split block
				split->size_status = remainingsize+2; // updating p-bit of the next block
				blockHeader *footer = (blockHeader*) ((char*)bestfit + maxsize - 4); // updating the footer
    				footer->size_status = remainingsize; 
			}
			return (void*)((char*)bestfit + 4);// return pointer to payload
		}
	}
    
	return NULL;
}  
 
/* 
 * Function for freeing up a previously allocated block.
 * Argument ptr: address of the block to be freed up.
 * Returns 0 on success.
 * Returns -1 on failure.
 * This function should:
 * - Return -1 if ptr is NULL.
 * - Return -1 if ptr is not a multiple of 8.
 * - Return -1 if ptr is outside of the heap space.
 * - Return -1 if ptr block is already freed.
 * - Update header(s) and footer as needed.
 */                    
int myFree(void *ptr) {    
    //TODO: Your code goes in here.
    if(ptr==NULL){ // if pointer in NULL
	    return -1;
    }
    blockHeader* current = (blockHeader*)(ptr-4); // blockHeader to current pointer
    if(current->size_status & 0){// if blockHeader is already free
	    return -1;
    }
    if((current->size_status - current->size_status%8)>allocsize){// pointer is outside heapBlock
	    return -1;
    }
    int bits = current->size_status%8;
    int size = current->size_status - bits;
    if(size>allocsize){// if size is greater than allocsize
	    return -1;
    }
    current->size_status=current->size_status-1; // udating a bit of current block
    blockHeader* next = (blockHeader*)((char*)current + size); // storing next block header
    blockHeader *footer = (blockHeader*) ((char*)current + size - 4); // updating footer
    
    footer->size_status=size; 

    if(next->size_status==1) // is next block is end block just return 0
	    return 0;
    else{
	    next->size_status = next->size_status - 2; // if not end block update p bit and then return 0
	    return 0;
    }
    return -1;
} 

/*
 * Function for traversing heap block list and coalescing all adjacent 
 * free blocks.
 *
 * This function is used for delayed coalescing.
 * Updated header size_status and footer size_status as needed.
 */
int coalesce() {
    //TODO: Your code goes in here.
    blockHeader* current = heapStart; 
    int pagesize = 8;
    int prevSize = 0; // stores the size of prev block
    int count = 0; // if there has been a coalesce it is 1 else it is 0

    while (current->size_status != 1) {
       	int currSize = current->size_status; // stores curr size 
	int currBits = current->size_status%pagesize; // stores curr bits
	
	if (current -> size_status% pagesize == 0 ){// if current and previous block is free, i.e. pa = 00
		blockHeader* prev = (blockHeader*)((char*)current - prevSize); // store previous blockHeader
		prev->size_status = prev->size_status + currSize - currBits; // update the header of prev block to store combined block data
		count = 1; // update count
		prevSize = prev->size_status - (prev->size_status%8); // update prev Size
	}else{
		prevSize =currSize - currBits; // update prev Size
	}
	current = (blockHeader*)((char*)current + currSize - currBits);// update current block
    }	
	return count; // return count
}

 
/* 
 * Function used to initialize the memory allocator.
 * Intended to be called ONLY once by a program.
 * Argument sizeOfRegion: the size of the heap space to be allocated.
 * Returns 0 on success.
 * Returns -1 on failure.
 */                    
int myInit(int sizeOfRegion) {    
 
    static int allocated_once = 0; //prevent multiple myInit calls
 
    int pagesize;   // page size
    int padsize;    // size of padding when heap size not a multiple of page size
    void* mmap_ptr; // pointer to memory mapped area
    int fd;

    blockHeader* endMark;
  
    if (0 != allocated_once) {
        fprintf(stderr, 
        "Error:mem.c: InitHeap has allocated space during a previous call\n");
        return -1;
    }

    if (sizeOfRegion <= 0) {
        fprintf(stderr, "Error:mem.c: Requested block size is not positive\n");
        return -1;
    }

    // Get the pagesize
    pagesize = getpagesize();

    // Calculate padsize as the padding required to round up sizeOfRegion 
    // to a multiple of pagesize
    padsize = sizeOfRegion % pagesize;
    padsize = (pagesize - padsize) % pagesize;

    allocsize = sizeOfRegion + padsize;

    // Using mmap to allocate memory
    fd = open("/dev/zero", O_RDWR);
    if (-1 == fd) {
        fprintf(stderr, "Error:mem.c: Cannot open /dev/zero\n");
        return -1;
    }
    mmap_ptr = mmap(NULL, allocsize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == mmap_ptr) {
        fprintf(stderr, "Error:mem.c: mmap cannot allocate space\n");
        allocated_once = 0;
        return -1;
    }
  
    allocated_once = 1;

    // for double word alignment and end mark
    allocsize -= 8;

    // Initially there is only one big free block in the heap.
    // Skip first 4 bytes for double word alignment requirement.
    heapStart = (blockHeader*) mmap_ptr + 1;

    // Set the end mark
    endMark = (blockHeader*)((void*)heapStart + allocsize);
    endMark->size_status = 1;

    // Set size in header
    heapStart->size_status = allocsize;

    // Set p-bit as allocated in header
    // note a-bit left at 0 for free
    heapStart->size_status += 2;

    // Set the footer
    blockHeader *footer = (blockHeader*) ((void*)heapStart + allocsize - 4);
    footer->size_status = allocsize;
  
    return 0;
} 
                  
/* 
 * Function to be used for DEBUGGING to help you visualize your heap structure.
 * Prints out a list of all the blocks including this information:
 * No.      : serial number of the block 
 * Status   : free/used (allocated)
 * Prev     : status of previous block free/used (allocated)
 * t_Begin  : address of the first byte in the block (where the header starts) 
 * t_End    : address of the last byte in the block 
 * t_Size   : size of the block as stored in the block header
 */                     
void dispMem() {     
 
    int counter;
    char status[6];
    char p_status[6];
    char *t_begin = NULL;
    char *t_end   = NULL;
    int t_size;

    blockHeader *current = heapStart;
    counter = 1;

    int used_size = 0;
    int free_size = 0;
    int is_used   = -1;

    fprintf(stdout, 
	"*********************************** Block List **********************************\n");
    fprintf(stdout, "No.\tStatus\tPrev\tt_Begin\t\tt_End\t\tt_Size\n");
    fprintf(stdout, 
	"---------------------------------------------------------------------------------\n");
  
    while (current->size_status != 1) {
        t_begin = (char*)current;
        t_size = current->size_status;
    
        if (t_size & 1) {
            // LSB = 1 => used block
            strcpy(status, "alloc");
            is_used = 1;
            t_size = t_size - 1;
        } else {
            strcpy(status, "FREE ");
            is_used = 0;
        }

        if (t_size & 2) {
            strcpy(p_status, "alloc");
            t_size = t_size - 2;
        } else {
            strcpy(p_status, "FREE ");
        }

        if (is_used) 
            used_size += t_size;
        else 
            free_size += t_size;

        t_end = t_begin + t_size - 1;
    
        fprintf(stdout, "%d\t%s\t%s\t0x%08lx\t0x%08lx\t%4i\n", counter, status, 
        p_status, (unsigned long int)t_begin, (unsigned long int)t_end, t_size);
    
        current = (blockHeader*)((char*)current + t_size);
        counter = counter + 1;
    }

    fprintf(stdout, 
	"---------------------------------------------------------------------------------\n");
    fprintf(stdout, 
	"*********************************************************************************\n");
    fprintf(stdout, "Total used size = %4d\n", used_size);
    fprintf(stdout, "Total free size = %4d\n", free_size);
    fprintf(stdout, "Total size      = %4d\n", used_size + free_size);
    fprintf(stdout, 
	"*********************************************************************************\n");
    fflush(stdout);

    return;  
} 


// end of myHeap.c (sp 2021)                                         

