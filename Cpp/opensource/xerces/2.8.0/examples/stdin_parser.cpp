#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/framework/StdInInputSource.hpp>

#include <iostream>

using namespace std;
using namespace xercesc;

class XMLSerializer: public DefaultHandler {
protected:
	std::wostream& theOStream;
	bool preserveWhiteSpaces;

public:
	XMLSerializer( std::wostream & aOStream, bool useWS = true )
		: theOStream( aOStream )
		, preserveWhiteSpaces( useWS ){}

	virtual ~XMLSerializer(){
	}     

	void endDocument()     {       
		theOStream << std::endl;
	}     

	void startElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs )      {
		theOStream << "<" << qname;
		for ( unsigned int i = 0; i < attrs.getLength(); i++ ) {
			theOStream  <<  " " << attrs.getQName( i ) << "=\"" << attrs.getValue( i ) << "\"";
		}
		theOStream << ">";
	}     

	void endElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname )     {       
		theOStream << "</" << qname << ">";     
	}          

	void characters(const XMLCh* const chars, const unsigned int    length)     {      
		theOStream.write(chars, length);
	}

	void ignorableWhitespace(const XMLCh* const chars, const unsigned int length)     {       
		if ( preserveWhiteSpaces ) {
			theOStream.write(chars, length);
		}
	} 
}; 

int main (int argc, char* args[]) {

	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Error during initialization! :\n";
		cout << "Exception message is: \n"
			<< message << "\n";
		XMLString::release(&message);
		return 1;
	}

	StdInInputSource lStdInStream;
	SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
	parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
	parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional

	XMLSerializer* defaultHandler = new XMLSerializer(wcout);
	parser->setContentHandler(defaultHandler);
	parser->setErrorHandler(defaultHandler);

	try {
		parser->parse(lStdInStream);
	}
	catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n"
			<< message << "\n";
		XMLString::release(&message);
		return -1;
	}
	catch (const SAXParseException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n"
			<< message << "\n";
		XMLString::release(&message);
		return -1;
	}
	catch (...) {
		cout << "Unexpected Exception \n" ;
		return -1;
	}

	delete parser;
	delete defaultHandler;
	return 0;
}

