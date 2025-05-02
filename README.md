# Command-Line Interface emulator
### Credits: Professor Allen Malony, CS 415 Operating Systems at the University of Oregon

This application acts as a command-line emulator. The possible commands it accepts are: "ls", "pwd", "mkdir", "cd", "cp", "mv", "rm", "cat", and "exit". There are two different modes of operation:
  - File Mode: Takes in a file of command-line arguments, separated by ";" and newlines, and performs all of the actions in the file, returning any printed output into output.txt.

To Run: /pseudo-shell -f {file name}

  - Interactive Mode: Acts as a command-line and gets user input in the form of command-line arguments. Can be exited with the code word "exit".

 To Run: /pseudo-shell
