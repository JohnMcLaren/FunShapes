#ifndef UNDO_H
#define UNDO_H
#include <QtWidgets>

enum UNDOREDO
{
	NONE =0,
	UNDO =1,
	REDO =2,
	BOTH =3
};
//........................................................................................
class CUndoRedo : public QObject
{
	Q_OBJECT

public:
	CUndoRedo();
	void		push(const QString &record);// последовательно заполняет стек
	QString*	popUndo();				// извлекает запись вниз по стеку.
	QString*	popRedo();				// извлекает запись вверх по стеку.
	void		clear();				// очищает стек.
	int			getCurrentIndex();		// возвращает текущий индекс записи <исходный [-1]>
										// нужен для определения былили изменения на сцене
private:
	QVector	<QString>	undoredoStack;	// стек записей в произвольном текстовом формате
										// понятном движку разбора Undo/Redo команд.
	int		iRecord;					// текущий индекс записи
	int		CheckUndoRedoAvailability(UNDOREDO undoredo =BOTH); // метод проверяет доступность и отправляет сигналы кнопкам Undo/Redo
signals:
	void	setUndoRedoAvailable(UNDOREDO undoredo,bool available);
};
#endif // UNDO_H
