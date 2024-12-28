/*
 * CSE 351 Lab 1b (Manipulating Bits in C)
 *
 * Name(s): Zifeng Wang  
 * NetID(s): 2478280
 *
 * This is a file for managing a store of various aisles, represented by an
 * array of 64-bit integers. See aisle_manager.c for details on the aisle
 * layout and descriptions of the aisle functions that you may call here.
 *
 * Written by Porter Jones (pbjones@cs.washington.edu)
 */

#include <stddef.h>  // To be able to use NULL
#include "aisle_manager.h"
#include "store_client.h"
#include "store_util.h"

// Number of aisles in the store
#define NUM_AISLES 10

// Number of sections per aisle
#define SECTIONS_PER_AISLE 4

// Number of items in the stockroom (2^6 different id combinations)
#define NUM_ITEMS 64

//size of section IN BYTE
#define SECTION_SIZE 2 

// Global array of aisles in this store. Each unsigned long in the array
// represents one aisle.
unsigned long aisles[NUM_AISLES];

// Array used to stock items that can be used for later. The index of the array
// corresponds to the item id and the value at an index indicates how many of
// that particular item are in the stockroom.
int stockroom[NUM_ITEMS];


/* Starting from the first aisle, refill as many sections as possible using
 * items from the stockroom. A section can only be filled with items that match
 * the section's item id. Prioritizes and fills sections with lower addresses
 * first. Sections with lower addresses should be fully filled (if possible)
 * before moving onto the next section.
 */
void refill_from_stockroom() {
  // TODO: implement this function

	// Loop through all aisles
  for (int aisle_idx = 0; aisle_idx < NUM_AISLES; aisle_idx++) {
    // Loop through all sections in each aisle
    for (int section_idx = 0; section_idx < SECTIONS_PER_AISLE; section_idx++) {
    	// Get the item ID for this section
        unsigned short item_id = get_id(&aisles[aisle_idx], section_idx);
      
        // Check how many of this item are available in the stockroom
        int stock = stockroom[item_id];

	// Calculate how many empty spaces are in this section
        unsigned short empty_spaces = 10 - num_items(&aisles[aisle_idx], section_idx);

        // If we have items in stock
        if (stock > 0 && empty_spaces > 0) { 
        	// Directly call add_items with the available stock  
        	add_items(&aisles[aisle_idx], section_idx, stock);

		// Determine how many items we can actually add
                int items_to_add = (stock < empty_spaces) ? stock : empty_spaces;  // ternary operator: condition ? result_if_true : result_if_false;

      		// Update the stockroom by reducing the number of added items
                stockroom[item_id] -= items_to_add;      
	}
    }
  }

}


/* Remove at most num items from sections with the given item id, starting with
 * sections with lower addresses, and return the total number of items removed.
 * Multiple sections can store items of the same item id. If there are not
 * enough items with the given item id in the aisles, first remove all the
 * items from the aisles possible and then use items in the stockroom of the
 * given item id to finish fulfilling an order. If the stockroom runs out of
 * items, you should remove as many items as possible.
 */
int fulfill_order(unsigned short id, int num) {
  // TODO: implement this function

      int items_removed = 0; // Track the number of items removed
	int remaining = num;   // Track the number of items still to remove

	// Loop through all aisles
  	for (int aisle_idx = 0; aisle_idx < NUM_AISLES; aisle_idx++) {
    		// Loop through all sections in each aisle
    		for (int section_idx = 0; section_idx < SECTIONS_PER_AISLE; section_idx++) {
			// Get the item ID for this section
        		unsigned short item_id = get_id(&aisles[aisle_idx], section_idx);

			// If the section contains the given item id
                	if (item_id == id) {
                		// items from this section
                		unsigned short items_in_section = num_items(&aisles[aisle_idx], section_idx);
				// We can remove either all items in the section or as many as needed to fulfill the order
                        	int items_to_remove = (items_in_section <= remaining) ? items_in_section : remaining;
				// Remove items from the section
                		remove_items(&aisles[aisle_idx], section_idx, items_to_remove);

				// Update counters
                		items_removed += items_to_remove;
                		remaining -= items_to_remove;

				if (remaining == 0) {
                    			return items_removed;
                		}
			}
		}
	}
	// If we couldn't fulfill the order from the aisles, use items from the stockroom
    	int stock_available = stockroom[id];  // Get the stockroom amount for this id
    	int stock_to_remove = (stock_available <= remaining) ? stock_available : remaining;

	stockroom[id] -= stock_to_remove;
        items_removed += stock_to_remove;

    	return items_removed;

}

/* Return a pointer to the first section in the aisles with the given item id
 * that has no items in it or NULL if no such section exists. Only consider
 * items stored in sections in the aisles (i.e., ignore anything in the
 * stockroom). Break ties by returning the section with the lowest address.
 */
unsigned short* empty_section_with_id(unsigned short id) {
  // TODO: implement this function

	// Iterate through all aisles and sections
	for (int aisle_idx = 0; aisle_idx < NUM_AISLES; aisle_idx++) {
        	for (int section_idx = 0; section_idx < SECTIONS_PER_AISLE; section_idx++) {
                	// Get the item ID of the current section
            		unsigned short section_id = get_id(&aisles[aisle_idx], section_idx);

            		// Check if the section matches the given ID and is empty
            		if (section_id == id && num_items(&aisles[aisle_idx], section_idx) == 0) {
                		// return the pointer to the section
				unsigned short* section_ptr = (unsigned short*)((char*)(&aisles[aisle_idx]) + section_idx * (SECTION_SIZE)); //SECTION_SIZE is 16 bits = 2 bytees
				return section_ptr;
            		}
        	}
    	}

    	// if no such section exists, return NULL
	return NULL;

}

/* Return a pointer to the section with the most items in the store. Only
 * consider items stored in sections in the aisles (i.e., ignore anything in
 * the stockroom). Break ties by returning the section with the lowest address.
 */
unsigned short* section_with_most_items() {
  // TODO: implement this function

	
	unsigned short* max_section_ptr = NULL;  // Pointer to the section with the most items
        int max_items = -1;  // Tracks the maximum number of items found so far

	// Iterate through all aisles and sections
    	for (int aisle_idx = 0; aisle_idx < NUM_AISLES; aisle_idx++) {
        	for (int section_idx = 0; section_idx < SECTIONS_PER_AISLE; section_idx++) {
			// Get the number of items in the current section
            		int current_items = num_items(&aisles[aisle_idx], section_idx);

			// If this section has more items than the current maximum, update the max
            		if (current_items > max_items) {
                		max_items = current_items;
                		// Set the pointer to the current section
                		max_section_ptr = (unsigned short*)((char*)(&aisles[aisle_idx]) + section_idx * (SECTION_SIZE));
            		}
		}		
	}
  return max_section_ptr;

}
