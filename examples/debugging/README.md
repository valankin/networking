# Debugging with LLDB

Create object file and executable
```
make
```


## Debug

[LLDB documentation](https://lldb.llvm.org/use/map.html)


Run debugger
```sh
lldb ./build/debug
```

Env
```sh
set env DEBUG 1
unset env DEBUG
```

Set breakpoints
```sh
breakpoint set --name main
breakpoint set --name foo
br s -n main
b main

breakpoint list # list breakpoints
```

Run debugger
```sh
run
run 10 # run with an argument
```


Disassemble
```sh
# Disassemble the current function for the current frame
disassemble --frame
di -f

# Disassemble any functions named main
disassemble --name main 
di -n main

# Disassemble an address range
disassemble --start-address 0x1eb8 --end-address 0x1ec3
di -s 0x1eb8 -e 0x1ec3

# Disassemble 20 instructions from a given address
disassemble --start-address 0x1eb8 --count 20
di -s 0x1eb8 -c 20

# Disassemble the current function for the current frame and show the opcode bytes
disassemble --frame --bytes
di -f -b
```


Inspect state
```sh

# bt, thread, frame, print 
# Backtrace
bt # stack backtraces for all threads
thread select thread_num # select frame
thread until 12 # rfun until we hit line 12 or control leaves the current function
frame select frame_num # select frame

# process attach --pid 123 # attach to the process with process ID 123
# process attach --name a.out # attach to the process named a.out
# attach -waitfor a.out # wait for a process named a.out to launch and attach
# gdb-remote eorgadd:8000 # servername = eorgadd
# gdb-remote 8000 # localhost


# View Local Variables
frame # display help 
frame variable # show variables for the current stack frame
frame info # current stack frame in the current thread

# Print Variables
settings show target.run-args

print argc
print argv[0]
print argv[1]

print a
print x
print y

```

Navigation
```sh
# next, continue
next # Step over to the next line
continue # Continue running the program until the next breakpoint
```



Executable and Shared Library Query Commands
```sh
image list # list the main executable and all dependent shared libraries

image lookup --address 0x1ec4
im loo -a 0x1ec4


# Look up functions matching a regular expression in a binary
#This one finds debug symbols:
image lookup -r -n <FUNC_REGEX>

#This one finds non-debug symbols:
image lookup -r -s <FUNC_REGEX>


# Find full source line information
image lookup -v --address 0x0000000100000000


# Look up information for an address in a.out only
image lookup --address 0x1ec4 a.out
im loo -a 0x1ec4 a.out


# Look up information for for a type Point by name
image lookup --type Point
im loo -t Point
```
