#ifndef CHRROMDISPLAYDIALOG_H
#define CHRROMDISPLAYDIALOG_H

#include "cdesignereditorbase.h"
#include "panzoomrenderer.h"

#include "iprojecttreeviewitem.h"

#include "emulator_core.h"

#include "debuggerupdatethread.h"

namespace Ui
{
class CHRROMDisplayDialog;
}

class CHRROMDisplayDialog : public CDesignerEditorBase
{
   Q_OBJECT
public:
   CHRROMDisplayDialog(bool usePPU,qint8* data,IProjectTreeViewItem* link = 0,QWidget* parent = 0);
   virtual ~CHRROMDisplayDialog();

protected:
   qint8 chrrom[MEM_8KB];

protected:
   void changeEvent(QEvent* event);
   void showEvent(QShowEvent* event);
   void hideEvent(QHideEvent* event);

private:
   Ui::CHRROMDisplayDialog* ui;
   char* imgData;
   bool m_usePPU;
   DebuggerUpdateThread* pThread;
   PanZoomRenderer* renderer;
   QPoint pressPos;

public slots:
   void renderData();
   void repaintNeeded();

private slots:
   void on_exportPushButton_clicked();
   void on_updateScanline_editingFinished();
   void applyProjectPropertiesToTab();
};

#endif // CHRROMDISPLAYDIALOG_H
