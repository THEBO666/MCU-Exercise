;------------------------------------------------------------------------------
; 程序说明：
; 1. 将内部RAM 30H - 3FH的 16 个无符号整数按照从小到大进行排序（冒泡排序为例）。
; 2. 排序完成后，最大值位于 3FH，最小值位于 30H。
; 3. 将最大值存入外部 RAM 1000H 中。
; 4. 计算最大值与最小值的差，存入外部 RAM 1001H 中。
; 5. 程序仅示例基本逻辑，可以根据实际需求进行优化和修改。
;------------------------------------------------------------------------------

            ORG  0000H

START:      
            ;--------------------
            ; 冒泡排序部分
            ;--------------------
            ; 外层循环计数，需进行16-1=15次冒泡
            MOV   R0, #0FH       ; R0 = 15，外层循环计数

OUTER_LOOP: 
            MOV   R1, #0FH       ; R1 = 内层循环次数 = 15
            MOV   R2, #30H       ; R2用于指向RAM中当前比较的起始地址

INNER_LOOP:
            ; 比较 [R2] 和 [R2+1]
            MOV   A, @R2         ; A <- [R2]
            MOV   B, A           ; B <- A (保存当前值备比较)
            INC   R2             ; R2指向下一个单元
            MOV   A, @R2         ; A <- [R2]
            CJNE  A, B, COMPARE  ; 如果 A != B，跳到 COMPARE，否则继续
            
            ; 如果相等则无需交换，直接进行下一次比较
            DEC   R1
            DJNZ  R1, NEXT_CMP
            ; 如果内层循环结束则跳到下一轮外层循环
            SJMP  END_INNER

COMPARE:    
            ; 判断B是否大于A，如果B > A则交换
            ; 这里 A = 值2, B = 值1
            CJNE  B, A, SWAP_CHECK
            SJMP  NEXT_CMP

SWAP_CHECK:
            JC    NO_SWAP        ; 如果B < A，则不需要交换 (注意CJNE+JC的流程)
            ; B > A 情况下需要交换
            ; 由于现在R2指向了第二个数的位置，所以需要先回退R2来写入比较之前的地址
            DEC   R2
            MOV   @R2, A         ; @R2 <- 值2(较小值)
            INC   R2
            MOV   @R2, B         ; @R2 <- 值1(较大值)

NO_SWAP:    
NEXT_CMP:
            ; 进入下一次内层比较
            ; 需要将R2回退一次，这样下次循环时，起始地址又是下一对进行比较
            DEC   R2      
            INC   R2      
            DEC   R1
            DJNZ  R1, INNER_LOOP
END_INNER:
        DJNZ  R0, OUTER_LOOP

            ;--------------------
            ; 查找最大、最小值并存入外部RAM
            ;--------------------
            ; 冒泡排序完成后：
            ;  - 最小值位于30H
            ;  - 最大值位于3FH

            ; 1) 最大值存入外部RAM 1000H
            MOV   DPTR, #1000H   ; DPTR 指向外部RAM 1000H
            MOV   A, 0x3F        ; A <- 内部RAM地址 3FH 对应的存储单元的内容
            MOVX  @DPTR, A       ; 将最大值存入外部RAM 1000H

            ; 2) 计算最大值与最小值的差存入外部RAM 1001H
            MOV   A, 0x3F        ; A <- 最大值
            MOV   B, 0x30        ; B <- 最小值
            CLR   C              ; 清除进位，准备做无符号减法
            SUBB  A, B           ; A = A - B
            INC   DPTR           ; DPTR = 1001H
            MOVX  @DPTR, A       ; 差值存入外部RAM 1001H

            SJMP  $

            END