#pragma once

// Jack Sense bits as defined by jack sense pin connections to external GPIO expander chip:
//    Lin, bit 6
//    Rin, bit 7
//    CVA, bit 0
//    CVB, bit 1
//    CVC, bit 2
//    CVD, bit 3
//    Gt1, bit 10
//    Gt2, bit 11
//    CkIn, bit 12
//    Lout, bit 8
//    Rout, bit 9
//    CVO1, bit 4
//    CVO2, bit 5
//    CkO, bit 13
//    Pat, bit 14
static inline const unsigned jacksense_pin_order[15] = {6, 7, 0, 1, 2, 3, 10, 11, 12, 8, 9, 4, 5, 13, 14};
