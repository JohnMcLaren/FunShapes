#include "object.h"
/* Объект сам меняет курсор над грипами */
Qt::CursorShape GRIP_CURSOR[]={Qt::ArrowCursor,
							   Qt::SizeFDiagCursor,
							   Qt::SizeBDiagCursor,
							   Qt::SizeFDiagCursor,
							   Qt::SizeBDiagCursor,
							   Qt::SizeVerCursor,
							   Qt::SizeHorCursor,
							   Qt::SizeVerCursor,
							   Qt::SizeHorCursor};
//-------------------------------------------------------------------------------------
CGraphObject::CGraphObject(const QString type,
						   const QString name,
						   const qreal x,
						   const qreal y,
						   const qreal z,
						   const qreal width,
						   const qreal height,
						   const qreal angle,
						   const DWORD color,
						   const QString text,
						   QString textfont,
						   DWORD textsize,
						   const DWORD textcolor,
						   const QString image,
						   DWORD *scenemode)
{
IsValid =false;
TypeObject	=type;		// тип фигуры (строка)
/* если задан текст (для любого объекта) или создаётся объект "Text" */
	if(!text.isEmpty() || type == "Text")
	{
		/* текст */
		if((TextObject =text).isEmpty() && type == "Text")
		{
		/* шрифт (по умолчанию)*/
			TextObject ="Text";
			textfont ="Arial";
			textsize =20;
		}
		if(!textfont.isEmpty())setTextFontObject(&textfont);
		if(textsize)setTextSizeObject(textsize);
		/* цвет */
		if(textcolor)setTextColorObject(textcolor);
		/* геометрия текста */
		setTextObject(&TextObject);
	}
/* выбор фигуры под объект */
	if(type == "Rectangle")SourceShapeObject =getRectanglePath();
		else
	if(type == "Triangle")SourceShapeObject =getTrianglePath();
		else
	if(type == "Circle")SourceShapeObject =getCirclePath();
		else
	if(type == "Text");
		else
	if(type == "Image")
	{
		if(image.isEmpty())
		{
			setImageObjectFromFile(":/images/DefaultImage.png");
		}
		else
		{
			setImageObjectFromBase64(image);
		}
	}
		else
	if(type == "Arrow")SourceShapeObject =getArrowPath();
		else
	return;

	setData(0,"GraphObject");	// идентифицирующий тип объекта на сцене
	NameObject		=name;		// уникальное имя объекта
	Grip = new CGripObject(this);
	if(!width || !height)
		resizeObject(QRectF(x,y,SourceShapeObject.controlPointRect().width(),SourceShapeObject.controlPointRect().height()));
	else
		resizeObject(QRectF(x,y,width,height));

	setAngleObject(angle);
	setColorObject(color);
	SceneMode =scenemode;
	if(z)setZValue(z);
	setFlags(ItemIsSelectable|ItemIsMovable);
	setAcceptHoverEvents(true);
IsValid =true; /* успешное создание объекта */
}
//.............................................
CGraphObject::~CGraphObject()
{
	prepareGeometryChange();
	delete Grip;
}
//--------------------------------------------------------------------
QString CGraphObject::getBase64FromImage(QImage *image)
{
QByteArray byteArray;
QBuffer buffer(&byteArray);
if(TypeObject != "Image")return "";
if(!image)image = &ImageObject;

	image->save(&buffer, "PNG");

return (QString::fromLatin1(byteArray.toBase64().data()));
}
//....................................................................
QImage CGraphObject::getImageFromBase64(const QString &imagebase64)
{
return QImage::fromData(QByteArray::fromBase64(imagebase64.toLatin1()));
}
//--------------------------------------------------------------------
void CGraphObject::setAngleObject(const qreal angle)
{
	AngleObject =fmod(angle, 360.0);
	setTransform(QTransform().translate(RectObject.width()/2,RectObject.height()/2)
							.rotate(AngleObject,Qt::ZAxis)
							.translate(-RectObject.width()/2,-RectObject.height()/2));
update();
}
//--------------------------------------------------------------------
void CGraphObject::setColorObject(const DWORD color)
{
ColorObject.setRgba(color);
	GradientObject	=QRadialGradient(50,50,100,60,40);// (X,Y,R,focalX,focalY)
	GradientObject.setColorAt(0.0, Qt::white);
	GradientObject.setColorAt(0.4, ColorObject);
	GradientObject.setColorAt(1.0, Qt::black);
	BrushObject =QBrush(GradientObject);

	ShadowObject.setOffset(QPoint(-5,5));
	ShadowObject.setBlurRadius(10);
	setGraphicsEffect(&ShadowObject);
update();
}
//--------------------------------------------------------------------
void CGraphObject::setTextObject(const QString *text)
{
	if(text)
	{
		TextObject = *text;
		TextSizeObject =TextFontObject.pointSize();
		ShapeTextObject =getTextPath(TextObject,TextFontObject);
		if(TypeObject == "Text")SourceShapeObject =ShapeTextObject;
	resizeObject(0,0,0,0);
	}
}

