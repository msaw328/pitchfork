# pitchfork
Custom DSL parser for nonexistent load balancer


# Language Specification
Example config files can be found in "assets" directory.

Config file consists of an "entry" block, which can be of type ip or unix.
Inside brackets, entry has to have an "addr" directive, which specifies an address, which depending on type of entry may be:
1. An ip:port pair separated by a colon
2. A unix path to a socket file

Entry also requires a "method" directive specifying a method used to balance traffic among streams (right now two viable options are "random" or "order"),
as well as a series of "stream" blocks, each of type ip or unix, which represent sinks between which data flow should be balanced. Streams also have an "addr" directive.

Inside entry brackets, an "include" directive may be used, which pastes contents of a file in its place (path to file is relative to the directory current file is in)
