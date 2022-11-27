INSTRUCTIONS
In order to run the program, compile the main.c file using the following command:
gcc main.c -o A3 -lpthread

To execute the program, enter either of the following arguments:
./A3 -nodelay <vocalist int> <composer int> <room int> (example ./A3 -nodelay 4 4 3)

or

./A3 -randomdelay <vocalist int> <composer int> <room int> <MaxWanderTime int> <MaxSoundRoomUsageTime int> (example ./A3 -randomdelay 4 4 3 2 5)

If the -nodelay option is used, there will be no delays between the selection of pairs and rooms, whereas if a -randomdelay is selected the order
will slow down and occur less chaotically.

Make sure to include the -lpthread in compilation or the fill will not work. Please also ignore the errors it throws on compilation, the program
still functions as intended!

Issues: The program throws warnings regarding the functions created. The program will also hang when the number of composers are not equal to
the number of vocalists. It also will not clean up the memory for the pair list.