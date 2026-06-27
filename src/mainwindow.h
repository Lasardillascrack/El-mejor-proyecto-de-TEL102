#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <algorithm>
#include "mazo.hpp"
#include "cartas.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnJugarMano_clicked();
    void on_btnDescartar_clicked();
    void on_btnVerMazo_clicked();
    void on_btnAyudaManos_clicked();

private:
    Ui::MainWindow *ui;

    // Backend del juego
    mazo mazo_permanente;
    mazo mazo_ronda;
    std::vector<carta*> mano_actual;

    // Estadísticas de la partida
    int nivel_actual;
    int puntos_actuales;
    int puntos_objetivo;
    int manos_restantes;
    int descartes_restantes;
    int multiplicador_global;
    int bonos_fichas;

    // Power-Ups (Comodines Matemáticos)
    bool powerup_primos = false;
    bool powerup_fibonacci = false;
    bool powerup_distributiva = false;
    bool powerup_exponencial = false;

    // Variables de apoyo para Fibonacci
    std::string ultima_mano_jugada = "";
    int indice_fibonacci = 1;

    // Funciones internas
    void iniciarPartida();
    void avanzarNivel();
    void rellenarMano();
    void actualizarTextosUI();
    void revisarFinDeJuego();
    // Nueva función para elegir comodín
    void mostrarPantallaPowerUps();
};

#endif // MAINWINDOW_H
