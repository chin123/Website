; SegDesc B1, Base[0..31], Limit[0..19], Type1[0..7], Type2[4..7], limit
SegDesc MACRO
        dw (#3 AND 0FFFF)
        dw (#2 AND 0FFFF)
        db #1 AND 0FFh
        db #4
        db #5 OR #6                     ;
        db #1 SHR 8
#EM

