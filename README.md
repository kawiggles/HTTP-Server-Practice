# Kawika's HTTP Server
This is my attempt at creating an HTTP Server from scratch using C++. The basis is the Berkley Socket API and the HTTP protocol.

## Overall Architecture
I'm taking advantage of C++'s Object-Oriented programming paradigm to better handle memory and socket management. The primary class in the program is the server. The server is a simple object which contains a unique pointer to a Socket (wrapper class for socket struct and associated functions, as detailed by the Berkley Socket API), the server configuration, and the methods necessary to run the server and handle client connections. The run() method creates new threads with the handleClient() method in order to handle multiple clients simultaneously.

## HTTP Request Parsing
handleClient() first breaks a client request into a vector of strings, where each string is a line of the request. This is passed to a function called parseHeader(), which generates a Request struct from the header. The Request struct is polymorphic, with the existing a derived class for each kind of HTTP request. Parsing the request into a data structure makes it eeasier to generate responses later on.
