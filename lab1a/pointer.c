/*
 * CSE 351 Lab 1a (Pointers in C)
 *
 * Name(s):  
 * NetID(s): 
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc compiler.
 * You can still use printf for debugging without including <stdio.h>. The
 * included file, "common.c" contains a function declaration that should
 * prevent a compiler warning. In general, it's not good practice to ignore
 * compiler warnings, but in this case it's OK.
 */

#ifndef COMMON_H
#include "common.h"
#endif

/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

#if 0
You will provide your solution to this homework by editing the collection of
functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one or more lines of C
  code that implements the function. Your code must conform to the following
  style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are not allowed to
     use big constants such as 0xFFFFFFFF. However, you are allowed to combine
     constants to produce values outside this range (e.g., 250 + 250 = 500) so
     long as the operator you are using to combine the constants is listed as
     "legal" at the top of the method you are writing.
  2. Function arguments and local variables (no global variables).
  3. Any operators listed as "ALLOWED" in the function header comment of the
     method you are writing.
  4. Casting.

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to one
  operator per line.

  You are expressly forbidden from:
  1. Using control constructs such as if, do, while, for, switch (unless
     otherwise stated).
  2. Defining or using macros.
  3. Defining additional functions in this file.
  4. Calling functions (unless otherwise stated).
  5. Using operators listed as "DISALLOWED" in the function header comment of
     the method you are writing.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has *undefined* behavior when shifting by a negative amount or an amount
     greater than or equal to the number of bits in the value being shifted.
     (i.e., x >> n is undefined when n < 0 or n >= *size of x*)
     (e.g., if x is a 32-bit int, shifts by >= 32 bits are undefined)
     Undefined behvaior means that the result of the operation may change in
     different environments -- this should be avoided.
#endif

/*
 * STEP 2: Modify the following functions according the coding rules.
 */

/*
 * Return the size of an integer in bytes.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Unary integer operators: !
 *   Shorthand operators based on the above: +=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
int int_size() {
  int int_array[10];
  int* int_ptr1;
  int* int_ptr2;
  int_ptr1 = int_array;
  int_ptr2 = int_array + 1;
  return (char*)int_ptr2 - (char*)int_ptr1;       //usually pointer subtraction will get how many item between the address, if we know char count one byte, we can seem it as a unit and cast the type to char pointer to check the size of int

/*int address1 = int_ptr1;       //another we can create a new variable and use address to subtraction
 *int address2 = int_ptr2;
 *return address1 - address2;
 * */
  ;
}

/*
 * Return the size of a double in bytes.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Unary integer operators: !
 *   Shorthand operators based on the above: +=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
int double_size() {
  double doub_array[10];
  double* doub_ptr1;
  double* doub_ptr2;
  // Write code to compute size of a double.
  doub_ptr1 = doub_array;
  doub_ptr2 = doub_array + 1;
  return (char*)doub_ptr2 - (char*)doub_ptr1;
/*double address1 = doub_ptr1;
 *double address2 = doub_ptr2;
 *return address2 - address1;
 * */

}

/*
 * Return the size of a pointer in bytes.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Unary integer operators: !
 *   Shorthand operators based on the above: +=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
int pointer_size() {
  double* ptr_array[10];
  double** ptr_ptr1;
  double** ptr_ptr2;
  // Write code to compute size of a pointer.
  ptr_ptr1 = ptr_array;
  ptr_ptr2 = ptr_array + 1;
  return (char*)ptr_ptr2 - (char*)ptr_ptr1;
/*ptr_ptr1 = ptr_array;
 *ptr_ptr2 = ptr_array + 1;
 *int address1 = ptr_ptr1;
 *int address2 = ptr_ptr2;
 *return address2 - address1;
 * */
}

/*
 * Given pointers to two variables, exchange/swap the values of the variables.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Unary integer operators: !
 *   Shorthand operators based on the above: +=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
void swap_ints(int* ptr1, int* ptr2) {
  // Your code here
  
// Store the value at *ptr1 in a temporary variable
    int temp = *ptr1; // Store the *ptr1 in a temporary variable
    *ptr1 = *ptr2;// Assign the value at *ptr2 to *ptr1
    *ptr2 = temp; // Assign the value in temp to *ptr2
}

/*
 * Modify int_array[5] to be the value 351 using only int_array and pointer
 * arithmetic.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, <<, >>, ==, ^
 *   Unary integer operators: !, ~
 *   Shorthand operators based on the above: +=, *=, ++, --, ~= etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, !=, /, %
 *   Unary integer operators: -
 */
int change_value() {
  int int_array[10];
  int* int_ptr1 = int_array;
  // Remember not to use constants greater than 255.
  // Remember to use * to dereference. You cannot use '[<index>]' syntax.

  *(int_ptr1 + 5) = (250 + 101);// use the pointer to int_array[5] and give it a new value both 250 and 101 are not larger than 255
  return *(int_ptr1 + 5);
}

/*
 * Return 1 if the addresses stored in ptr1 and ptr2 are within the *same*
 * 64-byte aligned block of memory or return 0 otherwise. Check the spec for
 * examples if you are unsure of what this means.
 *
 * Note that loops and the operators / and % are NOT allowed.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, <<, >>, ==, ^
 *   Unary integer operators: !, ~
 *   Shorthand operators based on the above: <<=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, !=, /, %
 *   Unary integer operators: -
 */
