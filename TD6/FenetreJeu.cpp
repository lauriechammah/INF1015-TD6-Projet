/**
 * Nom :         FenetreJeu.cpp
 * Description : Implementation de l'interface graphique Qt pour l'echiquier
 * Auteurs :     Laurie Chammah, Marie-Josee Sarkis
 * Date :        21 avril 2026
 **/

#include "FenetreJeu.hpp"
#include "Roi.hpp"
#include "Tour.hpp"
#include "Cavalier.hpp"

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

    for (int ligne = 0; ligne < TAILLE; ++ligne) {
        for (int col = 0; col < TAILLE; ++col) {
            auto* bouton = new QPushButton(this);
            bouton->setFixedSize(TAILLE_CASE, TAILLE_CASE);
            bouton->setStyleSheet("background-color: " + couleurCase(ligne, col) + ";");
            QFont font = bouton->font();
            font.setPointSize(24);
            bouton->setFont(font);

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
    QFont fontLabel = labelMessage_->font();
    fontLabel.setPointSize(14);
    labelMessage_->setFont(fontLabel);

    layoutPrincipal->addLayout(grille);
    layoutPrincipal->addWidget(labelMessage_);
    setCentralWidget(widgetCentral);
}

void FenetreJeu::initialiserPieces()
{
    echiquier_.ajouterPiece(std::make_unique<Tour>(Position{0, 0}, false));
    echiquier_.ajouterPiece(std::make_unique<Cavalier>(Position{0, 1}, false));
    echiquier_.ajouterPiece(std::make_unique<Roi>(Position{0, 4}, false));
    echiquier_.ajouterPiece(std::make_unique<Cavalier>(Position{0, 6}, false));
    echiquier_.ajouterPiece(std::make_unique<Tour>(Position{0, 7}, false));

    echiquier_.ajouterPiece(std::make_unique<Tour>(Position{7, 0}, true));
    echiquier_.ajouterPiece(std::make_unique<Cavalier>(Position{7, 1}, true));
    echiquier_.ajouterPiece(std::make_unique<Roi>(Position{7, 4}, true));
    echiquier_.ajouterPiece(std::make_unique<Cavalier>(Position{7, 6}, true));
    echiquier_.ajouterPiece(std::make_unique<Tour>(Position{7, 7}, true));
}

void FenetreJeu::rafraichirAffichage()
{
    reinitialiserCouleurs();

    for (int ligne = 0; ligne < TAILLE; ++ligne) {
        for (int col = 0; col < TAILLE; ++col) {
            const Piece* piece = echiquier_.getPiece(Position{ligne, col});
            cases_[ligne][col]->setText(piece ? QString::fromStdString(piece->getSymbole()) : "");
        }
    }
}

void FenetreJeu::caseCliquee(int ligne, int colonne)
{
    selectionnerCase(ligne, colonne);
}

void FenetreJeu::selectionnerCase(int ligne, int colonne)
{
    Position pos{ligne, colonne};

    if (caseSelectionnee_ == nullptr) {
        const Piece* piece = echiquier_.getPiece(pos);
        if (piece != nullptr && piece->estBlanc() == tourBlanc_) {
            caseSelectionnee_ = new Position(pos);
            surlignerCasesValides(pos);
            cases_[ligne][colonne]->setStyleSheet("background-color: #aaf;");
        }
    }
    else {
        Position source = *caseSelectionnee_;
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

void FenetreJeu::surlignerCasesValides(const Position& source)
{
    const Piece* piece = echiquier_.getPiece(source);
    if (piece == nullptr) return;

    for (int ligne = 0; ligne < TAILLE; ++ligne) {
        for (int col = 0; col < TAILLE; ++col) {
            Position dest{ligne, col};
            if (piece->estMouvementValide(dest, echiquier_))
                cases_[ligne][col]->setStyleSheet("background-color: #afa;");
        }
    }
}

void FenetreJeu::reinitialiserCouleurs()
{
    for (int ligne = 0; ligne < TAILLE; ++ligne)
        for (int col = 0; col < TAILLE; ++col)
            cases_[ligne][col]->setStyleSheet("background-color: " + couleurCase(ligne, col) + ";");
}

QString FenetreJeu::couleurCase(int ligne, int colonne) const
{
    return ((ligne + colonne) % 2 == 0) ? "#f0d9b5" : "#b58863";
}