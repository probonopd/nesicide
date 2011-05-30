#ifndef CODEEDITORFORM_H
#define CODEEDITORFORM_H

#include "cdesignereditorbase.h"
#include "iprojecttreeviewitem.h"

#include <Qsci/qsciscintilla.h>
#include "qscilexerca65.h"

enum
{
   Margin_Decorations = 0,
   Margin_LineNumbers
};

enum
{
   Marker_Breakpoint = 0,
   Marker_BreakpointDisabled,
   Marker_Execution,
   Marker_Error,
   Marker_Highlight
};

namespace Ui
{
class CodeEditorForm;
}

class CodeEditorForm : public CDesignerEditorBase
{
   Q_OBJECT
public:
   CodeEditorForm(QString fileName,QString sourceCode,IProjectTreeViewItem* link = 0,QWidget* parent = 0);
   ~CodeEditorForm();

   QString sourceCode();
   void setSourceCode(QString source);
   void showExecutionLine(int linenumber);
   void highlightLine(int linenumber);
   QString fileName() { return m_fileName; }
   void setReadOnly(bool readOnly) { m_scintilla->setReadOnly(readOnly); }

   virtual bool isModified() { return m_scintilla->isModified(); }
   virtual void setModified(bool modified) { m_scintilla->setModified(modified); }

protected:
   void changeEvent(QEvent *e);
   void contextMenuEvent(QContextMenuEvent *e);
   bool eventFilter(QObject *obj, QEvent *event);
   void timerEvent(QTimerEvent *e);

private:
   Ui::CodeEditorForm* ui;
   QString m_fileName;
   QsciScintilla* m_scintilla;
   QsciLexerCA65* m_lexer;
   int m_breakpointIndex;
   int m_timer;
   void updateToolTip(QString symbol);

signals:
   void breakpointsChanged();

public slots:
   void restyleText();

private slots:
   void editor_marginClicked(int margin,int line,Qt::KeyboardModifiers modifiers);
   void editor_linesChanged();
   void editor_modificationChanged(bool m);
   void editor_copyAvailable(bool yes);
   void external_breakpointsChanged();
   void compiler_compileStarted();
   void compiler_compileDone(bool ok);
   void emulator_emulatorStarted();
   void breakpointHit();
   void on_actionClear_marker_triggered();
   void on_actionEnd_marker_here_triggered();
   void on_actionStart_marker_here_triggered();
   void on_actionEnable_breakpoint_triggered();
   void on_actionRemove_breakpoint_triggered();
   void on_actionDisable_breakpoint_triggered();
   void on_actionRun_to_here_triggered();
   void on_actionBreak_on_CPU_execution_here_triggered();
};

#endif // CODEEDITORFORM_H
