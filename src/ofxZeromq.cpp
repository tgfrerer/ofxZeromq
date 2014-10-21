//
//     _____    ___     
//    /    /   /  /     ofxZeromq - some utility wrappers around 0MQ
//   /  __/ * /  /__    (c) ponies & light, 2014. All rights reserved.
//  /__/     /_____/    poniesandlight.co.uk
//
//  ofxZeromq.cpp
//  Created by tim on 04/03/2014.
//  
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "ofxZeromq.h"

namespace pal {

	// ----------------------------------------------------------------------
	/// explicit deleter for context
	void deleteContext(zmq::context_t* ctx) {
		ofLogNotice() << "!!  ZMQ CLS context";
		ctx->close();
		ofLogNotice() << "!!  ZMQ DEL context";
		delete ctx;
	}
	
	/// explicit deleter for socket
	void deleteSocket(zmq::socket_t* sck){
			// we make sure to close the socket before deleting it.
			ofLogNotice() << "!!  ZMQ CLS socket";
			sck->close();
			ofLogNotice() << "!!  ZMQ DEL socket";
			delete sck;
	}
	
	// ----------------------------------------------------------------------
	zmqContextP zmqMakeContext(int io_threads_){
		return zmqContextP(new zmq::context_t(io_threads_), deleteContext);
	};

	// ----------------------------------------------------------------------

	/// creates a zmq socket shared_ptr with a custom deleter, 
	/// the deleter will make sure to close the socket when 
	/// deleting the socket.
	zmqSocketP zmqMakeSocket(zmq::context_t &context_, int type_){

		auto pt = zmqSocketP(new zmq::socket_t(context_, type_), deleteSocket);
		static int lingerMillis = 0; // don't linger
		pt->setsockopt(ZMQ_LINGER, &lingerMillis, sizeof(lingerMillis));	
		return pt;
	};

	// ----------------------------------------------------------------------
	/// creates a zmq socket shared_ptr with a custom deleter, 
	/// the deleter will make sure to close the socket when 
	/// deleting the socket.
	zmqSocketP zmqMakeSocket(shared_ptr<zmq::context_t> context_, int type_){

		auto pt = zmqSocketP(new zmq::socket_t(*context_, type_), deleteSocket);
		static int lingerMillis = 0; // don't linger
		pt->setsockopt(ZMQ_LINGER, &lingerMillis, sizeof(lingerMillis));	
		return pt;
	};

	// ----------------------------------------------------------------------

	/// poll socket for new message
	/// return false if no new messge within timeoutMillis_
	bool zmqPollMessage(zmqSocketP sock_, size_t timeoutMillis_){
		zmq::message_t rMsg;
		ofLogVerbose() << "~~ : waiting for REQ ... ";

		int REQUEST_TIMEOUT = timeoutMillis_;
		zmq::pollitem_t pollService[] = { { *sock_, 0, ZMQ_POLLIN, 0 } };
		zmq::poll (&pollService[0], 1, REQUEST_TIMEOUT);
		if (!(pollService[0].revents & ZMQ_POLLIN)) {
			// request timed out
			return false;
		} else {
			// message waiting!
			return true;
		}
	}

};
