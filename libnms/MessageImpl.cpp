#include "MessageImpl.h"
#include "Message.h"
#include "ObjImplMapper.h"
#include "Parameter.h"
#include "ParameterImpl.h"
#include "IntWrapper.h"
#include "BoolWrapper.h"
#include "DoubleWrapper.h"
#include "StringWrapper.h"
#include "LongWrapper.h"
#include "FloatWrapper.h"
#include "IntImpl.h"
#include "ObjectFactory.h"
#include "constants.h"
#include "Logger.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <sstream>

using namespace std;

int MessageImpl::messageCounter = 0;

/**
 * Constructor
 */
MessageImpl::MessageImpl(int _ttl) : ttl(_ttl)
{
time_t now;
	time(&now);
stringstream ss;
	ss << (int)now << "_" << messageCounter ++;
	messageId = ss.str();
}

/**
 * Destructor
 */
MessageImpl::~MessageImpl(void)
{
	for (size_t i = 0; i<parameters.size(); i++)
	{
	Parameter* parI = parameters[i];
		if(parI)
		{
			delete parI;
		}		
	}
}

/**
 * Add a parameter to the message
 */
void MessageImpl::addParameter(Parameter* param)
{
	parameters.push_back(param);
}

Parameter* MessageImpl::getParameter(const std::string &name)
{
	for (size_t i = 0; i<parameters.size(); i++)
	{
	Parameter* parI = parameters[i];
		if(ObjImplMapper<Parameter, ParameterImpl>::getImpl(const_cast<Parameter*>(parI))->getName() == name)
		{
			return parI;
		}		
	}
	return NULL;
}

/**
 * Serializes the message
 */
string MessageImpl::serialize()
{
string result("<Message><Parameters>");
	for(unsigned int i=0; i<parameters.size(); i++)
	{
		result += ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->serialize();
	}
	result += "</Parameters></Message>";
	LOG(result);
	return result;
}

/**
 * Returns the string for the given name
 */
string MessageImpl::getString(const string& stringName)
{
	for(size_t i=0; i<parameters.size(); i++)
	{
		if(ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->getName() == stringName )
		{
		String* strI = dynamic_cast<String*>(ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->getValue());
			if(strI) return string(strI->c_str());
		}
	}
	return "";
}

/**
 * Returns the bool for the given name
 */
double MessageImpl::getDouble(const string& doubleName)
{
	for(size_t i=0; i<parameters.size(); i++)
	{
		if(ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->getName() == doubleName )
		{
		Double* doubleI = dynamic_cast<Double*>(ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->getValue());
			if(doubleI) return doubleI->operator double();
		}
	}
	return 0;
}

/**
 * Returns the bool for the given name
 */
bool MessageImpl::getBool(const string& boolName)
{
	for(size_t i=0; i<parameters.size(); i++)
	{
		if(ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->getName() == boolName )
		{
		Bool* boolI = dynamic_cast<Bool*>(ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->getValue());
			if(boolI) return boolI->operator bool();
		}
	}
	return false;
}

/**
 * Returns the long for the given name
 */
long MessageImpl::getLong(const string& longName)
{
	for(size_t i=0; i<parameters.size(); i++)
	{
		if(ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->getName() == longName )
		{
		Long* longI = dynamic_cast<Long*>(ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->getValue());
			if(longI) return longI->operator long();
		}
	}
	return 0;
}


/**
 * Returns the int for the given name
 */
int MessageImpl::getInt(const string& intName)
{
	for(size_t i=0; i<parameters.size(); i++)
	{
		if(ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->getName() == intName )
		{
		Integer* intI = dynamic_cast<Integer*>(ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->getValue());
			if(intI) return intI->operator int();
		}
	}
	return 0;
}

/**
 * Returns the float for the given name
 **/
float MessageImpl::getFloat(const string& floatName)
{
	for(size_t i=0; i<parameters.size(); i++)
	{
		if(ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->getName() == floatName )
		{
		Float* floatI = dynamic_cast<Float*>(ObjImplMapper<Parameter, ParameterImpl>::getImpl(parameters[i])->getValue());
			if(floatI) return floatI->operator float();
		}
	}
	return 0.0F;
}

/**
 * Deserializes the input string, i.e. it creates a new MessageImpl object
 * from the input string which contains the neccessary data.
 * In caze of any errors return an empty message, without parameters.
 */
Message *MessageImpl::deserialize(const char* src)
{
Message *retValue = new(std::nothrow) Message();
	if(NULL == retValue)
	{
		LOG_ERR("Cannot create a new Message");
		return NULL;
	}

const char* xmlStart = src;
	if(*xmlStart != '<') return retValue;
	
xmlDocPtr doc = xmlReadMemory(xmlStart, strlen(xmlStart), "", NULL, 0);
	if(!doc) 
	{
		LOG_ERR("Could not read the XML into the memory");
		return retValue;
	}
xmlNodePtr messageNode = doc->children;	// The "Message" node
	if(!messageNode || xmlStrcmp(messageNode->name,  const_cast<xmlChar*>(reinterpret_cast<const xmlChar *>("Message"))))
	{
		LOG_ERR("The message hasn't got a \"Message\" node");
		return retValue;
	}
xmlNodePtr parametersNode = messageNode->children;	// the Parameters node from the Message node
	if(!parametersNode || xmlStrcmp(parametersNode->name, const_cast<xmlChar*>(reinterpret_cast<const xmlChar *>("Parameters"))))
	{
		LOG_ERR("The message hasn't got a \"Parameters\" node");
		return retValue;
	}
xmlNodePtr parameterNode = parametersNode->children;	// the first parameter from the Parameters
	while(parameterNode)
	{
	DESERIALIZER objCreator = ObjectFactory::getDeserializer(ParameterImpl::TYPESTR_PARAMETER);
	SerializableObject* newObj = objCreator(doc, parameterNode);
	Parameter *newParameter = dynamic_cast<Parameter*>(newObj);
		retValue->addParameter(newParameter);
		parameterNode = parameterNode->next;
	}
	return retValue;
}
