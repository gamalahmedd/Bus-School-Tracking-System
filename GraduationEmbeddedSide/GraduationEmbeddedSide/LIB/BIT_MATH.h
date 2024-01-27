#ifndef BIT_MATH_H
#define BIT_MATH_H

#define REGISTER_SIZE       (8U)


/******************************************************************************
 * @brief Read state of a specific bit
 * @param[in] REGISTER: the register includes the bit
 * @param[in] BIT: the required bit number to be read
 * @return state of the bit: 1 or 0
 * @par For example:
 *  @code
 *  GET_BIT(PORT_A, PIN0);  // Return 1 if bit 0 of PORT_A is HIGH or 0 if it is LOW
 *  @endcode
 ******************************************************************************/
#define GET_BIT(REGISTER, BIT)      ( 1 & ( (REGISTER) >> (BIT) ) )

/******************************************************************************
 * @brief Set state of a specific bit (set to 1)
 * @param[in] REGISTER: the register includes the bit
 * @param[in] BIT: the required bit number to be set
 * @par For example:
 *  @code
 *  SET_BIT(PORT_A, PIN0);  // Set bit 0 of PORT_A to HIGH (1)
 *  @endcode
 ******************************************************************************/
#define SET_BIT(REGISTER, BIT)      ( REGISTER |= (1 << (BIT)) )

/******************************************************************************
 * @brief Clear state of a specific bit (set to 0)
 * @param[in] REGISTER: the register includes the bit
 * @param[in] BIT: the required bit number to be cleared
 * @par For example:
 *  @code
 *  CLEAR_BIT(PORT_A, PIN0);    // Set bit 0 of PORT_A to LOW (0)
 *  @endcode
 ******************************************************************************/
#define CLR_BIT(REGISTER, BIT)      ( REGISTER &= ~(1 << (BIT)) )

/******************************************************************************
 * @brief Toggle state of a specific bit (set to 0)
 * @param[in] REGISTER: is the register includes the bit
 * @param[in] BIT: the required bit number to be toggled
 * @par For example:
 *  @code
 *  TOG_BIT(PORT_A, PIN0);  // Toggle bit 0 of PORT_A. So if it was HIGH, 
 *                          // it will be LOW, and if it was LOW, it will be HIGH.
 *  @endcode
 ******************************************************************************/
#define TOG_BIT(REGISTER, BIT)      ( REGISTER ^= (1 << (BIT)) )

/******************************************************************************
 * @brief Check if state of a specific bit is set (state = 1)
 * @param[in] REGISTER: the register includes the bit
 * @param[in] BIT: the required bit number to be set
 * @return 1 or 0: 1 if the bit is set, 0 if the bit is cleared
 * @par For example:
 *  @code
 *  BIT_IS_SET(PORT_A, PIN0);   // Return 1 if bit 0 of PORT_A is HIGH or 0 if it is LOW
 *  @endcode
 ******************************************************************************/
#define BIT_IS_SET(REGISTER,Bit) 	( REGISTER & (1 << (Bit)) )


/******************************************************************************
 * @brief Check if state of a specific bit is Cleared (state =  0)
 * @param[in] REGISTER: the register includes the bit
 * @param[in] BIT: the required bit number to be set
 * @return 1 or 0: 1 if the bit is cleared, 0 if the bit is set
 * @par For example:
 *  @code
 *  BIT_IS_CLEAR(PORT_A, PIN0);     // Return 1 if bit 0 of PORT_A is LOW or 0 if it is HIGH
 *  @endcode
 ******************************************************************************/
#define BIT_IS_CLEAR(REGISTER,Bit)	( !( REGISTER & (1 << (Bit)) ) )

/******************************************************************************
 * @brief Rotate a register (8-bits) to the right by a specific number of bits
 * @param[in] reg: the register to be rotated
 * @param[in] num: the number of bits to be rotated
 * @return the rotated register
 * @par For example:
 *  @code
 *  ROTATE_RIGHT(PORT_A, 1);         // Rotate PORT_A to the right by 1 bit.
 *  ROTATE_RIGHT(0b11100011, 2);     // Return 0b11111000
 *  @endcode
 * @warning The number of bits to be rotated must be less than 8 and greater than 0
 * @precondition REGISTRER_SIZE
 ******************************************************************************/
#define ROTATE_RIGHT(reg, num)  ( reg = (reg << (REGISTER_SIZE - (num)) ) | (reg >> (num)) )

/*******************************************************************************
 * @brief Rotate a register (8-bits) to the left by a specific number of bits
 * @param[in] reg: the register to be rotated
 * @param[in] num: the number of bits to be rotated
 * @return the rotated register
 * @par For example:
 *  @code
 *  ROTATE_LEFT(PORT_A, 1);         // Rotate PORT_A to the left by 1 bit.
 *  ROTATE_LEFT(0b11100011, 2);     // Return 0b10001111
 *  @endcode
 * @warning The number of bits to be rotated must be less than 8 and greater than 0
 * @precondition REGISTRER_SIZE
 ******************************************************************************/
#define ROTATE_LEFT(reg, num)   ( reg = (reg >> (REGISTER_SIZE - (num)) ) | (reg << (num)) ) 



#define CONCAT_8BITS(b7, b6, b5, b4, b3, b2, b1, b0)  (0b##b7##b6##b5##b4##b3##b2##b1##b0)
#define CONCAT_7BITS(b6, b5, b4, b3, b2, b1, b0)      (0b##b6##b5##b4##b3##b2##b1##b0)
#define CONCAT_6BITS(b5, b4, b3, b2, b1, b0)          (0b##b5##b4##b3##b2##b1##b0)
#define CONCAT_5BITS(b4, b3, b2, b1, b0)              (0b##b4##b3##b2##b1##b0)
#define CONCAT_4BITS(b3, b2, b1, b0)                  (0b##b3##b2##b1##b0)
#define CONCAT_3BITS(b2, b1, b0)                      (0b##b2##b1##b0)
#define CONCAT_2BITS(b1, b0)                          (0b##b1##b0)

#endif			/* BIT_MATH_H	*/
