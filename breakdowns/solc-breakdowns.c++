// contract bytecode
// 0x6080604052348015600e575f80fd5b5060a58061001b5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea2646970667358221220e48966983a7dca85f7643a015e5f1fd84506592dac75a824e2595af6e12a69ad64736f6c63430008140033

// Contract creation code
// 0x6080604052348015600e575f80fd5b5060a58061001b5f395ff3

// Runtime code
// fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056

// metadata
// fea2646970667358221220e48966983a7dca85f7643a015e5f1fd84506592dac75a824e2595af6e12a69ad64736f6c63430008140033

// 3 sections:
// 1. Contract Creation
// 2. Runtime
// 3. Metadata

// 1. Contract Creation Code
// Free Memory Pointer
PUSH1 0x80                      // [0x80]
PUSH1 0x40                      // [0x40, 0x80]
MSTORE                          // []               // Memory 0x40 -> 0x80

// What's this chunk do?
// If someone sent value with this call revert!
// Otherwise, jump, to continue execution   
CALLVALUE                       // [msg.value]
DUP1                            // [msg.value, msg.value]
ISZERO                          // [msg.value == 0, msg.value]
PUSH1 0x0e                      // [0x0E, msg.value == 0, msg.value]
JUMPI                           // [msg.value]
PUSH0                           // [0x00, msg.value]
DUP1                            // [0x00, 0x00, msg.value]
REVERT                          // [msg.value]

// Jump dest if msg.value == 0
// Sticks the runtime code on chain (this sticks our runtime smart contract onchain)
JUMPDEST                        // [msg.value]
POP                             // []
PUSH1 0xa5                      // [0xa5]
DUP1                            // [0xa5, 0xa5]
PUSH2 0x001b                    // [0x001b, 0xa5, 0xa5]
PUSH0                           // [0x00, 0x001b, 0xa5, 0xa5]
CODECOPY                        // [0xa5]                     Memory: [runtime code]
PUSH0                           // [0x00, 0xa5] 
RETURN                          // []
INVALID                         // []

// 2. Runtime Code
// Entry point of all calls
// Free Memory Pointer
PUSH1 0x80
PUSH1 0x40
MSTORE

// Checking for msg.value, and if given, reverting
CALLVALUE                       // [msg.value]
DUP1                            // [msg.value, msg.value]
ISZERO                          // [msg.value == 0, msg.value]
PUSH1 0x0e                      // [0x0e, msg.value == 0, msg.value]
JUMPI                           // [msg.value]
// Jump to "continue" if msg.value == 0

PUSH0                           // [0x00, msg.value]
DUP1                            // [0x00, 0x00, msg.value]
REVERT                          // [msg.value]

// If msg.value == 0, start here!
// continue!
JUMPDEST                        // [msg.value]
POP                             // []
PUSH1 0x04                      // [0x04]
CALLDATASIZE                    // [calldata_size, 0x04]
LT                              // [calldata_size < 0x04]
PUSH1 0x30                      // [0x30, calldata_size < 0x04]
JUMPI                           // []
// if calldata_size < 0x04  -> calldata_jump

// Function dispatching in solidity!
PUSH0                           // [0]
CALLDATALOAD                    // [32 bytes of calldata]
PUSH1 0xe0                      // [0xe0, 32 bytes of calldata]
SHR                             // [calldata[0:4]] // function_selector

// Function dispatching for setNumberOfHorses
DUP1                            // [func_selector, func_selector]
PUSH4 0xcdfead2e                // [0xcdfead2e, func_selector, func_selector]
EQ                              // [0xcdfead2e == func_selector, func_selector]
PUSH1 0x34                      // [0x34, func_selector == 0xcdfead2e, func_selector]
JUMPI                           // [func_selector]  
// if func_selector == 0xcdfead2e -> set_number_of_horses

// Function dispatching for readNumberOfHorses
DUP1                            // [func_selector, func_selector]
PUSH4 0xe026c017                // [0xe026c017, func_selector, func_selector]
EQ                              // [func_selector == 0xe026c017, func_selector]
PUSH1 0x45                      // [0x45, func_selector == 0xe026c017, func_selector]
JUMPI                           // [func_selector]
// if func_selector == 0xe026c017  -> get_number_of_horses

// calldata_jump
// Revert Jumpdest
JUMPDEST                        // []
PUSH0                           // [0x00]
DUP1                            // [0x00, 0x00]
REVERT                          // []

