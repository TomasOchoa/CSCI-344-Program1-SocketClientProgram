# CSCI 344: Intro To Computer Communications
## Program 1: A Simple Sockets Client Program, Word Definitions and Zip Codes 
### Description:
* Linux socket/client program that returns;
    * Definitions of words based upon the WordNet database 
    * Information about zip codes based upon a zip code database. 
    * NOTE: Databases are located at the web site shown in class called dict.org.

### Commands:
- d or D: 
    - Prompt user for a word, submit to dict.org, and retrieve its definition using the "WordNet" database. 
    - Answer is checked to make sure no errors occured communicating to server
        - If error, display a generic error message
        - If no error, the word and it's definition neatly on screen and in an output file
- z or Z:
    - Prompts user for a five digit zip code and retrieves zip's info from dict.org using the "U.S. Gazetter Zip Code Tabulation Areas (2000) database"
    - Error check
        - If error, display a generic error message
        - If no error, display zip info neatly on screen and write it to an output file
- q or Q:
    - Clean up and quit (Close sockets)

### Notes:
- Need an output file to write output to
- RFC number of dictionary protocol is 2229 and the port is 2628
- Program must compile and execute properly on Linux machine in Fitzelle 252 


