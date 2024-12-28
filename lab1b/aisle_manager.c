/*
 * CSE 351 Lab 1b (Manipulating Bits in C)
 *
 * Name(s): Zifeng Wang  
 * NetID(s): 2478280
 *
 * ----------------------------------------------------------------------------
 * Overview
 * ----------------------------------------------------------------------------
 *  This is a program to keep track of the items in a small aisle of a store.
 *
 *  A store's aisle is represented by a 64-bit long integer, which is broken
 *  into 4 16-bit sections representing one type of item each. Note that since
 *  a section is 16-bits, it fits nicely into C's short datatype.
 *
 *  Aisle Layout:
 *
 *    Within an aisle, sections are indexed starting with the least-significant
 *    section being at index 0 and continuing up until one less than the number
 *    of sections.
 *
 *    Example aisle:
 *
 *                MSB                                                       LSB
 *                  +-------------+-------------+-------------+-------------+
 *                  |  Section 3  |  Section 2  |  Section 1  |  Section 0  |
 *                  +-------------+-------------+-------------+-------------+
 *                  |             |             |             |             |
 *      bit offset: 64            48            32            16            0
 *
 *  Section Layout:
 *
 *    A section in an aisle is broken into 2 parts. The 6 most significant bits
 *    represent a unique identifier for the type of item stored in that
 *    section. The rest of the bits in a section (10 least significant)
 *    indicate individual spaces for items in that section. For each of the 10
 *    bits/spaces, a 1 indicates that an item of the section's type is stored
 *    there and a 0 indicates that the space is empty.
 *
 *    Example aisle section: 0x651A
 *
 *                MSB                               LSB
 *                  +-----------+-------------------+
 *                  |0 1 1 0 0 1|0 1 0 0 0 1 1 0 1 0|
 *                  +-----------+-------------------+
 *                  | item id   | section spaces    |
 *      bit offset: 16          10                  0
 *
 *      In this example, the item id is 0b011001, and there are currently 4
 *      items stored in the section (at bit offsets 8, 4, 3, and 1) and 6
 *      vacant spaces.
 *
 *  Written by Porter Jones (pbjones@cs.washington.edu)
 */

#include "aisle_manager.h"
#include "store_util.h"

// the number of total bits in a section
#define SECTION_SIZE 16

// The number of bits in a section used for the item spaces
#define NUM_SPACES 10

// The number of bits in a section used for the item id
#define ID_SIZE 6

// The number of sections in an aisle
#define NUM_SECTIONS 4

// TODO: Fill in these with the correct hex values

// Mask for extracting a section from the least significant bits of an aisle.
// (aisle & SECTION_MASK) should preserve a section's worth of bits at the
// lower end of the aisle and set all other bits to 0. This is essentially
// extracting section 0 from the example aisle shown above.
#define SECTION_MASK 0xFFFF

// Mask for extracting the spaces bits from a section.
// (section & SPACES_MASK) should preserve all the spaces bits in a section and
// set all non-spaces bits to 0.
#define SPACES_MASK 0x03FF

// Mask for extracting the ID bits from a section.
// (section & ID_MASK) should preserve all the id bits in a section and set all
// non-id bits to 0.
#define ID_MASK 0xFC00


/* Given a pointer to an aisle and a section index, return the section at the
 * given index of the given aisle.
 *
 * Can assume the index is a valid index (0-3 inclusive).
 */
unsigned short get_section(unsigned long* aisle, int index) {
  // TODO: implement this method

  	// Shift the aisle to the right by (index * 16) bits
	unsigned long shifted_aisle = (*aisle) >> (index * SECTION_SIZE);
	
	// Apply the SECTION_MASK to isolate the section
    	unsigned short section = (unsigned short)(shifted_aisle & SECTION_MASK);
		
return section;

}

/* Given a pointer to an aisle and a section index, return the spaces of the
 * section at the given index of the given aisle. The returned short should
 * have the least 10 significant bits set to the spaces and the 6 most
 * significant bits set to 0.
 *
 * Can assume the index is a valid index (0-3 inclusive).
 */