void CGraphObject::setTextFontObject(const QString *textfont)
{
	if(textfont)
	{
		TextFontObject.setFamily(*textfont);
		ShapeTextObject =getTextPath(TextObject,TextFontObject);
		if(TypeObject == "Text")SourceShapeObject =ShapeTextObject;
	resizeObject(0,0,0,0);
	}
}

void CGraphObject::setTextSizeObject(const ULONG textsize)
{
	if(textsize)
	{
		TextFontObject.setPointSize(textsize);
		TextSizeObject =TextFontObject.pointSize();
		ShapeTextObject =getTextPath(TextObject,TextFontObject);
		if(TypeObject == "Text")SourceShapeObject =ShapeTextObject;
	resizeObject(0,0,0,0);
	}
}

void CGraphObject::setTextColorObject(const DWORD textcolor)
{
	TextColorObject.setRgba(textcolor);
	update();
}
//--------------------------------------------------------------------
void CGraphObject::setImageObjectFromFile(const QString &filename)
{
QPainterPath path;

	if(!filename.isEmpty())
	{
	prepareGeometryChange();
		ImageObject.load(filename);
		path.addRect(ImageObject.rect());
		SourceShapeObject =path;
		resizeObject(QRectF(x(),y(),SourceShapeObject.controlPointRect().width(),SourceShapeObject.controlPointRect().height()));
	update();
	}
}
//--------------------------------------------------------------------
void CGraphObject::setImageObjectFromBase64(const QString &imagebase64)
{
QPainterPath path;

	if(!imagebase64.isEmpty())
	{
	prepareGeometryChange();
		ImageObject =getImageFromBase64(imagebase64);
		path.addRect(ImageObject.rect());
		SourceShapeObject =path;
		resizeObject(QRectF(x(),y(),SourceShapeObject.controlPointRect().width(),SourceShapeObject.controlPointRect().height()));
	update();
	}
}
//--------------------------------------------------------------------
/* относительное изменение координат объекта */
void CGraphObject::resizeObject(qreal dX, qreal dY, qreal dW, qreal dH)
{
prepareGeometryChange(); // информирование сцены о предстоящем изменении элемента

	setX(x()+dX);
	setY(y()+dY);
	RectObject.setRect(x(),y(),RectObject.width()+dW,RectObject.height()+dH);	// новая геометрия объекта
/* подстройка грипа под объект */
	if(Grip)Grip->setGripArea(RectObject);
/* масштабирование вписанной фигуры под объект */
	ObjectScaleX =RectObject.width()/SourceShapeObject.controlPointRect().width();
	ObjectScaleY =RectObject.height()/SourceShapeObject.controlPointRect().height();
	ShapeObject =QTransform().scale(ObjectScaleX,ObjectScaleY).map(SourceShapeObject);
update();
}
//....................................................................
/* абсолютное изменение координат объекта */
void CGraphObject::resizeObject(const QRectF &rect)
{
prepareGeometryChange(); // информирование сцены о предстоящем изменении элемента

	setX(rect.x());
	setY(rect.y());
	RectObject.setRect(x(),y(),rect.width(),rect.height());	// новая геометрия объекта
/* подстройка грипа под объект */
	if(Grip)Grip->setGripArea(RectObject);
/* масштабирование вписанной фигуры под объект */
	ObjectScaleX =RectObject.width()/SourceShapeObject.controlPointRect().width();
	ObjectScaleY =RectObject.height()/SourceShapeObject.controlPointRect().height();
	ShapeObject =QTransform().scale(ObjectScaleX,ObjectScaleY).map(SourceShapeObject);
SourceRectObject =RectObject;
update();
}
//-------------------------------------------------------------------
int CGraphObject::getObjectStatusPos(const QPointF &posXY)
{
// mapFromScene - переводит координаты сцены в локальные координаты объекта
// т.е. 0 сцены -> 0 объекта
	if(Grip)
		return Grip->getGripStatusPos(mapFromScene(posXY));
return 0;
}
//-------------------------------------------------------------------
/* XY - относительно 0 сцены */
QString CGraphObject::getXML()
{
QString textparam ="";
QString imageparam ="";

	if(!TextObject.isEmpty())
	{
		textparam.sprintf("text ='%ls' textfont ='%ls' textsize ='%u' textcolor ='%u'",
						  TextObject.data(),
						  TextFontObject.family().data(),
						  TextSizeObject,
						  TextColorObject.rgba());
	}

	if(TypeObject == "Image")
	{
		imageparam.sprintf("image ='%ls'",getBase64FromImage().data());
	}

return QString().sprintf("<Object type ='%ls' name ='%ls' x ='%f' y ='%f' z ='%f' width ='%f' height ='%f' angle ='%f' color ='%u' %ls %ls/>",
						 TypeObject.data(),
						 NameObject.data(),
						 x(),
						 y(),
						 zValue(),
						 RectObject.width(),
						 RectObject.height(),
						 AngleObject,
						 ColorObject.rgba(),
						 textparam.data(),
						 imageparam.data());
}
//........................................................................
/* XY - относительно originXY (курсора) */
QString CGraphObject::getXML(QPointF originXY)
{
QString textparam ="";
QString imageparam ="";

	if(!TextObject.isEmpty())
	{
		textparam.sprintf("text ='%ls' textfont ='%ls' textsize ='%u' textcolor ='%u'",
						  TextObject.data(),
						  TextFontObject.family().data(),
						  TextSizeObject,
						  TextColorObject.rgba());
	}

	if(TypeObject == "Image")
	{
		imageparam.sprintf("image ='%ls'",getBase64FromImage().data());
	}

return QString().sprintf("<Object clipboard='true' type ='%ls' x ='%f' y ='%f' width ='%f' height ='%f' angle ='%f' color ='%u' %ls %ls/>",
						 TypeObject.data(),
						 x() - originXY.x(),
						 y() - originXY.y(),
						 RectObject.width(),
						 RectObject.height(),
						 AngleObject,
						 ColorObject.rgba(),
						 textparam.data(),
						 imageparam.data());
}
/*==============================================================================*/
/*									События										*/
/*==============================================================================*/
void CGraphObject::mousePressEvent(QGraphicsSceneMouseEvent *event)// начало модификации объекта
{
ModifyMODE =getObjectStatusPos(event->scenePos());
kProp =RectObject.height()/RectObject.width();

	switch(ModifyMODE)
	{
	case NORTH_WEST://
		GripClickXY	=RectObject.topLeft();
		break;
	case NORTH_EAST://
		GripClickXY	=RectObject.topRight();
		break;
	case SOUTH_EAST://
		GripClickXY	=RectObject.bottomRight();
		break;
	case SOUTH_WEST://
		GripClickXY	=RectObject.bottomLeft();
		break;
	case NORTH:
		GripClickXY	=QPointF(RectObject.center().x(),RectObject.top());
		break;
	case EAST:
		GripClickXY	=QPointF(RectObject.right(),RectObject.center().y());
		break;
	case SOUTH:
		GripClickXY	=QPointF(RectObject.center().x(),RectObject.bottom());
		break;
	case WEST:
		GripClickXY	=QPointF(RectObject.left(),RectObject.center().y());
		break;
	}
QGraphicsItem::mousePressEvent(event);
}
//...................................................................
void CGraphObject::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
int OverGripUnit;

	if(this->isSelected() && (OverGripUnit =getObjectStatusPos(event->scenePos())))
	{
	DWORD scenemode=0;
	if(SceneMode)scenemode= *SceneMode;
	/* просто меняет курсор над грип-юнитами */
		switch(scenemode)
		{
		case 1:		// вращение
			setCursor(QPixmap("://images/rotate_cursor.png"));
			break;
		default:	// геометрия
			setCursor(GRIP_CURSOR[OverGripUnit]);
		}
	}
	else
		setCursor(GRIP_CURSOR[NO_DIR]);
