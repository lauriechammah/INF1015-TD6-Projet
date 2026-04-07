/**
 * Nom :         FenetreJeu.h
 * Description : Interface graphique Qt pour l'échiquier
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#pragma once
#include "Echiquier.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

class FenetreJeu : public QMainWindow {
    Q_OBJECT

public:
    FenetreJeu(QWidget* parent = nullptr);

private slots:
    void caseCliquee(int ligne, int colonne);

private:
    static constexpr int TAILLE = 8;
    static constexpr int TAILLE_CASE = 70;

    Echiquier echiquier_;
    QPushButton* cases_[TAILLE][TAILLE] = {};
    QLabel* labelMessage_;

    Position* caseSelectionnee_ = nullptr;
    bool tourBlanc_ = true;

    void initialiserPlateau();
    void initialiserPieces();
    void rafraichirAffichage();
    void selectionnerCase(int ligne, int colonne);
    void deselectionner();
    void afficherMessage(const QString& message);
    void surlignerCasesValides(const Position& source);
    void reinitialiserCouleurs();
    QString couleurCase(int ligne, int colonne) const;
};