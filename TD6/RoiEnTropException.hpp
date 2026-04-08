/**
 * Nom :         Roi.hpp
 * Description : Exception lancee quand on tente de creer plus de 2 rois
 * Auteurs :     CHAMMAH (2451396) et SARKIS (2461138)
 * Date :        21 avril 2026
 **/

 #pragma once
#include <stdexcept>

namespace modele {

class RoiEnTropException : public std::logic_error {
public:
    using std::logic_error::logic_error;
};

}