QGraphicsItem::hoverMoveEvent(event);
}
//...................................................................
void CGraphObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
DWORD scenemode=0;
if(SceneMode)scenemode= *SceneMode;

	if(this->isSelected())
	{
	QPointF deltaXY =event->scenePos() - event->lastScenePos();
		if(ModifyMODE)
		{
		//emit objectModify(this);
			if(scenemode == 0)
			{
			/* выбор действия */
				switch(ModifyMODE)
				{
				case NORTH_WEST://
					//resizeObject(deltaXY.x(),deltaXY.y(),-deltaXY.x(),-deltaXY.y());	// произвольный
					resizeObject(deltaXY.x(),deltaXY.x()*kProp,-deltaXY.x(),-deltaXY.x()*kProp);	// пропорциональный
					break;
				case NORTH_EAST://
					//resizeObject(0,deltaXY.y(),deltaXY.x(),-deltaXY.y());
					resizeObject(0,-deltaXY.x()*kProp,deltaXY.x(),deltaXY.x()*kProp);
					break;
				case SOUTH_EAST://
					//resizeObject(0,0,deltaXY.x(),deltaXY.y());
					resizeObject(0,0,deltaXY.x(),deltaXY.x()*kProp);
					break;
				case SOUTH_WEST://
					//resizeObject(deltaXY.x(),0,-deltaXY.x(),deltaXY.y());
					resizeObject(deltaXY.x(),0,-deltaXY.x(),-deltaXY.x()*kProp);
					break;
				case NORTH:
					resizeObject(0,deltaXY.y(),0,-deltaXY.y());
					break;
				case EAST:
					resizeObject(0,0,deltaXY.x(),0);
					break;
				case SOUTH:
					resizeObject(0,0,0,deltaXY.y());
					break;
				case WEST:
					resizeObject(deltaXY.x(),0,-deltaXY.x(),0);
					break;
				}
			}
			//..................................................
			if(scenemode == 1)
			{
				setAngleObject(getAngleBy3Points(RectObject.center(), GripClickXY, event->scenePos()));
			}
		return;	// блокировка передвижения объекта за мышью
		}
	resizeObject(deltaXY.x(),deltaXY.y(),0,0);
	}
