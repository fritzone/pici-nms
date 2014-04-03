#include "ConfigReader.h"
#ifndef DISPATCHER
#include "Logger.h"
#else
#include "local.h"
#endif

#include "constants.h"

#include <sys/stat.h>

#ifdef WIN32
#include <direct.h>
#include <shlobj.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xmlstring.h>

/**
 * Creates a new config dynamically searching for config file locations.
 */
ConfigReader::ConfigReader(const string& file) : configFile(file), doc(NULL), initSuccesful(true)
{
	if(loadConfig(provideConfigFile(0)))
	{
		return;
	}
	if(loadConfig(provideConfigFile(1)))
	{
		return;
	}
	initSuccesful = false;
}

/**
 * Loads the given config file from the given location. 
 * It does not search for another locations
 */
ConfigReader::ConfigReader(const string& file, const string& location) : initSuccesful(true), doc(NULL)
{

	configFile = location + 
#ifdef WIN32
		"\\"
#else
		"/"
#endif
		+ file;
	LOG("Trying:");
	LOG(configFile.c_str());

	if(loadConfig(configFile))
	{
		LOG("Read configuration");
		return;
	}
	LOG("Did not read configuration");
	
	initSuccesful = false;
}

/**
 * The following method returns the users home directory
 */
#ifndef WIN32
static string getHomeDir()
{
passwd* pw = getpwent();
int can_go = true;
int uid = getuid();
	while(can_go)
	{
		if(pw->pw_uid == uid)
		{
			can_go = false;
		}
		else
		{
			pw = getpwent();
		}
	}
	return string(pw->pw_dir);
}	
#else
static string getHomeDir()
{
char path[1024];
	SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0, path);
	return string(path);
}
#endif

/**
 * Provides a config file from the given location
 * @param loc:
 * 0 - the current directory. If none found, then:
 * 1 - the users HOME directory
 */
string ConfigReader::provideConfigFile(int loc)
{
string homeDir;
char dir [1024];
string res = "";
	switch(loc)
	{
	case 0:	// config file from the current directory
		getcwd(dir, 1024);
		res = dir;
#ifdef WIN32
		res += "\\";
#else
		res += "/";
#endif
		res += configFile;
		fullPath = res;
		return res;

	case 1:	// config file from the users home directory
		homeDir = getHomeDir();
#ifdef WIN32
		homeDir += "\\";
#else
		homeDir += "/";
#endif
		homeDir += configFile;
		fullPath = homeDir;
		return homeDir;
	default:
		return "";
	}
}

/**
 * Load the config from the given file
 */
bool ConfigReader::loadConfig(const string& file)
{
	LOG("\nUsing config file ");
	LOG(file.c_str());
	try
	{
		doc = xmlParseFile (file.c_str());
	}
	catch (...)
	{
		LOG("\nDocument not parsed successfully. Exception was thrown");
		return false;
	}

	if (doc == NULL)
	{
		LOG("\nDocument not parsed successfully. NULL object");
		return false;
	}
xmlNodePtr cur = xmlDocGetRootElement (doc);
	if (cur == NULL)
	{
		LOG("empty document");
		xmlFreeDoc (doc);
		return false;
	}
	if (xmlStrcmp (cur->name, (const xmlChar *) "daemon"))	// if it's NOT daemon
	{
		if(xmlStrcmp (cur->name, (const xmlChar *) "client"))	// and NOT client
		{
			if(xmlStrcmp (cur->name, (const xmlChar *) "dispatcher"))	// and NOT dispatcher
			{
				LOG("\ndocument of the wrong type, root node not a valid value ");
				xmlFreeDoc (doc);
				return false;
			}
		}
	}
	return true;
}

/**
 * Returns the config value for the given parent/branch/value triplet
 */
string ConfigReader::getValue(const char *parent, const char *branch, const char *cfgval)
{
xmlNodePtr cur = xmlDocGetRootElement(doc);
    cur = cur->xmlChildrenNode;
    while (cur != NULL)
    {
        if ((!xmlStrcmp (cur->name, (const xmlChar *)parent)))
        {
		xmlNodePtr parentsChildren = cur->xmlChildrenNode;
			while(parentsChildren != NULL)
			{
				if(!xmlStrcmp(parentsChildren->name, (const xmlChar*)branch))
				{
				xmlNodePtr branchNodes = parentsChildren->xmlChildrenNode;
					while(branchNodes != NULL)
					{
						if(!xmlStrcmp(branchNodes->name, (const xmlChar*)cfgval))
						{
						xmlChar* val =	xmlNodeListGetString(doc, branchNodes->xmlChildrenNode, 1);
						string g = string((char*)val);
							xmlFree(val);
							return g;
						}
						branchNodes = branchNodes->next;
					}
				}
				parentsChildren = parentsChildren->next;
			}
        }
		cur = cur->next;
	}
	return "";	
}
