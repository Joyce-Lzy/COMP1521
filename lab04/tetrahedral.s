# Read a number n and print the first n tetrahedral numbers
# https://en.wikipedia.org/wiki/Tetrahedral_number

main:                  # int main(void) {

    la   $a0, prompt   # printf("Enter how many: ");
    li   $v0, 4
    syscall

    li   $v0, 5         # scanf("%d", number);
    syscall

    move $t1, $v0     # t1 = v0 (how_many)
    li   $t0, 1      # n = 1;

loop1:                 # loop1:
    bgt  $t0, $t1, end  # if (n > how_many) goto end;
    li   $t2, 0         # total = 0
    li   $t3, 1         # j = 1

    ble  $t3, $t0, loop2  # j <= n goto loop2

    addi $t0, $t0, 1  #   n++;
    j    loop1         # goto loop1;


loop3:
    bgt  $t4, $t3, jj  # if (i > j) goto jj;
    add $t2, $t2, $t4
    addi $t4, $t4, 1  #   i++;
    j    loop3         # goto loop3;

jj:  
    addi $t3, $t3, 1  #   j++;
    j    loop2         # goto loop2;

loop2:
    bgt  $t3, $t0, print  # if (j > n) goto print; 
    
    li   $t4, 1   # i = 1 
    ble  $t4, $t3, loop3  # if i <= j goto loop3
    
    addi $t3, $t3, 1  #   j++;
    j    loop2         # goto loop2;

print:
    move $a0, $t2     #   printf("%d" total);
    li   $v0, 1
    syscall

    li   $a0, '\n'    # printf("%c", '\n');
    li   $v0, 11
    syscall
    
    addi $t0, $t0, 1  #   n++;
    j    loop1         # goto loop1;

end:
    li   $v0, 0       # return 0
    jr   $ra

    .data
prompt:
    .asciiz "Enter how many: "