QGraphicsItem::mouseMoveEvent(event);
}
//.......................................................................
void CGraphObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)// конец модификации
{
ModifyMODE =0;

QGraphicsItem::mouseReleaseEvent(event);
}
//--------------------------------------------------------------------------------------------
void CGraphObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
Q_UNUSED(widget); // не используемый параметр
QRadialGradient gradObj =GradientObject;
painter->setRenderHint(QPainter::Antialiasing);

	if(option->state & QStyle::State_MouseOver)
		gradObj.setColorAt(0.4, ColorObject.light(110));
//.........................................................................
painter->save();
	/* масштабируется сам инструмент рисования/заливка */
	painter->setTransform(QTransform(painter->transform()).scale(ObjectScaleX,ObjectScaleY));

	if(TypeObject == "Image")
	{
		painter->drawImage(QPointF(0, 0),ImageObject);
	}
	else
		painter->fillPath(SourceShapeObject, QBrush(gradObj));// заливка
painter->restore();
//	if(TypeObject == "Text")
//	{
//		QPen pen(Qt::black,0.5);
//		pen.setCosmetic(true);
//		painter->strokePath(SourceShapeObject,pen);		// контур
//	}

	if(TypeObject != "Text" && !TextObject.isEmpty())
	{
		painter->fillPath(ShapeTextObject,QBrush(TextColorObject));
	}
