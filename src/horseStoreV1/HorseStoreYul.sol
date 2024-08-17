// SPDX-License-Identifier: MIT
pragma solidity 0.8.20;

contract HorseStoreYul {
    uint256 numOfHorses;

    function updateHorseNumber(uint256 newNumberOfHorses) external {
        // numOfHorses = newNumberOfHorses;
        assembly {
            sstore(numOfHorses.slot, newNumberOfHorses)
        }
    }

    function readNumberOfHorses() external view returns (uint256) {
        // return numOfHorses;
        assembly {
            let num := sload(numOfHorses.slot)
            mstore(0, num)
            return(0, 0x20)
        }
    }
}
