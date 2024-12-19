# First Arduino Lab
## Background/information
You may do this lab in teams of one or two. Doing this lab with a lab partner is recommended. 

If you're working in a team of two, I recommend working together in the STEM Center to build one set of hardware and write on program together to run on that hardware. If you want to work remotely (for example on Zoom or some other platform) you will each build the hardware and write one program together to run on both hardware.

Either way, turn in one lab report with both names (both names on the report and as part of the file names). Only one of you should turn in the report.

You'll need to take pictures to document your lab report

Install Arduino software if you haven't already done so

Read chapters one through four of Getting Started with Arduino
(Introduction, The Arduino Way, The Arduino Platform, Really Getting Started With Arduino)

## Parts
- 1 solderless breadboard
- 1 pushbutton
- 7 LEDs (assorted colors)
- 8 resistors (330 Ohm)
- 15 wires
- 1 USB A/B Cable

## Pre-lab exercises
- Complete the Blinking LED exercise (chapter four)
- Complete the push button LED control exercise (chapter four)

Your report should state that you completed those labs, but don't need to include any additional details unless something interesting happens.

## Lab specifications
Board has 7 colored LEDs in a row

LEDs light up in a pattern comprising of the seven least significant bits of the ascii values in the letters of your first name followed by a "space" (indicated by all lights off.) (followed by the first letters in the name of your lab partner and then another "space" before returning to the first letter of the first name) If you work on this lab by yourself, use your first name and your last name instead.

Your name(s) must be stored as a string in your program. The program logic must be based on this string (i.e. changing the string changes the letters displayed via LED.)

Show one letter (character) at a time, use a button press to advance to the next letter