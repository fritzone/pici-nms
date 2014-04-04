#ifndef _XML_HANDLER_H_
#define _XML_HANDLER_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <libxml/xmlstring.h>
#include <libxml/xpath.h>
#include <libxml/parser.h>
#include <libxml/xpathInternals.h>
#include <libxml/tree.h>

#include <vector>
#include <string>

/**
 * Returns the XMLs value for the node with the given name. The node must be a child node of the nNode".
 */
std::string getXmlValue ( xmlDocPtr doc, xmlNodePtr node, std::string nodeName );

/**
 * Returns a list of nodes that can be found under the "node" with the given name
 */
std::vector <xmlNodePtr> getNodeList ( xmlDocPtr doc, xmlNodePtr node, std::string nodeName );

/**
 * Returns the first node with the given name
 */
xmlNodePtr getNamedNode ( xmlDocPtr doc, xmlNodePtr node, std::string nodeName );

#endif
