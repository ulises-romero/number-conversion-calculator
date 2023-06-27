.data
    endl: .asciiz "\n"
    baseOfNum: .asciiz "Enter base of number: "
    convert: .asciiz "Enter new base to convert to: "
    numberPrompt: .asciiz "Enter a number to convert: "
    result: .word 80
    array: .word 80
    output: .space 40 #used to store final num
    numberInput: .space 33
.text
main: 
    #enter num
    li $v0, 4
    la $a0, numberPrompt
    syscall
    #user input number
    li $v0, 8
    la $a0, numberInput
    la $a1, 33
    syscall
    #enter base
    li $v0, 4
    la $a0, baseOfNum
    syscall
    
    li $v0, 5
    syscall
    
    la $a0, numberInput
    move $a1, $v0
    
    #calling baseToDecimal
    jal baseToDecimal
    move $a2, $v1 #load num into a2
    
    #ask for base to convert to
    li $v0, 4
    la $a0, convert
    syscall
    
    #get base in a1
    li $v0, 5
    syscall
    
    move $a1, $v0
    #base = a1, number = a2
    jal decimalToAny
exit:
    li $v0, 10
    syscall

#This function converts the user input into a Int that is also a decimal number so 
#that we can call our decimalToAny function and make the conversion
# the params we take in are char s[], int base
#int base being the base of the number the user entered
baseToDecimal:
    # $a1 = int base
    #storing the ra to the stack so we can use it later
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    
    la $a3, numberInput
    # jal to get the size of the users input
    jal stringSize
    move $s2, $v1
    
    # $s2 = size -1
    addi $s2, $s2, -1 #now it's the last element in numberInput string
    #decimalNumb = 0
    add $s3, $zero, $zero
    #exp = 0
    add $s4, $zero, $zero
    
    loop:
         #checks to see if we are done looping aka the index is -1
         slt $t0, $s2, $zero
         #return if index is -1
         beq $t0, 1, baseToDecReturn 
         #if not we continue
         lb $a2, numberInput($s2) 
         jal valueGet 
         #result from this would be the val of the last bit
         
         #calling pow so we load $a1 = base, $a2 = exponent
         move $a2, $s4
         jal pow 
         #$v0 stores the product we multiply the bit val by
         mulu $t1, $v0, $v1 #multiplication to get bitvalue * the base and exponent
         add $s3, $s3, $t1 # put the result in the decimalNum
         addi $s4, $s4, 1 # move the exponent up 1 for next loop
         #gets next bit
         addi $s2, $s2, -1 
         j loop
         #loop back to run again with new bit
    
    baseToDecReturn:
    	#pop so we can get ra and go back to main func
         lw $ra, 0($sp)
         addi $sp, $sp, 4
         move $v1, $s3
         jr $ra
stringSize: # $a3 = char s[] 
	# 
    addi $t8, $zero, 0 #count = 0
    stringLoop:
         lb $t9, 0($a3)
         beqz $t9, stringReturn
         addi $t8, $t8, 1
         addi $a3, $a3, 1
         j stringLoop
         
    stringReturn: 
         addi $t8, $t8, -1 #size will hit null so we sub 1 
         move $v1, $t8
         jr $ra
         
decimalToAny: # a1 = base, a2 = number
    move $t0, $a2
    li $t2, 0 
    divideLoop:
         # divide number by base
         div $t0, $a1
         mflo $t0
         mfhi $t1
         
         #if bit is from 0-9
         slti $t3, $t1, 10 
         beq $t3, 0, convLetter
         convNum:
            addi $t1, $t1, 48
            j store
         #if bit is over 9
         convLetter:
            addi $t1, $t1, 55
            j store
         store:
            sw $t1, array($t2) #store offset in array
            #add 4 to offset for next bit
            addi $t2, $t2, 4 
         
         #dividing 
         bne $t0, $zero, divideLoop #checks qoutient
         print:
            addi $t2, $t2 -4 
            lw $a0, array($t2) # t2 = size -1 (in offset form)
            li $v0, 11
            syscall
            bgtz $t2, print
            j exit

#only takes in binary and does all conversions
binaryToOther: # a1 = convert to base a3 = number
    addi $t0, $zero, 0 
    addi $t5, $zero, 1000
    
    beq $a1, 8, binaryLoop
    addi $t5, $zero, 10000
    binaryLoop:
        rem $s0, $a3, $t5 
        #store result in array
        sw $s0, result($t0)
        #adding offset
        addi $t0, $t0, 4 
        #update number
        div $a3, $a3, $t5 
        #repeat loop
        bne $a3, $zero, binaryLoop 
    
    biprint: 
        addi $t0, $t0, -4
        lw $t1, result($t0)
        #exp
        addi $t2, $zero, 0
        addi $t3, $zero, 0 # current number
       
        converting:
            rem $s1, $t1, 10 # gets digit
            sllv $s1, $s1, $t2
            add $t3, $t3, $s1
            #increase exp
            addi $t2, $t2, 1 
            #update number
            div $t1, $t1, 10 
            bne $t1, $zero, converting 
        bgt $t3, 9, cLetter
        addi $t3, $t3, 48
        j asciiPrint
        cLetter: 
            addi $t3, $t3, 55
        asciiPrint: 
            li $v0, 11
            move $a0, $t3
            syscall
        bgtz $t0, biprint
    jr $ra
# int valueGet
valueGet:
    #a2 = char s
    addi $sp, $sp, -4
    sw $ra, ($sp)
    # s - 48 = $v1
    subi $v1, $a2, 48
    #check if value is A-F
    # if $v1 < 16 then we subtract by 7
    bgt $v1, 16, letter
    j vReturn
    letter:
        addi $v1, $v1, -7
        j vReturn
    vReturn:
        lw $ra, ($sp)
        addi $sp, $sp, 4
        jr $ra
pow: # $a1 = base, $a2 = exponent
    addi $t4, $zero, 1 #timesAround
    addi $t5, $zero, 0 #for loop
    ploop:
    	# if $t5 = $a2 return
        beq $t5, $a2, leaving 
        #timesAround *= base
        mulu $t4, $t4, $a1 
        addi $t5, $t5, 1 
        j ploop
    leaving:
    	#return
        move $v0, $t4
        jr $ra