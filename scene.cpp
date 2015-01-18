#include "scene.h"
#include "xmlparser.h"
#include "dialogs.h"
/********************************************************************************/
CScene::CScene(QWidget* pParent, QString nameScene)
{
/* сцена */
QGraphicsTextItem	*pTxtBackGround;

	setBackgroundBrush(QColor(238,254,255));
	pTxtBackGround =addText(nameScene,QFont("Bookman Old Style",100));
	pTxtBackGround->setDefaultTextColor(QColor(0,0,0,50));
	pTxtBackGround->setZValue(-1);
	ListNameObjects.clear();
	ListNameObjects << "";
	SceneName =nameScene;
/* вид сцены */
	ViewScene = new QGraphicsView(this,pParent); // (*сцена, *родитель)
	ViewScene->show();
/* надпись вида сцены */
	Caption	= new QLabel(nameScene,ViewScene);
	Caption->setFixedWidth(1000);
	history.clear();
}
//..................................
CScene::~CScene()
{
	clear();
	delete ViewScene;
}
/********************************************************************************/
/*								Методы/Слоты									*/
/********************************************************************************/
/* Обёртка/wrapper для родительского метода.
 * Обновление списка имён объектов после добавления нового объекта. */
void CScene::addItem(QGraphicsItem *item)
{
/* сначала вставить в сцену */
QGraphicsScene::addItem(item);

	int iObj =items().indexOf(item); // ищем куда сцена вставила

	if(item->data(0).toString() == "GraphObject")
		ListNameObjects.insert(iObj,((CGraphObject*)item)->NameObject);
	else
		ListNameObjects.insert(iObj,"");
}
//.................................................................................
/* Обёртка/wrapper для родительского метода.
 * Обновление списка имён объектов после удаления объекта. */