int within_same_block(int* ptr1, int* ptr2) {
  //A 64-byte block means that the lower 6 bits of the address determine its position within the block (since 2^6 = 64).
  //Mask off the lower 6 bits to get the block start address
  // Return 1 if both addresses are in the same block, otherwise return 0
  return (long int) ptr1 >> 6 == (long int) ptr2 >> 6;
  //other idea: int mask = 0000 0000 0000 0000 0000 0000 0100 0000 == (1 << 31) >> 25
  //return (add1 & mask) == (addr2 & mask);
}

/*
 * Return 1 if ptr points to a byte within the specified int_array or return 0
 * otherwise. ptr does not have to point to the beginning of an element. Check
 * the spec for examples if you are unsure of what this means. size is the
 * size of int_array in number of ints; assume size != 0.
 *
 * Note that loops and the operators / and % are NOT allowed.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, <<, >>, ==, ^
 *   Unary integer operators: !, ~
 *   Shorthand operators based on the above: <<=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, !=, /, %
 *   Unary integer operators: -
 */
int within_array(int* int_array, int size, int* ptr) {
  // Your code here
  char* last_byte = (char*)(int_array + size - 1) + int_size() - 1; //Find the address of the last byte in the array
  int diff1 = (char*)ptr - (char*)int_array; //The address difference between the first byte to ptr
  int diff2 = (char*)ptr - last_byte; //The address difference between the last byte to ptr
  int ab1 = ((diff1 >> 31) *2 + 1) * diff1; //A tricky way to find the absolute value of the diff1 and diff2 
  int ab2 = ((diff2 >> 31) *2 + 1) * diff2;  //if negative >> 31 will become 0xFFFF(signed=-1) *2+1 =-1
                                             //if positive >> 31 will become 0x0*2+1 =1
	return (size * int_size() - 1) == (ab1 + ab2); 
//instead method like ptr > int_array = (ptr - int_array)>0 and check its wheather positive or negative use >> to avoid < and >
//I use the way to check ptr in array or not by |diff1|+|diff2| = (last_byte - first byte), |diff1| means absolute value here. If this is true, ptr is in the array, otherwise it's false. (since if it's on the left or right side of array, the two absolute value must more than difference between fist and last byte. And no matter what place inside the array two value are equal.)
}

/*
 * In C, the end of a "string" is indicated by the null terminator ('\0').
 * Given a pointer to the start of a "string," return the string length.
 * The null terminator is not counted as part of the string length.
 *
 * Note that loops ARE allowed.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, ==, !=, <, >
 *   Unary integer operators: !
 *   Shorthand operators based on the above: <<=, *=, ++, --, etc.
 *   Control constructs: for, while
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <<, >>, ^, /, %
 *   Unary integer operators: ~, -
 */
int string_length(char* s) {
  // Your code here
  int length = 0; // Initialize length counter to 0
 // Loop through the string until we reach the null terminator
  while (*s != '\0'){
  	length++;// Increment the length for each character
	s++;// Move to the next character
  }
  return length;
}


/*
 * Change the value pointed to by ptr byte-by-byte so that when returned as an
 * integer the value is 351351.
 *
 * Hints: Recall that an int is 4 bytes and how little endian works for
 * multibyte memory storage. We suggest starting by converting 351351 into
 * binary/hexadecimal.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Shorthand operators based on the above: +=, *=, ++, --, etc.
 *   Unary integer operators: !
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
int endian_experiment(int* ptr) {      //351351 = 0x55c77  
  char* byte_ptr;
  // Your code here
  byte_ptr = (char*)ptr;  //casting
    *(byte_ptr + 0) = 0x77; // Least significant byte
    *(byte_ptr + 1) = 0x5C; // Second byte 
    *(byte_ptr + 2) = 0x05; // Third byte
    *(byte_ptr + 3) = 0x00; // Most significant byte

  return *ptr;
}

/*
 * Selection sort is a sorting algorithm that works by partitioning the array
 * into a sorted section and unsorted section. Then it repeatedly selects the
 * minimum element from the unsorted section and moves it to the end of the
 * sorted section.
 *
 * Pseudo-code for an array (arr) and its length (n) might look like:
 *
 *   for i = 0 to n - 1
 *     minIndex = i
 *     for  j = i + 1 to n
 *       if arr[minIndex] > arr[j]
 *         minIndex = j
 *       end if
 *     end for
 *     Swap(arr[i], arr[minIndex])
 *   end for
 *
 * Note that control constructs and calling swap_ints() ARE allowed.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, ==, !=, <, >
 *   Unary integer operators: !
 *   Shorthand operators based on the above: +=, *=, ++, --, etc.
 *   Control constructs: for, while, if
 *   Function calls: swap_ints()
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <<, >>, ^, /
 *   Unary integer operators: ~, -
 */
void selection_sort(int arr[], int arr_length) {
  int i, j, min_index;
  // Your code here
  for (i = 0; i < arr_length - 1; i++){
	min_index = i;	  
  	for(j = i + 1; j < arr_length; j++){ // Iterate through the unsorted part
		if(*(arr + j)< *(arr + min_index)){
			min_index = j; // Update minptr if a smaller element is found
		}		
	}
	// Swap the min with the with the element at position i
  	swap_ints(arr + i, arr + min_index);
  
  }



}
