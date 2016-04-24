/*
 * VirtualInode.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: huang630
 */

#include "VirtualFS.h"
#include <iostream>
#include <mutex>
#include <algorithm>
#include <cstddef>
#include <sstream>

using namespace std;

namespace raftfs {
    namespace server {    // FIXME: put this under server first

    /******************************************************************
     *
     * Currently expect this is used one instance per server.
     * So we use the single lock for convenience and safety.
     *
     *******************************************************************/

    VirtualFS::VirtualFS() :
		root("/", VINODE_DIR)	{


    }

    VirtualFS::~VirtualFS() {
    	// TODO: delete everything one by one.
    }

    bool VirtualFS::Chdir(char * path) {
    	std::lock_guard<std::mutex> guard(m);
        VirtualInode * dir;
    	if(path[0] == '/') {	// trace from root
    		dir = &root;
    		if(path[1] == '\0') {	// "cd /"
    			this->curdir = &root;
    			return true;
    		}
    	} else {
    		dir = this->curdir;
    	}
    	//
        istringstream f(path);
        string next_lvl;
        bool error = false;
        while (getline(f, next_lvl, '/')) {
        	if(next_lvl.compare("") == 0)
        		continue;	// to prevent double layer "//"

        	cout << "Next level: " << next_lvl << endl;
        	VirtualInode * nextdir = dir->ExistChildDir(next_lvl.c_str());
        	if(nextdir != nullptr) {
        		dir = nextdir;
        	}else{
        		error = true;
        		break;
        	}
        }
        if(error)	return false;
        this->curdir = dir;
        return true;
    }

#if(1)
    bool VirtualFS::MakeDir(char * path) {
    	std::lock_guard<std::mutex> guard(m);
        VirtualInode * dir;
    	if(path[0] == '/') {	// trace from root
    		dir = &root;
    	} else {
    		dir = this->curdir;
    	}
    	//
        istringstream f(path);
        string next_lvl;
        //
        while (getline(f, next_lvl, '/')) {
        	if(next_lvl.compare("") == 0)
        		continue;	// to prevent double layer "//"

        	VirtualInode * nextdir = dir->ExistChildDir(next_lvl.c_str());
        	//
        	if(f.eof())	{
        		//-- Reach final level -> Create if not exist
            	if(nextdir == nullptr) {
            		dir->CreateDir(next_lvl.c_str());
            		return true;
            	}else{
            		return false;
            	}
        	} else {
        		//-- Advance to next level
        		cout << "Next level: " << next_lvl << endl;
            	if(nextdir != nullptr) {
            		dir = nextdir;
            	}else{
            		return false;
            	}
        	}
        }
        return false;
    }
#endif

    const char * VirtualFS::GetCurDir() const	{
    	// FIXME
    	if(curdir == &root) {
    		return root.GetName();
    	}else{
    		return this->curdir->GetName();
    	}
    }
    std::ostream& operator<<(std::ostream& os, const VirtualFS& fs) {
            	os << fs.GetCurDir();
    }

#if(0)
    VirtualFS::
    bool MakeDir(char * path);
    bool MakeFile(char * path);
    bool ExistDir(char * path);
    bool ExistFile(char * path);
    bool Remove(char * path);
    const char * GetCurDir() const;

    bool Move(char * old_path, char * new_path);
#endif




    } // namespace raftfs::server
} // namespace raftfs
