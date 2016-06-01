/*  Author:     Tomas Ochoa
 *  Date:       3/31/15
 *  Purpose:       This is the main of the client. Main put's everything together for
 *              the client to being working.
 *
 *  Article:    http://tldp.org/LDP/LG/issue74/tougher.html#3.4
 */
#include "clientsocket.h"
#include "socketexception.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <string.h>
#include <cstring>
// Function headers
// Functions to make main look neater
void quit_choice();
void define_choice();
void zip_choice();
void show_menu();
void menu_options();
// Global variable for file input

using namespace std;

int main(void)
{
    // Open the file
    ofstream session;
    session.open("DictClientSession.txt",ios::out|ios::trunc);
    // Menu Options
    menu_options();
    // Close the file
    session.close();

    return 0;
}
// ****************************** FUNCTION IMPLEMENTATIONS ******************************

// Stuff to do if user wants a definiton of a word
void define_choice()
{
    // Output File
    ofstream session;
    session.open("DictClientSession.txt",ios::app);

    // These strings declaration will help get the
    // user's word definition by appending them all
    // to the end into one string and seinding it as a
    // command to the dict server
    std::string send;
    std::string DEFINE = "DEFINE wn ";
    std::string word;
    std::string CRLF = "\r\n";

    // Get the user's word
    session << "Please enter an option: D" << endl;
    cout    << "Enter a word: ";
    session << "Enter a word: ";
    cin     >> word;
    session << word << endl;

    // Setup the command to get the deffinition
    send.append(DEFINE);
    send.append(word);
    send.append(CRLF);
    // Do stuff
    try
    {
        ClientSocket dict("216.18.20.172",2628);

        // Declare a string variable for reply from server
        std::string reply;
        try
        {
            // Send the word to the server
            dict << send;
            // Get back response from server
            dict >> reply >> reply;
        }
        catch(SocketException&){}
            std::cout << endl << "Server response:" << endl << reply << endl << endl;
            session   << endl << "Server response:" << endl << reply << endl << endl;
    }

    catch(SocketException& e)
    {
        std::cout << "Exception was caught: " << e.description() << endl;
        session   << "Exception was caught: " << e.description() << endl;
    }
    // Close the file
    session.close();
    return;
}
// **************************************************************************************
// Stuff to do if user wants to learn more about zips
void zip_choice()
{
    // Output File
    ofstream session;
    session.open("DictClientSession.txt",ios::app);

    // These strings declaration will help get the
    // user's zip by appending them all in the end
    // into one string and seinding it as a
    // command to the dict server
    std::string send;
    std::string DEFINE = "DEFINE gaz2k-zips ";
    std::string zip;
    std::string CRLF = "\r\n";

    // Get the zip code to be looked up
    cout    << "Enter a zip-code: ";
    session << "Please enter an option: Z" << endl;
    session << "Enter a zip-code: ";
    cin     >> zip;
    session << zip << endl;
    // Appends the string
    send.append(DEFINE);
    send.append(zip);
    send.append(CRLF);
    // Try doing stuff
    try
    {
        ClientSocket dict("216.18.20.172",2628);
        //Declare a string variable for reply from server
        std::string reply;
        try
        {
            // Send the zip to the server
            dict << send;
            // Get back response from server
            dict >> reply >> reply;
        }
        catch(SocketException&){}
        std::cout << endl << "Server response:" << endl << reply << endl << endl;
        session   << endl << "Server response:" << endl << reply << endl << endl;
    }

    catch(SocketException& e)
    {
      std::cout << "Exception was caught: " << e.description() << endl;
      session   << "Exception was caught: " << e.description() << endl;
    }
    return;
}
// **************************************************************************************
// Stuff to do if user quits
void quit_choice()
{
    // Output File
    ofstream session;
    session.open("DictClientSession.txt",ios::app);

    std::string QUIT = "QUIT\r\n";
    try
    {
        ClientSocket dict("216.18.20.172",2628);

        // Declare a string variable for reply from server
        std::string reply;

        try
        {
            // Send quit to the server
            dict << QUIT;
            // Get back response from server
            dict >> reply;
        }
        catch(SocketException&){}
        std::cout << endl << "Server response:" << endl << reply << endl << endl;
        // Write to output file
        session   << "Please enter an option : Q "<< endl  << endl
                  << "Server response:" << endl << reply << endl << endl;
    }
    catch(SocketException& e)
    {
        std::cout << "Exception was caught: " << e.description() << endl;
        session   << "Exception was caught: " << e.description() << endl;
    }
    // Close the file
    session.close();
    return;
}
// **************************************************************************************
// Show choices again
void show_menu()
{
    // Output File
    ofstream session;
    session.open("DictClientSession.txt",ios::app);

    session << "******************** DICTIONARY CLIENT ********************" << endl;
    session << "                                                           " << endl;
    session << "OPTIONS:                                                   " << endl;
    session << "                                                           " << endl;
    session << "  1. D (Gets the definition of a word)                     " << endl;
    session << "  2. Z (Gets information about a zipcode)                  " << endl;
    session << "  3. Q (Quits the program)                                 " << endl;
    session << "                                                           " << endl;

    cout << "******************** DICTIONARY CLIENT ********************" << endl;
    cout << "                                                           " << endl;
    cout << "OPTIONS:                                                   " << endl;
    cout << "                                                           " << endl;
    cout << "  1. D (Gets the definition of a word)                     " << endl;
    cout << "  2. Z (Gets information about a zipcode)                  " << endl;
    cout << "  3. Q (Quits the program)                                 " << endl;
    cout << "                                                           " << endl;
    cout << "Please enter an option: ";
    return;
}
// **************************************************************************************
// Function that does the menu options using
// switch statements
void menu_options()
{
    // Declarations of basic
    // variables
    bool quit = true;           // bool flag while user doesnt want to quit loop
    char choice;                // user's choice

    // Do menu and options while the user doesnt want to quit
    do
    {
        // Show menu
        show_menu();
        // Get user's choice
        cin >> choice;
        // Switch statements to do the correct choices
        switch(choice)
        {
            case'd':
            case'D':
                define_choice();
                break;
            case'z':
            case'Z':
                zip_choice();
                break;
            case'q':
            case'Q':
                quit_choice();
                quit = false;
                break;
        }
    }while(quit);

    return;
}