void CScene::removeItem(QGraphicsItem *item)
{
/* сначала удалить из списка имён */
	if(item->data(0).toString() == "GraphObject")
	{
	int iObj;
		if((iObj =ListNameObjects.indexOf(((CGraphObject*)item)->NameObject)) >= 0)
		{
			ListNameObjects.removeAt(iObj);
		}
	}
/* потом удаление со сцены */
QGraphicsScene::removeItem(item);
delete(item);
}
//--------------------------------------------------------------------------------
CGraphObject* CScene::searchObjectByName(const QString &nameobject)
{
int iObj;		// индекс объекта в списке сцены/списке имён

	/* поиск объекта по имени В списке имён объектов сцены */
	if((iObj =ListNameObjects.indexOf(nameobject)) >= 0)
	/* если найден по имени берём указатель на него */
		return ((CGraphObject*)items().value(iObj));
return NULL;
}
/*--------------------------------------------------------------------------------
								Ловушки Undo/Redo
--------------------------------------------------------------------------------*/
void CScene::undo()
{
QStringList listRec = history.popUndo()->split(";");

	for(int c=(listRec.size()-1);c >= 0;c--)
	{
		UndoRedoEngine(UNDO, &listRec[c]);
	}
}
//...................................................
void CScene::redo()
{
QStringList listRec = history.popRedo()->split(";");

	for(int c=0;c < listRec.size();c++)
	{
		UndoRedoEngine(REDO, &listRec[c]);
	}
}
/*********************************************************************************
- Движок Undo/Redo
- Формат разбираемой записи - <имя объекта, действие, параметры действия ... >
*********************************************************************************/
void CScene::UndoRedoEngine(int undoredo, QString *record)
{
	if(record)
	{
	QStringList listArg = record->split(",");
		if(listArg.size()>1)
		{
		CGraphObject* obj =searchObjectByName(listArg.at(0));
//.................................................................................
			/*** СОЗДАНИЕ ***/
			if(listArg.at(1) == "Create")
			{
				if(obj && undoredo == UNDO) // отменить Создание = Удалить
				{
					removeItem(obj);
				}
				else
				{
				obj = new CGraphObject(listArg.at(2),				// type
									   listArg.at(0),				// name
									   listArg.at(3).toDouble(),	// x
									   listArg.at(4).toDouble(),	// y
									   listArg.at(5).toDouble(),	// z
									   listArg.at(6).toDouble(),	// w
									   listArg.at(7).toDouble(),	// h
									   listArg.at(8).toDouble(),	// angle
									   listArg.at(9).toULong(),		// clr
									   listArg.at(10),				// text
									   listArg.at(11),				// textfont
									   listArg.at(12).toULong(),	// textsize
									   listArg.at(13).toULong(),	// textclr
									   listArg.at(14),				// image
									   &SceneMode);
					if(obj->IsValid)
					{
						//connect(obj,SIGNAL(objectModify(CGraphObject*)),this,SLOT(objectModify(CGraphObject*)));
						addItem(obj);
					}
					else
						removeItem(obj);
				}
			return;
			}
			/*** УДАЛЕНИЕ ***/
			if(listArg.at(1) == "Delete")
			{
				if(undoredo == UNDO) // отменить Удаление = Создать
				{
				obj = new CGraphObject(listArg.at(2),				// type
									   listArg.at(0),				// name
									   listArg.at(3).toDouble(),	// x
									   listArg.at(4).toDouble(),	// y
									   listArg.at(5).toDouble(),	// z
									   listArg.at(6).toDouble(),	// w
									   listArg.at(7).toDouble(),	// h
									   listArg.at(8).toDouble(),	// angle
									   listArg.at(9).toULong(),		// clr
									   listArg.at(10),				// text
									   listArg.at(11),				// textfont
									   listArg.at(12).toULong(),	// textsize
									   listArg.at(13).toULong(),	// textclr
									   listArg.at(14),				// image
									   &SceneMode);
					if(obj->IsValid)
					{
						//connect(obj,SIGNAL(objectModify(CGraphObject*)),this,SLOT(objectModify(CGraphObject*)));
						addItem(obj);
					}
					else
						removeItem(obj);
				}
				else
					if(obj)removeItem(obj);
			return;
			}
			/* выполнение следующих инструкций возможно только при существовании объекта */
			if(!obj)return;

			/*** ИЗМЕНЕНИЕ размера/положения ***/
			if(listArg.at(1) == "MoveResize")/* для этого действия разницы между Undo/Redo нет */
			{
				obj->resizeObject(QRectF(listArg.at(2).toDouble(),
										 listArg.at(3).toDouble(),
										 listArg.at(4).toDouble(),
										 listArg.at(5).toDouble()));
			return;
			}
			/*** ИЗМЕНЕНИЕ цвета ***/
			if(listArg.at(1) == "ColorChange")
			{
				obj->setColorObject(listArg.at(2).toULong());
				obj->update();
			return;
			}
			/*** ИЗМЕНЕНИЕ угла ***/
			if(listArg.at(1) == "AngleChange")
			{
				obj->setAngleObject(listArg.at(2).toDouble());
			return;
			}
			/*** ИЗМЕНЕНИЕ текста и его параметров ***/
			if(listArg.at(1) == "TextChange")
			{
				obj->setTextObject(&listArg.at(2));
			return;
			}
			if(listArg.at(1) == "TextFontChange")
			{
				obj->setTextFontObject(&listArg.at(2));
			return;
			}
			if(listArg.at(1) == "TextSizeChange")
			{
				obj->setTextSizeObject(listArg.at(2).toULong());
			return;
			}
			if(listArg.at(1) == "TextColorChange")
			{
				obj->setTextColorObject(listArg.at(2).toULong());
			return;
			}
			/*** ИЗМЕНЕНИЕ рисунка ***/
			if(listArg.at(1) == "ImageChange")
			{
				obj->setImageObjectFromBase64(listArg.at(2));
			return;
			}
//................................................................................
		}// check list
	}
}
//--------------------------------------------------------------------------------
void CScene::createObject(const QString xmlObject)
{
QString strChanges="";
CGraphObject* obj;
QString	tmpstr="";
QTextStream intxt(&QString().append(xmlObject));
QString textparam;
CXMLParser	parser;
QPointF CursorPosToScene =ViewScene->mapToScene(ViewScene->mapFromGlobal(ViewScene->cursor().pos()));

	while(!intxt.atEnd())
	{
	tmpstr.append(intxt.readLine());
	/* Создание объекта */
		if(parser.parse(tmpstr))
		{
		tmpstr ="";
			if(parser.attr.tag != "Object")continue;
			/* если имя объекта не задано */
			if(parser.attr.name == "")parser.attr.name =QString().sprintf("%ls%u",
																		  parser.attr.type.data(),
																		  idLastObject);
			/* если слой не задан */
			if(!parser.attr.z)parser.attr.z =idLastObject;
			/* если это вставка объекта из буфера обмена, значит координаты указаны относительно курсора */
			if(parser.attr.clipboard)
			{
				parser.attr.x += CursorPosToScene.x();
				parser.attr.y += CursorPosToScene.y();
			}
//.................................................
		obj = new CGraphObject(parser.attr.type,
							   parser.attr.name,
							   parser.attr.x,
							   parser.attr.y,
							   parser.attr.z,
							   parser.attr.width,
							   parser.attr.height,
							   parser.attr.angle,
							   parser.attr.color,
							   parser.attr.text,
							   parser.attr.textfont,
							   parser.attr.textsize,
							   parser.attr.textcolor,
							   parser.attr.image,
							   &SceneMode);

			if(obj->IsValid)	// если объект успешно создан
			{
				//connect(obj,SIGNAL(objectModify(CGraphObject*)),this,SLOT(objectModify(CGraphObject*)));
				addItem(obj);
				textparam.sprintf("%ls,%ls,%u,%u",
								  obj->TextObject.data(),
								  obj->TextFontObject.family().data(),
								  obj->TextSizeObject,
								  obj->TextColorObject.rgba());

				strChanges.append(QString().sprintf("%ls,%s,%ls,%f,%f,%f,%f,%f,%f,%u,%ls,%ls;",
													obj->NameObject.data(),
													"Create",
													obj->TypeObject.data(),
													obj->pos().x(),
													obj->pos().y(),
													obj->zValue(),
													obj->RectObject.width(),
													obj->RectObject.height(),
													obj->AngleObject,
													obj->ColorObject.rgba(),
													textparam.data(),
													obj->getBase64FromImage().data()));
			idLastObject++;
			}
			else
				delete obj;
		}
		else
			tmpstr.append("\n"); // продолежение тэга на следующей строке
	}

	if(!strChanges.isEmpty())history.push(strChanges);
}
//-------------------------------------------------------------------------------
void CScene::deleteObject(CGraphObject* obj)
{
QString strChanges="";
/* Удаление объекта */
	while(selectedItems().size() || obj) // пока есть выделенные или объект был задан
	{
	QString textparam;
	if(!obj)obj =(CGraphObject*)selectedItems().first();

		if(obj->data(0) == "GraphObject")
		{
			textparam.sprintf("%ls,%ls,%u,%u",
							  obj->TextObject.data(),
							  obj->TextFontObject.family().data(),
							  obj->TextSizeObject,
							  obj->TextColorObject.rgba());

			strChanges.append(QString().sprintf("%ls,%s,%ls,%f,%f,%f,%f,%f,%f,%u,%ls,%ls;",
												obj->NameObject.data(),
												"Delete",
												obj->TypeObject.data(),
												obj->x(),
												obj->y(),
												obj->zValue(),
												obj->RectObject.width(),
												obj->RectObject.height(),
												obj->AngleObject,
												obj->ColorObject.rgba(),
												textparam.data(),
												obj->getBase64FromImage().data()));
		removeItem(obj);
		}
	obj =NULL;
	}

	if(!strChanges.isEmpty())history.push(strChanges);
}
//-------------------------------------------------------------------------------
void CScene::changePropertyObjects(CGraphObject *obj, QString property, QStringList listvalues)
{
if(!selectedItems().size())return;
QString strChanges="";
int	idChanges=0;

	for(int c =0;(c < selectedItems().size()) || obj; c++, obj =NULL)
	{
	if(!obj)obj =(CGraphObject*)selectedItems().at(c);
//.........................................................................
		/*** изменение цвета объекта ***/
		if(property == "Color")
		{
		if(listvalues.at(0).isEmpty())return;
		if(obj->TypeObject == "Image")continue;
			/* цвет был */
			strChanges.append(QString().sprintf("%ls,%s,%u;",
												obj->NameObject.data(),
												"ColorChange",
												obj->ColorObject.rgba()));
			obj->setColorObject(listvalues.at(0).toULong());
			/* цвет стал */
			strChanges.append(QString().sprintf("%ls,%s,%u;",
												obj->NameObject.data(),
												"ColorChange",
												obj->ColorObject.rgba()));
		}
			else
		/*** изменение текста и атрибутов текста объекта ***/
		if(property == "Text")
		{
			idChanges =listvalues[0].toULong();

			if(idChanges & TEXT_CHANGED)
			{
				/* текст был */
				strChanges.append(QString().sprintf("%ls,%s,%ls;",
													obj->NameObject.data(),
													"TextChange",
													obj->TextObject.data()));
				obj->setTextObject(&listvalues[1]);
				/* текст стал */
				strChanges.append(QString().sprintf("%ls,%s,%ls;",
													obj->NameObject.data(),
													"TextChange",
													obj->TextObject.data()));
			}

			if(idChanges & TEXT_FONT_CHANGED)
			{
				/* шрифт был */
				strChanges.append(QString().sprintf("%ls,%s,%ls;",
													obj->NameObject.data(),
													"TextFontChange",
													obj->TextFontObject.family().data()));
				obj->setTextFontObject(&listvalues[2]);
				/* шрифт стал */
				strChanges.append(QString().sprintf("%ls,%s,%ls;",
													obj->NameObject.data(),
													"TextFontChange",
													obj->TextFontObject.family().data()));
			}

			if(idChanges & TEXT_SIZE_CHANGED)
			{
				/* размер был */
				strChanges.append(QString().sprintf("%ls,%s,%u;",
													obj->NameObject.data(),
													"TextSizeChange",
													obj->TextSizeObject));
				obj->setTextSizeObject(listvalues[3].toULong());
				/* размер стал */
				strChanges.append(QString().sprintf("%ls,%s,%u;",
													obj->NameObject.data(),
													"TextSizeChange",
													obj->TextSizeObject));
			}

			if(idChanges & TEXT_COLOR_CHANGED)
			{
				/* цвет текста был */
				strChanges.append(QString().sprintf("%ls,%s,%u;",
													obj->NameObject.data(),
													"TextColorChange",
													obj->TextColorObject.rgba()));
				obj->setTextColorObject(listvalues[4].toULong());
				/* цвет текста стал */
				strChanges.append(QString().sprintf("%ls,%s,%u;",
													obj->NameObject.data(),
													"TextColorChange",
													obj->TextColorObject.rgba()));
			}
		}
			else
		/*** изменение картинки объекта (только для объектов типа Image) ***/
		if(property == "Image")
		{
		if(listvalues.at(0).isEmpty())return;
		if(obj->TypeObject != "Image")continue;
			/* картинка была */
			strChanges.append(QString().sprintf("%ls,%s,%ls;",
												obj->NameObject.data(),
												"ImageChange",
												obj->getBase64FromImage().data()));

			obj->setImageObjectFromFile(listvalues.at(0));
			/* картинка стала */
			strChanges.append(QString().sprintf("%ls,%s,%ls;",
												obj->NameObject.data(),
												"ImageChange",
												obj->getBase64FromImage().data()));
		}
			else
		/*** изменение угла объекта ***/
		if(property == "Angle")
		{
			/* угол был */
			strChanges.append(QString().sprintf("%ls,%s,%f;",
												obj->NameObject.data(),
												"AngleChange",
												obj->AngleObject));

			obj->setAngleObject(listvalues.at(0).toDouble());
			/* угол стал */
			strChanges.append(QString().sprintf("%ls,%s,%f;",
												obj->NameObject.data(),
												"AngleChange",
												obj->AngleObject));
		}
//.........................................................................
	}

	if(!strChanges.isEmpty())history.push(strChanges);
}
//-------------------------------------------------------------------------------
QString CScene::getSceneXML()
{
CGraphObject* obj;
QString xmlScene="<Scene>\n";

	for(int c=items().size()-1;c>=0;c--)
	{
	obj =(CGraphObject*)items().at(c);
		if(obj && obj->data(0).toString()== "GraphObject")
			xmlScene.append("\t").append(obj->getXML().append("\n"));
	}
return xmlScene.append("</Scene>");
}
//-------------------------------------------------------------------------------
CGraphObject* CScene::getGraphObject(QPointF posXY,QTransform transformState)
{
CGraphObject *obj =(CGraphObject*)itemAt(posXY,transformState);

	if(obj && obj->data(0).toString()== "GraphObject")
		return obj;
return (NULL);
}
//-------------------------------------------------------------------------------
void CScene::cut(QClipboard *clipboard)
{

	if(selectedItems().size())
	{
	QString strClipboard ="";
	QPointF CursorPosToScene =ViewScene->mapToScene(ViewScene->mapFromGlobal(ViewScene->cursor().pos()));

		for(int c=0;c < selectedItems().size();c++)
		{
			CGraphObject *obj =(CGraphObject*)selectedItems().at(c);
			strClipboard.append(QString().sprintf("%ls\n",
												  obj->getXML(CursorPosToScene).data()));
		}

		if(!strClipboard.isEmpty())clipboard->setText(strClipboard);
	}

	deleteObject();
}
//.....................................................
void CScene::copy(QClipboard *clipboard)
{
	if(selectedItems().size())
	{
	QString strClipboard ="";
	QPointF CursorPosToScene =ViewScene->mapToScene(ViewScene->mapFromGlobal(ViewScene->cursor().pos()));

		for(int c=0;c < selectedItems().size();c++)
		{
			CGraphObject *obj =(CGraphObject*)selectedItems().at(c);
			strClipboard.append(QString().sprintf("%ls\n",
												  obj->getXML(CursorPosToScene).data()));
		}

		if(!strClipboard.isEmpty())clipboard->setText(strClipboard);
	}
}
//.....................................................
void CScene::paste(QClipboard *clipboard)
{
	createObject(clipboard->text());
}
//-----------------------------------------------------
bool CScene::isModified()
{
	if(history.getCurrentIndex() + 1)
		return true;
return false;
}
//-----------------------------------------------------
void CScene::resetSceneXY()
{
	sceneXY.setX(0);
	sceneXY.setY(0);
}
//-----------------------------------------------------
//void CScene::objectModify(CGraphObject *obj) // не используется
//{
//	if(obj)
//	{
//		switch(obj->ModifyMODE)
//		{
//		case NORTH_WEST:
//			break;
//		case NORTH_EAST:
//			break;
//		case SOUTH_EAST:
//			break;
//		case SOUTH_WEST:
//			break;
//		}
//	}
////LastClickPos =ViewScene->cursor().pos();
//}
//-------------------------------------------------------------------------------
void CScene::clear()
{
	while(items().size() > 1)
		removeItem(items().first());

idLastObject=0;
}
/********************************************************************************
							Обработчики событий
********************************************************************************/
void CScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
qreal kZoom =fabs(fabs(event->delta())/event->delta()-0.05f);
QTransform transform =ViewScene->transform();
	ViewScene->setTransform(transform.scale(kZoom,kZoom));
	//ViewScene->centerOn(event->scenePos());
}
//................................................................................
void CScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
CGraphObject *obj =getGraphObject(event->scenePos(),ViewScene->transform());

	if(obj)// если клик на объекте
	{
		obj->setSelected(true);
		emit showContextMenuObject(obj);	// сигнал форме
	return;
	}