// updateHorseNumber jump dest 1
// Setup jumping program counters in the stack
JUMPDEST                        // [func_selector]
PUSH1 0x43                      // [0x43, func_selector]
PUSH1 0x3f                      // [0x3f, 0x43, func_selector]
CALLDATASIZE                    // [calldata_size, 0x3f, 0x43, func_selector]
PUSH1 0x04                      // [0x04, calldata_size, 0x3f, 0x43, func_selector]
PUSH1 0x59                      // [0x59, 0x04, calldata_size, 0x3f, 0x43, func_selector]
JUMP                            // [0x04, calldata_size, 0x3f, 0x43, func_selector]

// Jump dest 4
// We can finally run an sstore to save our value to storage:
// 1. Function dispatch
// 2. Checked for msg.value
// 3. Checked that calldata is long enough
// 4. Received the number to use from the calldata
JUMPDEST                        // [calldata (of numberToUpdate), 0x43, func_selector]
PUSH0                           // [0x00, calldata (of numberToUpdate), 0x43, func_selector]
SSTORE                          // [0x43, func_selector]
JUMP                            // [func_selector]
// Jump dest 5

// Jump dest 5
JUMPDEST                        // [func_selector]
STOP                            // [func_selector]

// readNumberOfHorses jump dest 1
// the only jump dest
JUMPDEST                        // [func_selector]
PUSH0                           // [0x00, func_selector]
SLOAD                           // [numHorses, func_selector]
PUSH1 0x40                      // [0x40, numHorses, func_selector]
MLOAD                           // [0x80, numHorses, func_selector]   // Memory [0x40: 0x80] (free memory pointer)
SWAP1                           // [numHorses, 0x80, func_selector]
DUP2                            // [0x80, numHorses, 0x80, func_selector]
MSTORE                          // [0x80, func_selector]     Memory: 0x80: numHorses
PUSH1 0x20                      // [0x20, 0x80, func_selector]
ADD                             // [0xa0, func_selector]
PUSH1 0x40                      // [0x40, 0xa0, func_selector]
MLOAD                           // [0x80, 0xa0, func_selector]
DUP1                            // [0x80, 0x80, 0xa0, func_selector]
SWAP2                           // [0xa0, 0x80, 0x80, func_selector]
SUB                             // [0xa0 - 0x80, 0x80, func_selector]
SWAP1                           // [0x80, 0xa0 - 0x80 (0x20), func_selector]
// Return a value of size 32 bytes, that's located at position 0x80 in memory
RETURN                          // [func_selector]

// updateHorseNumber jump dest 2 
// Check to see if there is a value to update the horse number to 
// 4 bytes for function selector, 32 bytes for horse number
JUMPDEST                        // [0x04, calldata_size, 0x3f, 0x43, func_selector]
PUSH0                           // [0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
PUSH1 0x20                      // [0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
DUP3                            // [0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
DUP5                            // [calldata_size, 0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
SUB                             // [calldata_size - 0x04, 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// is there more calldaa than just the function selector?
SLT                             // [calldata_size - 0x04 < 0x20, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
ISZERO                          // [more_calldata_than_selector, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
PUSH1 0x68                      // [0x68, more_calldata_than_selector, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
JUMPI                           // [0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
// We are going to jump to jump dest 3 if there is more calldata than:
// function selector + 0x20

// Revert if there isn't enough calldata!
PUSH0                           // [0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
DUP1                            // [0x00, 0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
REVERT                          

// updateHorseNumber jump dest 3
// Grab the calldata for updating the horse number
// Delete some stuff in the stack
JUMPDEST                        // [0x00, 0x04, calldata_size, 0x3f, 0x43, func_selector]
POP                             // [0x04, calldata_size, 0x3f, 0x43, func_selector]
// Ignore the function selector, and just grab the data
// 0xcdfead2e 0000000000000000000000000000000000000000000000000000000000000007
CALLDATALOAD                    // [calldata (of numberToUpdate), calldata_size, 0x3f, 0x43, func_selector]
SWAP2                           // [0x3f, calldata_size, calldata (of numberToUpdate), 0x43, func_selector]
SWAP1                           // [calldata_size, 0x3f, calldata (of numberToUpdate), 0x43, func_selector]
POP                             // [0x3f, calldata (of numberToUpdate), 0x43, func_selector]
JUMP                            // [calldata (of numberToUpdate), 0x43, func_selector]
// jump to jump dest 4

INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
INVALID
DUP10
PUSH7 0x983a7dca85f764
GASPRICE
ADD
MCOPY
PUSH0
INVALID
INVALID
GASLIMIT
MOD
MSIZE
INVALID
INVALID
PUSH22 0xa824e2595af6e12a69ad64736f6c63430008140033