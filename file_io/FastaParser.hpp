/*
 * FastaParser.h
 *
 *  Created on: Jan 9, 2013
 *      Author: stef
 */

#ifndef FASTAPARSER_H_
#define FASTAPARSER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <cstring>
#include <sstream>

using namespace std;

class FastaParser {
protected:
    string filename;	///< string containing name of file
    ifstream fin;	///< file input stream
    string currIDLine;	///< keeps entire ID line

public:
    FastaParser() {}
    /**
     * @param fastaFilePath A string denoting the path of the FASTA file
     */
    FastaParser(string fastaFilePath);
    virtual ~FastaParser() {}

string getID();

    string getCurrIDLine() { return currIDLine; }	///< get method
    /**
     * opens the specified file
     * @return A boolean if the file was opened properly or not
     */
    bool openFile();
    bool closeFile();			///< closes the file stream
    /*
     * @return A string of the next sequence in the FASTA file
     */
    string getNextSequence();
    bool hasNextSequence();		///< tests if there is another sequence
    /**
     * returns the next entry ID and sequence as a pair
     * @return A pair of strings representing the ID and sequence of 
     * the next entry of the FASTA file
     */
    virtual pair<string,string> getNextEntry();
};



#endif /* FASTAPARSER_H_ */
