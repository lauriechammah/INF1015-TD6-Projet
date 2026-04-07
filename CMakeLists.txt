cmake_minimum_required(VERSION 3.16)
project(TD6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Indiquez le chemin de votre installation Qt (adaptez si nécessaire)
set(CMAKE_PREFIX_PATH "L:/QT/6.11.0/msvc2022_64" CACHE PATH "Qt installation path")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(TD6
    main.cpp
    Piece.h
    Piece.cpp
    Roi.h
    Roi.cpp
    Tour.h
    Tour.cpp
    Cavalier.h
    Cavalier.cpp
    Echiquier.h
    Echiquier.cpp
    FenetreJeu.h
    FenetreJeu.cpp
    Position.h
)

target_link_libraries(TD6 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# Exécute windeployqt automatiquement après chaque build
add_custom_command(TARGET TD6 POST_BUILD
    COMMAND "${CMAKE_PREFIX_PATH}/bin/windeployqt.exe"
            "$<TARGET_FILE:TD6>"
    COMMENT "Deploiement des DLLs Qt..."
)