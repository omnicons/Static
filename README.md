# Static
Version 3 of the Static IRC bot hosted for BronyTV written in C++
# Installation
It's as simple as going in the directory and building it as long as you have the build-essential package installed

    cd Static/
    make
# Configuration
This bit is subject to change as how we're handing configuration right now is simple, but more functionality will be added later.

Current options are:

* irc_host (Currently only supports IPv4 hosts)

* irc_port (Currently only supports non ssl ports)

Proposted configuration options that have not been added as of yet:

* irc_nick

* autojoin (For having the bot join channels upon connection)

* nickerv authentication perform on connect (sasl might come later after ssl connctions are implemented)

# Features
The bot is based around plugins and will support functions similar to a network services bot for larger channels that require more functionality and automation.

The functions this bot is being built around are automatic moderation, services extention and link tagging, but will also supplement in maintaining the channel as it will contian the settings to help put the channel in moderated mode, as well as undo that action, as some of our moderators do not quite understand IRC and how it works, and this is simpler.