unsigned short get_spaces(unsigned long* aisle, int index) {
  // TODO: implement this method
	
  	// Get the section from the aisle
	unsigned short section = get_section(aisle, index);

	// Apply the SPACES_MASK to isolate the spaces bits
	unsigned short space = (section & SPACES_MASK);

  return space;
}

/* Given a pointer to an aisle and a section index, return the id of the
 * section at the given index of the given aisle. The returned short should
 * have the least 6 significant bits set to the id and the 10 most significant
 * bits set to 0.
 *
 * Example: if the section is 0b0110010100011010, return 0b0000000000011001.
 *
 * Can assume the index is a valid index (0-3 inclusive).
 */
unsigned short get_id(unsigned long* aisle, int index) {
  // TODO: implement this method
	
  	// Get the section from the aisle
	unsigned short section = get_section(aisle, index);

	// Shift the section right by 10 bits to extract the ID
	unsigned short id = section >> 10;

  return id;
}

/* Given a pointer to an aisle, a section index, and a short representing a new
 * bit pattern to be used for section, set the section at the given index of
 * the given aisle to the new bit pattern.
 *
 * Can assume the index is a valid index (0-3 inclusive).
 */
void set_section(unsigned long* aisle, int index, unsigned short new_section) {
  // TODO: implement this method
	
	// unsigned short size just equal 16 bits, we can create a unsigned short pointer
	unsigned short *ptr;
	ptr = (unsigned short*) aisle;
	ptr += index;
	*ptr = new_section;


	//silly way:
  	//if use &, other section data will broken, so we clear the old section first and then use | or to get new section
	// Create a mask to clear the 16-bit section at the given index
    	//unsigned long clear_mask = ~((unsigned long)SECTION_MASK << (index * SECTION_SIZE));

	// Clear the section at the given index
   	//*aisle &= clear_mask;

    	// Shift the new section into the appropriate position
    	//unsigned long newsection_mask = ((unsigned long)new_section) << (index * SECTION_SIZE);

	// Set the new section in the aisle using bitwise OR
    	//*aisle |= newsection_mask;

}

/* Given a pointer to an aisle, a section index, and a short representing a new
 * bit pattern to be used for the spaces of the section, set the spaces for the
 * section at the given index of the given aisle to the new bit pattern. The
 * new spaces pattern should be in the 10 least significant bits of the given
 * bit pattern. If the new pattern uses bits outside the 10 least significant
 * bits, then the method should leave the spaces unchanged.
 *
 * Can assume the index is a valid index (0-3 inclusive).
 */
void set_spaces(unsigned long* aisle, int index, unsigned short new_spaces) {
  // TODO: implement this method
	
  	// Check if new_spaces has any bits set outside the 10 least significant bits
  	if (new_spaces & ~SPACES_MASK) {
    		// If there are bits set beyond the 10 least significant bits, do nothing
    	return;
  	}

	// Get the current section from the aisle
	unsigned short current_section = get_section(aisle, index);

	// Mask new_spaces to ensure only the 10 least significant bits are used
 	// new_spaces = new_spaces & SPACES_MASK;  // SPACES_MASK = 0x03FF we already have if statement, no need to mask again
  
 	// Clear the current spaces bits (using ID_MASK to preserve the ID)
 	current_section = current_section & ID_MASK;  // ID_MASK = 0xFC00
	
	// Combine the ID (preserved) with the new spaces bits
  	unsigned short updated_section = current_section | new_spaces;

	// Set the new section in the aisle
  	set_section(aisle, index, updated_section);
}

/* Given a pointer to an aisle, a section index, and a short representing a new
 * bit pattern to be used for the id of the section, set the id for the section
 * at the given index of the given aisle to the new bit pattern. The new id
 * pattern should be in the 6 least significant bits of the given bit pattern.
 * If the new pattern uses bits outside the 6 least significant bits, then the
 * method should leave the id unchanged.
 *
 * Can assume the index is a valid index (0-3 inclusive).
 */
