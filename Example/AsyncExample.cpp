#include "PnmsSecureClient.h"
#include "PnmsDynamicClient.h"
#include "Receiver.h"
#include "Message.h"
#include "Parameter.h"

#include <iostream>


using namespace std;

/******************************************************************************
 *                                                                            *
 * Example file for the Asynchronous messaging feature of the PICI/NMS package*
 *                                                                            *
 * (c) 2006 fritzone. All rights reserved, and this file can be used in any   *
 * manners you consider helpful for yourself or others, but if it screws your *
 * computer (or other people's computer) it's entirely your responsability.   *
 * I'm not responsible entirely for it, you're on your own, pal, 'cause       *
 * I don't wanna break the written and unwritten rules of the Free Softwares. *
 *                                                                            *
 ******************************************************************************/

/**
 * This will be the class that will receive the sent messages.
 */
class MyReceiver: public Receiver
{
public:

	MyReceiver() {}

	/**
	 *  This method must be overridden so that the system will work as supposed to
	 * the Reply could be a new Message too, but now we just send nothing back
	 */	
	void receive(const Message& msg)
	{
		try
		{
			cout<<endl<< "TESTINT:" <<(  int)msg["TESTINT"];
			cout<<endl<< "TESTLONG:" <<(long)msg["TESTLONG"];
			cout<<endl<< "TESTBOOL:" <<(bool)msg["TESTBOOL"];
			cout<<endl<< "TESTCHAR:"<<(char)msg["TESTCHAR"];
			cout<<endl<< "TESTFLOAT:"<<(float)msg["TESTFLOAT"];
			cout<<endl<< "TESTDOUBLE:"<<(double)msg["TESTDOUBLE"];
			cout<<endl<< "TESTSTRING:" << (const char*)msg["TESTSTRING"];
		}
		catch (std::exception ex)
		{
			cout << ex.what();
		}
	}
};

/**
 * Main entry point
 */
int main()
{
	// we create a new object to be able to receive the messages
	MyReceiver *myReceiver = new MyReceiver();

   // this object is the dynamic client that will send and subscribe to various subjects
PnmsDynamicClient client("TESTCLIENT");

	// the constructor of the client class is suppsoed to initialize the network correctly ... But let's verify
	if(!client.isInitialized())
	{
		std::cout << "The client is not initialized" << std::endl;
		return 0;
	}

   
	// and instruct the transporter object to subscribe this object to the "HELLO.B" message
	client.subscribe("HELLO.B", myReceiver);

	// this will be a message object that will be prepared and sent across the network with 
	// the message "Hello World"
Message m;
  
	m["TESTSTRING"]		= "tst";
	m["TESTINT"]		= 1234;
	m["TESTDOUBLE"]		= (double)5678.987;
	m["TESTFLOAT"]		= (float)1267.98;
	m["TESTBOOL"]		= true;
	m["TESTLONG"]		= (long)6789;
	m["TESTCHAR"]		= (char)'a';

	client.publishMessage("HELLO.B", m);
   
   // if we don't put here a pause it might go so fast that actually we won't see anything...

   // cleaning the garbage
   delete myReceiver;

   return 1;
}