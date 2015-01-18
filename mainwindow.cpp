#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"
/*-------------------------------------------------------------------------*/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
/* Отрисовка "ручных" объектов формы */
ui->setupUi(this);
/****************************************************************************
							Диспетчер сигналов
****************************************************************************/
signalMapper = new QSignalMapper(this);
/*** Обработчик всех зарегитрированных в диспетчере сигналов ***/
connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(signalManager(int)));

/* Регистрация сигналов в диспетчере */
/* Сцена */
addSignalToMapper(ui->actionOpen, ACT_OPEN_SCENE,signalMapper);
addSignalToMapper(ui->actionSave, ACT_SAVE_SCENE,signalMapper);
addSignalToMapper(ui->actionSave_As, ACT_SAVE_AS_SCENE,signalMapper);
addSignalToMapper(ui->actionNew, ACT_CLR_SCENE,signalMapper);
/* режимы редактирования сцены */
addSignalToMapper(ui->actionGeometry, ACT_GEOMETRY_MODE,signalMapper);
addSignalToMapper(ui->actionRotate, ACT_ROTATE_MODE,signalMapper);
addSignalToMapper(ui->actionLink, ACT_LINK_MODE,signalMapper);
/* Объект  */
addSignalToMapper(ui->actionTriangle, ACT_ADD_TRIANGLE,signalMapper);
addSignalToMapper(ui->actionRectangle, ACT_ADD_RECTANGLE,signalMapper);
addSignalToMapper(ui->actionCircle, ACT_ADD_CIRCLE,signalMapper);
addSignalToMapper(ui->actionText, ACT_ADD_TEXT,signalMapper);
addSignalToMapper(ui->actionImage, ACT_ADD_IMAGE,signalMapper);
addSignalToMapper(ui->actionDelete, ACT_DEL,signalMapper);
/* буфер обмена */
addSignalToMapper(ui->actionCut, ACT_CUT_OBJECT,signalMapper);
addSignalToMapper(ui->actionCopy, ACT_COPY_OBJECT,signalMapper);
addSignalToMapper(ui->actionPaste, ACT_PASTE_OBJECT,signalMapper);
/* сигналы контексных меню */
actionImageChange =createNewAction("Change Image..",":/images/ChangeImage.png");
addSignalToMapper(actionImageChange, ACT_IMAGE_CHANGE,signalMapper);

actionColorChange =createNewAction("Change Color..",":/images/ChangeColor.png");
addSignalToMapper(actionColorChange, ACT_COLOR_CHANGE,signalMapper);

actionTextChange =createNewAction("Change Text..",":/images/ChangeText.png");
addSignalToMapper(actionTextChange, ACT_TEXT_CHANGE,signalMapper);

actionAngleChange =createNewAction("Change Angle..",":/images/ChangeAngle.png");
addSignalToMapper(actionAngleChange, ACT_ANGLE_CHANGE,signalMapper);

/* Создание слоя для компоновки объектов формы */
mainLayout= new QGridLayout(ui->centralWidget);
mainLayout->setContentsMargins(0, 0, 0, 0);
mainLayout->setObjectName(QStringLiteral("mainLayout"));
/* Создание сцены */
	scene =new CScene(this,QString("Scene"));
/* компоновка */
	scene->ViewScene->setFrameShadow(QFrame::Plain);
	scene->ViewScene->setLineWidth(2);
	scene->ViewScene->setFrameShape(QFrame::Panel);

mainLayout->addWidget(scene->ViewScene);
/* подключение сцены к сигналам/событиям */
connect(scene,SIGNAL(changedStatusXY(QPoint*)),this,SLOT(ChangeStatusXY(QPoint*)));
connect(ui->actionUndo,SIGNAL(triggered()),scene,SLOT(undo()));
connect(ui->actionRedo,SIGNAL(triggered()),scene,SLOT(redo()));
connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
connect(&scene->history,SIGNAL(setUndoRedoAvailable(UNDOREDO,bool)), this, SLOT(setUndoRedoAvailable(UNDOREDO,bool)));
connect(scene,SIGNAL(showContextMenuObject(CGraphObject*)), this, SLOT(showContextMenuObject(CGraphObject*)));
connect(ui->toolObject, SIGNAL(actionTriggered(QAction*)), scene, SLOT(resetSceneXY()));// чтоб объекты появлялись в <0,0> точке сцены а не за курсором
connect(ui->toolMode, SIGNAL(actionTriggered(QAction*)), scene, SLOT(resetSceneXY()));
/* добавление 'переключательного' фукционала кнопок режимов редактирования */
modeactiongroup = new QActionGroup(this);
modeactiongroup->addAction(ui->actionGeometry);
modeactiongroup->addAction(ui->actionRotate);
modeactiongroup->addAction(ui->actionLink);

