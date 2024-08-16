// SPDX-License-Identifier: MIT
pragma solidity 0.8.20;

contract HorseStore {
    uint256 numOfHorses;

    function updateHorseNumber(uint256 newNumberOfHorses) external {
        numOfHorses = newNumberOfHorses;
    }

    function readNumberOfHorses() external view returns (uint256) {
        return numOfHorses;
    }
}
