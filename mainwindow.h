#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

namespace Ui {
class MainWindow;
}

#define SUC_ZERO 0

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void resizeEvent(QResizeEvent *) override;

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

    int makeFinalData();

    //
    int excludeInheritedFromLine();
    void excludeEmpty();
    void replaceTabToSpace();
    void ensureSpaceAfterStarChar();
    void makeSpacesToSpace();
    void ensuerNonSpaceStarSpaceFmt();

    //
    void CategorizeData(QMap<QString, QStringList>& mapCatData);

    //
    void makeDesiredData(QMap<QString, QStringList>& mapCatData);

    //
    void dataToPlainTextEdit();

private:
    Ui::MainWindow *ui;
    QString m_strFinalText;
    QStringList m_strLineTextList;

    const QStringList m_strHdrs = {
    "Properties",

    "Public Types",
    "Public Functions",
    "Reimplemented Public Functions",
    "Public Slots",
    "Static Public Members",

    "Protected Types",
    "Protected Functions",
    "Reimplemented Protected Functions",
    "Protected Slots",
    "staitc Protected Members",

    "Private Types",
    "Private Functions",
    "Private Slots",
    "Static Private Members",

    "Signals",
    "Related Non-Members",
    "Macros"
    };
};

#endif // MAINWINDOW_H
