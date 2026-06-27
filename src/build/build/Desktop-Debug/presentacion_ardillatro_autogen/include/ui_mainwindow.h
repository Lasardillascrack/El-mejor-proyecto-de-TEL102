/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayoutPrincipal;
    QHBoxLayout *layoutPaneles;
    QVBoxLayout *panelIzquierdo;
    QLabel *lblMarcadorGlobal;
    QLabel *lblEstadisticasMano;
    QLabel *lblManoYDescartes;
    QPushButton *btnAyudaManos;
    QSpacerItem *spacerIzquierdo;
    QListWidget *listManoVisual;
    QHBoxLayout *layoutBotones;
    QPushButton *btnJugarMano;
    QPushButton *btnDescartar;
    QPushButton *btnVerMazo;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(850, 550);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #111827; color: #f9fafb; font-family: 'Segoe UI', Arial;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutPrincipal = new QVBoxLayout(centralwidget);
        verticalLayoutPrincipal->setSpacing(15);
        verticalLayoutPrincipal->setObjectName(QString::fromUtf8("verticalLayoutPrincipal"));
        verticalLayoutPrincipal->setContentsMargins(20, 20, 20, 20);
        layoutPaneles = new QHBoxLayout();
        layoutPaneles->setSpacing(20);
        layoutPaneles->setObjectName(QString::fromUtf8("layoutPaneles"));
        panelIzquierdo = new QVBoxLayout();
        panelIzquierdo->setSpacing(12);
        panelIzquierdo->setObjectName(QString::fromUtf8("panelIzquierdo"));
        lblMarcadorGlobal = new QLabel(centralwidget);
        lblMarcadorGlobal->setObjectName(QString::fromUtf8("lblMarcadorGlobal"));
        lblMarcadorGlobal->setStyleSheet(QString::fromUtf8("font-size: 26px; font-weight: bold; color: #f43f5e;"));
        lblMarcadorGlobal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        panelIzquierdo->addWidget(lblMarcadorGlobal);

        lblEstadisticasMano = new QLabel(centralwidget);
        lblEstadisticasMano->setObjectName(QString::fromUtf8("lblEstadisticasMano"));
        lblEstadisticasMano->setMinimumSize(QSize(250, 0));
        lblEstadisticasMano->setStyleSheet(QString::fromUtf8("font-size: 15px; color: #38bdf8; background-color: #1f2937; padding: 12px; border-radius: 6px; border: 1px solid #374151;"));
        lblEstadisticasMano->setWordWrap(true);

        panelIzquierdo->addWidget(lblEstadisticasMano);

        lblManoYDescartes = new QLabel(centralwidget);
        lblManoYDescartes->setObjectName(QString::fromUtf8("lblManoYDescartes"));
        lblManoYDescartes->setStyleSheet(QString::fromUtf8("font-size: 15px; color: #a3e635; font-weight: 500;"));

        panelIzquierdo->addWidget(lblManoYDescartes);

        btnAyudaManos = new QPushButton(centralwidget);
        btnAyudaManos->setObjectName(QString::fromUtf8("btnAyudaManos"));
        btnAyudaManos->setStyleSheet(QString::fromUtf8("QPushButton { \n"
"    background-color: #000000; \n"
"    color: white; \n"
"    font-weight: bold; \n"
"    font-size: 14px; \n"
"    padding: 14px; \n"
"    border-radius: 6px; \n"
"    border: 1px solid #374151;\n"
"} \n"
"QPushButton:hover { \n"
"    background-color: #1f2937; \n"
"}"));

        panelIzquierdo->addWidget(btnAyudaManos);

        spacerIzquierdo = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        panelIzquierdo->addItem(spacerIzquierdo);


        layoutPaneles->addLayout(panelIzquierdo);

        listManoVisual = new QListWidget(centralwidget);
        listManoVisual->setObjectName(QString::fromUtf8("listManoVisual"));
        listManoVisual->setStyleSheet(QString::fromUtf8("background-color: #1f2937; border: 2px solid #4b5563; border-radius: 8px; font-size: 15px; color: #f3f4f6; padding: 8px;"));
        listManoVisual->setSelectionMode(QAbstractItemView::MultiSelection);

        layoutPaneles->addWidget(listManoVisual);


        verticalLayoutPrincipal->addLayout(layoutPaneles);

        layoutBotones = new QHBoxLayout();
        layoutBotones->setSpacing(12);
        layoutBotones->setObjectName(QString::fromUtf8("layoutBotones"));
        btnJugarMano = new QPushButton(centralwidget);
        btnJugarMano->setObjectName(QString::fromUtf8("btnJugarMano"));
        btnJugarMano->setCursor(QCursor(Qt::ArrowCursor));
        btnJugarMano->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #ef4444; color: white; font-weight: bold; font-size: 14px; padding: 14px; border-radius: 6px; } QPushButton:hover { background-color: #dc2626; }"));

        layoutBotones->addWidget(btnJugarMano);

        btnDescartar = new QPushButton(centralwidget);
        btnDescartar->setObjectName(QString::fromUtf8("btnDescartar"));
        btnDescartar->setCursor(QCursor(Qt::ArrowCursor));
        btnDescartar->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #f59e0b; color: white; font-weight: bold; font-size: 14px; padding: 14px; border-radius: 6px; } QPushButton:hover { background-color: #d97706; }"));

        layoutBotones->addWidget(btnDescartar);

        btnVerMazo = new QPushButton(centralwidget);
        btnVerMazo->setObjectName(QString::fromUtf8("btnVerMazo"));
        btnVerMazo->setCursor(QCursor(Qt::ArrowCursor));
        btnVerMazo->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #10b981; color: white; font-weight: bold; font-size: 14px; padding: 14px; border-radius: 6px; } QPushButton:hover { background-color: #059669; }"));

        layoutBotones->addWidget(btnVerMazo);


        verticalLayoutPrincipal->addLayout(layoutBotones);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Balatro Math Seminar - Engine v1.0", nullptr));
        lblMarcadorGlobal->setText(QCoreApplication::translate("MainWindow", "PUNTOS: 0 / 5000", nullptr));
        lblEstadisticasMano->setText(QCoreApplication::translate("MainWindow", "Fichas Base: 0 | Mult: x1 | Bonos: +0", nullptr));
        lblManoYDescartes->setText(QCoreApplication::translate("MainWindow", "Manos Restantes: 4 | Descartes: 3", nullptr));
        btnAyudaManos->setText(QCoreApplication::translate("MainWindow", "Ayuda: Manos", nullptr));
        btnJugarMano->setText(QCoreApplication::translate("MainWindow", "JUGAR MANO", nullptr));
        btnDescartar->setText(QCoreApplication::translate("MainWindow", "DESCARTAR SELECCI\303\223N", nullptr));
        btnVerMazo->setText(QCoreApplication::translate("MainWindow", "VER MAZO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
