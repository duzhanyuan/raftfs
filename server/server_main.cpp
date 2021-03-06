//
// Created by yzhh on 3/29/16.
//

#include <iostream>
#include <thread>
#include <boost/program_options.hpp>
#include "RaftMetaServer.h"
#include "../utils/Options.h"

using namespace std;
using namespace raftfs::server;
using namespace raftfs;

int main(int argc, char** argv) {

    Options opt(argc, argv);

    cout << opt.GetSelfName() << endl;

    opt.GetHosts();
    RaftMetaServer server(opt);
    server.Run();
    cout << "Hello, World!" << endl;

    return 0;
}