void set_id(unsigned long* aisle, int index, unsigned short new_id) {
  // TODO: implement this method

	unsigned long newidtest_mask = ~0x3F;

	// Check if new_spaces has any bits set outside the 6 least significant bits
  	if (new_id & newidtest_mask) {
    		// If there are bits set beyond the 6 least significant bits, do nothing
    	return;
  	}

	// Get the current section from the aisle
	unsigned short current_section = get_section(aisle, index);
  
 	// Clear the current id bits (using SPACES_MASK to preserve the space)
 	current_section = current_section & SPACES_MASK;  // SPACES_MASK = 0x03FF
	
	// Combine the ID (preserved) with the new spaces bits
  	unsigned short updated_section = current_section | (new_id << 10);

	// Set the new section in the aisle
  	set_section(aisle, index, updated_section);

}


/* Given a pointer to an aisle, a section index, and a space index, toggle the
 * item in the given space index of the section at the given section index in
 * the given aisle. Toggling means that if the space was previously empty, it
 * should now be filled with an item, vice-versa.
 *
 * Can assume the section index is a valid index (0-3 inclusive).
 * Can assume the spaces index is a valid index (0-9 inclusive).
 */
void toggle_space(unsigned long* aisle, int index, int space_index) {
  // TODO: implement this method
	
	// Get the current spaces in the section
	unsigned short current_spaces = get_spaces(aisle, index);
	
	// Create a bitmask with a 1 at the position space_index
  	unsigned short mask = (1 << space_index);
  
  	// Toggle the bit at space_index using XOR, 0^x x won't change, 1^x x will flip 0-1, 1-0
 	unsigned short new_spaces = current_spaces ^ mask;

	// Set the updated spaces back into the section
	set_spaces(aisle, index, new_spaces);

}

/* Given a pointer to an aisle and a section index, return the number of items
 * in the section at the given index of the given aisle.
 *
 * Can assume the index is a valid index (0-3 inclusive).
 */
unsigned short num_items(unsigned long* aisle, int index) {
  // TODO: implement this method

	// Get the current spaces in the section
	unsigned short current_spaces = get_spaces(aisle, index);

	// Counter for the number of items
	unsigned short count = 0;

	// Iterate through the least significant 10 bits
 	for (int i = 0; i < 10; i++) {
   		if (current_spaces & (1 << i)) {  // Check if the bit at position i is 1
      			count++;
    		}
	}
  return count;
      
}

/* Given a pointer to an aisle, a section index, and the desired number of
 * items to add, add at most the given number of items to the section at the
 * given index in the given aisle. Items should be added to the least
 * significant spaces possible. If n is larger than or equal to the number of
 * empty spaces in the section, then the section should appear full after the
 * method finishes.
 *
 * Can assume the index is a valid index (0-3 inclusive).
 */
void add_items(unsigned long* aisle, int index, int n) {
  // TODO: implement this method

	// Get the current spaces in the section
  	unsigned short current_spaces = get_spaces(aisle, index);

	// Calculate the number of empty spaces
	unsigned short empty_spaces = 10 - num_items(aisle, index);

	if(n >= empty_spaces){
		unsigned short full_spaces = 0x3FF; // 0x3FF means all 10 spaces are filled
		set_spaces(aisle, index, full_spaces);
	} else {
		// If not, add `n` items to the least significant empty spaces
    		unsigned short new_spaces = current_spaces;
    		int added_items = 0;

   		// Iterate through each space and add items
    		for (int i = 0; added_items < n; i++) {  //will always reach added_items == n before the loop iterates 10 times, so we don't need to add i < 10 condition
      			if (!(new_spaces & (1 << i))) {  // Check if the space is empty (bit is 0)   another way is ((current_spaces >> i) & 1) == 0     					
				new_spaces |= (1 << i);  // Set the bit to 1 to add an item  new_spaces = new_spaces | (1 << i)
        			added_items++;
      			}	
		}
		// Update the section with the new bit pattern
   		set_spaces(aisle, index, new_spaces);
	}

}

/* Given a pointer to an aisle, a section index, and the desired number of
 * items to remove, remove at most the given number of items from the section
 * at the given index in the given aisle. Items should be removed from the
 * least significant spaces possible. If n is larger than or equal to the
 * number of items in the section, then the section should appear empty after
 * the method finishes.
 *
 * Can assume the index is a valid index (0-3 inclusive).
 */
