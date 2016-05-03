
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

/**
 * @brief An Abstract Exception class, defining basic structure of all exception classes
 */
class Exception {
public:
	/**
	 * @brief Exception message getter
	 */
	string getMsg()const;
protected:
	string msg; ///< Exception message
};
/**
 * @brief File Path Exception
 * @details Indicates when path to the file is noth correct
 */
class WrongFilePathException : public Exception {
public:
	/**
	 * @brief Constructor
	 * @param path Wrong path
	 */
	WrongFilePathException(string path);
};

/**
 * @brief Insertion Exception
 * @details Indicates when insertion of an element was not successfull
 */
class WrongInsertionException : public Exception {
public:
	/**
	 * @brief Constructor
	 * 
	 * @param problem Reason of unsuccessfull insertion
	 */
	 WrongInsertionException(string problem);
};

/**
 * @brief Filter Exception
 * @details Indicates when filtering was not succsessfull
 */
class WrongFilterException : public Exception{
public:
	/**
	 * @brief Constructor
	 */
	WrongFilterException();
};

/**
 * @brief Edit Exception
 * @details Indicates when editation of an element was not succsessfull
 */
class WrongEditException : public Exception{
public:
	/**
	 * @brief Constructor
	 * 
	 * @param problem Reason of unsuccessfull editation
	 */
	WrongEditException(string problem);
};

/**
 * @brief Xml validity Exception
 * @details Indicates when loaded xml file is not valid
 */
class WrongXmlException : public Exception {
public:
	/**
	 * @brief Constructor
	 */
	WrongXmlException();
};

/**
 * @brief Deletion Exception
 * @details Indicates when deletion is not possible (In case of root element)
 */
class WrongDeletionException : public Exception {
public:
	/**
	 * @brief Constructor
	 */
	WrongDeletionException();
};




#endif //EXCEPTION_H
