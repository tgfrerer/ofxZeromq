
# Attention VS 2012 users

Make sure to add the .props files for debug and release to your visual studio property sheets. 

These are located under:

	ofxZeromq\libs\zeromq\lib\vs

The property sheets will make sure that the preprocessor definition ZMQ_STATIC is set, otherwise the linker will not be able to correctly link your app to the static libzmq.lib or libzmqd.lib.

See also: http://stackoverflow.com/questions/10367678/linking-to-a-static-0mq-library-in-vs

## Compilation recipe

This was compiled on the Raspberry PI using the following steps:

	curl http://download.zeromq.org/zeromq-4.0.4.tar.gz -o
	tar xf zeromq-4.0.4.tar.gz
	cd zeromq-4.0.4
	mkdir -p /tmp/build
	./configure --enable-static --prefix=/tmp/build
	make
	make install
	cd /tmp/build/lib/
	ls libzmq.a