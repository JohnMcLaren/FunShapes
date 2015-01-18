#ifndef SCENE_H
#define SCENE_H
#include <QtWidgets>
#include "object.h"
#include "undoredo.h"

enum SCENEMODE
{
	GEOMETRY_EDIT =0,
	ROTATE_EDIT,
	LINK_EDIT
};

class CScene : public QGraphicsScene
{
	Q_OBJECT // макрос нужен для работы механизма слотов/сигналов

public:
	CScene(QWidget *pParent, QString nameScene=0);
	~CScene();
	QString				getSceneXML();
	CGraphObject*		searchObjectByName(const QString &nameobject);
	QGraphicsView		*ViewScene;		/* указатель на объект отображения сцены (вид/окно) */
	QLabel				*Caption;
	QString				SceneName;
	QPointF				sceneXY;		/* координаты курсора в координатах сцены */
	CUndoRedo			history;
	bool				isModified();
	QPoint				LastClickPos;
	CGraphObject*		LastClickObject;
	DWORD				SceneMode =GEOMETRY_EDIT;
	QStringList			ListNameObjects;
private:
	int					idLastObject=0;
	QPoint				viewXY;
	QPoint				screenXY;
	QPointF				globalXY;
	CGraphObject*		getGraphObject(QPointF posXY,QTransform transformState);
protected:
	void			mousePressEvent(QGraphicsSceneMouseEvent *event);
	void			mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void			mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void			wheelEvent(QGraphicsSceneWheelEvent *event);
	void			contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	void			addItem(QGraphicsItem *item);
	void			removeItem(QGraphicsItem *item);
public slots:
	void			clear();
	void			createObject(const QString xmlObject);
	void			deleteObject(CGraphObject *obj=NULL);
	void			changePropertyObjects(CGraphObject *obj, QString property, QStringList listvalues);
	void			undo();
	void			redo();
	void			UndoRedoEngine(int undoredo, QString *record);
	void			cut(QClipboard *clipboard);
	void			copy(QClipboard *clipboard);
	void			paste(QClipboard *clipboard);
	void			resetSceneXY();
//	void			objectModify(CGraphObject *obj=NULL);
signals:
	void			changedStatusXY(QPoint *pos);
	void			showContextMenuObject(CGraphObject *obj);
};

#endif // SCENE_H
