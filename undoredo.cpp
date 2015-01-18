#include "undoredo.h"
/*==================================================================*/
/* UNDOREDO - реализует базовые функции управления Undo/Redo стека	*/
/*						simpler == better							*/
/*==================================================================*/
CUndoRedo::CUndoRedo()
{
	clear();
}
//-------------------------------------------------------------------
void CUndoRedo::push(const QString &record)
{
	undoredoStack.resize(iRecord+1); // удаление истории выше индекса по стеку

	if(!record.isEmpty())
	{
		undoredoStack.append(record);
	}

	iRecord =undoredoStack.size()-1;// индекс на последнее/текущее состояние
CheckUndoRedoAvailability(REDO);
}
//-------------------------------------------------------------------
QString* CUndoRedo::popUndo()// извлекает из стека предидущую запись
{
CheckUndoRedoAvailability(UNDO);

	if(iRecord >= 0)
	{
		return(&undoredoStack[iRecord--]);	// сначала извлечь потом декремент
	}
return (NULL);
}
//...................................................................
QString* CUndoRedo::popRedo()// извлекает из стека следующую запись
{
CheckUndoRedoAvailability(REDO);

	if(iRecord < undoredoStack.size() && undoredoStack.size())
	{
		return(&undoredoStack[++iRecord]);	// сначала инкремент потом извлечь
	}
return (NULL);
}
//--------------------------------------------------------------
int CUndoRedo::getCurrentIndex()
{
return iRecord;
}
//--------------------------------------------------------------
void CUndoRedo::clear()
{
	iRecord=(-1);
	undoredoStack.clear();
CheckUndoRedoAvailability();
}
//--------------------------------------------------------------
int CUndoRedo::CheckUndoRedoAvailability(UNDOREDO undoredo)	// отправляет сигналы кнопкам формы
{														// в зависимости от состояния стека
	switch(undoredo)
	{
	case UNDO:
		if(iRecord <= 0)
		{
			emit setUndoRedoAvailable(UNDO,0);
		}
		emit setUndoRedoAvailable(REDO,1);
		break;

	case REDO:
		if(iRecord >= (undoredoStack.size()-2))
		{
			emit setUndoRedoAvailable(REDO,0);
		}
		emit setUndoRedoAvailable(UNDO,1);
		break;

	default:
		emit setUndoRedoAvailable(BOTH,0);
	}
}
//===============================================================