QGraphicsScene::contextMenuEvent(event);
}
//................................................................................
void CScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
CGraphObject *obj =getGraphObject(event->scenePos(),ViewScene->transform());
LastClickPos =ViewScene->cursor().pos();
LastClickObject =obj;

	if(obj)
	{
		Caption->setText(QString("Current object: %1 - x=%2 : y=%3")
								 .arg(obj->NameObject)
								 .arg(obj->scenePos().x())
								 .arg(obj->scenePos().y()));

		for(int c =0;c < selectedItems().size();c++)
		{
			obj =(CGraphObject*)selectedItems().at(c);
			obj->SourceRectObject =obj->RectObject;
			obj->SourceAngleObject =obj->AngleObject;
		}
	}
	else
	{
		if(event->button() == Qt::LeftButton)ViewScene->setDragMode(QGraphicsView::ScrollHandDrag);
			else
		if(event->button() == Qt::RightButton)ViewScene->setDragMode(QGraphicsView::RubberBandDrag);
	}
QGraphicsScene::mousePressEvent(event);
}
//.................................................................................
void CScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
CGraphObject *obj;
QString		strChanges="";

	if(event->button() == Qt::LeftButton)
	{
	/* для всех выделенных */
		for(int c =0;c < selectedItems().size();c++)
		{
			obj =(CGraphObject*)selectedItems().at(c);
			/* если были изменения геометрии */
			if(obj->SourceRectObject != QRectF(obj->x(),obj->y(),obj->RectObject.width(),obj->RectObject.height()))
			{
				/* исходное положение */
				strChanges.append(QString().sprintf("%ls,%s,%f,%f,%f,%f;",
													obj->NameObject.data(),
													"MoveResize",
													obj->SourceRectObject.x(),
													obj->SourceRectObject.y(),
													obj->SourceRectObject.width(),
													obj->SourceRectObject.height()));
				/* новое положение */
				strChanges.append(QString().sprintf("%ls,%s,%f,%f,%f,%f;",
													obj->NameObject.data(),
													"MoveResize",
													obj->x(),
													obj->y(),
													obj->RectObject.width(),
													obj->RectObject.height()));
			obj->RectObject.setRect(obj->x(),obj->y(),obj->RectObject.width(),obj->RectObject.height());
			}
			/* если были изменения угла */
			if(obj->AngleObject != obj->SourceAngleObject)
			{
				/* угол был */
				strChanges.append(QString().sprintf("%ls,%s,%f;",
													obj->NameObject.data(),
													"AngleChange",
													obj->SourceAngleObject));
				/* угол стал */
				strChanges.append(QString().sprintf("%ls,%s,%f;",
													obj->NameObject.data(),
													"AngleChange",
													obj->AngleObject));
			}
		}
	}

	if(!strChanges.isEmpty())history.push(strChanges);

	ViewScene->setDragMode(QGraphicsView::NoDrag);
QGraphicsScene::mouseReleaseEvent(event);
}
//.................................................................................
void CScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
globalXY	=event->pos();
screenXY	=event->screenPos();
viewXY		=ViewScene->mapFromGlobal(screenXY);
sceneXY		=event->scenePos(); // относительно <0,0> сцены
CGraphObject *obj =getGraphObject(sceneXY,ViewScene->transform());

	if(obj)
	{
		Caption->setText(QString("Current object: %1 - x=%2 : y=%3")
						 .arg(obj->NameObject)
						 .arg(sceneXY.x())
						 .arg(sceneXY.y()));

		if(obj->isSelected())
		{
			Caption->setText(Caption->text().append(" <selected>"));
		}
	}

emit changedStatusXY(&viewXY);
QGraphicsScene::mouseMoveEvent(event);
}
//................................................................................


