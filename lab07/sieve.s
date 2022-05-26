# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
main:
    li $t0, 0       # int i = 0;
loop0:
    bge $t0, 1000, end0     # while (i < 1000) { 
    
    mul  $t1, $t0, 4    #  calculate &prime[i]
    la   $t2, prime   
    add  $t3, $t1, $t2  #
    li  $t5, 1
    sw   $t5, ($t3)     #  prime[i] = 1; 

    addiu	$t0, $t0, 1     # i++; 
    jr  loop0           # }  

end0:
    li $t0, 2       # int i = 2;

loop1:
    bge $t0, 1000, end1     # while (i < 1000) { 
    
    mul  $t1, $t0, 4    #  calculate &prime[i]
    la   $t2, prime   
    add  $t3, $t1, $t2  #
    lw   $t5, ($t3)     #  $t5 = prime[i]; 
    beq $t5, 1, goif    # if (prime[i] == true) 

    addiu	$t0, $t0, 1     # i++; 
    jr  loop1           # }

goif:
    move $a0, $t0          # printf("%d", i)
    li $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
    
    mul $t4, $t0, 2     # int j = 2 * i;

loop2:
    bge $t4, 1000, end2     #  while (j < 1000) {
    
    mul  $t1, $t4, 4    #  calculate &prime[j]
    la   $t2, prime   
    add  $t3, $t1, $t2  #
    li  $t5, 0
    sw   $t5, ($t3)     #  prime[j] = 0;
    
    add	$t4, $t4, $t0     # j = j+i; 
    jr  loop2       # }

end2:
    addiu	$t0, $t0, 1     # i++; 
    jr  loop1           # }

end1:
    li $v0, 0           # return 0
    jr $31

.data
prime:
    .space 1000