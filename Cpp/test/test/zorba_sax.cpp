/*  * Copyright 2006-2008 The FLWOR Foundation.  *   * Licensed under the Apache License, Version 2.0 (the "License");  * you may not use this file except in compliance with the License.  * You may obtain a copy of the License at  *   * http://www.apache.org/licenses/LICENSE-2.0  *   * Unless required by applicable law or agreed to in writing, software  * distributed under the License is distributed on an "AS IS" BASIS,  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  * See the License for the specific language governing permissions and  * limitations under the License.  */
#include <iostream>
#include <zorba/zorba.h>
#include <zorba/default_content_handler.h>
#include <zorba/store_manager.h>
#include <zorba/zorba_exception.h>

using namespace zorba;
// implement a new sax content handler
// that prints information to an output stream passed in the constructor
class XMLSerializer: public DefaultContentHandler {
protected:
	std::ostream& theOStream;
	bool preserveWhiteSpaces;
public:
	XMLSerializer( std::ostream & aOStream, bool useWS = true )
		: theOStream( aOStream )
		, preserveWhiteSpaces( useWS ){}
	virtual ~XMLSerializer(){}     
	void endDocument()     {       
		//theOStream << std::endl;
	}     
	void startElement( const String &uri, const String &localname, const String &qname, const SAX2_Attributes& attrs )      {
		//theOStream << "<" << qname;       for ( unsigned int i = 0; i < attrs.getLength(); i++ ) {         theOStream  <<  " " << attrs.getQName( i ) << "=\"" << attrs.getValue( i ) << "\"";           }       theOStream << ">";    
	}     
	void endElement( const String &uri, const String &localname, const String &qname )     {       
		//theOStream << "</" << qname << ">";     
	}          
	void characters( const String & text )     {      
		//theOStream << text;     
	}          
	void processingInstruction( const String &target, const String &data ){}
	void ignorableWhitespace( const String & whitespace )     {       
		//if ( preserveWhiteSpaces ) {         theOStream << whitespace;       }     
	} 
}; 

int main( int argc, char * argv[] ) {
	// create a SAX content handler that prints all events to standard out
	XMLSerializer lContentHandler( std::cout );
	void* lStore = zorba::StoreManager::getStore();
	// initialize the Zorba engine and get a pointer to it
	Zorba* lZorba = Zorba::getInstance(lStore);   
	try    {     
		// compile a query  
		//XQuery_t lQuery = lZorba->compileQuery("declare namespace op = \"http://www.zorba-xquery.org/options\";\
			declare namespace an = \"http://www.zorba-xquery.com/annotations\";\
			import module namespace f = \"http://expath.org/ns/file\";\
			variable $file-name := fn:resolve-uri(\"resources/ITEM_CCTR_MNTH_SLS.xml\");\
			fn:parse-xml(f:read-text( $file-name ))\
		");
		XQuery_t lQuery = lZorba->compileQuery("fn:doc(fn:resolve-uri(\"D:\\ITEM_CCTR_MNTH_SLS.xml\"));<a />");
		// register the content handler created above
		lQuery->registerSAXHandler( &lContentHandler ); 
		// execute the query and call according SAX callbacks      
		// i.e. equivalent to serializing to xml and parsing using SAX).     
		lQuery->executeSAX();   
	}   catch ( ZorbaException &e )    {     
			std::cerr << e << std::endl;   
	}   
	lZorba->shutdown();   
	zorba::StoreManager::shutdownStore(lStore);  
	return 0;
}