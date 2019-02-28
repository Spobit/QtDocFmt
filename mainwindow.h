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
    void head();
    void toc();
    void briefIntroduction();
    void detailedDescrition();
    void dataStuct();

    void properties();
    void publicTypes();
    void publicFunctions();
    void ReimplementedPublicFunctions();
    void publicSlots();
    void staticPublicMembers();

    void protectedTypes();
    void protectedFunctions();
    void ReimplementedProtectedFunctions();
    void protectedSlots();
    void staticProtectedMembers();

    void privateTypes();
    void privateTypesFunctions();
    void ReimplementedPrivateFunctions();
    void privateTypesSlots();
    void staticPrivateMembers();

    void signalsKey();
    void relatedNonMembers();
    void macros();

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
