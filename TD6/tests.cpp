/**
 * Nom :         tests.cpp
 * Description : Tests Google Test pour le modele de l'echiquier
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        6 mai 2026
 **/

#include "Echiquier.hpp"
#include "Roi.hpp"
#include "Tour.hpp"
#include "Cavalier.hpp"
#include "DeplacementTemp.hpp"

#include <gtest/gtest.h>

 // ============================================================
 // Roi
 // ============================================================

TEST(RoiTest, MouvementValide)
{
    modele::Echiquier e;
    e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{ 4, 4 }, true));

    EXPECT_TRUE(e.getPiece({ 4, 4 })->estMouvementValide({ 5, 5 }, e));
    EXPECT_TRUE(e.getPiece({ 4, 4 })->estMouvementValide({ 4, 5 }, e));
}

TEST(RoiTest, MouvementInvalide)
{
    modele::Echiquier e;
    e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{ 4, 4 }, true));

    EXPECT_FALSE(e.getPiece({ 4, 4 })->estMouvementValide({ 6, 4 }, e)); // trop loin
    EXPECT_FALSE(e.getPiece({ 4, 4 })->estMouvementValide({ 4, 4 }, e)); // sur place
}

TEST(RoiTest, ExceptionTroisRois)
{
    modele::Echiquier e;
    e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{ 0, 0 }, true));
    e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{ 7, 7 }, false));

    EXPECT_THROW(
        e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{ 4, 4 }, true)),
        modele::RoiEnTropException
    );
}

// ============================================================
// Tour
// ============================================================

TEST(TourTest, MouvementValide)
{
    modele::Echiquier e;
    e.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{ 0, 0 }, true));
    e.ajouterPiece(std::make_unique<modele::Cavalier>(modele::Position{ 0, 7 }, false));

    EXPECT_TRUE(e.getPiece({ 0, 0 })->estMouvementValide({ 0, 7 }, e)); // capture adverse
    EXPECT_TRUE(e.getPiece({ 0, 0 })->estMouvementValide({ 7, 0 }, e)); // deplacement vertical
}

TEST(TourTest, BloqueeParAllie)
{
    modele::Echiquier e;
    e.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{ 0, 0 }, true));
    e.ajouterPiece(std::make_unique<modele::Cavalier>(modele::Position{ 0, 5 }, true));
    e.ajouterPiece(std::make_unique<modele::Cavalier>(modele::Position{ 0, 7 }, false));

    EXPECT_FALSE(e.getPiece({ 0, 0 })->estMouvementValide({ 0, 5 }, e)); // ne peut pas capturer allie
    EXPECT_FALSE(e.getPiece({ 0, 0 })->estMouvementValide({ 0, 7 }, e)); // bloquee par allie
}

// ============================================================
// Cavalier
// ============================================================

TEST(CavalierTest, MouvementValide)
{
    modele::Echiquier e;
    e.ajouterPiece(std::make_unique<modele::Cavalier>(modele::Position{ 4, 4 }, true));

    EXPECT_TRUE(e.getPiece({ 4, 4 })->estMouvementValide({ 6, 5 }, e));
    EXPECT_TRUE(e.getPiece({ 4, 4 })->estMouvementValide({ 2, 3 }, e));
    EXPECT_TRUE(e.getPiece({ 4, 4 })->estMouvementValide({ 3, 6 }, e));
}

TEST(CavalierTest, MouvementInvalide)
{
    modele::Echiquier e;
    e.ajouterPiece(std::make_unique<modele::Cavalier>(modele::Position{ 4, 4 }, true));

    EXPECT_FALSE(e.getPiece({ 4, 4 })->estMouvementValide({ 4, 6 }, e)); // pas en L
    EXPECT_FALSE(e.getPiece({ 4, 4 })->estMouvementValide({ 6, 6 }, e)); // pas en L
}

// ============================================================
// Echiquier - Echec
// ============================================================

TEST(EchiquierTest, DetectionEchec)
{
    modele::Echiquier e;
    e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{ 0, 0 }, true));
    e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{ 7, 7 }, false));
    e.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{ 5, 7 }, true));

    EXPECT_FALSE(e.estEnEchec(true));
    EXPECT_TRUE(e.estEnEchec(false));
}

TEST(EchiquierTest, DeplacementInterduitSiEchec)
{
    modele::Echiquier e;
    e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{ 0, 0 }, true));
    e.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{ 1, 0 }, true));
    e.ajouterPiece(std::make_unique<modele::Tour>(modele::Position{ 7, 0 }, false));

    EXPECT_FALSE(e.deplacerPiece({ 1, 0 }, { 1, 5 })); // se mettrait en echec
}

// ============================================================
// Echiquier - Positions limites
// ============================================================

TEST(EchiquierTest, PositionInvalide)
{
    modele::Echiquier e;
    e.ajouterPiece(std::make_unique<modele::Roi>(modele::Position{ 0, 0 }, true));

    modele::Position posInvalide = { 8, -1 };
    EXPECT_FALSE(posInvalide.estValide());
    EXPECT_FALSE(e.getPiece({ 0, 0 })->estMouvementValide(posInvalide, e));
}

// ============================================================
// RAII - DeplacementTemp
// ============================================================

TEST(DeplacementTempTest, RetourAutomatiqueAnciennePosition)
{
    modele::Position posDepart = { 3, 3 };
    modele::Position posTemp = { 5, 5 };

    modele::Echiquier e;
    auto roi = std::make_unique<modele::Roi>(posDepart, true);
    modele::Roi* roiPtr = roi.get();
    e.ajouterPiece(std::move(roi));

    EXPECT_EQ(roiPtr->getPosition(), posDepart);

    {
        modele::DeplacementTemp depl(roiPtr, posTemp);
        EXPECT_EQ(roiPtr->getPosition(), posTemp);
    }

    EXPECT_EQ(roiPtr->getPosition(), posDepart);
}
