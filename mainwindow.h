#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"
#include "dialogs.h"

namespace Ui
{
	class MainWindow;
}
/*	Идентификаторы сигналов в диспетчере */
enum SIGNALID
{
	ACT_ADD_RECTANGLE =1,
	ACT_ADD_TRIANGLE,
	ACT_ADD_CIRCLE,
	ACT_ADD_TEXT,
	ACT_ADD_IMAGE,
	ACT_DEL,
	ACT_TEXT_CHANGE,
	ACT_COLOR_CHANGE,
	ACT_IMAGE_CHANGE,
	ACT_ANGLE_CHANGE,
	ACT_CLR_SCENE,
	ACT_OPEN_SCENE,
	ACT_SAVE_SCENE,
	ACT_SAVE_AS_SCENE,
	ACT_GEOMETRY_MODE,
	ACT_ROTATE_MODE,
	ACT_LINK_MODE,

	ACT_CUT_OBJECT,
	ACT_COPY_OBJECT,
	ACT_PASTE_OBJECT
};

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	QString			ProgName="FunShapes";
private:
	Ui::MainWindow	*ui;
	QAction*		createNewAction(const QString &caption, const QString &icon="");
	void			addSignalToMapper(QAction *action, SIGNALID idSignal, QSignalMapper *mapper);
	void			setCurrentFile(const QString &filename);
	bool			maybeSave();
	QString			FullFileName;
	CScene			*scene;		/* активная сцена */
	QSignalMapper	*signalMapper;	// Диспетчер сигналов
	QGridLayout		*mainLayout;
	QActionGroup	*modeactiongroup;
	QAction			*actionColorChange;
	QAction			*actionTextChange;
	QAction			*actionImageChange;
	QAction			*actionAngleChange;
protected:
	void contextMenuEvent(QContextMenuEvent *event);
	void closeEvent(QCloseEvent *event);
public slots:
	void ChangeStatusXY(QPoint* pos);
	void setUndoRedoAvailable(UNDOREDO undoredo, bool available);
	void showContextMenuObject(CGraphObject *obj);
private slots:
	bool loadScene();
	bool saveScene(const QString &fileName);
	void signalManager(int idSignal);	// Обработка сигнала диспетчера
};
#endif // MAINWINDOW_H
