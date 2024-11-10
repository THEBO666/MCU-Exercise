  ORG 0000H       

; 初始化片内 RAM 30H-3FH 为 80H-8FH
        MOV R0, #30H    ; R0 指向片内 RAM 起始地址 30H
        MOV A, #80H     ; A 初始化为 80H

INIT_LOOP:
        MOV @R0, A      ; 将 A 的值写入片内 RAM [R0]
        INC R0          ; R0 = R0 + 1
        INC A           ; A = A + 1
        CJNE A, #90H, INIT_LOOP ; 如果 A 不等于 90H，继续循环

; 将片内 RAM 30H-3FH 的内容传送到外部 RAM 1000H-100FH
        MOV R0, #30H    ; R0 重新指向片内 RAM 起始地址 30H
        MOV DPTR, #1000H ; DPTR 指向外部 RAM 起始地址 1000H

TRANSFER_LOOP1:
        MOV A, @R0      ; 从片内 RAM [R0] 读取数据到 A
        MOVX @DPTR, A   ; 将 A 的值写入外部 RAM [DPTR]
        INC R0          ; R0 = R0 + 1
        INC DPTR        ; DPTR = DPTR + 1
        CJNE R0, #40H, TRANSFER_LOOP1 ; 如果 R0 不等于 40H，继续循环

; 将外部 RAM 1000H-100FH 的内容传送到 1040H-104FH
        MOV DPTR, #1000H ; DPTR 指向外部 RAM 源地址 1000H
        MOV R0, #40H     ; R0 保存目的地址低字节（1040H 的低字节）
        MOV R1, #10H     ; R1 保存目的地址高字节（1040H 的高字节）
        MOV R7, #16      ; 循环计数器，传输 16 字节

TRANSFER_LOOP2:
        MOVX A, @DPTR    ; 从源地址 [DPTR] 读取数据到 A
        INC DPTR         ; 源地址递增

        ; 保存当前的 DPTR（源地址）
        MOV R2, DPL      ; R2 = DPL（源地址低字节）
        MOV R3, DPH      ; R3 = DPH（源地址高字节）

        ; 设置 DPTR 为目的地址（1040H 开始）
        MOV DPL, R0      ; DPL = R0（目的地址低字节）
        MOV DPH, R1      ; DPH = R1（目的地址高字节）

        MOVX @DPTR, A    ; 将 A 的值写入目的地址 [DPTR]


        MOV DPL, R2      ; DPL = R2（恢复源地址低字节）
        MOV DPH, R3      ; DPH = R3（恢复源地址高字节）

        INC R0           ; 目的地址低字节加 1
        CJNE R0, #00H, NO_CARRY_DST ; 如果 R0 不为 0，跳过进位
        INC R1          
NO_CARRY_DST:

        DJNZ R7, TRANSFER_LOOP2 

        END
