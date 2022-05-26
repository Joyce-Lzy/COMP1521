# Recursive factorial function
# n < 1 yields n! = 1
# $s0 is used for n
# we use an s register because the convention is their value
# is preserved across function calls
# f is in $t0

# DO NOT CHANGE THE CODE IN MAIN

main:
    addi $sp, $sp, -8  # create stack frame
    sw   $ra, 4($sp)   # save return address
    sw   $s0, 0($sp)   # save $s0

    li   $s0, 0        # int n = 0;
    la   $a0, msg1
    li   $v0, 4
    syscall            # printf(Enter n: ")

    li    $v0, 5
    syscall            # scanf("%d", &n)
    move  $s0, $v0

    move  $a0, $s0     # factorial(n)
    jal   factorial    #
    move  $t0, $v0     #

    move  $a0, $s0
    li    $v0, 1
    syscall            # printf ("%d", n)

    la    $a0, msg2
    li    $v0, 4
    syscall            # printf("! = ")

    move  $a0, $t0
    li    $v0, 1
    syscall            # printf ("%d", f)

    li   $a0, '\n'     # printf("%c", '\n');
    li   $v0, 11
    syscall

                       # clean up stack frame
    lw   $s0, 0($sp)   # restore $s0
    lw   $ra, 4($sp)   # restore $ra
    addi $sp, $sp, 8   # restore sp

    li  $v0, 0         # return 0
    jr  $ra

########################################################################
# .TEXT <factorial>
	.text
factorial:
	# Args:
	#   - $a0: int n
	# Returns:  int result
	#
	# Frame:    None
	# Uses:     $a0, $a1, $a2, $t0
	# Clobbers: $t0
	#
	# Locals:   None
	#
	# Structure:
	#   factorial

	# Code:
set__prologue:
	# set up stack frame
	addiu	$sp, $sp, -12
	sw	$ra, 8($sp)
	sw	$s0, 4($sp)
	sw	$s1,  ($sp)
body:
    move    $s0, $a0
	bgt $s0, 1, goif
    li $v0, 1     # result = 1;
    jr  end
goif:
    addiu $a0, $s0, -1 # n-1
    jal   factorial    # factorial(n - 1);
    move  $s1, $v0     #
    mul $v0, $s0, $s1  # result = n * factorial(n - 1);
end: 
    # tear down stack frame
	lw	$s1,  ($sp)
	lw	$s0, 4($sp)
	lw	$ra, 8($sp)
	addiu 	$sp, $sp, 12

    jr	$ra			# return;


    .data
msg1:   .asciiz "Enter n: "
msg2:   .asciiz "! = "

