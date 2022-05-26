# COMP1521 20T3 final exam Q4 starter code

# This code reads 1 integer and prints it

# Change it to read integers until low is greater or equal to high,
# then print their difference

main:
    li  $t0, 0          # low
    li  $t1, 100          # high 
    
loop:
    bge $t0, $t1, endloop

    li   $v0, 5        #   scanf("%d", &x);
    syscall

    add $t0, $t0, $v0   # low = low + x
    sub $t1, $t1, $v0   # high = high - x;
    j   loop
endloop:
    sub $a0, $t0, $t1
    li   $v0, 1
    syscall

    li   $a0, '\n'     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0        #   return 0
    jr   $ra
