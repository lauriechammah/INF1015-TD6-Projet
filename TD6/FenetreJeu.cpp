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
#include <QApplication>
#include <QInputDialog>

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

            QFont policeDefaut = QApplication::font(); 
            policeDefaut.setPointSize(50);
            bouton->setFont(policeDefaut);

            bouton->setStyleSheet(
                "QPushButton { background-color: " + couleurCase(ligne, col) + "; "
                "border: none; "
                "color: black; }"
            );

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
    fontLabel.setPointSize(16);
    labelMessage_->setFont(fontLabel);

    auto* boutonReset = new QPushButton("Nouvelle Partie", this);
    boutonReset->setFixedHeight(40);
    boutonReset->setStyleSheet(
        "QPushButton { "
        "  background-color: #e1e1e1; "
        "  border: 1px solid #8f8f91; "
        "  border-radius: 3px; "
        "  padding: 3px; "
        "  font-size: 12px; "
        "  color: black; "
        "} "
        "QPushButton:pressed { background-color: #d1d1d1; }"
    );

    connect(boutonReset, &QPushButton::clicked, this, &FenetreJeu::initialiserPieces);

    layoutPrincipal->addLayout(grille);
    layoutPrincipal->addWidget(labelMessage_);
    layoutPrincipal->addWidget(boutonReset);
    setCentralWidget(widgetCentral);
}


void FenetreJeu::initialiserPieces()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Configuration");
    dialog.setMinimumSize(300, 150);

    auto* layout = new QVBoxLayout(&dialog);
    auto* label = new QLabel("Choisir une position :", &dialog);
    auto* comboBox = new QComboBox(&dialog);
    comboBox->addItems({ "Partie Standard", "Duel de Rois (Test)", "Fin de partie (Tours)" });

    auto* boutons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    connect(boutons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(boutons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    layout->addWidget(label);
    layout->addWidget(comboBox);
    layout->addWidget(boutons);

    if (dialog.exec() != QDialog::Accepted)
        return;

    QString choix = comboBox->currentText();

    echiquier_.vider();

    try
    {
        if (choix == "Partie Standard")
            echiquier_.chargerPartieStandard();
        else if (choix == "Duel de Rois (Test)")
            echiquier_.chargerDuelDeRois();
        else if (choix == "Fin de partie (Tours)")
            echiquier_.chargerFinDePartie();
    }
    catch (const modele::RoiEnTropException& ex)
    {
        QMessageBox::critical(this, "Erreur - Trop de rois", ex.what());
    }

    rafraichirAffichage();
    tourBlanc_ = true;
}

void FenetreJeu::rafraichirAffichage()
{
    reinitialiserCouleurs();

    for (int ligne = 0; ligne < TAILLE; ++ligne) {
        for (int col = 0; col < TAILLE; ++col) {
            const modele::Piece* piece = echiquier_.getPiece(modele::Position{ ligne, col });
            if (piece != nullptr) {
                cases_[ligne][col]->setText(QString::fromStdString(piece->getSymbole()));
                QString couleurTexte = piece->estBlanc() ? "white" : "black";
                cases_[ligne][col]->setStyleSheet(
                    "QPushButton { background-color: " + couleurCase(ligne, col) + "; "
                    "border: none; "
                    "color: " + couleurTexte + "; "
                    "font-size: 40px; }"
                );
            }
            else {
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
    modele::Position pos{ ligne, colonne };

    if (caseSelectionnee_ == nullptr) {
        const modele::Piece* piece = echiquier_.getPiece(pos);
        if (piece != nullptr && piece->estBlanc() == tourBlanc_) {
            caseSelectionnee_ = new modele::Position(pos);
            surlignerCasesValides(pos);
            // Garder la couleur du texte de la pièce sélectionnée
            QString couleurTexte = piece->estBlanc() ? "white" : "black";
            cases_[ligne][colonne]->setStyleSheet(
                "QPushButton { background-color: #aaf; "
                "border: none; "
                "color: " + couleurTexte + "; "
                "font-size: 40px; }"
            );
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
            afficherMessage("Mouvement invalide!");
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
            modele::Position dest{ ligne, col };
            if (piece->estMouvementValide(dest, echiquier_)) {
                const modele::Piece* cible = echiquier_.getPiece(dest);
                QString couleurTexte = (cible != nullptr && cible->estBlanc()) ? "white" : "black";
                QString couleurFond = ((ligne + col) % 2 == 0) ? "#c8e06e" : "#8fb03a";
                cases_[ligne][col]->setStyleSheet(
                    "QPushButton { background-color: " + couleurFond + "; "
                    "border: 2px solid #5a7a1a; "
                    "color: " + couleurTexte + "; "
                    "font-size: 40px; }"
                );
            }
        }
    }
}
void FenetreJeu::reinitialiserCouleurs()
{
    for (int ligne = 0; ligne < TAILLE; ++ligne) {
        for (int col = 0; col < TAILLE; ++col) {
            const modele::Piece* piece = echiquier_.getPiece(modele::Position{ ligne, col });
            QString couleurTexte = (piece != nullptr && piece->estBlanc()) ? "white" : "black";
            cases_[ligne][col]->setStyleSheet(
                "QPushButton { background-color: " + couleurCase(ligne, col) + "; "
                "border: none; "
                "color: " + couleurTexte + "; "
                "font-size: 40px; }"
            );
        }
    }
}

QString FenetreJeu::couleurCase(int ligne, int colonne) const
{
    return ((ligne + colonne) % 2 == 0) ? "#f0d9b5" : "#b58863";
}

}