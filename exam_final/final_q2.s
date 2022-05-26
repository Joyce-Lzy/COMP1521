# COMP1521 21T2 ... final exam, question 2

	.data
even_parity_str:	.asciiz "the parity is even\n"
odd_parity_str:		.asciiz "the parity is odd\n"

	.text
main:
	li	$v0, 5
	syscall
	move	$t0, $v0
	# input is in $t0 scanf ("%d", &n)

	# TODO
	li	$t1, 0		# int bit_idx = 0;
	li 	$t2, 0		# int n_bits_set = 0;

loop:
	beq	$t1, 32, end	# while (bit_idx != 32) 
	srlv	$t3, $t0, $t1	# n >> bit_idx
	andi 	$t5, $t3, 1		# int bit = (n >> bit_idx) & 1;
	add	$t2, $t2, $t5		# n_bits_set = n_bits_set + bit;
	addi	$t1, $t1, 1 # bit_idx++;
	j	loop
end:
	li	$t4, 2
	rem	$t3, $t2, $t4
	beq	$t3, 0, even	# (n_bits_set % 2 != 0) 

	li	$v0, 4
	la	$a0, odd_parity_str
	syscall

	li	$v0, 0
	jr	$ra

even:
	li	$v0, 4
	la	$a0, even_parity_str
	syscall

	li	$v0, 0
	jr	$ra
	
