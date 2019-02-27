#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("QtDocmentationFormatTransfer-Esc");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* /*event*/)
{
    QRect rt = rect();
    rt = rt.marginsAdded(QMargins(-2, 0, -2, 0));
    ui->plainTextEdit->setGeometry(rt);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (Qt::Key_Escape != event->key()) return;

    if(makeFinalData())
        QMessageBox::information(this, "Err", "maek data failed!");

    dataToPlainTextEdit();
}

int MainWindow::makeFinalData()
{
    int res = -1;

    if ((res = excludeInheritedFromLine())) return res;
    excludeEmpty();
    replaceTabToSpace();
    ensureSpaceAfterStarChar();
    makeSpacesToSpace();
    ensuerNonSpaceStarSpaceFmt();

    QMap<QString, QStringList> mapCatData;
    CategorizeData(mapCatData);
    makeDesiredData(mapCatData);

    dataToPlainTextEdit();
    return SUC_ZERO;
}

int MainWindow::excludeInheritedFromLine()
{
    QString strTmp = ui->plainTextEdit->toPlainText();
    if (strTmp.isNull() || strTmp.isEmpty()) return 1;
    m_strLineTextList = strTmp.split("\n");

    for (int i = static_cast<int>(m_strLineTextList.size()) - 1; i >= 0; i--)
        if (-1 != m_strLineTextList[i].indexOf("inherited from"))
            m_strLineTextList.removeAt(i);

    return SUC_ZERO;
}

void MainWindow::excludeEmpty()
{
    for (int i = static_cast<int>(m_strLineTextList.size()) - 1; i >= 0; i--)
        if (m_strLineTextList[i].isEmpty() || '\t' == m_strLineTextList[i])
            m_strLineTextList.removeAt(i);
}

void MainWindow::replaceTabToSpace()
{   
    m_strLineTextList.replaceInStrings("\t", " ");
}

void MainWindow::makeSpacesToSpace()
{
    for (int i = 0; i < static_cast<int>(m_strLineTextList.size()); i++) {
        while (true)
            if (-1 != m_strLineTextList[i].indexOf("  "))
                m_strLineTextList[i].replace("  ", " ");
            else
                break;
    }

    for (int i = 0; i < static_cast<int>(m_strLineTextList.size()); i++) {
        if (!m_strLineTextList[i].isEmpty() && ' ' == m_strLineTextList[i][0])
            m_strLineTextList[i].remove(0, 1);
    }
}

void MainWindow::ensuerNonSpaceStarSpaceFmt()
{
    m_strLineTextList.replaceInStrings(" * ", "* ");
    m_strLineTextList.replaceInStrings(" *", "* ");
    m_strLineTextList.replaceInStrings("* >", "*>");
}

void MainWindow::CategorizeData(QMap<QString, QStringList> &mapCatData)
{
    //
    int iIdx = -1;
    QVector<int> vctHdrIdxs;
    foreach (QString strHdr, m_strHdrs) {
        iIdx = m_strLineTextList.indexOf(strHdr);
        if (-1 == iIdx) continue;
        vctHdrIdxs.append(iIdx);
    }

    //
    int iLoop = vctHdrIdxs.size();
    if (iLoop < 2) return;
    for (int i = 0; i < iLoop-1; i++)
        for (int j = i+1; j < iLoop; j++)
            if (vctHdrIdxs[i] == vctHdrIdxs[j])
                Q_ASSERT(0);
            else if (vctHdrIdxs[i] > vctHdrIdxs[j]) {
                int iTmp = vctHdrIdxs[i];
                vctHdrIdxs[i] = vctHdrIdxs[j];
                vctHdrIdxs[j] = iTmp;
            }

    //
    int iEnd = -1;
    for (int i = 0; i < iLoop; i++) {
        if (i == iLoop -1) iEnd = m_strLineTextList.size();
        else iEnd = vctHdrIdxs[i+1];

        for (int j = vctHdrIdxs[i]+1; j < iEnd; j++) {
            mapCatData[m_strLineTextList[vctHdrIdxs[i]]] << m_strLineTextList[j];
        }
    }
}

void MainWindow::makeDesiredData(QMap<QString, QStringList> &mapCatData)
{
    m_strLineTextList.clear();

    m_strLineTextList << "***"
                      << "`Version:` Qt 5.12.1, QtCreate 4.8.1"
                      << "`Declaration:`"
                      << "`Defination:`"
                      << "`Reference:`"
                      << "`Keyword:` \\[\\]"
                      << "***"
                      << "[TOC]"
                      << "***"
                      << "\n\n";

    m_strLineTextList << "# `Brief Introduction`"
                      << "\n\n"
                      << "# `Detailed Description`"
                      << "\n\n"
                      << "# `Data Struct`"
                      << "## `Type Declaration`"
                      << "```"
                      << "class Q_CORE_EXPORT QString"
                      << "{"
                      << "///> 0. Prepare"
                      << "///> 1. Properties"
                      << "///> 2. Constructor"
                      << "///> 3. Functions"
                      << "}"
                      << "```"
                      << "## `Constructor`"
                      << "```"
                      << "```"
                      << "## `Memory Model`"
                      << "```"
                      << "```"
                      << "\n\n";

    QString strFinalHdr, strFinalItem;
    foreach (QString strHdr, m_strHdrs)
    {
        for(QMap<QString, QStringList>::iterator it = mapCatData.begin(), itEnd = mapCatData.end(); it != itEnd; it++)
        {
            if (strHdr == it.key())
            {
                strFinalHdr = QString("# `%1`").arg(strHdr);
                m_strLineTextList << strFinalHdr;

                QStringList& strItems = it.value();
                foreach (QString strItem, strItems)
                {
                    strFinalItem = QString("###### `%1`").arg(strItem);
                    m_strLineTextList << strFinalItem;
                    if ("Macros" == strHdr) continue;
                    m_strLineTextList << "`Interpretation:`"
                                      << "`StorePosition:`"
                                      << "`Defualt:`"
                                      << "`Access:`"
                                      << "`Remark:`"
                                      << "`Eg 0:`";
                }

                m_strLineTextList << "\n\n";
            }
        }
    }
}

void MainWindow::ensureSpaceAfterStarChar()
{
    m_strLineTextList.replaceInStrings("*", "* ");
}

void MainWindow::dataToPlainTextEdit()
{
    m_strFinalText = m_strLineTextList.join("\n");

    ui->plainTextEdit->setPlainText(m_strFinalText);
}
