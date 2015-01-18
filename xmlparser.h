#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QtWidgets>
#include <QtXml>
/* стандартные атрибуты для большинства объектов */
typedef struct _STD_ATTR_
{
	int		id;
	QString	tag;
	QString	name;
	QString	type;
	QString	shape;
	qreal	x;
	qreal	y;
	qreal	z;
	qreal	width;
	qreal	height;
	qreal	top;
	qreal	left;
	qreal	angle;
	DWORD	color;
	QString	text;
	QString	textfont;
	DWORD	textsize;
	DWORD	textcolor;
	QString	image;
	qreal	value;
	bool	clipboard;
}STD_ATTR;
//..................................................
class CXMLParser : public QXmlDefaultHandler
{
public:
	CXMLParser();
	bool				parse(const QString &xml);
	STD_ATTR			attr;
private:
	QXmlSimpleReader	reader;
	void				clear_attr();
protected:
	bool startElement(const QString &namespaceURI,
					  const QString &localName,
					  const QString &qName,
					  const QXmlAttributes &atts);
};
//--------------------------------------------------
#endif // XMLPARSER_H
