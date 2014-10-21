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

#ifndef guard_pal_ofxzeromq_h
#define guard_pal_ofxzeromq_h

#include "ofMain.h"
#include <zeromq/zmq.hpp>

namespace pal {

	typedef shared_ptr<zmq::context_t> zmqContextP;
	typedef shared_ptr<zmq::socket_t> zmqSocketP;

	// ----------------------------------------------------------------------
	zmqContextP zmqMakeContext(int io_threads_);

	// ----------------------------------------------------------------------

	/// creates a zmq socket shared_ptr with a custom deleter, 
	/// the deleter will make sure to close the socket when 
	/// deleting the socket.
	zmqSocketP zmqMakeSocket(zmq::context_t &context_, int type_);

	// ----------------------------------------------------------------------
	/// creates a zmq socket shared_ptr with a custom deleter, 
	/// the deleter will make sure to close the socket when 
	/// deleting the socket.
	zmqSocketP zmqMakeSocket(shared_ptr<zmq::context_t> context_, int type_);

	// ----------------------------------------------------------------------

	/// poll socket for new message
	/// return false if no new messge within timeoutMillis_
	bool zmqPollMessage(zmqSocketP sock_, size_t timeoutMillis_);

}
#endif