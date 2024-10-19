//// This is the number of entries in the queue. Please leave
//// this value set to 16.
//#define QUEUE_DEPTH (16)
//// Student edit:
////   define this to 1 if your design uses all array entries
////   define this to 0 if your design leaves 1 array entry empty
//#define USE_ALL_ENTRIES (1)
//s
///*
// * ---------------------------------------------------------------------
// * This function resets the queue.
// * @param
// *      none
// * @return
// *     none
// * ---------------------------------------------------------------------
// */
//void reset_queue(void);
//
///* ---------------------------------------------------------------------
// * This function writes an entry to the queue if the the queue is not full.
// * Input parameter "charHandle" should be written to queue_struct_t element "charHandle".
// * Input parameter "bufLength" should be written to queue_struct_t element "bufLength"
// * The bytes pointed at by input parameter "buffer" should be written to queue_struct_t element "buffer"
// * Returns bool false if successful or true if writing to a full fifo.
// * i.e. false means no error, true means an error occurred.
// * @param :
// *      uint16_t charHandle: charHandle for GattDB
// *      uint32_t bufLength: Bufferlength for buffer which should be greater than or =1 and less than or =5
// *      uint8_t *buffer: buffer to store ,need 5-bytes for HTM and 1-byte for button_state.
// * @return :
// *     bool:
// * ---------------------------------------------------------------------
// */
//bool write_queue(uint16_t charHandle, uint32_t bufLength, uint8_t *buffer);
//
///* ---------------------------------------------------------------------
// * Public function.
// * This function reads an entry from the queue, and returns values to the
// * caller. The values from the queue entry are returned by writing
// * the values to variables declared by the caller, where the caller is passing
// * in pointers to charHandle, bufLength and buffer. The caller's code will look like this:
// *
// *   uint16_t     charHandle;
// *   uint32_t     bufLength;
// *   uint8_t      buffer[5];
// *
// *   status = read_queue (&charHandle, &bufLength, &buffer[0]);
// *
// * *** If the code above doesn't make sense to you, you probably lack the
// * necessary prerequisite knowledge to be successful in this course.
// *
// * Write the values of charHandle, bufLength, and buffer from my_queue[rptr] to
// * the memory addresses pointed at by charHandle, bufLength and buffer, like this :
// *      *charHandle = <something>;
// *      *bufLength  = <something_else>;
// *      *buffer     = <something_else_again>; // perhaps memcpy() would be useful?
// *
// * In this implementation, we do it this way because
// * standard C does not provide a mechanism for a C function to return multiple
// * values, as is common in perl or python.
// * Returns bool false if successful or true if reading from an empty fifo.
// * i.e. false means no error, true means an error occurred.
// * ---------------------------------------------------------------------
// */
//bool read_queue(uint16_t *charHandle, uint32_t *bufLength, uint8_t *buffer);
//
///* ---------------------------------------------------------------------
// * This function returns the wptr, rptr, full and empty values, writing
// * to memory using the pointer values passed in, same rationale as read_queue()
// * The "_" characters are used to disambiguate the global variable names from
// * the input parameter names, such that there is no room for the compiler to make a
// * mistake in interpreting your intentions.
// * ---------------------------------------------------------------------
// */
//void get_queue_status(uint32_t *wptr, uint32_t *rptr, bool *full, bool *empty);
//
///* ---------------------------------------------------------------------
// * Function that computes the number of written entries currently in the queue. If there
// * are 3 entries in the queue, it should return 3. If the queue is empty it should
// * return 0. If the queue is full it should return either QUEUE_DEPTH if
// * USE_ALL_ENTRIES==1 otherwise returns QUEUE_DEPTH-1.
// * ---------------------------------------------------------------------
// */
//uint32_t get_queue_depth(void);
