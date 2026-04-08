/**
 * Nom :         FenetreJeu.cpp
 * Description : Implementation de l'interface graphique Qt pour l'echiquier
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

#include "FenetreJeu.hpp"
#include "Roi.hpp"
#include "Tour.hpp"
#include "Cavalier.hpp"
#include <QMessageBox>

namespace vue {

FenetreJeu::FenetreJeu(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Jeu d'echecs");
    initialiserPlateau();
    initialiserPieces();
    rafraichirAffichage();
}

void FenetreJeu::initialiserPlateau()
{
    auto* widgetCentral = new QWidget(this);
    auto* layoutPrincipal = new QVBoxLayout(widgetCentral);
    auto* grille = new QGridLayout();
    grille->setSpacing(0);

    for (int ligne = 0; ligne < TAILLE; ++ligne) {
        for (int col = 0; col < TAILLE; ++col) {
            auto* bouton = new QPushButton(this);
            bouton->setFixedSize(TAILLE_CASE, TAILLE_CASE);

            QFont font("DejaVu Sans", 50);
            bouton->setFont(font);

            bouton->setStyleSheet(
                "QPushButton { background-color: " + couleurCase(ligne, col) + "; "
                "border: none; "
                "color: black; }"
            );

            // bouton->setStyleSheet("background-color: " + couleurCase(ligne, col) + ";");
            // QFont font = bouton->font();
            // font.setPointSize(24);
            // bouton->setFont(font);

            int l = ligne, c = col;
            connect(bouton, &QPushButton::clicked, this, [this, l, c]() {
                caseCliquee(l, c);
            });

            cases_[ligne][col] = bouton;
            grille->addWidget(bouton, ligne, col);
        }
    }

    labelMessage_ = new QLabel("Tour des blancs", this);
    labelMessage_->setAlignment(Qt::AlignCenter);
    QFont fontLabel;
    // QFont fontLabel = labelMessage_->font();
    fontLabel.setPointSize(14);
    labelMessage_->setFont(fontLabel);

    layoutPrincipal->addLayout(grille);
    layoutPrincipal->addWidget(labelMessage_);
    setCentralWidget(widgetCentral);
}

void FenetreJeu::initialiserPieces()
{
    try 
    {
        echiquier_.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{0, 0}, false));
        echiquier_.ajouterPiece(std::make_unique<modele::Cavalier>(modele::Position{0, 1}, false));
        echiquier_.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{0, 4}, false));
        echiquier_.ajouterPiece(std::make_unique<modele::Cavalier>(modele::Position{0, 6}, false));
        echiquier_.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{0, 7}, false));

        echiquier_.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{7, 0}, true));
        echiquier_.ajouterPiece(std::make_unique<modele::Cavalier>(modele::Position{7, 1}, true));
        echiquier_.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{7, 4}, true));
        echiquier_.ajouterPiece(std::make_unique<modele::Cavalier>(modele::Position{7, 6}, true));
        echiquier_.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{7, 7}, true));
    }
    catch (const modele::RoiEnTropException& e) 
    {
        QMessageBox::critical(this, "Erreur - Trop de rois", e.what());
    }
}

void FenetreJeu::rafraichirAffichage()
{
    reinitialiserCouleurs();

    for (int ligne = 0; ligne < TAILLE; ++ligne) {
        for (int col = 0; col < TAILLE; ++col) {
            const modele::Piece* piece = echiquier_.getPiece(modele::Position{ligne, col});
            if (piece != nullptr)
            {
                cases_[ligne][col]->setText(QString::fromStdString(piece->getSymbole()));
                QString couleurTexte = piece->estBlanc() ? "white" : "black";
                cases_[ligne][col]->setStyleSheet(
                    "QPushButton { background-color: " + couleurCase(ligne, col) + "; "
                    "border: none; "
                    "color: " + couleurTexte + "; "
                    "font-size: 40px; }"
                );
            } else {
                cases_[ligne][col]->setText("");
            }
        }
    }
}

void FenetreJeu::caseCliquee(int ligne, int colonne)
{
    selectionnerCase(ligne, colonne);
}

void FenetreJeu::selectionnerCase(int ligne, int colonne)
{
    modele::Position pos{ligne, colonne};

    if (caseSelectionnee_ == nullptr) {
        const modele::Piece* piece = echiquier_.getPiece(pos);
        if (piece != nullptr && piece->estBlanc() == tourBlanc_) {
            caseSelectionnee_ = new modele::Position(pos);
            surlignerCasesValides(pos);
            cases_[ligne][colonne]->setStyleSheet("background-color: #aaf;");
        }
    }
    else {
        modele::Position source = *caseSelectionnee_;
        bool reussi = echiquier_.deplacerPiece(source, pos);

        if (reussi) {
            tourBlanc_ = !tourBlanc_;
            afficherMessage(tourBlanc_ ? "Tour des blancs" : "Tour des noirs");

            if (echiquier_.estEnEchec(tourBlanc_))
                afficherMessage((tourBlanc_ ? "Blancs" : "Noirs") + QString(" en echec !"));
        }
        else {
            afficherMessage("Mouvement invalide !");
        }

        deselectionner();
        rafraichirAffichage();
    }
}

void FenetreJeu::deselectionner()
{
    delete caseSelectionnee_;
    caseSelectionnee_ = nullptr;
    reinitialiserCouleurs();
}

void FenetreJeu::afficherMessage(const QString& message)
{
    labelMessage_->setText(message);
}

void FenetreJeu::surlignerCasesValides(const modele::Position& source)
{
    const modele::Piece* piece = echiquier_.getPiece(source);
    if (piece == nullptr) return;

    for (int ligne = 0; ligne < TAILLE; ++ligne) {
        for (int col = 0; col < TAILLE; ++col) {
            modele::Position dest{ligne, col};
            if (piece->estMouvementValide(dest, echiquier_))
                cases_[ligne][col]->setStyleSheet("background-color: #afa;");
        }
    }
}

void FenetreJeu::reinitialiserCouleurs()
{
    for (int ligne = 0; ligne < TAILLE; ++ligne)
        for (int col = 0; col < TAILLE; ++col)
            cases_[ligne][col]->setStyleSheet(
                "QPushButton { background-color: " + couleurCase(ligne, col) + "; "
                "border: none; color: black; font-size: 36px; }"
            );
}

QString FenetreJeu::couleurCase(int ligne, int colonne) const
{
    return ((ligne + colonne) % 2 == 0) ? "#f0d9b5" : "#b58863";
}

}