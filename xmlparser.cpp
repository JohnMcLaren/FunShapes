#include "xmlparser.h"
//-----------------------------------------------------------------
CXMLParser::CXMLParser()
{
	reader.setContentHandler(this);
}
//.................................................................
bool CXMLParser::parse(const QString &xml)
{
QXmlInputSource srcXML;
	srcXML.setData(xml);
return reader.parse(srcXML);
}
//.................................................................
bool CXMLParser::startElement(const QString &namespaceURI,
							  const QString &localName,
							  const QString &qName,
							  const QXmlAttributes &atts)
{
clear_attr();
attr.tag =qName;

	for(int c = 0;c < atts.length();c++)
	{
		if(atts.qName(c)=="name")attr.name =atts.value(c);
			else
		if(atts.qName(c)=="type")attr.type =atts.value(c);
			else
		if(atts.qName(c)=="color")attr.color =atts.value(c).toULong();
			else
		if(atts.qName(c)=="x")attr.x =atts.value(c).toDouble();
			else
		if(atts.qName(c)=="y")attr.y =atts.value(c).toDouble();
			else
		if(atts.qName(c)=="z")attr.z =atts.value(c).toDouble();
			else
		if(atts.qName(c)=="width")attr.width =atts.value(c).toDouble();
			else
		if(atts.qName(c)=="height")attr.height =atts.value(c).toDouble();
			else
		if(atts.qName(c)=="angle")attr.angle =atts.value(c).toDouble();
			else
		if(atts.qName(c)=="text")attr.text =atts.value(c);
			else
		if(atts.qName(c)=="textfont")attr.textfont =atts.value(c);
			else
		if(atts.qName(c)=="textsize")attr.textsize =atts.value(c).toULong();
			else
		if(atts.qName(c)=="textcolor")attr.textcolor =atts.value(c).toULong();
			else
		if(atts.qName(c)=="image")attr.image =atts.value(c);
			else
		if(atts.qName(c)=="clipboard")attr.clipboard =true;
	}
return true;
}
//-----------------------------------------------------------------
void CXMLParser::clear_attr()
{
	attr.id =0;
	attr.tag ="";
	attr.name ="";
	attr.type ="";
	attr.shape ="";
	attr.x =0;
	attr.y =0;
	attr.z =0;
	attr.width =0;
	attr.height =0;
	attr.top =0;
	attr.left =0;
	attr.angle =0;
	attr.color =0;
	attr.text ="";
	attr.textfont ="";
	attr.textsize =0;
	attr.textcolor =0;
	attr.image ="";
	attr.value =0;
	attr.clipboard =false;
}
//--------------------------------------------------------------------------
