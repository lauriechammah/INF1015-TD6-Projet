/**
 * Nom :         FenetreJeu.cpp
 * Description : Implémentation de l'interface graphique Qt
 * Auteurs :     Laurie Chammah, Marie-Josée Sarkis
 * Date :        21 avril 2026
 **/

#include "FenetreJeu.h"
#include "Roi.h"
#include "Tour.h"
#include "Cavalier.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QFont>

FenetreJeu::FenetreJeu(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Echecs — Fins de parties");
    initialiserPlateau();
    initialiserPieces();
    rafraichirAffichage();
}

void FenetreJeu::initialiserPlateau()
{
    auto* widgetCentral = new QWidget(this);
    auto* layoutPrincipal = new QVBoxLayout(widgetCentral);

    // Message en haut de la fenêtre
    labelMessage_ = new QLabel("Tour des blancs", this);
    labelMessage_->setAlignment(Qt::AlignCenter);
    labelMessage_->setFont(QFont("Arial", 14, QFont::Bold));
    layoutPrincipal->addWidget(labelMessage_);

    // Grille de l'échiquier
    auto* grille = new QGridLayout();
    grille->setSpacing(0);

    for (int ligne = 0; ligne < TAILLE; ++ligne) {
        for (int colonne = 0; colonne < TAILLE; ++colonne) {
            auto* bouton = new QPushButton(this);
            bouton->setFixedSize(TAILLE_CASE, TAILLE_CASE);
            bouton->setFont(QFont("Arial", 20, QFont::Bold));

            connect(bouton, &QPushButton::clicked, this,
                [=]() { caseCliquee(ligne, colonne); });

            cases_[ligne][colonne] = bouton;
            grille->addWidget(bouton, ligne, colonne);
        }
    }

    layoutPrincipal->addLayout(grille);
    setCentralWidget(widgetCentral);
    reinitialiserCouleurs();
}

void FenetreJeu::initialiserPieces()
{
    // Fin de partie : Roi + Tour vs Roi + Cavalier
    echiquier_.ajouterPiece(std::make_unique<Roi>(Position{0, 4}, false));     // Roi noir
    echiquier_.ajouterPiece(std::make_unique<Tour>(Position{0, 0}, false));    // Tour noire
    echiquier_.ajouterPiece(std::make_unique<Roi>(Position{7, 4}, true));      // Roi blanc
    echiquier_.ajouterPiece(std::make_unique<Cavalier>(Position{7, 6}, true)); // Cavalier blanc
}

void FenetreJeu::rafraichirAffichage()
{
    for (int ligne = 0; ligne < TAILLE; ++ligne) {
        for (int colonne = 0; colonne < TAILLE; ++colonne) {
            const Piece* piece = echiquier_.getPiece(Position{ligne, colonne});
            if (piece != nullptr)
                cases_[ligne][colonne]->setText(
                    QString::fromStdString(piece->getSymbole()));
            else
                cases_[ligne][colonne]->setText("");
        }
    }
}

void FenetreJeu::caseCliquee(int ligne, int colonne)
{
    if (caseSelectionnee_ == nullptr) {
        // Premier clic : sélectionner une pièce
        selectionnerCase(ligne, colonne);
    }
    else {
        // Deuxième clic : tenter le déplacement
        Position destination{ligne, colonne};
        bool succes = echiquier_.deplacerPiece(*caseSelectionnee_, destination);

        if (succes) {
            tourBlanc_ = !tourBlanc_;
            QString message = tourBlanc_ ? "Tour des blancs" : "Tour des noirs";

            if (echiquier_.estEnEchec(tourBlanc_))
                message += " — ÉCHEC !";

            afficherMessage(message);
        }
        else {
            afficherMessage("Mouvement invalide !");
        }

        deselectionner();
        rafraichirAffichage();
    }
}

void FenetreJeu::selectionnerCase(int ligne, int colonne)
{
    Position pos{ligne, colonne};
    const Piece* piece = echiquier_.getPiece(pos);

    if (piece == nullptr || piece->estBlanc() != tourBlanc_) {
        afficherMessage("Selectionnez une de vos pieces.");
        return;
    }

    caseSelectionnee_ = new Position{ligne, colonne};
    cases_[ligne][colonne]->setStyleSheet(
        "background-color: #6ecf6e; font-size: 20px;");
    surlignerCasesValides(pos);
}

void FenetreJeu::surlignerCasesValides(const Position& source)
{
    const Piece* piece = echiquier_.getPiece(source);
    if (piece == nullptr)
        return;

    for (int ligne = 0; ligne < TAILLE; ++ligne) {
        for (int colonne = 0; colonne < TAILLE; ++colonne) {
            Position dest{ligne, colonne};
            if (piece->estMouvementValide(dest, echiquier_) &&
                !(dest == source)) {
                cases_[ligne][colonne]->setStyleSheet(
                    "background-color: #aad4ff; font-size: 20px;");
            }
        }
    }
}

void FenetreJeu::deselectionner()
{
    delete caseSelectionnee_;
    caseSelectionnee_ = nullptr;
    reinitialiserCouleurs();
}

void FenetreJeu::reinitialiserCouleurs()
{
    for (int ligne = 0; ligne < TAILLE; ++ligne) {
        for (int colonne = 0; colonne < TAILLE; ++colonne) {
            cases_[ligne][colonne]->setStyleSheet(
                QString("background-color: %1; font-size: 20px;")
                    .arg(couleurCase(ligne, colonne)));
        }
    }
}

QString FenetreJeu::couleurCase(int ligne, int colonne) const
{
    return (ligne + colonne) % 2 == 0 ? "#f0d9b5" : "#b58863";
}

void FenetreJeu::afficherMessage(const QString& message)
{
    labelMessage_->setText(message);
}