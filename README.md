# Custom Project
**Trent Monahan *100574275***

Hi I'm Trent, and I'll be going over this tutorial on Network Programming in Swingame

**NOTE:** I would not reccomend using SwinGame for this. It is a horrible idea and you will spend more time swearing at SwinGame than seeing results.

All files mentioned in this document are available [here](http://github.com/SinZ163/IntroToProgramming_Project)

## Step 1: Setting up your environment
Getting into it, before you can do good code, need to get the development environment setup.

For this project, its actually two seperate programs, thus two environments. The Server program, and the Client program, but they have identical setup, just have to remember that two will exist.

For this, I will be using Visual Studio Code, because having a text editor capable of intellisense is super handy for this, and will be using MinGW GCC / GDB for compiling and debugging (Visual Studio Code supports GDB).

For VSCode, I will be using the official C/C++ Extension from Microsoft which does the language services, and manages GDB debugging.

So, first things first, gotta make a folder for the client and server, I will be referring to these as `Project_Client` and `Project_Server`.

Next step is to setup the environment, Copy the contents of `template/` in this repository into each of these environments.

For the most part I won't go over how these files work, as its a straight forward format, the important things are in `launch.json` line 25 needs to matchup your MinGW setup, as does lines 36,37,43 and 44 in `c_cpp_properties.json`.

Now you got vscode happy, gotta in VSCode, and Open Folder (via File menu or keyboard shortcut) and open `Project_Client`, when thats done, go New Window (via File menu or keyboard shortcut) and in this new window, use the earlier process to open `Project_Server`.

At this point, make a file, such as `src/client.cpp` or `src/server.cpp` depending on the environment, and put some boilerplate code. such as:
```c
#include <stdio.h>

int main() {
    printf("Hello World!");
    char buffer[256];
    gets(buffer);
    return 0;
}
```

If you were to run this (F5), it wont work. Its missing a `bin/` folder, and included in the template is a build.bat and theres also a bonus task in `tasks.json` that executes it.

To execute it, go to the Command Palette (ctrl+shift+P) and type in `tasks: run task`, and then type in `init`.

Now try running this again (F5), should get a command prompt window open up, that says:
```
Pre Init
Post Init
Hello World!
```
And pressing enter will close the prompt.

This is a quick test that the environment works, now we can go onto the next step.

## Step 2: Barebones Server

If we want the client to ever work, we need a working server first.

To do so, we include `SwinGame.h`, which in this setup is `../lib/SwinGame.h`

We want to create a server socket, using the SwinGame function
```c
server_socket create_server_with_protocol(char* name, int port, connection_type protocol)
```

So we will store this server_socket in a vairbale, such as `server` and we can pass this into other swingame functions.

Then, we want to do the following logic for a long time, and since why not, have a `while (true)` loop.

Inside this while loop, we will call:
```c
void check_network_activity()
```
Which is similiar to `process_events()` if you have done SwinGame Graphics and Events before, but is responsible for network IO instead.

Afterwards, we can check if we have received any messages using the function:
```c
bool has_message_on_server(server_socket server)
```
Which returns 1 (true) if there is atleast one message, and returns 0 (false) if there was no messages waiting.

If we have a message, we can get it using the function:
```c
message read_message_from_server(server_socket server)
```
which gets a message pointer which we can access fields using the following functions:
```c
void message_data(message message, char* result)
void message_host(message message, char* result)
short message_port(message message)
connection message_connection(message message)
```
In this program, we will be using _data and _connection, but for now only _data.

`message_data` requires an input char array buffer of 256,
so we define a char[256], and feed it into `message_data()` along with our message object, and that char array now contains the message, which we can print.

All this looks like is:
```c
#include <stdio.h>
#include "../lib/swingame.h"

int main()
{
    server_socket server = create_server_with_protocol("SwinServer", 25565, TCP);

    while(true) {
        check_network_activity();
        if (has_message_on_server(server)) {
            message newMessage = read_message_from_server(server);
            char data[256];
            message_data(newMessage, data);

            printf(data);
        }
        delay(10);
    }
    return 0;
}
```
But without a corresponding client, it won't do much, so lets fix that.

## Step 3, Basic Client.