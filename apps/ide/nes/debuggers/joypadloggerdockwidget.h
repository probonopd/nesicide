#ifndef JOYPADLOGGERDOCKWIDGET_H
#define JOYPADLOGGERDOCKWIDGET_H

#include "cdebuggerbase.h"

#include "panzoomrenderer.h"

#include "debuggerupdatethread.h"

namespace Ui {
   class JoypadLoggerDockWidget;
}

class JoypadLoggerDockWidget : public CDebuggerBase
{
   Q_OBJECT

public:
   explicit JoypadLoggerDockWidget(QWidget *parent = 0);
   virtual ~JoypadLoggerDockWidget();

protected:
   void showEvent(QShowEvent* event);
   void hideEvent(QHideEvent* event);
   void changeEvent(QEvent* e);

public slots:
   void renderData();
   void updateTargetMachine(QString target);

private slots:
   void on_showVisible_toggled(bool checked);
   void on_updateScanline_editingFinished();

private:
   Ui::JoypadLoggerDockWidget *ui;
   char* imgData;
   PanZoomRenderer* renderer;
   DebuggerUpdateThread* pThread;
   QPoint pressPos;
};

#endif // JOYPADLOGGERDOCKWIDGET_H