void remove_items(unsigned long* aisle, int index, int n) {
  // TODO: implement this method

	// Get the current spaces in the section
  	unsigned short current_spaces = get_spaces(aisle, index);

	// the number of items in spaces
	unsigned short item_spaces = num_items(aisle, index);

	if(n >= item_spaces){
		unsigned short empty_spaces = 0x0; // 0x0 means all 10 spaces are empty
		set_spaces(aisle, index, empty_spaces);
	} else {
		// If not, remove `n` items from the least significant empty spaces
    		unsigned short new_spaces = current_spaces;
    		int removed_items = 0;

   		// Iterate through each space and remove items
    		for (int i = 0; removed_items < n; i++) {  //will always reach added_items == n before the loop iterates 10 times, so we don't need to add i < 10 condition
      			if ((new_spaces >> i) & 1) {  // Check if the space is filled (bit is 1)        						// Clear the bit (set it to 0) to remove the item
                		new_spaces &= ~(1 << i); // Remove item by clearing the bit
                		removed_items++;
      			}	
		}
		// Update the section with the new bit pattern
   		set_spaces(aisle, index, new_spaces);
	}

}

/* Given a pointer to an aisle, a section index, and a number of slots to
 * rotate by, rotate the items in the section at the given index of the given
 * aisle to the left by the given number of slots.
 *
 * Example: if the spaces are 0b0111100001, then rotating left by 2 results
 *          in the spaces     0b1110000101
 *
 * Can assume the index is a valid index (0-3 inclusive).
 * Can NOT assume n < NUM_SPACES (hint: find an equivalent rotation).
 */
void rotate_items_left(unsigned long* aisle, int index, int n) {
  // TODO: implement this method

	// Get the current spaces in the section
  	unsigned short current_spaces = get_spaces(aisle, index);
	
	// rotate patern 10 times is equal not move, so we can take the remainder of n and the result of rotation is the same
	n %= 10;
	// Perform the left rotation
    	unsigned short new_spaces = (current_spaces << n) | (current_spaces >> (10 - n));
	//current_spaces << n, we get (10-n) most significant for new_spaces
	//current_spaces >> (10 - n), we get n least significant for new_spaces

	// Mask out any bits beyond the 10 least significant bits
   	new_spaces &= SPACES_MASK;

	// Update the section with the new bit pattern
   		set_spaces(aisle, index, new_spaces);

/*	for (int i = 0, i < n, i++ ){
 *		// check the most significant is 0 or 1   mask = | 0x200
 *		if (current_spaces ^mask){ \true, the most significant is 0, 
 *			current_spaces << 1;	\if most significant is 0, directly use <<
 *		} else {
 *			(current_spaces << 1) + 0x1;	\if most significant is 1, we need << and +1
 *		}
 *	}  silly way to use for loop and if statement
 */
}

/* Given a pointer to an aisle, a section index, and a number of slots to
 * rotate by, rotate the items in the section at the given index of the given
 * aisle to the right by the given number of slots.
 *
 * Example: if the spaces are 0b1000011110, then rotating right by 2 results
 *          in the spaces     0b1010000111
 *
 * Can assume the index is a valid index (0-3 inclusive).
 * Can NOT assume n < NUM_SPACES (hint: find an equivalent rotation).
 */
void rotate_items_right(unsigned long* aisle, int index, int n) {
  // TODO: implement this method

	// Get the current spaces in the section
  	unsigned short current_spaces = get_spaces(aisle, index);
	
	// rotate patern 10 times is equal not move, so we can take the remainder of n and the result of rotation is the same
	n %= 10;
	// Perform the left rotation
    	unsigned short new_spaces = (current_spaces >> n) | (current_spaces << (10 - n));
	//current_spaces >> n, we get (10-n) least significant for new_spaces
	//current_spaces << (10 - n), we get n most significant for new_spaces

	// Mask out any bits beyond the 10 least significant bits
   	new_spaces &= SPACES_MASK;

	// Update the section with the new bit pattern
   		set_spaces(aisle, index, new_spaces);
}
