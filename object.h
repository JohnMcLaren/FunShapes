#ifndef GPHOBJECT_H
#define GPHOBJECT_H
#include <QtWidgets>
#include <QColor>
#include <QGraphicsItem>
#include "undoredo.h"

/* направление грипа */
enum GRIP_DIR_TYPE
{
	NO_DIR =0,
	NORTH_WEST,
	NORTH_EAST,
	SOUTH_EAST,
	SOUTH_WEST,
	NORTH,
	EAST,
	SOUTH,
	WEST
};
//-----------------------------------------------------------------
class CGripUnit : public QRectF
{
public:
	CGripUnit(const QRectF *gripRect=0);
	friend class CGripObject;
private:
	GRIP_DIR_TYPE	gripUnitDir;
	void setGripUnit(const QRectF &gripRect, int direction);
};
//.........................................................
class CGripObject : public QRectF
{
public:
	/* тип области (задаёт кол-во и расположение грип-юнитов)*/
	enum GRIP_STYLE_TYPE{GRIP_NO_STYLE =0,
						 GRIP_SQUARE_STYLE,
						 GRIP_ROMB_STYLE,
						 GRIP_ROSE_STYLE};

	CGripObject			(const QGraphicsItem *parent);
	int					getGripStatusPos(const QPointF &posXY);
	void				drawGrip(QPainter *painter);
	void				setGripStyle(GRIP_STYLE_TYPE style=GRIP_NO_STYLE);
	void				setGripArea(const QRectF &area);
	QColor				GripBorderClr;
	QBrush				gripsClr;
	QVector<CGripUnit>	grips;
	GRIP_STYLE_TYPE		GripViewStyle;
private:
	int		wgrip;
};
//----------------------------------------------------------------------------------
class CGraphObject : public QGraphicsObject
{
	Q_OBJECT // макрос нужен для работы механизма слотов/сигналов

public:
	CGraphObject(const QString type,
				 const QString name,
				 const qreal x =0,
				 const qreal y =0,
				 const qreal z =0,
				 const qreal width =0,
				 const qreal height =0,
				 const qreal angle =0,
				 const DWORD color =Qt::black,
				 const QString text ="",
				 QString textfont ="",
				 DWORD textsize =0,
				 const DWORD textcolor =0,
				 const QString image ="",
				 DWORD *scenemode=NULL);
	~CGraphObject();
	int							getObjectStatusPos(const QPointF &posXY);
	QString						getXML();					// относительно 0 сцены
	QString						getXML(QPointF originXY);	// XY относительно курсора
	QString						NameObject;
	QRectF						RectObject;
	QPainterPath				ShapeObject;	/* геометрия фигуры */
	QString						TypeObject;		/* тип фигуры */
	QColor						ColorObject;
	QString						TextObject;
	QFont						TextFontObject;
	int							TextSizeObject;
	QColor						TextColorObject;
	qreal						AngleObject=0.0;
	int							ModifyMODE;
	bool						IsValid;
	QRectF						SourceRectObject;
	qreal						SourceAngleObject=0.0; /* исходный угол фигуры перед изменением */
	QString						getBase64FromImage(QImage *image=NULL);
	QImage						getImageFromBase64(const QString &imagebase64);

	qreal						getAngleBy3Points(QPointF center, QPointF start, QPointF current);
	qreal						getVectorLength(QPointF A, QPointF B);
	qreal						getVectorLength(QPointF vector);
private:
	CGripObject					*Grip =NULL;
	QBrush						BrushObject;
	QRadialGradient				GradientObject;
	QGraphicsDropShadowEffect	ShadowObject;
	QPainterPath				ShapeTextObject;
	QImage						ImageObject;
	qreal						ObjectScaleX;
	qreal						ObjectScaleY;
	qreal						kProp;			// коэффициент пропорциональности сторон
	DWORD						*SceneMode=0;
	QPointF						GripClickXY;
	QPainterPath				SourceShapeObject; /* геометрия фигуры (исходная без трансформаций) */
	QPainterPath				getRectanglePath();
	QPainterPath				getTrianglePath();
	QPainterPath				getCirclePath();
	QPainterPath				getArrowPath();
	QPainterPath				getTextPath(QString text, QFont font);
	QRectF						getTextMetrics(const QString &text, const QFont &font);
protected:
	void			mousePressEvent(QGraphicsSceneMouseEvent *event);
	void			mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void			mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void			hoverMoveEvent(QGraphicsSceneHoverEvent *event);
	QRectF			boundingRect()const;
	QPainterPath	shape() const;
	void			paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
public slots:
	void			setAngleObject(const qreal angle);
	void			setColorObject(const DWORD color);
	void			setImageObjectFromFile(const QString &filename);
	void			setImageObjectFromBase64(const QString &imagebase64);
	void			setTextObject(const QString *text);
	void			setTextFontObject(const QString *textfont);
	void			setTextSizeObject(const ULONG textsize);
	void			setTextColorObject(const DWORD textcolor);
	void			resizeObject(qreal dX=0, qreal dY=0, qreal dW=0, qreal dH=0);	// относительное
	void			resizeObject(const QRectF &rect);								// абсолютное
signals:
	void			objectModify(CGraphObject *obj);	// не используется
};

#endif // GPHOBJECT_H