scene->history.clear();
statusBar()->addPermanentWidget(ui->lblXY);
statusBar()->showMessage(tr("Ready"));
setCurrentFile("");
}
//...........................................................................
MainWindow::~MainWindow()
{
	delete ui;
}
//---------------------------------------------------------------------------
void MainWindow::signalManager(int idSignal)
{
CGraphObject *obj =scene->LastClickObject;
QColor color;
bool ok;
QStringList properties(QString(",,,,").split(","));// инициализация списка пустыми строками (ужас!)

	switch (idSignal)
	{
/* Действия над объектами */
	case ACT_ADD_TRIANGLE:
		scene->createObject(QString().sprintf("<Object type ='Triangle' x ='%f' y ='%f' color ='4283804415'/>",
											   scene->sceneXY.x(),
											   scene->sceneXY.y()));
		break;

	case ACT_ADD_RECTANGLE:
		scene->createObject(QString().sprintf("<Object type ='Rectangle' x ='%f' y ='%f' color ='4283804415'/>",
											   scene->sceneXY.x(),
											   scene->sceneXY.y()));
		break;

	case ACT_ADD_CIRCLE:
		scene->createObject(QString().sprintf("<Object type ='Circle' x ='%f' y ='%f' color ='4283804415'/>",
											   scene->sceneXY.x(),
											   scene->sceneXY.y()));
		break;

	case ACT_ADD_TEXT:
		scene->createObject(QString().sprintf("<Object type ='Text' x ='%f' y ='%f' color ='4283804415'/>",
											   scene->sceneXY.x(),
											   scene->sceneXY.y()));
		break;
	/* создание дефолтного объекта Image */
	case ACT_ADD_IMAGE:
		scene->createObject(QString().sprintf("<Object type ='Image' x ='%f' y ='%f'/>",
											   scene->sceneXY.x(),
											   scene->sceneXY.y()));
		break;

	case ACT_DEL:
		scene->deleteObject();
		break;
//................................
	case ACT_TEXT_CHANGE:
		properties =CTextDialog().getNewTextAndAttributes(&obj->TextObject,
														  &obj->TextFontObject,
														  &obj->TextColorObject);
		if (!properties[0].isEmpty())
		{
			scene->changePropertyObjects(0, "Text", properties);
		}
		break;

	case ACT_COLOR_CHANGE:
		/* инициализация диалога тем цветом объекта, по которому клик */
		if(!obj)return;
		color =QColorDialog::getColor(obj->ColorObject,0,"",QColorDialog::ShowAlphaChannel);
		if (!color.isValid())return;
		scene->changePropertyObjects(0, "Color", QStringList(QString().sprintf("%u",color.rgba())));
		break;

	case ACT_IMAGE_CHANGE:
		properties[0] =QFileDialog::getOpenFileName(this,
													tr("Choose image file.."),
													0,
													tr("Image Files (*.png; *.jpg; *.bmp);;All Files (*.*)"));
		if (!properties[0].isEmpty())
		{
			scene->changePropertyObjects(0, "Image", properties);
		}
		break;

	case ACT_ANGLE_CHANGE:
		properties[0].sprintf("%f",QInputDialog().getDouble(this,
															tr("Choose angle object.."),
															tr("Set new angle object:"),
															obj->AngleObject,-180.0,180.0,1,&ok));
		if (ok)
		{
			scene->changePropertyObjects(0, "Angle", properties);
		}
		break;
//................................
/* Действия над сценой */
	case ACT_CLR_SCENE:
		if(maybeSave())
		{
			scene->clear();
			scene->history.clear();
			setCurrentFile("");
		}
		break;

	case ACT_OPEN_SCENE:
		if(maybeSave())
		{
			loadScene();
			scene->history.clear();
		}
		break;

	case ACT_SAVE_SCENE:
		if(saveScene(FullFileName))
		{
			scene->history.clear();
		}
		break;

	case ACT_SAVE_AS_SCENE:
		if(saveScene(""))
		{
			scene->history.clear();
		}
		break;
//.........................
	case ACT_GEOMETRY_MODE:
		scene->SceneMode =GEOMETRY_EDIT;
		break;

	case ACT_ROTATE_MODE:
		scene->SceneMode =ROTATE_EDIT;
		break;

	case ACT_LINK_MODE:
		scene->SceneMode =LINK_EDIT;
		scene->createObject(QString().sprintf("<Object type ='Arrow' x ='%f' y ='%f' color ='4283804415'/>",
											   scene->sceneXY.x(),
											   scene->sceneXY.y()));
		break;
//.........................................
/* буфер обмена */
	case ACT_CUT_OBJECT:
		scene->cut(QApplication::clipboard());
		break;

	case ACT_COPY_OBJECT:
		scene->copy(QApplication::clipboard());
		break;

	case ACT_PASTE_OBJECT:
		scene->paste(QApplication::clipboard());
		break;
//........................................
	default:;
//qDebug() << "SignalsMgr: " << idSignal;
	}
}
//---------------------------------------------------------------------------
QAction* MainWindow::createNewAction(const QString &caption, const QString &icon)
{
QAction *act;
	act = new QAction(this);
	act->setText(caption);
	act->setIcon(QIcon(icon));
return act;
}
//..........................................................................
void MainWindow::addSignalToMapper(QAction *action,
								   SIGNALID idSignal,
								   QSignalMapper *mapper)
{
	mapper->setMapping(action, idSignal);						// присвоение идетификатора сигналу
	connect(action, SIGNAL(triggered()), mapper, SLOT(map()));	// перенаправление на диспетчер
}
//---------------------------------------------------------------------------
bool MainWindow::maybeSave()
{
	if (scene->isModified())
	{
	QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, ProgName,
								   tr("The scene has been modified.\n"
									  "Save changes?"),
								   QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
		if (ret == QMessageBox::Yes)
			return saveScene(FullFileName);
		else	if (ret == QMessageBox::Cancel)
					return false;
	}
return true;
}
//---------------------------------------------------------------------------
bool MainWindow::saveScene(const QString &fileName)
{
QString filename =fileName;

	if (filename.isEmpty())filename = QFileDialog::getSaveFileName(this,
																   tr("Save scene"),
																   0,
																   tr("XML Files (*.xml);;All Files (*.*)"));
	if (!filename.isEmpty())
	{
	QFile file(filename);
		if (file.open(QFile::WriteOnly|QFile::Text))
		{
			QTextStream out(&file);

			QApplication::setOverrideCursor(Qt::WaitCursor);
			out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
			out << scene->getSceneXML();
			QApplication::restoreOverrideCursor();

			setCurrentFile(filename);
		return true;
		}
		QMessageBox::warning(this, ProgName,tr("Cannot write file %1:\n%2.")
							 .arg(filename)
							 .arg(file.errorString()));
	}
return false;
}
//...........................................
bool MainWindow::loadScene()
{
QString fileName = QFileDialog::getOpenFileName(this,
												tr("Open scene"),
												0,
												tr("XML Files (*.xml);;All Files (*.*)"));
	if (!fileName.isEmpty())
	{
	QFile file(fileName);
		if (!file.open(QFile::ReadOnly | QFile::Text))
		{
			QMessageBox::warning(this,ProgName,
								 tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
		return false;
		}

		QTextStream in(&file);
		QApplication::setOverrideCursor(Qt::WaitCursor);
		scene->clear();
		/* Parse XML file */
		while(!in.atEnd())
		{
			scene->createObject(in.readLine());
		}
		scene->history.clear();
		QApplication::restoreOverrideCursor();

		setCurrentFile(fileName);
		statusBar()->showMessage(tr("CScene loaded"), 2000);
	}
return false;
}
//.........................................................
void MainWindow::setCurrentFile(const QString &filename)
{
FullFileName =filename;

	if (FullFileName.isEmpty())
		setWindowFilePath(ProgName + " - untitled.xml");
	else
		setWindowFilePath(ProgName + " - " + QFileInfo(FullFileName).fileName());
}
/************************************************************************************/
/*								События/Слоты										*/
/************************************************************************************/
void MainWindow::setUndoRedoAvailable(UNDOREDO undoredo,bool available)
{
	if(undoredo & UNDO)ui->actionUndo->setEnabled(available);
	if(undoredo & REDO)ui->actionRedo->setEnabled(available);

	if(ui->actionUndo->isEnabled())
		setWindowModified(true);
	else
		setWindowModified(false);
}
//...................................................... меню СЦЕНЫ
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
if(scene->LastClickPos != cursor().pos())return;// показать меню только если клик "на месте"
QMenu	menu;

	menu.addAction(ui->actionTriangle);
	menu.addAction(ui->actionRectangle);
	menu.addAction(ui->actionCircle);
	menu.addSeparator();
	menu.addAction(ui->actionPaste);

	menu.exec(event->globalPos());
}
//...................................................... меню ОБЪЕКТА
void MainWindow::showContextMenuObject(CGraphObject *obj)
{
if(scene->LastClickPos != cursor().pos())return;// показать меню только если клик "на месте"
QMenu	menu;

	if(obj->TypeObject == "Image")
		menu.addAction(actionImageChange);
	else
		menu.addAction(actionColorChange);
	menu.addAction(actionTextChange);
	menu.addAction(actionAngleChange);
	menu.addAction(ui->actionDelete);
	menu.addSeparator();
	menu.addAction(ui->actionCut);
	menu.addAction(ui->actionCopy);
	menu.addAction(ui->actionPaste);

	menu.exec(cursor().pos());
}
//----------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent*event)
{
	if (maybeSave())
		event->accept();
	else
		event->ignore();
}
//........................................................
void MainWindow::ChangeStatusXY(QPoint* pos)
{
	ui->lblXY->setText(QString("x =%1 : y =%2").arg(pos->x()).arg(pos->y()));
}
//---------------------------------------------------------------------------------



