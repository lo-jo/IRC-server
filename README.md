# IRC Server
Fully functional IRC (Internel Relay Chat) server in C++ capable of handling multiple clients simultaneously.

This project was done in collaboration with @Sacha & @Alan.

## Features

- **Multi-client Handling:** The server supports concurrent connections, efficiently managing multiple clients without performance degradation or hangs.

- **Standard IRC Operations:** Implemented core IRC functionalities, such as user authentication, nickname and username management, joining channels, and sending/receiving private messages.

- **Channel Communication:** Ensures that messages sent by a client to a channel are correctly broadcasted to all other members of that channel.

- **User Roles and Privileges:** Distinguishes between regular users and channel operators, providing enhanced control to operators over channel management.


# Implemented Commands

The server includes the implementation of various IRC commands to manage server-client interactions, user authentication, and channel operations:

- **`NICK`**: Manages the setting and updating of user nicknames.
- **`USER`**: Processes the USER command to register a new user on the server, including setting usernames.
- **`WHOIS`**: Provides detailed information about a user when queried.
- **`PASS`**: Handles the setting of a password for server authentication, allowing secure access.
- **`PING`**: Implements the PING command to check connectivity and keep the connection alive between client and server.
- **`QUIT`**: Manages the QUIT command, allowing clients to disconnect gracefully from the server.
- **`JOIN`**: Allows users to join channels on the server.
- **`PRIVMSG`**: Facilitates private messaging between clients or to channels.
- **`KICK`**: Permits operators to remove users from a channel.
- **`TOPIC`**: Lets channel operators set or view the current topic of a channel.
- **`MODE`**: Adjusts channel settings, such as access restrictions and operator privileges.
- **`INVITE`**: Allows operators to invite users to channels.
- **`PART`**: Enables users to leave channels they are currently in.
- Channel modes ```+``` ```-```
    - **`i`:** Set or remove the invite-only restriction on channels.
    - **`t`:** Restrict the ability to change the topic to channel operators only.
    - **`k`:** Set or remove a channel key (password) for restricted access.
    - **`o`:** Grant or revoke channel operator privileges to users.
    - **`l`:** Set or remove the limit on the number of users in a channel.


## Installation

```
make
```

## Usage
```
./ircserv {port_nb} {name_of_host} {password}
```
Test with:
```
irssi
/CONNECT {name_of_host} {port_nb} {password}
```

## Resources
https://modern.ircdocs.horse/