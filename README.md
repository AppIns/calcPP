[![AppIns](https://i.imgur.com/xEPu5Ug.png)](https://github.com/appins)
# Calc++

#### Why?
It is exceptionally useful for calculations with tons of variables, (say a grade or a gpa) and is open source

#### How do I use it?

You might have an executable for your system just open that (In linux, open a terminal, cd into the directory, and type ./calcpp)

If not, type `make` in the main directory

Just enter a number and hit enter to add it to the "Stack"

#### Example usage

```
    1) [ Oldest >> Newest ]
    2) :4
    2) [ 4 ]
    3) :1
    3) [ 4 1 ]
    4) :mean
    4) [ 2.5 ]
    5) :7.5
    5) [ 2.5 7.5 ]
    6) :add_
    7) > 10
    6) [ 2.5 7.5 ]

```

1. This is output, it just reminds you that the stuff farther out in the output is newer
2. It always starts with the prompt :, which means your turn to input numbers. We inputed 4 and it added that to the stack
3. We then add in 1 to the stack (it's actually just a vector) by just typing one and hitting enter
4. Now we want the average. You can type commands after the : too. In this case, its an average. It overwrites the vector and just has 2.5 now
5. We add 7.5 to the vector
6. We want to add all the numbers together and not overwrite the vector. We do this by simply putting a _ at the end. It keeps the exact same vector
7. This is the output of the equation we just did. It doesn't change the numbers inside of the vector though. This is displayed in a very similar format to the vector

###### (It's just a vector)

### Math commands
| Command | Shortcut | Function |
|---------|----------|----------|
| `ADD` | `+` | Take the sum of every number |
| `MUL` | `*` | Take the product of every number |
| `MEAN` | `+/` | Take the average of every number |
| `MAX` | `123=3` | Get the largest number |
| `MIN` | `123=1` | Get the smallest number |
| `NTO` | `123=312` | Shift the newest number where the oldest number was (cycles) |
| `OTN` | `123=231` | Shift the oldest number where the newest number was (cycles) |
| `LOOP` | `2-4-6` | Asks for a starting, stopping, and increment value. Inserts every number in the range. |
| `DIV` | `/` | Divide the second to last number by the last number (secondToLast / last) |
| `SUB` | `-` | Subtract the second to last number by the last number (secondToLast - last) |
| `FILL` | `0.0.0.0` | Asks you to pick a value and an amount, adds the value to the end amount times |

### Array modification commands
| Command | Shortcut | Function |
|---------|----------|----------|
| `CLEAR` | `=0` | Clear the entire array |
| `DELETE` | `--1` | Delte the newest element |
| `SWAP` | N/A | Switch between the current vector and the background one (note that _ doesn't work!)|
| `COPY` | N/A | Copies the current vector to the background one (no _ command)|
| `UNDO` | N/A | Undo the last command (note that _ doesn't work!)|
| `EXIT` | N/A | Exit the program (note that _ doesn't work!)|

#### One more thing
All commands will overwrite the vector by default. Add `_` add the end of a command (say `add_`) to disable this
The "Example Usage" includes one of these
