#include "userdata.h"

userData::userData()
{
    fName = "null";
    lName = "null";
    userID = "null";
    password = "null";
    rank = 0;
}
 userData::userData(string first, string last, string user, string pass, int r)
 {
     fName = first;
     lName = last;
     userID = user;
     password = pass;
     rank = r;
 }
 void userData::setfName(string first)
 {
     fName = first;
 }
 void userData::setlName(string last)
 {
     lName = last;
 }
 void userData::setUserID(string user)
 {
     userID = user;
 }
 void userData::setPassword(string pass)
 {
     password = pass;
 }
 void userData::setRank(int r)
 {
     rank = r;
 }

 void userData::getfName(string& first) const
 {
     first = fName;
 }
 void userData::getlName(string& last) const
 {
     last = lName;
 }
 void userData::getUserId(string& user) const
 {
     user = userID;
 }
 void userData::getPassword(string& pass) const
 {
     pass = password;
 }
 void userData::getRank(int& r) const
 {
     r = rank;
 }
 void userData::incUserCount()
 {
     userCount++;
 }
 void userData::decUserCount()
 {
     userCount--;
 }
