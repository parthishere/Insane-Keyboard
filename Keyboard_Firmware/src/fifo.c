//typedef struct
//{
//
//    uint16_t charHandle;               // GATT DB handle from gatt_db.h
//    uint32_t bufLength;                // Number of bytes written to field buffer[5]
//    uint8_t buffer[MAX_BUFFER_LENGTH]; // The actual data buffer for the indication,
//                                       //   need 5-bytes for HTM and 1-byte for button_state.
//                                       //   For testing, test lengths 1 through 5,
//                                       //   a length of 0 shall be considered an
//                                       //   error, as well as lengths > 5
//} queue_struct_t;
//
//
///*
// * ---------------------------------------------------------------------
// * Private function used only by this .c file.
// * Compute the next ptr value. Given a valid ptr value, compute the next valid
// * value of the ptr and return it.
// * Isolation of functionality: This defines "how" a pointer advances.
// * ---------------------------------------------------------------------
// */
//static uint32_t nextPtr(uint32_t ptr)
//{
//
//    // Advance the pointer to desired range of 0 to QUEUE_DEPTH
//    // with use of modulo, to make circular buffer
//    ptr = (ptr + 1) % QUEUE_DEPTH;
//
//    // Return the next pointer
//    return ptr;
//
//} // nextPtr()
//
///*
// * ---------------------------------------------------------------------
// * Check if the Queue is full or not with respect to current length
// * Queue
// * @params:
// *      int for_write: true or false based on for queue is full for writing or reading
// * @returns:
// *     return true or false based on queue is full or not
// * ---------------------------------------------------------------------
// */
//static bool checkFull(int for_write)
//{
//    // Check for_write variable for length check
//    if (for_write)
//    {
//        // If current_length of queue is equal to queue depth it would be full
//        // so we return true if length is equal to queue_depth
//        // Used for write constraint check
//        return (current_length == QUEUE_DEPTH);
//    }
//    else
//    {
//        // If current_length is equal to 0 that means there is no value left tor
//        // read in the queue
//        // Used for read constraint check
//        return (current_length == 0);
//    }
//}
//
///*
// * ---------------------------------------------------------------------
// * Printing Whole queue values for debugging purpose
// * printing all the values of queue charHandle, bufLength, Buffer values in formatted way
// * @params:
// *      none
// * @returns:
// *     none
// * ---------------------------------------------------------------------
// */
//void printBuffer(void)
//{
//    // Looping through each element for printing
//    for (int i = 0; i < QUEUE_DEPTH; i++)
//    {
//        LOG_INFO("Queue charHandle: %d, Queue length: %ld , Buffer: ", my_queue[i].charHandle, my_queue[i].bufLength);
//        // Looping through each buffer value for printing
//        for (int j = 0; j < MAX_BUFFER_LENGTH; j++)
//        {
//            // Printing buffer elements
//            LOG_INFO("%d ", my_queue[i].buffer[j]);
//        }
//        LOG_INFO("\n");
//    }
//}
//
///*
// * ---------------------------------------------------------------------
// * Public function.
// * This function resets the queue.
// * @params:
// *      none
// * @returns:
// *     none
// * ---------------------------------------------------------------------
// */
//void reset_queue(void)
//{
//    // reset every element to zero in the queue depth
//    for (int index = 0; index < QUEUE_DEPTH; index++)
//    {
//        // Setting bufLength and charLength to zero
//        my_queue[index].bufLength = 0;
//        my_queue[index].charHandle = 0;
//        memset(my_queue[index].buffer, 0, QUEUE_DEPTH); // Setting array value zero with memset
//    }
//    // setting pointers to initial (0) position
//    rptr = 0;
//    wptr = 0;
//
//} // reset_queue()
//
///* ---------------------------------------------------------------------
// * Public function.
// * This function writes an entry to the queue if the the queue is not full.
// * Input parameter "charHandle" should be written to queue_struct_t element "charHandle".
// * Input parameter "bufLength" should be written to queue_struct_t element "bufLength"
// * The bytes pointed at by input parameter "buffer" should be written to queue_struct_t element "buffer"
// * Returns bool false if successful or true if writing to a full fifo.
// * i.e. false means no error, true means an error occurred.
// * @params:
// *      uint16_t charHandle: charHandle for GattDB
// *      uint32_t bufLength: Bufferlength for buffer which should be greater than or =1 and less than or =5
// *      uint8_t *buffer: buffer to store ,need 5-bytes for HTM and 1-byte for button_state.
// * @returns:
// *     bool:
// * ---------------------------------------------------------------------
// */
//bool write_queue(uint16_t charHandle, uint32_t bufLength, uint8_t *buffer)
//{
//
//    // check if charHandle, bufLength, buffer is not null and
//    if (buffer == NULL || bufLength > MAX_BUFFER_LENGTH || bufLength < MIN_BUFFER_LENGTH)
//        return false;
//
//    // check rptr and wptr for full condition and round condition
//    if (checkFull(true))
//        return true;
//
//    // write the value at current write-ptr
//    my_queue[wptr].charHandle = charHandle;
//    my_queue[wptr].bufLength = bufLength;
//    memcpy(my_queue[wptr].buffer, buffer, bufLength); // copy to queue buffer via memcpy
//
//    // Increment the length of queue
//    current_length++;
//    // advance the write-ptr
//    wptr = nextPtr(wptr);
//
//    // return false at end to show no error
//    return false;
//} // write_queue()
//
///* ---------------------------------------------------------------------
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
//bool read_queue(uint16_t *charHandle, uint32_t *bufLength, uint8_t *buffer)
//{
//
//    // check rptr and wptr for full condition and round condition
//    if (checkFull(false))
//        return true;
//
//    // copy data to pointer
//    *bufLength = my_queue[rptr].bufLength;
//    *charHandle = my_queue[rptr].charHandle;
//    memcpy(&buffer[0], &my_queue[rptr].buffer[0], *bufLength); // Copy buffer with memcpy
//
//    // Reduce the length of queue as we just read the value
//    current_length--;
//    // advance the read pointer to next location
//    rptr = nextPtr(rptr);
//
//    // if everything went good return false = no error
//    return false;
//
//} // read_queue()
//
///* ---------------------------------------------------------------------
// * Public function.
// * This function returns the wptr, rptr, full and empty values, writing
// * to memory using the pointer values passed in, same rationale as read_queue()
// * The "_" characters are used to disambiguate the global variable names from
// * the input parameter names, such that there is no room for the compiler to make a
// * mistake in interpreting your intentions.
// * ---------------------------------------------------------------------
// */
//void get_queue_status(uint32_t *_wptr, uint32_t *_rptr, bool *_full, bool *_empty)
//{
//    // set the values according to the global variables
//    *_wptr = wptr;
//    *_rptr = rptr;
//    *_full = checkFull(true); // check if queue is full for write ?
//    *_empty = !(*_full);
//
//} // get_queue_status()
//
///* ---------------------------------------------------------------------
// * Public function.
// * Function that computes the number of written entries currently in the queue. If there
// * are 3 entries in the queue, it should return 3. If the queue is empty it should
// * return 0. If the queue is full it should return either QUEUE_DEPTH if
// * USE_ALL_ENTRIES==1 otherwise returns QUEUE_DEPTH-1.
// * ---------------------------------------------------------------------
// */
//uint32_t get_queue_depth()
//{
//
//    // just return the current length variable
//    return (current_length);
//
//} // get_queue_depth()