//.........................................................................
/* рисуем грип по клику */
	if(option->state & QStyle::State_Selected)
		if(Grip)Grip->drawGrip(painter);
}
//-------------------------------------------------------------------
/* ограничивающий прямоугольник объекта (примерная область рисования для paint) */
QRectF CGraphObject::boundingRect()const
{
QPainterPath path;
	path.addRect(ShapeTextObject.controlPointRect());
	path.addRect(0,0,RectObject.width(),RectObject.height());
return path.boundingRect();
}
//...................................................................
/* область мыши */
QPainterPath CGraphObject::shape()const
{
	if(isSelected())
	{
	QPainterPath path;
		path.addRect(QRectF(0,0,RectObject.width(),RectObject.height()));
	return path;
	}
return ShapeObject;
}
/*==================================================================*/
/*							Фигуры									*/
/*==================================================================*/
QPainterPath CGraphObject::getTrianglePath()	// bounding 100x100
{
QPainterPath	path;
	path.moveTo(0,100);
	path.lineTo(50,0);
	path.lineTo(100,100);
	path.lineTo(0,100);
	path.closeSubpath();
return path;
}
//---------------------------------------------
QPainterPath CGraphObject::getRectanglePath()	// bounding 100x100
{
QPainterPath	path;
	path.moveTo(0,0);
	path.lineTo(100,0);
	path.lineTo(100,100);
	path.lineTo(0,100);
	path.lineTo(0,0);
	path.closeSubpath();
return path;
}
//---------------------------------------------
QPainterPath CGraphObject::getCirclePath()	// bounding 100x100
{
QPainterPath	path;
	path.moveTo(100,50);
	path.arcTo(0,0,100,100,0,360);
	path.closeSubpath();
return path;
}
//---------------------------------------------
QPainterPath CGraphObject::getArrowPath()	// bounding 100x15
{
QPainterPath	path;
	path.moveTo(0,5);
	path.lineTo(80,5);
	path.lineTo(80,0);
	path.lineTo(100,7.5);
	path.lineTo(80,15);
	path.lineTo(80,10);
	path.lineTo(0,10);
	path.lineTo(0,5);
	path.closeSubpath();
return path;
}
//---------------------------------------------
QPainterPath CGraphObject::getTextPath(QString text, QFont font)	// bounding variable
{
QPainterPath path;
qreal y =0.0;
QStringList listtext;

/* QPainterPath не понимает переноса строк */
text.remove("\r");
listtext =text.split("\n");

	for(int c =0; c < listtext.size();c++)
	{
		if(!listtext.at(c).isEmpty())
		{
			y += getTextMetrics(listtext.at(c),font).height();

				path.addText(0, y, font, listtext.at(c));

			y +=(1.0);// межстрочный интервал
		}
	}
return path;
}
//....................................................................
QRectF	CGraphObject::getTextMetrics(const QString &text, const QFont &font)	// return QRectF(TextArea)
{
QPainterPath path;
	path.addText(QPointF(0,0),font,text);
return path.controlPointRect();
}
/***********************************************************************************
 * Возвращает угол в градусах (+/- 180)
 * между векторами выходящими из точки 'center'
 **********************************************************************************/
qreal CGraphObject::getAngleBy3Points(QPointF center, QPointF start, QPointF current)
{
QPointF A =center - start;						// координаты векторов
QPointF B =center - current;
qreal a =getVectorLength(A);					// длины векторов
qreal b =getVectorLength(B);
qreal mulAB =A.x() * B.x() + A.y() * B.y();		// скалярное произведение векторов
qreal cosAB =(mulAB)/(a * b);					// косинус угла между векторами
qreal k =A.y()/A.x();
qreal deltaY =B.y() - k * B.x(); // положение current точки относительно вектора A (локальная ось X)
if(A.x() >= 0)deltaY =(-deltaY); // для NW,SW,N,S,W

	if(deltaY > 0)
		return (qAcos(cosAB)*(-180.0/M_PI));	// угол в градусах (1,2 четверти)
	else
		return (qAcos(cosAB)*(180.0/M_PI));		// угол в градусах (3,4 четверти)
}
//.......................................................
qreal CGraphObject::getVectorLength(QPointF A, QPointF B)	// по координатам точек
{
return qSqrt(qPow((B - A).x(),2) + qPow((B - A).y(),2));
}

