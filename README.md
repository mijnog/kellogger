MIT License

Copyright (c) 2026 Maxime

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

$${\color{red}EDUCATIONAL USE DISCLAIMER:}$$

This software was created strictly for educational purposes to demonstrate
Linux input event handling and low-level C programming concepts. It is intended
to be used only on systems you own or have explicit written permission to
monitor. Unauthorized use of this software to intercept input on systems you
do not own or have permission to access is illegal and unethical. The author
assumes no responsibility for any misuse of this software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

# Kellogger

![Kellog's Original Cornflakes Logo](kellogger.png)

Works on linux. On my Ubuntu keyboard input file is `/dev/input/event7`. This may be different on your system.

Since this keylogger runs as a daemon you won't see errors on stderr. On Ubuntu, you can use `journalctl -t kellogger` to find error messages, or `journalctl -t kellogger -f` to see them appear in real time.

#### Usage

First run `make`, then just run `./kellogger` as root or `./kellogger <path-to-event-file>`.

Key logs are stored in `/tmp/kellogs.txt`

#### Future features 
-> Beaconing to C&C Server.
-> Persistence and Stealth 

