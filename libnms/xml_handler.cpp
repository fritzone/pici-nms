#include "xml_handler.h"

/**
 * Returns the value of the node named "nodeName" being a child of "node"
 */
std::string getXmlValue ( xmlDocPtr doc, xmlNodePtr node, std::string nodeName )
{
    xmlNodePtr cur = node->xmlChildrenNode;
    while ( cur != NULL )
    {
        if ( !xmlStrcmp ( cur->name, ( const xmlChar* ) ( nodeName.c_str() ) ) )
        {
            xmlChar* value = xmlNodeListGetString ( doc, cur->xmlChildrenNode, 1 );
            if ( value == 0 )
            {
                return "";
            }
            std::string result = std::string ( ( char* ) value );
            xmlFree ( value );
            return result;
        }
        cur = cur->next;
    }
    return "";
}

/**
 * Returns a list of nodes starting from node, all having the same name.
 */
std::vector<xmlNodePtr> getNodeList ( xmlDocPtr /*doc*/ , xmlNodePtr node, std::string nodeName )
{
    std::vector<xmlNodePtr> result;
    result.clear();
    xmlNodePtr cur = node->xmlChildrenNode;
    while ( cur != NULL )
    {
        if ( !xmlStrcmp ( cur->name, ( const xmlChar* ) ( nodeName.c_str() ) ) )
        {
            result.push_back ( cur );
        }
        cur = cur->next;
    }
    return result;
}

/**
 * Returns the node with the given name
 */
xmlNodePtr getNamedNode ( xmlDocPtr /*doc*/ , xmlNodePtr node, std::string nodeName )
{
    xmlNodePtr cur = node->xmlChildrenNode;
    while ( cur != NULL )
    {
        if ( !xmlStrcmp ( cur->name, ( const xmlChar* ) ( nodeName.c_str() ) ) )
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}