qreal CGraphObject::getVectorLength(QPointF vector)			// по координатам вектора
{
return qSqrt(qPow(vector.x(),2) + qPow(vector.y(),2));
}
/*==================================================================*/
/*					ГРИП объекта									*/
/*==================================================================*/
CGripUnit::CGripUnit(const QRectF *gripRect)
{

}

void CGripUnit::setGripUnit(const QRectF &gripRect, int direction)
{
	setRect(gripRect.x(),gripRect.y(),
			gripRect.width(),gripRect.height());

	gripUnitDir =(GRIP_DIR_TYPE)direction;
}
//------------------------------------------------------------------
CGripObject::CGripObject(const QGraphicsItem *parent):
	GripBorderClr(Qt::red),
	gripsClr(Qt::yellow),
	wgrip(5)
{
	setSize(parent->boundingRect().size());
	setGripStyle(GRIP_ROSE_STYLE);
}
//...................................................
void CGripObject::setGripStyle(GRIP_STYLE_TYPE style)
{
grips.clear();
GripViewStyle =style;

/* квадрат *//* ромб *//* роза */
	switch(GripViewStyle)
	{
	case GRIP_NO_STYLE:
		grips.resize(0);
		break;
	case GRIP_SQUARE_STYLE:
		grips.resize(4);
		break;
	case GRIP_ROMB_STYLE:
		grips.resize(4);
		break;
	case GRIP_ROSE_STYLE:
		grips.resize(8);
		break;
	}

	for(int c=0;c<grips.size();c++)
		grips[c] = new CGripUnit();

	setGripArea(this->toRect());
}
//..............................................
void CGripObject::setGripArea(const QRectF &area)
{
int i=0;
int mprX[] ={0,2,2,0,1,2,1,0}; // NW,NE,SE,SW,N,E,S,W
int mprY[] ={0,0,2,2,0,1,2,1};

qreal	kwX=0, kwY=0,
		w2 =(area.width()-wgrip)/2,
		h2 =(area.height()-wgrip)/2;

	if(area.width() < 0)
	{
		kwX=wgrip;
		w2=(area.width()+wgrip)/2;
	}
	if(area.height() < 0)
	{
		kwY=wgrip;
		h2=(area.height()+wgrip)/2;
	}

if(GripViewStyle == GRIP_ROMB_STYLE)i=4;
	setSize(area.size());

	for(int c=0;c<grips.size();c++,i++)
		grips[c].setGripUnit(QRectF(w2*mprX[i]-kwX,h2*mprY[i]-kwY,wgrip,wgrip),(i+1));
}
//..............................................
void CGripObject::drawGrip(QPainter *painter)
{
QPen pen(GripBorderClr,1,Qt::DotLine);
pen.setCosmetic(true); // исключение линий грипа из масштабирования сцены
painter->save();
	painter->setPen(pen);
	painter->drawRect(toRect());

	pen.setStyle(Qt::SolidLine);
	painter->setPen(pen);

	for(int c=0;c < grips.size();c++)
	{
		painter->fillRect(grips[c].toRect(),gripsClr);
		painter->drawRect(grips[c].toRect());
	}
painter->restore();
}
//--------------------------------------------------------------------------
int CGripObject::getGripStatusPos(const QPointF &posXY)
{
// mapFromScene - переводит координаты сцены в локальные координаты объекта
// т.е. 0 сцены -> 0 объекта

	/* проход по грипам */
	for(int c=0;c<grips.size();c++)
	{
		if(grips[c].contains(posXY))
			return grips[c].gripUnitDir;
	}
return 0;
}
//=============================================================================
