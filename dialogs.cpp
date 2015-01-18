#include "dialogs.h"
//--------------------------------------------------------------------
CTextDialog::CTextDialog()
	: QDialog(0, Qt::WindowSystemMenuHint|Qt::WindowCloseButtonHint)
{
	setWindowTitle(tr("Title"));
	txtText	= new QTextEdit;
	listTextFontFamilies = new QComboBox;
	listTextFontSize = new QComboBox;
	cmdTextColor = new QPushButton;
//......................................
QPalette pal =txtText->palette();
	pal.setColor(QPalette::Base, Qt::lightGray);
	txtText->setPalette(pal);
	connect(txtText, SIGNAL(textChanged()), SLOT(textChanged()));

	listTextFontFamilies->addItems(QFontDatabase().families());
	connect(listTextFontFamilies, SIGNAL(currentIndexChanged(QString)), SLOT(setTextFont(QString)));

	listTextFontSize->addItems(QString("8,9,10,11,12,14,16,18,20,22,24,26,28,36,48,72").split(","));
	connect(listTextFontSize, SIGNAL(currentIndexChanged(QString)), SLOT(setTextFontSize(QString)));

	cmdTextColor->setStyle(QStyleFactory::create("Windows"));
	cmdTextColor->setFixedSize(30,20);
	cmdTextColor->setAutoFillBackground(true);
	connect(cmdTextColor, SIGNAL(clicked()), SLOT(chooseTextColor()));

	cmdOk     = new QPushButton("&Ok");
	cmdCancel = new QPushButton("&Cancel");
	connect(cmdOk, SIGNAL(clicked()), SLOT(accept()));
	connect(cmdCancel, SIGNAL(clicked()), SLOT(reject()));
//Layout setup
	layout = new QGridLayout;
	layout->addWidget(listTextFontFamilies,0,0);
	layout->addWidget(listTextFontSize,0,1);
	layout->addWidget(cmdTextColor,0,2);
	layout->addWidget(txtText,1,0,1,0);
	layout->addWidget(cmdOk,2,0);
	layout->addWidget(cmdCancel,2,1,1,2);
	setLayout(layout);
}
//...................................................................
QStringList CTextDialog::getNewTextAndAttributes(const QString *text,
												 const QFont *textfont,
												 const QColor *textcolor)
{
int i;
QStringList changes(QString(",,,,").split(","));

	if(text)txtText->setPlainText(*text);
	if(textfont)
	{
		if((i =listTextFontFamilies->findText(textfont->family())) >= 0)listTextFontFamilies->setCurrentIndex(i);
		setTextFont(textfont->family());

		if((i =listTextFontSize->findText(QString("%1").arg(textfont->pointSize()))) >= 0)listTextFontSize->setCurrentIndex(i);
		if(textfont->pointSize())
			setTextFontSize(textfont->pointSize());
		else
			setTextFontSize(listTextFontSize->currentText().toInt());
	}
	if(textcolor)setTextColor(*textcolor);

	changed =0;
//.................
	this->exec();
//.................
	if(changed)
	{
		if(changed & TEXT_CHANGED)
		{
			changes[1] =txtText->toPlainText();
		}

		if(changed & TEXT_FONT_CHANGED)
		{
			changes[2] =txtText->font().family();
		}

		if(changed & TEXT_SIZE_CHANGED)
		{
			changes[3].sprintf("%u", txtText->font().pointSize());
		}

		if(changed & TEXT_COLOR_CHANGED)
		{
			changes[4].sprintf("%u", txtText->palette().color(QPalette::Text).rgba());
		}

	changes[0].sprintf("%u", changed);
	}
return (changes);
}
//-------------------------------------------------------------------
void CTextDialog::setTextFont(const QString &fontname)
{
QFont font =txtText->font();
	font.setFamily(fontname);
	txtText->setFont(font);
changed	|=TEXT_FONT_CHANGED;
}
//.................................................
void CTextDialog::setTextFontSize(const QString fontsize)
{
	setTextFontSize(fontsize.toULong());
}

void CTextDialog::setTextFontSize(const int fontsize)
{
QFont font =txtText->font();
	font.setPointSize(fontsize);
	txtText->setFont(font);
changed	|=TEXT_SIZE_CHANGED;
}
//-------------------------------------------------------------------
void CTextDialog::chooseTextColor()
{
QColor color =QColorDialog::getColor(txtText->palette().color(QPalette::Text),0,"",QColorDialog::ShowAlphaChannel);
	if (!color.isValid())return;
	setTextColor(color);
}
//.................................................
void CTextDialog::setTextColor(const QColor &textcolor)
{
QPalette pal =txtText->palette();
	pal.setColor(QPalette::Text,textcolor);
	txtText->setPalette(pal);
	cmdTextColor->setPalette(textcolor);
changed	|=TEXT_COLOR_CHANGED;
}
//-------------------------------------------------------------------
void CTextDialog::textChanged()
{
changed	|=TEXT_CHANGED;
}
//-------------------------------------------------------------------
