#ifndef DIALOGS_H
#define DIALOGS_H

#include <QtWidgets>
#include <QDialog>

#define TEXT_CHANGED		1
#define TEXT_FONT_CHANGED	2
#define TEXT_SIZE_CHANGED	4
#define TEXT_COLOR_CHANGED	8

class CTextDialog : public QDialog
{
	Q_OBJECT
public:
	CTextDialog();
	QStringList getNewTextAndAttributes(const QString *text=NULL,
										const QFont *textfont=NULL,
										const QColor *textcolor=NULL);
private:
	QTextEdit	*txtText;
	QComboBox	*listTextFontFamilies;
	QComboBox	*listTextFontSize;
	QPushButton *cmdTextColor;

	QPushButton *cmdOk;
	QPushButton *cmdCancel;
	QGridLayout *layout;
	int			changed =0;
public slots:
	void		setTextFont(const QString &fontname);
	void		setTextFontSize(const QString fontsize);
	void		setTextFontSize(const int fontsize);
	void		chooseTextColor();
	void		setTextColor(const QColor &textcolor);
	void		textChanged();
};

#endif // DIALOGS_H
