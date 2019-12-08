/** @file userData.h
*	@brief Class for the accounts created for the program.
*/

#ifndef USERDATA_H
#define USERDATA_H
#include <iomanip>
#include <string>

using namespace std;

/**
*	@brief Class userData is the base class for all the user's information.  It will contain all the common information needed for all types of the users, interacting with the application.
*/

class userData
{
private:
    //! string variable to store user's first name-INPUT
    string fName;

    //! string variable to store user's last name-INPUT
    string lName;

     //! string variable to store user's userID-INPUT
    string userID;

     //! string variable to store user's password-INPUT
    string password;

    //! a variable of type int; it will be used to keep count of the total number of users using the application.
    //! userCount will only be used with increment and decrement operations.
    int userCount;

    //! int rank will be used as a method to develop a heirarchy. Such that depending on the
    //! interface you create your account you will be assigned a corresponding rank.
    //! Example: rank = 1; Admin
    //!                 rank = 2; Manager
    //!                 rank = 0; Null (will have no access to any operations)
    int rank;


public:
    //! default constructor of the class, will set all variables to null or 0
    userData();

    //!constructor using special parameters, taking string fName, string lName, string email
    //!string phoneNumber, string userId, string password, and an int rank.
    userData(string first, string last, string user, string pass, int r);

    //!Set the first name of the user
    void setfName (string f);
    //! Set the last name of the user
    void setlName (string l);

    //! Set the userId of the user
    void setUserID (string u);
    //! Set the password of the user
    void setPassword (string pass);
    //! Set the rank of the user
    void setRank (int r);

    //! Gets the first name of the user
    void getfName (string& f) const;
    //! Gets the last name of the user
    void getlName (string& l) const;
    //! Get the userId of the user
    void getUserId (string& u) const;
    //! Get the password of the user
    void getPassword (string& pass) const;
    //! Get the rank of the user
    void getRank (int& r)const;

    //! Function to increment the userCount variable
    void incUserCount();
    //! Function to decrement the userCount variable
    void decUserCount();
};

#endif // USERDATA_H
