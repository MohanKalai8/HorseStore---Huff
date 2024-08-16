// SPDX-License-Identifier: MIT
pragma solidity 0.8.20;

import {Base_TestV1,HorseStore} from "./Base_TestV1.t.sol";
import {HuffDeployer} from "foundry-huff/HuffDeployer.sol";

contract HorseStoreHuff is Base_TestV1{
    string public constant HORSE_STORE_HUFF_LOCATION = "horseStoreV1/HorseStore";
    function setUp() public override {
        // horseStore = // Huff edition
        horseStore = HorseStore(HuffDeployer.config().deploy(HORSE_STORE_HUFF_LOCATION));
    }
}