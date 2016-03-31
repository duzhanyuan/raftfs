//
// Created by yzhh on 3/30/16.
//

#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include <protocol/TMultiplexedProtocol.h>

#include "../protocol/RaftService.h"

#include <iostream>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;                                                                                                                       
using namespace raftfs::protocol;
using namespace std;

int main() {
    /*
    boost::shared_ptr<TSocket> socket(new TSocket("localhost", 12345));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> proto(new TBinaryProtocol(transport));
    */

    boost::shared_ptr<TSocket> sock(new TSocket("localhost", 12345));
    boost::shared_ptr<TBinaryProtocol> proto(new TBinaryProtocol(sock));
    boost::shared_ptr<TMultiplexedProtocol> raft_proto(
            new TMultiplexedProtocol(proto, "Raft")
    );

    RaftServiceClient client(raft_proto);

    try {
        sock->open();

        ReqVoteRequest req;
        ReqVoteResponse resp;

        req.term = 1;
        req.candidate_id = 2;
        req.__set_last_log_term(0);
        req.__set_last_log_index(123);

        client.RequestVote(resp, req);

        cout << "recv term" << resp.term << " granted " << resp.vote_granted << endl;

        sock->close();
    } catch (TException &tx) {
        cout << tx.what() << endl;
    }


    return 0;
}