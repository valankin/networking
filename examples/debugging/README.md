# Debugging with LLDB

Create object file and executable
```
make
```


## Debug

Run debugger
```sh
lldb ./build/debug
```

Set breakpoints
```sh
breakpoint set --name main
breakpoint set --name foo
breakpoint list # list breakpoints
```

Run debugger
```sh
run
run 10 # run with an argument
```

Inspect state
```sh

# bt, thread, frame, print 
# Backtrace
bt # stack backtraces for all threads
thread select thread_num # select frame
frame select frame_num # select frame

# View Local Variables
frame # display help 
frame variable # show variables for the current stack frame
frame info # current stack frame in the current thread

# Print Variables
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

