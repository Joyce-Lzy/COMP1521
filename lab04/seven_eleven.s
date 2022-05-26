# Read a number and print positive multiples of 7 or 11 < n

main:                  # int main(void) {

    la   $a0, prompt   # printf("Enter a number: ");
    li   $v0, 4
    syscall

    li   $v0, 5         # scanf("%d", number);
    syscall

    move $t1, $v0     # t1 = v0 (number)
    li   $t0, 1      # i = 1;

loop:                 # loop:
    bge  $t0, $t1, end  # if (i > number) goto end;
    
    li   $t3, 7         # let t3 = 7
    rem  $t2, $t0, $t3     # i % 7
    beq  $t2, 0, print   # if (i % 7 == 0) goto print

    li   $t3, 11         # let t3 = 11
    rem  $t2, $t0, 11    # i % 11
    beq  $t2, 0, print   # if (i % 11 == 0) goto print

    addi $t0, $t0, 1  #   i++;
    j    loop         # goto loop;

print:
    move $a0, $t0     #   printf("%d" i);
    li   $v0, 1
    syscall

    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall

    addi $t0, $t0, 1  #   i++;
    j    loop         # goto loop; 

end:
    li   $v0, 0       # return 0
    jr   $ra

    .data
prompt:
    .asciiz "Enter a number: "
