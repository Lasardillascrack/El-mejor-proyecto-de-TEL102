#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mano.hpp"
#include <cmath>
#include <QString>
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>

//  Verifica si un número es primo (Bono Primos)
bool esNumeroPrimo(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Genera la serie exacta solicitada (1, 2, 3, 5, 8, 13, 21...)
int calcularFibonacci(int n) {
    if (n <= 1) return 1;
    if (n == 2) return 2;
    int a = 1, b = 2;
    for (int i = 3; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iniciarPartida();
}

MainWindow::~MainWindow()
{
    for (carta* c : mano_actual) {
        delete c;
    }
    mano_actual.clear();
    delete ui;
}

void MainWindow::iniciarPartida()
{
    //Reiniciar todo desde cero (Solo ocurre al abrir el juego o perder)
    nivel_actual = 1;
    multiplicador_global = 1;
    bonos_fichas = 0;

    // RESETEAR POWER-UPS AL PERDER
    powerup_primos = false;
    powerup_fibonacci = false;
    powerup_distributiva = false;
    powerup_exponencial = false;
    ultima_mano_jugada = "";
    indice_fibonacci = 1;

    // Crear el mazo principal permanente
    mazo_permanente = mazo();
    llenar_mazo(mazo_permanente); // Las 52 cartas originales

    // Pasar al primer nivel
    avanzarNivel();
}


void MainWindow::avanzarNivel()
{
    // Limpiar mano visual y de memoria si quedó algo
    for (carta* c : mano_actual) {
        delete c;
    }
    mano_actual.clear();
    ui->listManoVisual->clear();

    // Configurar recursos del nivel
    puntos_actuales = 0;
    // Escalar la dificultad: 5000 en nivel 1, 10000 en nivel 2, etc.
    puntos_objetivo = 200*nivel_actual;
    manos_restantes = 4;
    descartes_restantes = 3;

    // Crear el mazo temporal para la ronda clonando el permanente
    std::vector<carta*> cartas_clonadas = mazo_permanente.clonar_mazo();
    mazo_ronda = mazo(); // Resetear el mazo de la ronda (el destructor limpia la memoria anterior si la hay)

    for(carta* c : cartas_clonadas) {
        mazo_ronda.agregar_carta(c);
    }

    mazo_ronda.barajar();

    rellenarMano();
    actualizarTextosUI();
}


void MainWindow::rellenarMano()
{
    // Robamos hasta tener 8 cartas sacando del mazo de la RONDA
    while (mano_actual.size() < 8) {
        carta* c = mazo_ronda.sacar_carta(); // Cambiado de mazo_juego a mazo_ronda
        if (c == nullptr) break;

        mano_actual.push_back(c);
        QString desc = QString::fromStdString(c->get_description());
        ui->listManoVisual->addItem(desc);
    }
}

void MainWindow::actualizarTextosUI()
{
    // Marcador principal
    ui->lblMarcadorGlobal->setText(QString("PUNTOS: %1 / %2")
                                       .arg(puntos_actuales)
                                       .arg(puntos_objetivo));

    // Estadísticas y buffos
    ui->lblEstadisticasMano->setText(QString("Fichas Base x Carta | Mult Global: x%1 | Bonos: +%2")
                                         .arg(multiplicador_global)
                                         .arg(bonos_fichas));

    // Descartes y Manos
    ui->lblManoYDescartes->setText(QString("Manos Restantes: %1 | Descartes: %2")
                                       .arg(manos_restantes)
                                       .arg(descartes_restantes));

    // Activar o desactivar botones según los recursos
    ui->btnJugarMano->setEnabled(manos_restantes > 0);
    ui->btnDescartar->setEnabled(descartes_restantes > 0);
}

void MainWindow::on_btnVerMazo_clicked()
{
    // 1. Preparamos los datos: copiamos el mazo permanente y obtenemos el de la ronda
    std::vector<carta*> copia_permanente = mazo_permanente.clonar_mazo();

    // 2. Creamos la ventana emergente
    QDialog dialog(this);
    dialog.setWindowTitle("Estado de los Mazos");
    dialog.resize(600, 500);
    dialog.setStyleSheet("background-color: #1f2937; color: #f3f4f6; font-size: 14px;");

    QHBoxLayout layoutHorizontal(&dialog);

    // --- Panel Mazo Permanente ---
    QVBoxLayout layoutPerm(&dialog);
    layoutPerm.addWidget(new QLabel("MAZO PERMANENTE (Inventario):"));
    QListWidget listaPerm(&dialog);
    for (carta* c : copia_permanente) {
        listaPerm.addItem(QString::fromStdString(c->get_description()));
        delete c; // Limpiamos el clon
    }
    layoutPerm.addWidget(&listaPerm);

    // --- Panel Mazo de Ronda (Cartas restantes ordenadas para inventario) ---
    std::vector<carta*> copia_ronda = mazo_ronda.clonar_mazo();

    // ORDENAMOS la copia por descripción antes de mostrarla
    std::sort(copia_ronda.begin(), copia_ronda.end(), [](carta* a, carta* b) {
        return a->get_description() < b->get_description();
    });

    QVBoxLayout layoutRonda(&dialog);
    layoutRonda.addWidget(new QLabel("MAZO DE RONDA (Cartas restantes):"));
    QListWidget listaRonda(&dialog);

    for (carta* c : copia_ronda) {
        listaRonda.addItem(QString::fromStdString(c->get_description()));
        delete c; // Limpiamos el clon
    }
    layoutRonda.addWidget(&listaRonda);

    // Agregamos ambos paneles al layout horizontal
    layoutHorizontal.addLayout(&layoutPerm);
    layoutHorizontal.addLayout(&layoutRonda);

    dialog.exec();
}

void MainWindow::on_btnJugarMano_clicked()
{
    QList<QListWidgetItem*> seleccionados = ui->listManoVisual->selectedItems();

    // --- LÍMITE DE 5 CARTAS ---
    if (seleccionados.size() > 5) {
        QMessageBox::warning(this, "Límite excedido", "Solo puedes seleccionar un máximo de 5 cartas por jugada.");
        return;
    }

    if (seleccionados.isEmpty()) return;

    std::vector<int> filas;
    for (auto item : seleccionados) {
        filas.push_back(ui->listManoVisual->row(item));
    }
    std::sort(filas.rbegin(), filas.rend());

    std::vector<carta*> cartas_jugadas;
    int fichas_cartas = 0;

    for (int fila : filas) {
        carta* c = mano_actual[fila];
        cartas_jugadas.push_back(c);
        fichas_cartas += c->calcular_puntaje();
    }

    // 1. Evaluar la jugada real usando la función
    PuntajeBalatro jugada = evaluar_mano(cartas_jugadas);

    int fichas_totales = fichas_cartas + jugada.fichas_base_jugada;
    int mult_final = jugada.mult_base_jugada * multiplicador_global;

    // --- NUEVO: TEXTO DINÁMICO PARA REPORTAR LOS PODERES ---
    QString reporte_poderes = "";

    // 2. POWER-UP: Sucesión de Fibonacci
    if (powerup_fibonacci) {
        if (jugada.nombre_jugada == ultima_mano_jugada) {
            indice_fibonacci++;
        } else {
            indice_fibonacci = 1;
            ultima_mano_jugada = jugada.nombre_jugada;
        }
        int mult_fibo = calcularFibonacci(indice_fibonacci);
        mult_final *= mult_fibo;
        reporte_poderes += QString("📈 Fibonacci (Racha %1): Mult x%2\n").arg(indice_fibonacci).arg(mult_fibo);
    }

    // 3. POWER-UP: Carta Exponencial (Ahora: Progresión Geométrica Controlada)
    if (powerup_exponencial) {
        std::map<PINTA, int> conteo_pintas;
        int max_pinta = 0;
        for (carta* c : cartas_jugadas) {
            conteo_pintas[c->get_pinta()]++;
            if (conteo_pintas[c->get_pinta()] > max_pinta) {
                max_pinta = conteo_pintas[c->get_pinta()];
            }
        }

        // Cada carta de la pinta dominante aporta +2 al multiplicador
        // Ejemplo: Si juegas 4 cartas de Picas, sumas +8 al mult.
        int bonus_mult = max_pinta * 2;
        mult_final += bonus_mult;

        reporte_poderes += QString("📈 Progresión Geométrica: +%1 al Mult\n").arg(bonus_mult);
    }

    // 4. POWER-UP: Números Primos
    if (powerup_primos) {
        if (esNumeroPrimo(fichas_totales)) {
            mult_final *= 2;
            reporte_poderes += QString("✨ ¡Bono Primo! (%1 es primo): Mult x2\n").arg(fichas_totales);
        } else {
            // Te avisa si calculaste mal mentalmente
            reporte_poderes += QString("❌ Bono Primo Fallido (%1 NO es primo)\n").arg(fichas_totales);
        }
    }

    // 5. POWER-UP: Propiedad Distributiva
    int puntaje_final = 0;
    if (powerup_distributiva) {
        puntaje_final = (fichas_totales + bonos_fichas) * mult_final;
        reporte_poderes += QString("✨ Propiedad Distributiva: Paréntesis añadido\n");
    } else {
        puntaje_final = (fichas_totales * mult_final) + bonos_fichas;
    }

    // Si no hay ningún poder activo, dejamos un texto limpio
    if (reporte_poderes.isEmpty()) {
        reporte_poderes = "Ningún Power-Up activo.\n";
    }

    puntos_actuales += puntaje_final;
    manos_restantes--;

    // Desplegar el pop-up inyectando el reporte de poderes que se armó
    QString desglose = QString("¡Jugada detectada: %1!\n\n"
                               "--- REPORTE MATEMÁTICO ---\n"
                               "%2\n"
                               "Cálculo Base: %3 Fichas x %4 Mult\n"
                               "Puntos ganados: +%5")
                           .arg(QString::fromStdString(jugada.nombre_jugada))
                           .arg(reporte_poderes)
                           .arg(fichas_totales)
                           .arg(mult_final)
                           .arg(puntaje_final);

    QMessageBox::information(this, "Ecuación Resuelta", desglose);

    // Borrar las cartas jugadas
    for (int fila : filas) {
        carta* c = mano_actual[fila];
        delete c;
        mano_actual.erase(mano_actual.begin() + fila);
        delete ui->listManoVisual->takeItem(fila);
    }

    rellenarMano();
    actualizarTextosUI();
    revisarFinDeJuego();
}

void MainWindow::on_btnDescartar_clicked()
{
    QList<QListWidgetItem*> seleccionados = ui->listManoVisual->selectedItems();

    // --- LÍMITE DE 5 CARTAS ---
    if (seleccionados.size() > 5) {
        QMessageBox::warning(this, "Límite excedido", "Solo puedes descartar un máximo de 5 cartas a la vez.");
        return;
    }

    if (seleccionados.isEmpty()) return;

    // Mismo proceso que al jugar, pero sin sumar puntos
    std::vector<int> filas;
    for (auto item : seleccionados) {
        filas.push_back(ui->listManoVisual->row(item));
    }
    std::sort(filas.rbegin(), filas.rend());

    for (int fila : filas) {
        carta* c = mano_actual[fila];
        delete c;
        mano_actual.erase(mano_actual.begin() + fila);
        delete ui->listManoVisual->takeItem(fila);
    }

    descartes_restantes--;
    rellenarMano();
    actualizarTextosUI();
}
void MainWindow::on_btnAyudaManos_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Tabla de Manos");
    dialog.resize(350, 400);
    dialog.setStyleSheet("background-color: #1f2937; color: #f3f4f6;");

    QVBoxLayout layout(&dialog);
    QListWidget listaAyuda(&dialog);

    // Definimos las manos igual que en tu evaluador
    QStringList manos;
    manos << "Escalera corrida: 100 x 8"
          << "Póker: 60 x 7"
          << "Full house: 40 x 4"
          << "Color: 35 x 4"
          << "Escalera: 30 x 4"
          << "Tercia: 30 x 3"
          << "Doble par: 20 x 2"
          << "Par: 10 x 2"
          << "Carta más alta: 5 x 1";

    listaAyuda.addItems(manos);
    layout.addWidget(new QLabel("Valores Base:"));
    layout.addWidget(&listaAyuda);

    dialog.exec();
}


void MainWindow::revisarFinDeJuego()
{
    if (puntos_actuales >= puntos_objetivo) {
        QMessageBox::information(this, "Nivel Superado", QString("¡Superaste el nivel %1!").arg(nivel_actual));
        nivel_actual++;

        // Verificamos si aún quedan poderes disponibles
        bool hay_poderes_disponibles = !(powerup_primos && powerup_fibonacci && powerup_distributiva && powerup_exponencial);

        if (hay_poderes_disponibles) {
            mostrarPantallaPowerUps();
        } else {
            // Si ya los tiene todos, pasamos directo al siguiente nivel
            avanzarNivel();
        }

    } else if (manos_restantes == 0) {
        QMessageBox::warning(this, "Derrota", "Te quedaste sin manos. Fin del juego.");
        iniciarPartida();
    }
}
void MainWindow::mostrarPantallaPowerUps()
{
    // Protección extra: si están todos activos, no abrir nada
    if (powerup_primos && powerup_fibonacci && powerup_distributiva && powerup_exponencial) {
        avanzarNivel();
        return;
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Elige tu Power-Up Matemático");
    dialog.setModal(true); // Obliga al jugador a elegir antes de continuar
    dialog.resize(400, 300);
    dialog.setStyleSheet("background-color: #1f2937; color: #f3f4f6; font-size: 14px;");

    QVBoxLayout layout(&dialog);

    // Crear los botones
    QPushButton* btnPrimos = new QPushButton("Bono Números Primos\n(Si la suma es prima, mult x2)", &dialog);
    QPushButton* btnFibo = new QPushButton("Sucesión de Fibonacci\n(Racha de la misma jugada aumenta mult)", &dialog);
    QPushButton* btnDistr = new QPushButton("Propiedad Distributiva\n(Suma bonos antes de multiplicar base)", &dialog);

    QPushButton* btnExpo = new QPushButton("Progresión Geométrica\n(+2 al Mult por cada carta de la pinta dominante)", &dialog);

    // NUEVO: Desactivamos botones si ya fueron elegidos
    btnPrimos->setEnabled(!powerup_primos);
    btnFibo->setEnabled(!powerup_fibonacci);
    btnDistr->setEnabled(!powerup_distributiva);
    btnExpo->setEnabled(!powerup_exponencial);

    // Estilo para que se vean bien
    QString estiloBtn = "QPushButton { background-color: #8b5cf6; padding: 15px; border-radius: 8px; font-weight: bold; color: white; } "
                        "QPushButton:hover { background-color: #7c3aed; }"
                        "QPushButton:disabled { background-color: #4b5563; color: #9ca3af; }";


    btnPrimos->setStyleSheet(estiloBtn);
    btnFibo->setStyleSheet(estiloBtn);
    btnDistr->setStyleSheet(estiloBtn);
    btnExpo->setStyleSheet(estiloBtn);

    layout.addWidget(btnPrimos);
    layout.addWidget(btnFibo);
    layout.addWidget(btnDistr);
    layout.addWidget(btnExpo);

    connect(btnPrimos, &QPushButton::clicked, [&]() { powerup_primos = true; dialog.accept(); });
    connect(btnFibo, &QPushButton::clicked, [&]() { powerup_fibonacci = true; dialog.accept(); });
    connect(btnDistr, &QPushButton::clicked, [&]() { powerup_distributiva = true; dialog.accept(); });
    connect(btnExpo, &QPushButton::clicked, [&]() { powerup_exponencial = true; dialog.accept(); });

    dialog.exec();
    avanzarNivel();
}
