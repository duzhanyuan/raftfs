/*
 * VirtualFS.h
 *  Created on: Apr 22, 2016
 *      Author: huang630
 */

#ifndef VIRTUAL_FS_H_
#define VIRTUAL_FS_H_

#include "../protocol/RaftService.h"
#include <memory>
#include <vector>
#include <deque>
#include <mutex>
#include <string>

#include "VirtualInode.h"


namespace raftfs {
    namespace  server {		// FIXME: Temporary put this under server...
        class VirtualFS {

        public:

            VirtualFS();
            ~VirtualFS();

            bool MakeDir(char * path);
            bool MakeFile(char * path);
            bool ExistDir(char * path);
            bool ExistFile(char * path);
            bool Remove(char * path);
            const char * GetCurDir() const;
            bool Chdir(char * path);
            bool Move(char * old_path, char * new_path);
            VirtualInode * GetDir(char * path);
            VirtualInode * GetFile(char * path);



			// Print a Log for debugging purposes.
			friend std::ostream& operator<<(std::ostream& os, const VirtualFS& log);

			// Log is not copyable for safety.
			VirtualFS(const VirtualFS&) = delete;
			VirtualFS& operator=(const VirtualFS&) = delete;

        private:
			// Data structures to entry storage
            mutable std::mutex m;

            VirtualInode root;
            VirtualInode * curdir;
            std::string curdir_str;
        };
    }
}


#endif /* RAFTLOG_H_ */